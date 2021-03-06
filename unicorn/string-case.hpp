// Internal to the library, do not include this directly

#pragma once

#include "unicorn/core.hpp"
#include "unicorn/character.hpp"
#include "unicorn/segment.hpp"
#include "unicorn/string-forward.hpp"
#include "unicorn/string-property.hpp"
#include "unicorn/string-size.hpp"
#include "unicorn/utf.hpp"
#include <algorithm>
#include <iterator>
#include <string>

namespace Unicorn {

    namespace UnicornDetail {

        template <typename C, typename F>
        const basic_string<C> casemap_helper(const basic_string<C>& src, F f) {
            basic_string<C> dst;
            char32_t buf[max_case_decomposition];
            auto out = utf_writer(dst);
            for (auto c: utf_range(src)) {
                auto n = f(c, buf);
                std::copy_n(buf, n, out);
            }
            return dst;
        }

        template <typename FwdIter>
        bool next_cased(FwdIter i, FwdIter e) {
            if (i == e)
                return false;
            for (++i; i != e; ++i)
                if (! char_is_case_ignorable(*i))
                    return char_is_cased(*i);
            return false;
        }

        struct LowerChar {
            static constexpr char32_t sigma = 0x3c3;
            static constexpr char32_t final_sigma = 0x3c2;
            bool last_cased = false;
            char32_t buf[max_case_decomposition];
            template <typename FwdIter, typename OutIter>
            void convert(FwdIter i, FwdIter e, OutIter to) {
                auto n = char_to_full_lowercase(*i, buf);
                if (buf[0] == sigma && last_cased && ! next_cased(i, e))
                    buf[0] = final_sigma;
                std::copy_n(buf, n, to);
                if (! char_is_case_ignorable(*i))
                    last_cased = char_is_cased(*i);
            }
        };

    }

    template <typename C>
    basic_string<C> str_uppercase(const basic_string<C>& str) {
        return UnicornDetail::casemap_helper(str, char_to_full_uppercase);
    }

    template <typename C>
    basic_string<C> str_lowercase(const basic_string<C>& str) {
        basic_string<C> dst;
        UnicornDetail::LowerChar lc;
        auto range = utf_range(str);
        auto out = utf_writer(dst);
        for (auto i = range.begin(), e = range.end(); i != e; ++i)
            lc.convert(i, e, out);
        return dst;
    }

    template <typename C>
    basic_string<C> str_titlecase(const basic_string<C>& str) {
        basic_string<C> dst;
        UnicornDetail::LowerChar lc;
        auto e = utf_end(str);
        auto out = utf_writer(dst);
        for (auto& w: word_range(str)) {
            bool initial = true;
            for (auto i = w.begin(); i != w.end(); ++i) {
                if (initial && char_is_cased(*i)) {
                    auto n = char_to_full_titlecase(*i, lc.buf);
                    std::copy_n(lc.buf, n, out);
                    lc.last_cased = true;
                    initial = false;
                } else {
                    lc.convert(i, e, out);
                }
            }
        }
        return dst;
    }

    template <typename C>
    basic_string<C> str_casefold(const basic_string<C>& str) {
        return UnicornDetail::casemap_helper(str, char_to_full_casefold);
    }

    template <typename C>
    void str_uppercase_in(basic_string<C>& str) {
        auto result = str_uppercase(str);
        str.swap(result);
    }

    template <typename C>
    void str_lowercase_in(basic_string<C>& str) {
        auto result = str_lowercase(str);
        str.swap(result);
    }

    template <typename C>
    void str_titlecase_in(basic_string<C>& str) {
        auto result = str_titlecase(str);
        str.swap(result);
    }

    template <typename C>
    void str_casefold_in(basic_string<C>& str) {
        auto result = str_casefold(str);
        str.swap(result);
    }

}
