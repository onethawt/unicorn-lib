#include "unicorn/io.hpp"
#include "unicorn/format.hpp"
#include "unicorn/mbcs.hpp"
#include "unicorn/string.hpp"
#include <algorithm>
#include <cerrno>
#include <system_error>

using namespace std::literals;
using namespace Unicorn::Literals;

namespace Unicorn {

    namespace {

        using SharedFile = shared_ptr<FILE>;

        void checked_fclose(FILE* f) { if (f) fclose(f); }
        template <typename C> u8string quote_file(const basic_string<C>& name) { return quote(to_utf8(name), true); }

        SharedFile shared_fopen(const NativeString& file, const NativeString& mode, bool check) {
            FILE* f =
                #if defined(PRI_TARGET_UNIX)
                    fopen
                #else
                    _wfopen
                #endif
                (file.data(), mode.data());
            int error = errno;
            if (check && f == nullptr)
                throw std::system_error(error, std::generic_category(), quote_file(file));
            return {f, checked_fclose};
        }

    }

    // Class FileReader

    struct FileReader::impl_type {
        u8string line8;
        string rdbuf;
        NativeString name;
        uint32_t flags;
        u8string enc;
        u8string eol;
        SharedFile handle;
        size_t lines;
        bool is_ready() noexcept {
            return handle.get() && ! ferror(handle.get()) && ! feof(handle.get());
        }
    };

    const u8string& FileReader::operator*() const noexcept {
        static const u8string dummy;
        return impl ? impl->line8 : dummy;
    }

    FileReader& FileReader::operator++() {
        do getline();
            while (impl && (impl->flags & io_notempty)
                && std::all_of(utf_begin(impl->line8), utf_end(impl->line8), char_is_line_break));
        return *this;
    }

    size_t FileReader::line() const noexcept {
        return impl ? impl->lines : size_t(0);
    }

    void FileReader::init(const NativeString& file, uint32_t flags, const u8string& enc, const u8string& eol) {
        static const NativeString dashfile = PRI_CSTR("-", NativeCharacter);
        if (bits_set(flags & (err_replace | err_throw)) > 1
                || bits_set(flags & (io_crlf | io_lf | io_striplf | io_striptws | io_stripws)) > 1)
            throw std::invalid_argument("Inconsistent file I/O flags");
        impl = make_shared<impl_type>();
        impl->name = file;
        impl->flags = flags;
        impl->enc = enc;
        impl->eol = eol;
        impl->lines = 0;
        if (enc.empty() || enc == "0")
            impl->enc = "utf-8";
        if ((flags & io_stdin) && (file.empty() || file == dashfile))
            impl->handle.reset(stdin, do_nothing);
        else
            impl->handle = shared_fopen(file, PRI_CSTR("rb", NativeCharacter), ! (flags & io_nofail));
        ++*this;
    }

    void FileReader::fixline() {
        if (impl->flags & io_bom) {
            if (str_first_char(impl->line8) == byte_order_mark)
                impl->line8.erase(0, utf_begin(impl->line8).count());
            impl->flags &= ~ io_bom;
        }
        if (impl->flags & io_lf)
            impl->line8 += '\n';
        else if (impl->flags & io_crlf)
            impl->line8 += "\r\n";
        else if (impl->flags & io_striptws)
            impl->line8 = str_trim_right(impl->line8);
        else if (impl->flags & io_stripws)
            impl->line8 = str_trim(impl->line8);
    }

    void FileReader::getline() {
        if (! impl)
            return;
        impl->line8.clear();
        size_t eolpos = npos, eolbytes = 0, eolsize = impl->eol.size();
        for (;;) {
            if (eolsize) {
                if (eolpos == npos)
                    eolpos = impl->rdbuf.find(impl->eol);
                if (eolpos != npos && (eolpos + eolsize < impl->rdbuf.size() || ! impl->is_ready()))
                    eolbytes = eolsize;
            } else {
                if (eolpos == npos)
                    eolpos = impl->rdbuf.find_first_of("\n\f\r");
                if (eolpos != npos) {
                    if (impl->rdbuf[eolpos] != '\r')
                        eolbytes = 1;
                    else if (impl->rdbuf.size() - eolpos >= 2 || ! impl->is_ready())
                        eolbytes = impl->rdbuf[eolpos + 1] == '\n' ? 2 : 1;
                }
            }
            if (eolbytes > 0 || ! impl->is_ready())
                break;
            getmore(256);
        }
        if (impl->rdbuf.empty()) {
            impl.reset();
            return;
        }
        string encoded(impl->rdbuf, 0, eolpos + eolbytes);
        impl->rdbuf.erase(0, eolpos + eolbytes);
        if (impl->flags & (io_lf | io_crlf | io_striplf | io_striptws | io_stripws))
            encoded.resize(eolpos);
        import_string(encoded, impl->line8, impl->enc, impl->flags & (err_replace | err_throw));
        fixline();
        ++impl->lines;
    }

    void FileReader::getmore(size_t n) {
        if (! impl || n == 0)
            return;
        auto offset = impl->rdbuf.size();
        impl->rdbuf.resize(offset + n);
        auto rc = fread(&impl->rdbuf[offset], 1, n, impl->handle.get());
        auto err = errno;
        impl->rdbuf.resize(offset + rc);
        if (ferror(impl->handle.get()))
            throw std::system_error(err, std::generic_category(), quote_file(impl->name));
    }

    // Class FileWriter

    struct FileWriter::impl_type {
        u8string wrbuf;
        NativeString name;
        uint32_t flags;
        u8string enc;
        SharedFile handle;
        shared_ptr<Mutex> mutex;
    };

    void FileWriter::flush() {
        if (! impl)
            throw std::system_error(std::make_error_code(std::errc::bad_file_descriptor));
        if (fflush(impl->handle.get()) == EOF) {
            int err = errno;
            throw std::system_error(err, std::generic_category(), quote_file(impl->name));
        }
    }

    void FileWriter::init(const NativeString& file, uint32_t flags, const u8string& enc) {
        static const NativeString dashfile{PRI_CHAR('-', NativeCharacter)};
        static Mutex stdout_mutex;
        static Mutex stderr_mutex;
        if (bits_set(flags & (err_replace | err_throw)) > 1
                || bits_set(flags & (io_autoline | io_writeline)) > 1
                || bits_set(flags & (io_crlf | io_lf)) > 1
                || bits_set(flags & (io_linebuf | io_unbuf)) > 1
                || bits_set(flags & (io_stderr | io_stdout)) > 1)
            throw std::invalid_argument("Inconsistent file I/O flags");
        impl = make_shared<impl_type>();
        impl->name = file;
        impl->flags = flags;
        impl->enc = enc;
        if (enc.empty() || enc == "0")
            impl->enc = "utf-8";
        if ((flags & io_stdout) && (file.empty() || file == dashfile))
            impl->handle.reset(stdout, do_nothing);
        else if ((flags & io_stderr) && (file.empty() || file == dashfile))
            impl->handle.reset(stderr, do_nothing);
        else
            impl->handle = shared_fopen(file,
                flags & io_append ? PRI_CSTR("ab", NativeCharacter) : PRI_CSTR("wb", NativeCharacter), true);
        if (flags & io_mutex) {
            if (impl->handle.get() == stdout)
                impl->mutex.reset(&stdout_mutex, do_nothing);
            else if (impl->handle.get() == stderr)
                impl->mutex.reset(&stderr_mutex, do_nothing);
            else
                impl->mutex = make_shared<Mutex>();
        }
    }

    void FileWriter::fixtext(u8string& str) const {
        if ((impl->flags & io_writeline) || ((impl->flags & io_autoline)
                && (str.empty() || ! char_is_line_break(str_last_char(str)))))
            str += '\n';
        if (impl->flags & (io_lf | io_crlf)) {
            u8string brk = (impl->flags & io_crlf) ? "\r\n"s : "\n"s;
            auto i = utf_begin(str);
            while (i.offset() < str.size()) {
                if (*i == '\r' && str[i.offset() + 1] == '\n')
                    i = str_insert_in(str, i, std::next(std::next(i)), brk).second;
                else if (char_is_line_break(*i))
                    i = str_insert_in(str, i, std::next(i), brk).second;
                else
                    ++i;
            }
        }
    }

    void FileWriter::write(u8string str) {
        if (! impl)
            throw std::system_error(std::make_error_code(std::errc::bad_file_descriptor));
        fixtext(str);
        if (impl->flags & io_linebuf) {
            str.insert(0, impl->wrbuf);
            impl->wrbuf.clear();
            auto b = utf_begin(str), e = utf_end(str), i = e;
            while (i != b) {
                --i;
                if (char_is_line_break(*i)) {
                    ++i;
                    break;
                }
            }
            if (i == b) {
                impl->wrbuf.swap(str);
            } else {
                impl->wrbuf = u_str(i, e);
                str.resize(i.offset());
            }
        }
        if (! str.empty()) {
            if (impl->flags & io_bom) {
                if (str_first_char(str) != byte_order_mark)
                    str.insert(0, utf8_bom);
                impl->flags &= ~ io_bom;
            }
            string encoded;
            export_string(str, encoded, impl->enc, impl->flags & (err_replace | err_throw));
            if (impl->mutex) {
                MutexLock lock(*impl->mutex);
                writembcs(encoded);
            } else {
                writembcs(encoded);
            }
        }
    }

    void FileWriter::writembcs(const string& str) {
        fwrite(str.data(), 1, str.size(), impl->handle.get());
        auto err = errno;
        if (ferror(impl->handle.get()))
            throw std::system_error(err, std::generic_category(), quote_file(impl->name));
        if (impl->flags & (io_linebuf | io_unbuf))
            flush();
    }

}
