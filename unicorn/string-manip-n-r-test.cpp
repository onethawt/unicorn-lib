#include "unicorn/string-manip.hpp"
#include "unicorn/core.hpp"
#include "unicorn/character.hpp"
#include "unicorn/utf.hpp"
#include "prion/unit-test.hpp"
#include <string>

using namespace std::literals;
using namespace Unicorn;

namespace {

    void check_pad_left() {

        u8string s8;
        u16string s16;
        u32string s32;

        TEST_EQUAL(str_pad_left(""s, 0), "");
        TEST_EQUAL(str_pad_left(""s, 1), " ");
        TEST_EQUAL(str_pad_left(""s, 2), "  ");
        TEST_EQUAL(str_pad_left(""s, 0, U'*'), "");
        TEST_EQUAL(str_pad_left(""s, 1, U'*'), "*");
        TEST_EQUAL(str_pad_left(""s, 2, U'*'), "**");
        TEST_EQUAL(str_pad_left(""s, 0, U'√'), "");
        TEST_EQUAL(str_pad_left(""s, 1, U'√'), "√");
        TEST_EQUAL(str_pad_left(""s, 2, U'√'), "√√");
        TEST_EQUAL(str_pad_left("Hello"s, 0), "Hello");
        TEST_EQUAL(str_pad_left("Hello"s, 5), "Hello");
        TEST_EQUAL(str_pad_left("Hello"s, 10), "     Hello");
        TEST_EQUAL(str_pad_left("Hello"s, 0, U'*'), "Hello");
        TEST_EQUAL(str_pad_left("Hello"s, 5, U'*'), "Hello");
        TEST_EQUAL(str_pad_left("Hello"s, 10, U'*'), "*****Hello");
        TEST_EQUAL(str_pad_left("Hello"s, 0, U'√'), "Hello");
        TEST_EQUAL(str_pad_left("Hello"s, 5, U'√'), "Hello");
        TEST_EQUAL(str_pad_left("Hello"s, 10, U'√'), "√√√√√Hello");
        TEST_EQUAL(str_pad_left("∀∃∀∃∀"s, 0), "∀∃∀∃∀");
        TEST_EQUAL(str_pad_left("∀∃∀∃∀"s, 5), "∀∃∀∃∀");
        TEST_EQUAL(str_pad_left("∀∃∀∃∀"s, 10), "     ∀∃∀∃∀");
        TEST_EQUAL(str_pad_left("∀∃∀∃∀"s, 0, U'*'), "∀∃∀∃∀");
        TEST_EQUAL(str_pad_left("∀∃∀∃∀"s, 5, U'*'), "∀∃∀∃∀");
        TEST_EQUAL(str_pad_left("∀∃∀∃∀"s, 10, U'*'), "*****∀∃∀∃∀");
        TEST_EQUAL(str_pad_left("∀∃∀∃∀"s, 0, U'√'), "∀∃∀∃∀");
        TEST_EQUAL(str_pad_left("∀∃∀∃∀"s, 5, U'√'), "∀∃∀∃∀");
        TEST_EQUAL(str_pad_left("∀∃∀∃∀"s, 10, U'√'), "√√√√√∀∃∀∃∀");

        TEST_EQUAL(str_pad_left(u""s, 0), u"");
        TEST_EQUAL(str_pad_left(u""s, 1), u" ");
        TEST_EQUAL(str_pad_left(u""s, 2), u"  ");
        TEST_EQUAL(str_pad_left(u""s, 0, U'*'), u"");
        TEST_EQUAL(str_pad_left(u""s, 1, U'*'), u"*");
        TEST_EQUAL(str_pad_left(u""s, 2, U'*'), u"**");
        TEST_EQUAL(str_pad_left(u""s, 0, U'√'), u"");
        TEST_EQUAL(str_pad_left(u""s, 1, U'√'), u"√");
        TEST_EQUAL(str_pad_left(u""s, 2, U'√'), u"√√");
        TEST_EQUAL(str_pad_left(u"Hello"s, 0), u"Hello");
        TEST_EQUAL(str_pad_left(u"Hello"s, 5), u"Hello");
        TEST_EQUAL(str_pad_left(u"Hello"s, 10), u"     Hello");
        TEST_EQUAL(str_pad_left(u"Hello"s, 0, U'*'), u"Hello");
        TEST_EQUAL(str_pad_left(u"Hello"s, 5, U'*'), u"Hello");
        TEST_EQUAL(str_pad_left(u"Hello"s, 10, U'*'), u"*****Hello");
        TEST_EQUAL(str_pad_left(u"Hello"s, 0, U'√'), u"Hello");
        TEST_EQUAL(str_pad_left(u"Hello"s, 5, U'√'), u"Hello");
        TEST_EQUAL(str_pad_left(u"Hello"s, 10, U'√'), u"√√√√√Hello");
        TEST_EQUAL(str_pad_left(u"∀∃∀∃∀"s, 0), u"∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(u"∀∃∀∃∀"s, 5), u"∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(u"∀∃∀∃∀"s, 10), u"     ∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(u"∀∃∀∃∀"s, 0, U'*'), u"∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(u"∀∃∀∃∀"s, 5, U'*'), u"∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(u"∀∃∀∃∀"s, 10, U'*'), u"*****∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(u"∀∃∀∃∀"s, 0, U'√'), u"∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(u"∀∃∀∃∀"s, 5, U'√'), u"∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(u"∀∃∀∃∀"s, 10, U'√'), u"√√√√√∀∃∀∃∀");

        TEST_EQUAL(str_pad_left(U""s, 0), U"");
        TEST_EQUAL(str_pad_left(U""s, 1), U" ");
        TEST_EQUAL(str_pad_left(U""s, 2), U"  ");
        TEST_EQUAL(str_pad_left(U""s, 0, U'*'), U"");
        TEST_EQUAL(str_pad_left(U""s, 1, U'*'), U"*");
        TEST_EQUAL(str_pad_left(U""s, 2, U'*'), U"**");
        TEST_EQUAL(str_pad_left(U""s, 0, U'√'), U"");
        TEST_EQUAL(str_pad_left(U""s, 1, U'√'), U"√");
        TEST_EQUAL(str_pad_left(U""s, 2, U'√'), U"√√");
        TEST_EQUAL(str_pad_left(U"Hello"s, 0), U"Hello");
        TEST_EQUAL(str_pad_left(U"Hello"s, 5), U"Hello");
        TEST_EQUAL(str_pad_left(U"Hello"s, 10), U"     Hello");
        TEST_EQUAL(str_pad_left(U"Hello"s, 0, U'*'), U"Hello");
        TEST_EQUAL(str_pad_left(U"Hello"s, 5, U'*'), U"Hello");
        TEST_EQUAL(str_pad_left(U"Hello"s, 10, U'*'), U"*****Hello");
        TEST_EQUAL(str_pad_left(U"Hello"s, 0, U'√'), U"Hello");
        TEST_EQUAL(str_pad_left(U"Hello"s, 5, U'√'), U"Hello");
        TEST_EQUAL(str_pad_left(U"Hello"s, 10, U'√'), U"√√√√√Hello");
        TEST_EQUAL(str_pad_left(U"∀∃∀∃∀"s, 0), U"∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(U"∀∃∀∃∀"s, 5), U"∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(U"∀∃∀∃∀"s, 10), U"     ∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(U"∀∃∀∃∀"s, 0, U'*'), U"∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(U"∀∃∀∃∀"s, 5, U'*'), U"∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(U"∀∃∀∃∀"s, 10, U'*'), U"*****∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(U"∀∃∀∃∀"s, 0, U'√'), U"∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(U"∀∃∀∃∀"s, 5, U'√'), U"∀∃∀∃∀");
        TEST_EQUAL(str_pad_left(U"∀∃∀∃∀"s, 10, U'√'), U"√√√√√∀∃∀∃∀");

        s8 = u8"";       TRY(str_pad_left_in(s8, 0));         TEST_EQUAL(s8, u8"");
        s8 = u8"";       TRY(str_pad_left_in(s8, 1));         TEST_EQUAL(s8, u8" ");
        s8 = u8"";       TRY(str_pad_left_in(s8, 2));         TEST_EQUAL(s8, u8"  ");
        s8 = u8"";       TRY(str_pad_left_in(s8, 0, U'*'));   TEST_EQUAL(s8, u8"");
        s8 = u8"";       TRY(str_pad_left_in(s8, 1, U'*'));   TEST_EQUAL(s8, u8"*");
        s8 = u8"";       TRY(str_pad_left_in(s8, 2, U'*'));   TEST_EQUAL(s8, u8"**");
        s8 = u8"";       TRY(str_pad_left_in(s8, 0, U'√'));   TEST_EQUAL(s8, u8"");
        s8 = u8"";       TRY(str_pad_left_in(s8, 1, U'√'));   TEST_EQUAL(s8, u8"√");
        s8 = u8"";       TRY(str_pad_left_in(s8, 2, U'√'));   TEST_EQUAL(s8, u8"√√");
        s8 = u8"Hello";  TRY(str_pad_left_in(s8, 0));         TEST_EQUAL(s8, u8"Hello");
        s8 = u8"Hello";  TRY(str_pad_left_in(s8, 5));         TEST_EQUAL(s8, u8"Hello");
        s8 = u8"Hello";  TRY(str_pad_left_in(s8, 10));        TEST_EQUAL(s8, u8"     Hello");
        s8 = u8"Hello";  TRY(str_pad_left_in(s8, 0, U'*'));   TEST_EQUAL(s8, u8"Hello");
        s8 = u8"Hello";  TRY(str_pad_left_in(s8, 5, U'*'));   TEST_EQUAL(s8, u8"Hello");
        s8 = u8"Hello";  TRY(str_pad_left_in(s8, 10, U'*'));  TEST_EQUAL(s8, u8"*****Hello");
        s8 = u8"Hello";  TRY(str_pad_left_in(s8, 0, U'√'));   TEST_EQUAL(s8, u8"Hello");
        s8 = u8"Hello";  TRY(str_pad_left_in(s8, 5, U'√'));   TEST_EQUAL(s8, u8"Hello");
        s8 = u8"Hello";  TRY(str_pad_left_in(s8, 10, U'√'));  TEST_EQUAL(s8, u8"√√√√√Hello");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_left_in(s8, 0));         TEST_EQUAL(s8, u8"∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_left_in(s8, 5));         TEST_EQUAL(s8, u8"∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_left_in(s8, 10));        TEST_EQUAL(s8, u8"     ∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_left_in(s8, 0, U'*'));   TEST_EQUAL(s8, u8"∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_left_in(s8, 5, U'*'));   TEST_EQUAL(s8, u8"∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_left_in(s8, 10, U'*'));  TEST_EQUAL(s8, u8"*****∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_left_in(s8, 0, U'√'));   TEST_EQUAL(s8, u8"∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_left_in(s8, 5, U'√'));   TEST_EQUAL(s8, u8"∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_left_in(s8, 10, U'√'));  TEST_EQUAL(s8, u8"√√√√√∀∃∀∃∀");

        s16 = u"";       TRY(str_pad_left_in(s16, 0));         TEST_EQUAL(s16, u"");
        s16 = u"";       TRY(str_pad_left_in(s16, 1));         TEST_EQUAL(s16, u" ");
        s16 = u"";       TRY(str_pad_left_in(s16, 2));         TEST_EQUAL(s16, u"  ");
        s16 = u"";       TRY(str_pad_left_in(s16, 0, U'*'));   TEST_EQUAL(s16, u"");
        s16 = u"";       TRY(str_pad_left_in(s16, 1, U'*'));   TEST_EQUAL(s16, u"*");
        s16 = u"";       TRY(str_pad_left_in(s16, 2, U'*'));   TEST_EQUAL(s16, u"**");
        s16 = u"";       TRY(str_pad_left_in(s16, 0, U'√'));   TEST_EQUAL(s16, u"");
        s16 = u"";       TRY(str_pad_left_in(s16, 1, U'√'));   TEST_EQUAL(s16, u"√");
        s16 = u"";       TRY(str_pad_left_in(s16, 2, U'√'));   TEST_EQUAL(s16, u"√√");
        s16 = u"Hello";  TRY(str_pad_left_in(s16, 0));         TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_pad_left_in(s16, 5));         TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_pad_left_in(s16, 10));        TEST_EQUAL(s16, u"     Hello");
        s16 = u"Hello";  TRY(str_pad_left_in(s16, 0, U'*'));   TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_pad_left_in(s16, 5, U'*'));   TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_pad_left_in(s16, 10, U'*'));  TEST_EQUAL(s16, u"*****Hello");
        s16 = u"Hello";  TRY(str_pad_left_in(s16, 0, U'√'));   TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_pad_left_in(s16, 5, U'√'));   TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_pad_left_in(s16, 10, U'√'));  TEST_EQUAL(s16, u"√√√√√Hello");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_left_in(s16, 0));         TEST_EQUAL(s16, u"∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_left_in(s16, 5));         TEST_EQUAL(s16, u"∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_left_in(s16, 10));        TEST_EQUAL(s16, u"     ∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_left_in(s16, 0, U'*'));   TEST_EQUAL(s16, u"∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_left_in(s16, 5, U'*'));   TEST_EQUAL(s16, u"∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_left_in(s16, 10, U'*'));  TEST_EQUAL(s16, u"*****∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_left_in(s16, 0, U'√'));   TEST_EQUAL(s16, u"∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_left_in(s16, 5, U'√'));   TEST_EQUAL(s16, u"∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_left_in(s16, 10, U'√'));  TEST_EQUAL(s16, u"√√√√√∀∃∀∃∀");

        s32 = U"";       TRY(str_pad_left_in(s32, 0));         TEST_EQUAL(s32, U"");
        s32 = U"";       TRY(str_pad_left_in(s32, 1));         TEST_EQUAL(s32, U" ");
        s32 = U"";       TRY(str_pad_left_in(s32, 2));         TEST_EQUAL(s32, U"  ");
        s32 = U"";       TRY(str_pad_left_in(s32, 0, U'*'));   TEST_EQUAL(s32, U"");
        s32 = U"";       TRY(str_pad_left_in(s32, 1, U'*'));   TEST_EQUAL(s32, U"*");
        s32 = U"";       TRY(str_pad_left_in(s32, 2, U'*'));   TEST_EQUAL(s32, U"**");
        s32 = U"";       TRY(str_pad_left_in(s32, 0, U'√'));   TEST_EQUAL(s32, U"");
        s32 = U"";       TRY(str_pad_left_in(s32, 1, U'√'));   TEST_EQUAL(s32, U"√");
        s32 = U"";       TRY(str_pad_left_in(s32, 2, U'√'));   TEST_EQUAL(s32, U"√√");
        s32 = U"Hello";  TRY(str_pad_left_in(s32, 0));         TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_pad_left_in(s32, 5));         TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_pad_left_in(s32, 10));        TEST_EQUAL(s32, U"     Hello");
        s32 = U"Hello";  TRY(str_pad_left_in(s32, 0, U'*'));   TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_pad_left_in(s32, 5, U'*'));   TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_pad_left_in(s32, 10, U'*'));  TEST_EQUAL(s32, U"*****Hello");
        s32 = U"Hello";  TRY(str_pad_left_in(s32, 0, U'√'));   TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_pad_left_in(s32, 5, U'√'));   TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_pad_left_in(s32, 10, U'√'));  TEST_EQUAL(s32, U"√√√√√Hello");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_left_in(s32, 0));         TEST_EQUAL(s32, U"∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_left_in(s32, 5));         TEST_EQUAL(s32, U"∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_left_in(s32, 10));        TEST_EQUAL(s32, U"     ∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_left_in(s32, 0, U'*'));   TEST_EQUAL(s32, U"∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_left_in(s32, 5, U'*'));   TEST_EQUAL(s32, U"∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_left_in(s32, 10, U'*'));  TEST_EQUAL(s32, U"*****∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_left_in(s32, 0, U'√'));   TEST_EQUAL(s32, U"∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_left_in(s32, 5, U'√'));   TEST_EQUAL(s32, U"∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_left_in(s32, 10, U'√'));  TEST_EQUAL(s32, U"√√√√√∀∃∀∃∀");

    }

    void check_pad_right() {

        u8string s8;
        u16string s16;
        u32string s32;

        TEST_EQUAL(str_pad_right(""s, 0), "");
        TEST_EQUAL(str_pad_right(""s, 1), " ");
        TEST_EQUAL(str_pad_right(""s, 2), "  ");
        TEST_EQUAL(str_pad_right(""s, 0, U'*'), "");
        TEST_EQUAL(str_pad_right(""s, 1, U'*'), "*");
        TEST_EQUAL(str_pad_right(""s, 2, U'*'), "**");
        TEST_EQUAL(str_pad_right(""s, 0, U'√'), "");
        TEST_EQUAL(str_pad_right(""s, 1, U'√'), "√");
        TEST_EQUAL(str_pad_right(""s, 2, U'√'), "√√");
        TEST_EQUAL(str_pad_right("Hello"s, 0), "Hello");
        TEST_EQUAL(str_pad_right("Hello"s, 5), "Hello");
        TEST_EQUAL(str_pad_right("Hello"s, 10), "Hello     ");
        TEST_EQUAL(str_pad_right("Hello"s, 0, U'*'), "Hello");
        TEST_EQUAL(str_pad_right("Hello"s, 5, U'*'), "Hello");
        TEST_EQUAL(str_pad_right("Hello"s, 10, U'*'), "Hello*****");
        TEST_EQUAL(str_pad_right("Hello"s, 0, U'√'), "Hello");
        TEST_EQUAL(str_pad_right("Hello"s, 5, U'√'), "Hello");
        TEST_EQUAL(str_pad_right("Hello"s, 10, U'√'), "Hello√√√√√");
        TEST_EQUAL(str_pad_right("∀∃∀∃∀"s, 0), "∀∃∀∃∀");
        TEST_EQUAL(str_pad_right("∀∃∀∃∀"s, 5), "∀∃∀∃∀");
        TEST_EQUAL(str_pad_right("∀∃∀∃∀"s, 10), "∀∃∀∃∀     ");
        TEST_EQUAL(str_pad_right("∀∃∀∃∀"s, 0, U'*'), "∀∃∀∃∀");
        TEST_EQUAL(str_pad_right("∀∃∀∃∀"s, 5, U'*'), "∀∃∀∃∀");
        TEST_EQUAL(str_pad_right("∀∃∀∃∀"s, 10, U'*'), "∀∃∀∃∀*****");
        TEST_EQUAL(str_pad_right("∀∃∀∃∀"s, 0, U'√'), "∀∃∀∃∀");
        TEST_EQUAL(str_pad_right("∀∃∀∃∀"s, 5, U'√'), "∀∃∀∃∀");
        TEST_EQUAL(str_pad_right("∀∃∀∃∀"s, 10, U'√'), "∀∃∀∃∀√√√√√");

        TEST_EQUAL(str_pad_right(u""s, 0), u"");
        TEST_EQUAL(str_pad_right(u""s, 1), u" ");
        TEST_EQUAL(str_pad_right(u""s, 2), u"  ");
        TEST_EQUAL(str_pad_right(u""s, 0, U'*'), u"");
        TEST_EQUAL(str_pad_right(u""s, 1, U'*'), u"*");
        TEST_EQUAL(str_pad_right(u""s, 2, U'*'), u"**");
        TEST_EQUAL(str_pad_right(u""s, 0, U'√'), u"");
        TEST_EQUAL(str_pad_right(u""s, 1, U'√'), u"√");
        TEST_EQUAL(str_pad_right(u""s, 2, U'√'), u"√√");
        TEST_EQUAL(str_pad_right(u"Hello"s, 0), u"Hello");
        TEST_EQUAL(str_pad_right(u"Hello"s, 5), u"Hello");
        TEST_EQUAL(str_pad_right(u"Hello"s, 10), u"Hello     ");
        TEST_EQUAL(str_pad_right(u"Hello"s, 0, U'*'), u"Hello");
        TEST_EQUAL(str_pad_right(u"Hello"s, 5, U'*'), u"Hello");
        TEST_EQUAL(str_pad_right(u"Hello"s, 10, U'*'), u"Hello*****");
        TEST_EQUAL(str_pad_right(u"Hello"s, 0, U'√'), u"Hello");
        TEST_EQUAL(str_pad_right(u"Hello"s, 5, U'√'), u"Hello");
        TEST_EQUAL(str_pad_right(u"Hello"s, 10, U'√'), u"Hello√√√√√");
        TEST_EQUAL(str_pad_right(u"∀∃∀∃∀"s, 0), u"∀∃∀∃∀");
        TEST_EQUAL(str_pad_right(u"∀∃∀∃∀"s, 5), u"∀∃∀∃∀");
        TEST_EQUAL(str_pad_right(u"∀∃∀∃∀"s, 10), u"∀∃∀∃∀     ");
        TEST_EQUAL(str_pad_right(u"∀∃∀∃∀"s, 0, U'*'), u"∀∃∀∃∀");
        TEST_EQUAL(str_pad_right(u"∀∃∀∃∀"s, 5, U'*'), u"∀∃∀∃∀");
        TEST_EQUAL(str_pad_right(u"∀∃∀∃∀"s, 10, U'*'), u"∀∃∀∃∀*****");
        TEST_EQUAL(str_pad_right(u"∀∃∀∃∀"s, 0, U'√'), u"∀∃∀∃∀");
        TEST_EQUAL(str_pad_right(u"∀∃∀∃∀"s, 5, U'√'), u"∀∃∀∃∀");
        TEST_EQUAL(str_pad_right(u"∀∃∀∃∀"s, 10, U'√'), u"∀∃∀∃∀√√√√√");

        TEST_EQUAL(str_pad_right(U""s, 0), U"");
        TEST_EQUAL(str_pad_right(U""s, 1), U" ");
        TEST_EQUAL(str_pad_right(U""s, 2), U"  ");
        TEST_EQUAL(str_pad_right(U""s, 0, U'*'), U"");
        TEST_EQUAL(str_pad_right(U""s, 1, U'*'), U"*");
        TEST_EQUAL(str_pad_right(U""s, 2, U'*'), U"**");
        TEST_EQUAL(str_pad_right(U""s, 0, U'√'), U"");
        TEST_EQUAL(str_pad_right(U""s, 1, U'√'), U"√");
        TEST_EQUAL(str_pad_right(U""s, 2, U'√'), U"√√");
        TEST_EQUAL(str_pad_right(U"Hello"s, 0), U"Hello");
        TEST_EQUAL(str_pad_right(U"Hello"s, 5), U"Hello");
        TEST_EQUAL(str_pad_right(U"Hello"s, 10), U"Hello     ");
        TEST_EQUAL(str_pad_right(U"Hello"s, 0, U'*'), U"Hello");
        TEST_EQUAL(str_pad_right(U"Hello"s, 5, U'*'), U"Hello");
        TEST_EQUAL(str_pad_right(U"Hello"s, 10, U'*'), U"Hello*****");
        TEST_EQUAL(str_pad_right(U"Hello"s, 0, U'√'), U"Hello");
        TEST_EQUAL(str_pad_right(U"Hello"s, 5, U'√'), U"Hello");
        TEST_EQUAL(str_pad_right(U"Hello"s, 10, U'√'), U"Hello√√√√√");
        TEST_EQUAL(str_pad_right(U"∀∃∀∃∀"s, 0), U"∀∃∀∃∀");
        TEST_EQUAL(str_pad_right(U"∀∃∀∃∀"s, 5), U"∀∃∀∃∀");
        TEST_EQUAL(str_pad_right(U"∀∃∀∃∀"s, 10), U"∀∃∀∃∀     ");
        TEST_EQUAL(str_pad_right(U"∀∃∀∃∀"s, 0, U'*'), U"∀∃∀∃∀");
        TEST_EQUAL(str_pad_right(U"∀∃∀∃∀"s, 5, U'*'), U"∀∃∀∃∀");
        TEST_EQUAL(str_pad_right(U"∀∃∀∃∀"s, 10, U'*'), U"∀∃∀∃∀*****");
        TEST_EQUAL(str_pad_right(U"∀∃∀∃∀"s, 0, U'√'), U"∀∃∀∃∀");
        TEST_EQUAL(str_pad_right(U"∀∃∀∃∀"s, 5, U'√'), U"∀∃∀∃∀");
        TEST_EQUAL(str_pad_right(U"∀∃∀∃∀"s, 10, U'√'), U"∀∃∀∃∀√√√√√");

        s8 = u8"";       TRY(str_pad_right_in(s8, 0));         TEST_EQUAL(s8, u8"");
        s8 = u8"";       TRY(str_pad_right_in(s8, 1));         TEST_EQUAL(s8, u8" ");
        s8 = u8"";       TRY(str_pad_right_in(s8, 2));         TEST_EQUAL(s8, u8"  ");
        s8 = u8"";       TRY(str_pad_right_in(s8, 0, U'*'));   TEST_EQUAL(s8, u8"");
        s8 = u8"";       TRY(str_pad_right_in(s8, 1, U'*'));   TEST_EQUAL(s8, u8"*");
        s8 = u8"";       TRY(str_pad_right_in(s8, 2, U'*'));   TEST_EQUAL(s8, u8"**");
        s8 = u8"";       TRY(str_pad_right_in(s8, 0, U'√'));   TEST_EQUAL(s8, u8"");
        s8 = u8"";       TRY(str_pad_right_in(s8, 1, U'√'));   TEST_EQUAL(s8, u8"√");
        s8 = u8"";       TRY(str_pad_right_in(s8, 2, U'√'));   TEST_EQUAL(s8, u8"√√");
        s8 = u8"Hello";  TRY(str_pad_right_in(s8, 0));         TEST_EQUAL(s8, u8"Hello");
        s8 = u8"Hello";  TRY(str_pad_right_in(s8, 5));         TEST_EQUAL(s8, u8"Hello");
        s8 = u8"Hello";  TRY(str_pad_right_in(s8, 10));        TEST_EQUAL(s8, u8"Hello     ");
        s8 = u8"Hello";  TRY(str_pad_right_in(s8, 0, U'*'));   TEST_EQUAL(s8, u8"Hello");
        s8 = u8"Hello";  TRY(str_pad_right_in(s8, 5, U'*'));   TEST_EQUAL(s8, u8"Hello");
        s8 = u8"Hello";  TRY(str_pad_right_in(s8, 10, U'*'));  TEST_EQUAL(s8, u8"Hello*****");
        s8 = u8"Hello";  TRY(str_pad_right_in(s8, 0, U'√'));   TEST_EQUAL(s8, u8"Hello");
        s8 = u8"Hello";  TRY(str_pad_right_in(s8, 5, U'√'));   TEST_EQUAL(s8, u8"Hello");
        s8 = u8"Hello";  TRY(str_pad_right_in(s8, 10, U'√'));  TEST_EQUAL(s8, u8"Hello√√√√√");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_right_in(s8, 0));         TEST_EQUAL(s8, u8"∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_right_in(s8, 5));         TEST_EQUAL(s8, u8"∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_right_in(s8, 10));        TEST_EQUAL(s8, u8"∀∃∀∃∀     ");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_right_in(s8, 0, U'*'));   TEST_EQUAL(s8, u8"∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_right_in(s8, 5, U'*'));   TEST_EQUAL(s8, u8"∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_right_in(s8, 10, U'*'));  TEST_EQUAL(s8, u8"∀∃∀∃∀*****");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_right_in(s8, 0, U'√'));   TEST_EQUAL(s8, u8"∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_right_in(s8, 5, U'√'));   TEST_EQUAL(s8, u8"∀∃∀∃∀");
        s8 = u8"∀∃∀∃∀";  TRY(str_pad_right_in(s8, 10, U'√'));  TEST_EQUAL(s8, u8"∀∃∀∃∀√√√√√");

        s16 = u"";       TRY(str_pad_right_in(s16, 0));         TEST_EQUAL(s16, u"");
        s16 = u"";       TRY(str_pad_right_in(s16, 1));         TEST_EQUAL(s16, u" ");
        s16 = u"";       TRY(str_pad_right_in(s16, 2));         TEST_EQUAL(s16, u"  ");
        s16 = u"";       TRY(str_pad_right_in(s16, 0, U'*'));   TEST_EQUAL(s16, u"");
        s16 = u"";       TRY(str_pad_right_in(s16, 1, U'*'));   TEST_EQUAL(s16, u"*");
        s16 = u"";       TRY(str_pad_right_in(s16, 2, U'*'));   TEST_EQUAL(s16, u"**");
        s16 = u"";       TRY(str_pad_right_in(s16, 0, U'√'));   TEST_EQUAL(s16, u"");
        s16 = u"";       TRY(str_pad_right_in(s16, 1, U'√'));   TEST_EQUAL(s16, u"√");
        s16 = u"";       TRY(str_pad_right_in(s16, 2, U'√'));   TEST_EQUAL(s16, u"√√");
        s16 = u"Hello";  TRY(str_pad_right_in(s16, 0));         TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_pad_right_in(s16, 5));         TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_pad_right_in(s16, 10));        TEST_EQUAL(s16, u"Hello     ");
        s16 = u"Hello";  TRY(str_pad_right_in(s16, 0, U'*'));   TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_pad_right_in(s16, 5, U'*'));   TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_pad_right_in(s16, 10, U'*'));  TEST_EQUAL(s16, u"Hello*****");
        s16 = u"Hello";  TRY(str_pad_right_in(s16, 0, U'√'));   TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_pad_right_in(s16, 5, U'√'));   TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_pad_right_in(s16, 10, U'√'));  TEST_EQUAL(s16, u"Hello√√√√√");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_right_in(s16, 0));         TEST_EQUAL(s16, u"∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_right_in(s16, 5));         TEST_EQUAL(s16, u"∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_right_in(s16, 10));        TEST_EQUAL(s16, u"∀∃∀∃∀     ");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_right_in(s16, 0, U'*'));   TEST_EQUAL(s16, u"∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_right_in(s16, 5, U'*'));   TEST_EQUAL(s16, u"∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_right_in(s16, 10, U'*'));  TEST_EQUAL(s16, u"∀∃∀∃∀*****");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_right_in(s16, 0, U'√'));   TEST_EQUAL(s16, u"∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_right_in(s16, 5, U'√'));   TEST_EQUAL(s16, u"∀∃∀∃∀");
        s16 = u"∀∃∀∃∀";  TRY(str_pad_right_in(s16, 10, U'√'));  TEST_EQUAL(s16, u"∀∃∀∃∀√√√√√");

        s32 = U"";       TRY(str_pad_right_in(s32, 0));         TEST_EQUAL(s32, U"");
        s32 = U"";       TRY(str_pad_right_in(s32, 1));         TEST_EQUAL(s32, U" ");
        s32 = U"";       TRY(str_pad_right_in(s32, 2));         TEST_EQUAL(s32, U"  ");
        s32 = U"";       TRY(str_pad_right_in(s32, 0, U'*'));   TEST_EQUAL(s32, U"");
        s32 = U"";       TRY(str_pad_right_in(s32, 1, U'*'));   TEST_EQUAL(s32, U"*");
        s32 = U"";       TRY(str_pad_right_in(s32, 2, U'*'));   TEST_EQUAL(s32, U"**");
        s32 = U"";       TRY(str_pad_right_in(s32, 0, U'√'));   TEST_EQUAL(s32, U"");
        s32 = U"";       TRY(str_pad_right_in(s32, 1, U'√'));   TEST_EQUAL(s32, U"√");
        s32 = U"";       TRY(str_pad_right_in(s32, 2, U'√'));   TEST_EQUAL(s32, U"√√");
        s32 = U"Hello";  TRY(str_pad_right_in(s32, 0));         TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_pad_right_in(s32, 5));         TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_pad_right_in(s32, 10));        TEST_EQUAL(s32, U"Hello     ");
        s32 = U"Hello";  TRY(str_pad_right_in(s32, 0, U'*'));   TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_pad_right_in(s32, 5, U'*'));   TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_pad_right_in(s32, 10, U'*'));  TEST_EQUAL(s32, U"Hello*****");
        s32 = U"Hello";  TRY(str_pad_right_in(s32, 0, U'√'));   TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_pad_right_in(s32, 5, U'√'));   TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_pad_right_in(s32, 10, U'√'));  TEST_EQUAL(s32, U"Hello√√√√√");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_right_in(s32, 0));         TEST_EQUAL(s32, U"∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_right_in(s32, 5));         TEST_EQUAL(s32, U"∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_right_in(s32, 10));        TEST_EQUAL(s32, U"∀∃∀∃∀     ");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_right_in(s32, 0, U'*'));   TEST_EQUAL(s32, U"∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_right_in(s32, 5, U'*'));   TEST_EQUAL(s32, U"∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_right_in(s32, 10, U'*'));  TEST_EQUAL(s32, U"∀∃∀∃∀*****");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_right_in(s32, 0, U'√'));   TEST_EQUAL(s32, U"∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_right_in(s32, 5, U'√'));   TEST_EQUAL(s32, U"∀∃∀∃∀");
        s32 = U"∀∃∀∃∀";  TRY(str_pad_right_in(s32, 10, U'√'));  TEST_EQUAL(s32, U"∀∃∀∃∀√√√√√");

    }

    void check_partition() {

        u8string s8, t8;
        u16string s16, t16;
        u32string s32, t32;

        TEST(! str_partition(""s, s8, t8));                     TEST_EQUAL(s8, "");       TEST_EQUAL(t8, "");
        TEST(! str_partition("Hello"s, s8, t8));                TEST_EQUAL(s8, "Hello");  TEST_EQUAL(t8, "");
        TEST(str_partition("Hello world"s, s8, t8));            TEST_EQUAL(s8, "Hello");  TEST_EQUAL(t8, "world");
        TEST(str_partition("Hello brave new world"s, s8, t8));  TEST_EQUAL(s8, "Hello");  TEST_EQUAL(t8, "brave new world");
        TEST(str_partition("€uro ∈lement"s, s8, t8));           TEST_EQUAL(s8, "€uro");   TEST_EQUAL(t8, "∈lement");

        TEST(! str_partition(u""s, s16, t16));                     TEST_EQUAL(s16, u"");       TEST_EQUAL(t16, u"");
        TEST(! str_partition(u"Hello"s, s16, t16));                TEST_EQUAL(s16, u"Hello");  TEST_EQUAL(t16, u"");
        TEST(str_partition(u"Hello world"s, s16, t16));            TEST_EQUAL(s16, u"Hello");  TEST_EQUAL(t16, u"world");
        TEST(str_partition(u"Hello brave new world"s, s16, t16));  TEST_EQUAL(s16, u"Hello");  TEST_EQUAL(t16, u"brave new world");
        TEST(str_partition(u"€uro ∈lement"s, s16, t16));           TEST_EQUAL(s16, u"€uro");   TEST_EQUAL(t16, u"∈lement");

        TEST(! str_partition(U""s, s32, t32));                     TEST_EQUAL(s32, U"");       TEST_EQUAL(t32, U"");
        TEST(! str_partition(U"Hello"s, s32, t32));                TEST_EQUAL(s32, U"Hello");  TEST_EQUAL(t32, U"");
        TEST(str_partition(U"Hello world"s, s32, t32));            TEST_EQUAL(s32, U"Hello");  TEST_EQUAL(t32, U"world");
        TEST(str_partition(U"Hello brave new world"s, s32, t32));  TEST_EQUAL(s32, U"Hello");  TEST_EQUAL(t32, U"brave new world");
        TEST(str_partition(U"€uro ∈lement"s, s32, t32));           TEST_EQUAL(s32, U"€uro");   TEST_EQUAL(t32, U"∈lement");

        TEST(! str_partition_at(""s, s8, t8, " "));                             TEST_EQUAL(s8, "");              TEST_EQUAL(t8, "");
        TEST(! str_partition_at("Hello"s, s8, t8, " "));                        TEST_EQUAL(s8, "Hello");         TEST_EQUAL(t8, "");
        TEST(str_partition_at("Hello world"s, s8, t8, " "));                    TEST_EQUAL(s8, "Hello");         TEST_EQUAL(t8, "world");
        TEST(str_partition_at("Hello brave new world"s, s8, t8, " "));          TEST_EQUAL(s8, "Hello");         TEST_EQUAL(t8, "brave new world");
        TEST(! str_partition_at(""s, s8, t8, "<>"));                            TEST_EQUAL(s8, "");              TEST_EQUAL(t8, "");
        TEST(! str_partition_at("Hello"s, s8, t8, "<>"));                       TEST_EQUAL(s8, "Hello");         TEST_EQUAL(t8, "");
        TEST(! str_partition_at("Hello world"s, s8, t8, "<>"));                 TEST_EQUAL(s8, "Hello world");   TEST_EQUAL(t8, "");
        TEST(! str_partition_at("Hello"s, s8, t8, "<>"));                       TEST_EQUAL(s8, "Hello");         TEST_EQUAL(t8, "");
        TEST(str_partition_at("Hello<>world"s, s8, t8, "<>"));                  TEST_EQUAL(s8, "Hello");         TEST_EQUAL(t8, "world");
        TEST(str_partition_at("Hello<>brave<>new<>world"s, s8, t8, "<>"));      TEST_EQUAL(s8, "Hello");         TEST_EQUAL(t8, "brave<>new<>world");
        TEST(str_partition_at("<>Hello<>world<>"s, s8, t8, "<>"));              TEST_EQUAL(s8, "");              TEST_EQUAL(t8, "Hello<>world<>");
        TEST(str_partition_at("<>Hello<>brave<>new<>world<>"s, s8, t8, "<>"));  TEST_EQUAL(s8, "");              TEST_EQUAL(t8, "Hello<>brave<>new<>world<>");
        TEST(! str_partition_at("€uro ∈lement"s, s8, t8, "∇√"));                TEST_EQUAL(s8, "€uro ∈lement");  TEST_EQUAL(t8, "");
        TEST(str_partition_at("€uro∇√∈lement"s, s8, t8, "∇√"));                 TEST_EQUAL(s8, "€uro");          TEST_EQUAL(t8, "∈lement");
        TEST(str_partition_at("∇√€uro∇√∈lement∇√"s, s8, t8, "∇√"));             TEST_EQUAL(s8, "");              TEST_EQUAL(t8, "€uro∇√∈lement∇√");

        TEST(! str_partition_at(u""s, s16, t16, u" "));                             TEST_EQUAL(s16, u"");              TEST_EQUAL(t16, u"");
        TEST(! str_partition_at(u"Hello"s, s16, t16, u" "));                        TEST_EQUAL(s16, u"Hello");         TEST_EQUAL(t16, u"");
        TEST(str_partition_at(u"Hello world"s, s16, t16, u" "));                    TEST_EQUAL(s16, u"Hello");         TEST_EQUAL(t16, u"world");
        TEST(str_partition_at(u"Hello brave new world"s, s16, t16, u" "));          TEST_EQUAL(s16, u"Hello");         TEST_EQUAL(t16, u"brave new world");
        TEST(! str_partition_at(u""s, s16, t16, u"<>"));                            TEST_EQUAL(s16, u"");              TEST_EQUAL(t16, u"");
        TEST(! str_partition_at(u"Hello"s, s16, t16, u"<>"));                       TEST_EQUAL(s16, u"Hello");         TEST_EQUAL(t16, u"");
        TEST(! str_partition_at(u"Hello world"s, s16, t16, u"<>"));                 TEST_EQUAL(s16, u"Hello world");   TEST_EQUAL(t16, u"");
        TEST(! str_partition_at(u"Hello"s, s16, t16, u"<>"));                       TEST_EQUAL(s16, u"Hello");         TEST_EQUAL(t16, u"");
        TEST(str_partition_at(u"Hello<>world"s, s16, t16, u"<>"));                  TEST_EQUAL(s16, u"Hello");         TEST_EQUAL(t16, u"world");
        TEST(str_partition_at(u"Hello<>brave<>new<>world"s, s16, t16, u"<>"));      TEST_EQUAL(s16, u"Hello");         TEST_EQUAL(t16, u"brave<>new<>world");
        TEST(str_partition_at(u"<>Hello<>world<>"s, s16, t16, u"<>"));              TEST_EQUAL(s16, u"");              TEST_EQUAL(t16, u"Hello<>world<>");
        TEST(str_partition_at(u"<>Hello<>brave<>new<>world<>"s, s16, t16, u"<>"));  TEST_EQUAL(s16, u"");              TEST_EQUAL(t16, u"Hello<>brave<>new<>world<>");
        TEST(! str_partition_at(u"€uro ∈lement"s, s16, t16, u"∇√"));                TEST_EQUAL(s16, u"€uro ∈lement");  TEST_EQUAL(t16, u"");
        TEST(str_partition_at(u"€uro∇√∈lement"s, s16, t16, u"∇√"));                 TEST_EQUAL(s16, u"€uro");          TEST_EQUAL(t16, u"∈lement");
        TEST(str_partition_at(u"∇√€uro∇√∈lement∇√"s, s16, t16, u"∇√"));             TEST_EQUAL(s16, u"");              TEST_EQUAL(t16, u"€uro∇√∈lement∇√");

        TEST(! str_partition_at(U""s, s32, t32, U" "));                             TEST_EQUAL(s32, U"");              TEST_EQUAL(t32, U"");
        TEST(! str_partition_at(U"Hello"s, s32, t32, U" "));                        TEST_EQUAL(s32, U"Hello");         TEST_EQUAL(t32, U"");
        TEST(str_partition_at(U"Hello world"s, s32, t32, U" "));                    TEST_EQUAL(s32, U"Hello");         TEST_EQUAL(t32, U"world");
        TEST(str_partition_at(U"Hello brave new world"s, s32, t32, U" "));          TEST_EQUAL(s32, U"Hello");         TEST_EQUAL(t32, U"brave new world");
        TEST(! str_partition_at(U""s, s32, t32, U"<>"));                            TEST_EQUAL(s32, U"");              TEST_EQUAL(t32, U"");
        TEST(! str_partition_at(U"Hello"s, s32, t32, U"<>"));                       TEST_EQUAL(s32, U"Hello");         TEST_EQUAL(t32, U"");
        TEST(! str_partition_at(U"Hello world"s, s32, t32, U"<>"));                 TEST_EQUAL(s32, U"Hello world");   TEST_EQUAL(t32, U"");
        TEST(! str_partition_at(U"Hello"s, s32, t32, U"<>"));                       TEST_EQUAL(s32, U"Hello");         TEST_EQUAL(t32, U"");
        TEST(str_partition_at(U"Hello<>world"s, s32, t32, U"<>"));                  TEST_EQUAL(s32, U"Hello");         TEST_EQUAL(t32, U"world");
        TEST(str_partition_at(U"Hello<>brave<>new<>world"s, s32, t32, U"<>"));      TEST_EQUAL(s32, U"Hello");         TEST_EQUAL(t32, U"brave<>new<>world");
        TEST(str_partition_at(U"<>Hello<>world<>"s, s32, t32, U"<>"));              TEST_EQUAL(s32, U"");              TEST_EQUAL(t32, U"Hello<>world<>");
        TEST(str_partition_at(U"<>Hello<>brave<>new<>world<>"s, s32, t32, U"<>"));  TEST_EQUAL(s32, U"");              TEST_EQUAL(t32, U"Hello<>brave<>new<>world<>");
        TEST(! str_partition_at(U"€uro ∈lement"s, s32, t32, U"∇√"));                TEST_EQUAL(s32, U"€uro ∈lement");  TEST_EQUAL(t32, U"");
        TEST(str_partition_at(U"€uro∇√∈lement"s, s32, t32, U"∇√"));                 TEST_EQUAL(s32, U"€uro");          TEST_EQUAL(t32, U"∈lement");
        TEST(str_partition_at(U"∇√€uro∇√∈lement∇√"s, s32, t32, U"∇√"));             TEST_EQUAL(s32, U"");              TEST_EQUAL(t32, U"€uro∇√∈lement∇√");

        TEST(! str_partition_by(""s, s8, t8, "+-_"));                     TEST_EQUAL(s8, "");       TEST_EQUAL(t8, "");
        TEST(! str_partition_by("Hello"s, s8, t8, "+-_"));                TEST_EQUAL(s8, "Hello");  TEST_EQUAL(t8, "");
        TEST(str_partition_by("Hello_world"s, s8, t8, "+-_"));            TEST_EQUAL(s8, "Hello");  TEST_EQUAL(t8, "world");
        TEST(str_partition_by("Hello_brave_new_world"s, s8, t8, "+-_"));  TEST_EQUAL(s8, "Hello");  TEST_EQUAL(t8, "brave_new_world");
        TEST(str_partition_by("€uro∇√∈lement∇√"s, s8, t8, "√∫∂∇"));       TEST_EQUAL(s8, "€uro");   TEST_EQUAL(t8, "∈lement∇√");

        TEST(! str_partition_by(u""s, s16, t16, u"+-_"));                     TEST_EQUAL(s16, u"");       TEST_EQUAL(t16, u"");
        TEST(! str_partition_by(u"Hello"s, s16, t16, u"+-_"));                TEST_EQUAL(s16, u"Hello");  TEST_EQUAL(t16, u"");
        TEST(str_partition_by(u"Hello_world"s, s16, t16, u"+-_"));            TEST_EQUAL(s16, u"Hello");  TEST_EQUAL(t16, u"world");
        TEST(str_partition_by(u"Hello_brave_new_world"s, s16, t16, u"+-_"));  TEST_EQUAL(s16, u"Hello");  TEST_EQUAL(t16, u"brave_new_world");
        TEST(str_partition_by(u"€uro∇√∈lement∇√"s, s16, t16, u"√∫∂∇"));       TEST_EQUAL(s16, u"€uro");   TEST_EQUAL(t16, u"∈lement∇√");

        TEST(! str_partition_by(U""s, s32, t32, U"+-_"));                     TEST_EQUAL(s32, U"");       TEST_EQUAL(t32, U"");
        TEST(! str_partition_by(U"Hello"s, s32, t32, U"+-_"));                TEST_EQUAL(s32, U"Hello");  TEST_EQUAL(t32, U"");
        TEST(str_partition_by(U"Hello_world"s, s32, t32, U"+-_"));            TEST_EQUAL(s32, U"Hello");  TEST_EQUAL(t32, U"world");
        TEST(str_partition_by(U"Hello_brave_new_world"s, s32, t32, U"+-_"));  TEST_EQUAL(s32, U"Hello");  TEST_EQUAL(t32, U"brave_new_world");
        TEST(str_partition_by(U"€uro∇√∈lement∇√"s, s32, t32, U"√∫∂∇"));       TEST_EQUAL(s32, U"€uro");   TEST_EQUAL(t32, U"∈lement∇√");

    }

    void check_remove() {

        u8string s8, t8;
        u16string s16, t16;
        u32string s32, t32;

        s8 = u8"";             TRY(t8 = str_remove(s8, U'o'));                                         TEST_EQUAL(t8, u8"");
        s8 = u8"";             TRY(t8 = str_remove(s8, u8"aeiou"));                                    TEST_EQUAL(t8, u8"");
        s8 = u8"Hello world";  TRY(t8 = str_remove(s8, U'o'));                                         TEST_EQUAL(t8, u8"Hell wrld");
        s8 = u8"Hello world";  TRY(t8 = str_remove(s8, u8"aeiou"));                                    TEST_EQUAL(t8, u8"Hll wrld");
        s8 = u8"";             TRY(t8 = str_remove_if(s8, [] (char32_t c) { return c < U'a'; }));      TEST_EQUAL(t8, u8"");
        s8 = u8"Hello world";  TRY(t8 = str_remove_if(s8, [] (char32_t c) { return c < U'a'; }));      TEST_EQUAL(t8, u8"elloworld");
        s8 = u8"";             TRY(t8 = str_remove_if_not(s8, [] (char32_t c) { return c < U'a'; }));  TEST_EQUAL(t8, u8"");
        s8 = u8"Hello world";  TRY(t8 = str_remove_if_not(s8, [] (char32_t c) { return c < U'a'; }));  TEST_EQUAL(t8, u8"H ");

        s8 = u8"";             TRY(str_remove_in(s8, U'o'));                                         TEST_EQUAL(s8, u8"");
        s8 = u8"";             TRY(str_remove_in(s8, u8"aeiou"));                                    TEST_EQUAL(s8, u8"");
        s8 = u8"Hello world";  TRY(str_remove_in(s8, U'o'));                                         TEST_EQUAL(s8, u8"Hell wrld");
        s8 = u8"Hello world";  TRY(str_remove_in(s8, u8"aeiou"));                                    TEST_EQUAL(s8, u8"Hll wrld");
        s8 = u8"";             TRY(str_remove_in_if(s8, [] (char32_t c) { return c < U'a'; }));      TEST_EQUAL(s8, u8"");
        s8 = u8"Hello world";  TRY(str_remove_in_if(s8, [] (char32_t c) { return c < U'a'; }));      TEST_EQUAL(s8, u8"elloworld");
        s8 = u8"";             TRY(str_remove_in_if_not(s8, [] (char32_t c) { return c < U'a'; }));  TEST_EQUAL(s8, u8"");
        s8 = u8"Hello world";  TRY(str_remove_in_if_not(s8, [] (char32_t c) { return c < U'a'; }));  TEST_EQUAL(s8, u8"H ");

    }

    void check_repeat() {

        u8string s8;
        u16string s16;
        u32string s32;

        TEST_EQUAL(str_repeat("", 0), "");
        TEST_EQUAL(str_repeat("", 1), "");
        TEST_EQUAL(str_repeat("", 2), "");
        TEST_EQUAL(str_repeat("@", 0), "");
        TEST_EQUAL(str_repeat("@", 1), "@");
        TEST_EQUAL(str_repeat("@", 2), "@@");
        TEST_EQUAL(str_repeat("@", 3), "@@@");
        TEST_EQUAL(str_repeat("Hello", 0), "");
        TEST_EQUAL(str_repeat("Hello", 1), "Hello");
        TEST_EQUAL(str_repeat("Hello", 2), "HelloHello");
        TEST_EQUAL(str_repeat("Hello", 3), "HelloHelloHello");
        TEST_EQUAL(str_repeat("Hello", 4), "HelloHelloHelloHello");
        TEST_EQUAL(str_repeat("Hello", 5), "HelloHelloHelloHelloHello");

        s8 = "";       TRY(str_repeat_in(s8, 0));  TEST_EQUAL(s8, "");
        s8 = "";       TRY(str_repeat_in(s8, 1));  TEST_EQUAL(s8, "");
        s8 = "";       TRY(str_repeat_in(s8, 2));  TEST_EQUAL(s8, "");
        s8 = "@";      TRY(str_repeat_in(s8, 0));  TEST_EQUAL(s8, "");
        s8 = "@";      TRY(str_repeat_in(s8, 1));  TEST_EQUAL(s8, "@");
        s8 = "@";      TRY(str_repeat_in(s8, 2));  TEST_EQUAL(s8, "@@");
        s8 = "@";      TRY(str_repeat_in(s8, 3));  TEST_EQUAL(s8, "@@@");
        s8 = "Hello";  TRY(str_repeat_in(s8, 0));  TEST_EQUAL(s8, "");
        s8 = "Hello";  TRY(str_repeat_in(s8, 1));  TEST_EQUAL(s8, "Hello");
        s8 = "Hello";  TRY(str_repeat_in(s8, 2));  TEST_EQUAL(s8, "HelloHello");
        s8 = "Hello";  TRY(str_repeat_in(s8, 3));  TEST_EQUAL(s8, "HelloHelloHello");
        s8 = "Hello";  TRY(str_repeat_in(s8, 4));  TEST_EQUAL(s8, "HelloHelloHelloHello");
        s8 = "Hello";  TRY(str_repeat_in(s8, 5));  TEST_EQUAL(s8, "HelloHelloHelloHelloHello");

        TEST_EQUAL(str_repeat(u"", 0), u"");
        TEST_EQUAL(str_repeat(u"", 1), u"");
        TEST_EQUAL(str_repeat(u"", 2), u"");
        TEST_EQUAL(str_repeat(u"@", 0), u"");
        TEST_EQUAL(str_repeat(u"@", 1), u"@");
        TEST_EQUAL(str_repeat(u"@", 2), u"@@");
        TEST_EQUAL(str_repeat(u"@", 3), u"@@@");
        TEST_EQUAL(str_repeat(u"Hello", 0), u"");
        TEST_EQUAL(str_repeat(u"Hello", 1), u"Hello");
        TEST_EQUAL(str_repeat(u"Hello", 2), u"HelloHello");
        TEST_EQUAL(str_repeat(u"Hello", 3), u"HelloHelloHello");
        TEST_EQUAL(str_repeat(u"Hello", 4), u"HelloHelloHelloHello");
        TEST_EQUAL(str_repeat(u"Hello", 5), u"HelloHelloHelloHelloHello");

        s16 = u"";       TRY(str_repeat_in(s16, 0));  TEST_EQUAL(s16, u"");
        s16 = u"";       TRY(str_repeat_in(s16, 1));  TEST_EQUAL(s16, u"");
        s16 = u"";       TRY(str_repeat_in(s16, 2));  TEST_EQUAL(s16, u"");
        s16 = u"@";      TRY(str_repeat_in(s16, 0));  TEST_EQUAL(s16, u"");
        s16 = u"@";      TRY(str_repeat_in(s16, 1));  TEST_EQUAL(s16, u"@");
        s16 = u"@";      TRY(str_repeat_in(s16, 2));  TEST_EQUAL(s16, u"@@");
        s16 = u"@";      TRY(str_repeat_in(s16, 3));  TEST_EQUAL(s16, u"@@@");
        s16 = u"Hello";  TRY(str_repeat_in(s16, 0));  TEST_EQUAL(s16, u"");
        s16 = u"Hello";  TRY(str_repeat_in(s16, 1));  TEST_EQUAL(s16, u"Hello");
        s16 = u"Hello";  TRY(str_repeat_in(s16, 2));  TEST_EQUAL(s16, u"HelloHello");
        s16 = u"Hello";  TRY(str_repeat_in(s16, 3));  TEST_EQUAL(s16, u"HelloHelloHello");
        s16 = u"Hello";  TRY(str_repeat_in(s16, 4));  TEST_EQUAL(s16, u"HelloHelloHelloHello");
        s16 = u"Hello";  TRY(str_repeat_in(s16, 5));  TEST_EQUAL(s16, u"HelloHelloHelloHelloHello");

        TEST_EQUAL(str_repeat(U"", 0), U"");
        TEST_EQUAL(str_repeat(U"", 1), U"");
        TEST_EQUAL(str_repeat(U"", 2), U"");
        TEST_EQUAL(str_repeat(U"@", 0), U"");
        TEST_EQUAL(str_repeat(U"@", 1), U"@");
        TEST_EQUAL(str_repeat(U"@", 2), U"@@");
        TEST_EQUAL(str_repeat(U"@", 3), U"@@@");
        TEST_EQUAL(str_repeat(U"Hello", 0), U"");
        TEST_EQUAL(str_repeat(U"Hello", 1), U"Hello");
        TEST_EQUAL(str_repeat(U"Hello", 2), U"HelloHello");
        TEST_EQUAL(str_repeat(U"Hello", 3), U"HelloHelloHello");
        TEST_EQUAL(str_repeat(U"Hello", 4), U"HelloHelloHelloHello");
        TEST_EQUAL(str_repeat(U"Hello", 5), U"HelloHelloHelloHelloHello");

        s32 = U"";       TRY(str_repeat_in(s32, 0));  TEST_EQUAL(s32, U"");
        s32 = U"";       TRY(str_repeat_in(s32, 1));  TEST_EQUAL(s32, U"");
        s32 = U"";       TRY(str_repeat_in(s32, 2));  TEST_EQUAL(s32, U"");
        s32 = U"@";      TRY(str_repeat_in(s32, 0));  TEST_EQUAL(s32, U"");
        s32 = U"@";      TRY(str_repeat_in(s32, 1));  TEST_EQUAL(s32, U"@");
        s32 = U"@";      TRY(str_repeat_in(s32, 2));  TEST_EQUAL(s32, U"@@");
        s32 = U"@";      TRY(str_repeat_in(s32, 3));  TEST_EQUAL(s32, U"@@@");
        s32 = U"Hello";  TRY(str_repeat_in(s32, 0));  TEST_EQUAL(s32, U"");
        s32 = U"Hello";  TRY(str_repeat_in(s32, 1));  TEST_EQUAL(s32, U"Hello");
        s32 = U"Hello";  TRY(str_repeat_in(s32, 2));  TEST_EQUAL(s32, U"HelloHello");
        s32 = U"Hello";  TRY(str_repeat_in(s32, 3));  TEST_EQUAL(s32, U"HelloHelloHello");
        s32 = U"Hello";  TRY(str_repeat_in(s32, 4));  TEST_EQUAL(s32, U"HelloHelloHelloHello");
        s32 = U"Hello";  TRY(str_repeat_in(s32, 5));  TEST_EQUAL(s32, U"HelloHelloHelloHelloHello");

    }

    void check_replace() {

        u8string s8;
        u16string s16;
        u32string s32;

        TEST_EQUAL(str_replace(""s, "", ""), "");
        TEST_EQUAL(str_replace("(abc)"s, "", ""), "(abc)");
        TEST_EQUAL(str_replace("(abc)"s, "abc", ""), "()");
        TEST_EQUAL(str_replace("(abc)"s, "abc", "xyz"), "(xyz)");
        TEST_EQUAL(str_replace("(abc)"s, "xyz", "abc"), "(abc)");
        TEST_EQUAL(str_replace("(abc)(abc)"s, "abc", ""), "()()");
        TEST_EQUAL(str_replace("(abc)(abc)"s, "abc", "xyz"), "(xyz)(xyz)");
        TEST_EQUAL(str_replace("(abc)(abc)"s, "xyz", "abc"), "(abc)(abc)");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "abc", ""), "()()()");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "abc", "xyz"), "(xyz)(xyz)(xyz)");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "xyz", "abc"), "(abc)(abc)(abc)");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "abc", "xyz", 0), "(abc)(abc)(abc)");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "abc", "xyz", 1), "(xyz)(abc)(abc)");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "abc", "xyz", 2), "(xyz)(xyz)(abc)");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "abc", "xyz", 3), "(xyz)(xyz)(xyz)");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "abc", "xyz", 4), "(xyz)(xyz)(xyz)");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "abc", "∀∃∇", 0), "(abc)(abc)(abc)");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "abc", "∀∃∇", 1), "(∀∃∇)(abc)(abc)");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "abc", "∀∃∇", 2), "(∀∃∇)(∀∃∇)(abc)");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "abc", "∀∃∇", 3), "(∀∃∇)(∀∃∇)(∀∃∇)");
        TEST_EQUAL(str_replace("(abc)(abc)(abc)"s, "abc", "∀∃∇", 4), "(∀∃∇)(∀∃∇)(∀∃∇)");
        TEST_EQUAL(str_replace("(∀∃∇)(∀∃∇)(∀∃∇)"s, "∀∃∇", "xyz", 0), "(∀∃∇)(∀∃∇)(∀∃∇)");
        TEST_EQUAL(str_replace("(∀∃∇)(∀∃∇)(∀∃∇)"s, "∀∃∇", "xyz", 1), "(xyz)(∀∃∇)(∀∃∇)");
        TEST_EQUAL(str_replace("(∀∃∇)(∀∃∇)(∀∃∇)"s, "∀∃∇", "xyz", 2), "(xyz)(xyz)(∀∃∇)");
        TEST_EQUAL(str_replace("(∀∃∇)(∀∃∇)(∀∃∇)"s, "∀∃∇", "xyz", 3), "(xyz)(xyz)(xyz)");
        TEST_EQUAL(str_replace("(∀∃∇)(∀∃∇)(∀∃∇)"s, "∀∃∇", "xyz", 4), "(xyz)(xyz)(xyz)");

        TEST_EQUAL(str_replace(u""s, u"", u""), u"");
        TEST_EQUAL(str_replace(u"(abc)"s, u"", u""), u"(abc)");
        TEST_EQUAL(str_replace(u"(abc)"s, u"abc", u""), u"()");
        TEST_EQUAL(str_replace(u"(abc)"s, u"abc", u"xyz"), u"(xyz)");
        TEST_EQUAL(str_replace(u"(abc)"s, u"xyz", u"abc"), u"(abc)");
        TEST_EQUAL(str_replace(u"(abc)(abc)"s, u"abc", u""), u"()()");
        TEST_EQUAL(str_replace(u"(abc)(abc)"s, u"abc", u"xyz"), u"(xyz)(xyz)");
        TEST_EQUAL(str_replace(u"(abc)(abc)"s, u"xyz", u"abc"), u"(abc)(abc)");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"abc", u""), u"()()()");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"abc", u"xyz"), u"(xyz)(xyz)(xyz)");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"xyz", u"abc"), u"(abc)(abc)(abc)");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"abc", u"xyz", 0), u"(abc)(abc)(abc)");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"abc", u"xyz", 1), u"(xyz)(abc)(abc)");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"abc", u"xyz", 2), u"(xyz)(xyz)(abc)");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"abc", u"xyz", 3), u"(xyz)(xyz)(xyz)");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"abc", u"xyz", 4), u"(xyz)(xyz)(xyz)");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"abc", u"∀∃∇", 0), u"(abc)(abc)(abc)");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"abc", u"∀∃∇", 1), u"(∀∃∇)(abc)(abc)");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"abc", u"∀∃∇", 2), u"(∀∃∇)(∀∃∇)(abc)");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"abc", u"∀∃∇", 3), u"(∀∃∇)(∀∃∇)(∀∃∇)");
        TEST_EQUAL(str_replace(u"(abc)(abc)(abc)"s, u"abc", u"∀∃∇", 4), u"(∀∃∇)(∀∃∇)(∀∃∇)");
        TEST_EQUAL(str_replace(u"(∀∃∇)(∀∃∇)(∀∃∇)"s, u"∀∃∇", u"xyz", 0), u"(∀∃∇)(∀∃∇)(∀∃∇)");
        TEST_EQUAL(str_replace(u"(∀∃∇)(∀∃∇)(∀∃∇)"s, u"∀∃∇", u"xyz", 1), u"(xyz)(∀∃∇)(∀∃∇)");
        TEST_EQUAL(str_replace(u"(∀∃∇)(∀∃∇)(∀∃∇)"s, u"∀∃∇", u"xyz", 2), u"(xyz)(xyz)(∀∃∇)");
        TEST_EQUAL(str_replace(u"(∀∃∇)(∀∃∇)(∀∃∇)"s, u"∀∃∇", u"xyz", 3), u"(xyz)(xyz)(xyz)");
        TEST_EQUAL(str_replace(u"(∀∃∇)(∀∃∇)(∀∃∇)"s, u"∀∃∇", u"xyz", 4), u"(xyz)(xyz)(xyz)");

        TEST_EQUAL(str_replace(U""s, U"", U""), U"");
        TEST_EQUAL(str_replace(U"(abc)"s, U"", U""), U"(abc)");
        TEST_EQUAL(str_replace(U"(abc)"s, U"abc", U""), U"()");
        TEST_EQUAL(str_replace(U"(abc)"s, U"abc", U"xyz"), U"(xyz)");
        TEST_EQUAL(str_replace(U"(abc)"s, U"xyz", U"abc"), U"(abc)");
        TEST_EQUAL(str_replace(U"(abc)(abc)"s, U"abc", U""), U"()()");
        TEST_EQUAL(str_replace(U"(abc)(abc)"s, U"abc", U"xyz"), U"(xyz)(xyz)");
        TEST_EQUAL(str_replace(U"(abc)(abc)"s, U"xyz", U"abc"), U"(abc)(abc)");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"abc", U""), U"()()()");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"abc", U"xyz"), U"(xyz)(xyz)(xyz)");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"xyz", U"abc"), U"(abc)(abc)(abc)");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"abc", U"xyz", 0), U"(abc)(abc)(abc)");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"abc", U"xyz", 1), U"(xyz)(abc)(abc)");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"abc", U"xyz", 2), U"(xyz)(xyz)(abc)");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"abc", U"xyz", 3), U"(xyz)(xyz)(xyz)");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"abc", U"xyz", 4), U"(xyz)(xyz)(xyz)");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"abc", U"∀∃∇", 0), U"(abc)(abc)(abc)");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"abc", U"∀∃∇", 1), U"(∀∃∇)(abc)(abc)");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"abc", U"∀∃∇", 2), U"(∀∃∇)(∀∃∇)(abc)");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"abc", U"∀∃∇", 3), U"(∀∃∇)(∀∃∇)(∀∃∇)");
        TEST_EQUAL(str_replace(U"(abc)(abc)(abc)"s, U"abc", U"∀∃∇", 4), U"(∀∃∇)(∀∃∇)(∀∃∇)");
        TEST_EQUAL(str_replace(U"(∀∃∇)(∀∃∇)(∀∃∇)"s, U"∀∃∇", U"xyz", 0), U"(∀∃∇)(∀∃∇)(∀∃∇)");
        TEST_EQUAL(str_replace(U"(∀∃∇)(∀∃∇)(∀∃∇)"s, U"∀∃∇", U"xyz", 1), U"(xyz)(∀∃∇)(∀∃∇)");
        TEST_EQUAL(str_replace(U"(∀∃∇)(∀∃∇)(∀∃∇)"s, U"∀∃∇", U"xyz", 2), U"(xyz)(xyz)(∀∃∇)");
        TEST_EQUAL(str_replace(U"(∀∃∇)(∀∃∇)(∀∃∇)"s, U"∀∃∇", U"xyz", 3), U"(xyz)(xyz)(xyz)");
        TEST_EQUAL(str_replace(U"(∀∃∇)(∀∃∇)(∀∃∇)"s, U"∀∃∇", U"xyz", 4), U"(xyz)(xyz)(xyz)");

        s8 = u8"";                 TRY(str_replace_in(s8, u8"", u8""));           TEST_EQUAL(s8, u8"");
        s8 = u8"(abc)";            TRY(str_replace_in(s8, u8"", u8""));           TEST_EQUAL(s8, u8"(abc)");
        s8 = u8"(abc)";            TRY(str_replace_in(s8, u8"abc", u8""));        TEST_EQUAL(s8, u8"()");
        s8 = u8"(abc)";            TRY(str_replace_in(s8, u8"abc", u8"xyz"));     TEST_EQUAL(s8, u8"(xyz)");
        s8 = u8"(abc)";            TRY(str_replace_in(s8, u8"xyz", u8"abc"));     TEST_EQUAL(s8, u8"(abc)");
        s8 = u8"(abc)(abc)";       TRY(str_replace_in(s8, u8"abc", u8""));        TEST_EQUAL(s8, u8"()()");
        s8 = u8"(abc)(abc)";       TRY(str_replace_in(s8, u8"abc", u8"xyz"));     TEST_EQUAL(s8, u8"(xyz)(xyz)");
        s8 = u8"(abc)(abc)";       TRY(str_replace_in(s8, u8"xyz", u8"abc"));     TEST_EQUAL(s8, u8"(abc)(abc)");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"abc", u8""));        TEST_EQUAL(s8, u8"()()()");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"abc", u8"xyz"));     TEST_EQUAL(s8, u8"(xyz)(xyz)(xyz)");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"xyz", u8"abc"));     TEST_EQUAL(s8, u8"(abc)(abc)(abc)");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"abc", u8"xyz", 0));  TEST_EQUAL(s8, u8"(abc)(abc)(abc)");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"abc", u8"xyz", 1));  TEST_EQUAL(s8, u8"(xyz)(abc)(abc)");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"abc", u8"xyz", 2));  TEST_EQUAL(s8, u8"(xyz)(xyz)(abc)");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"abc", u8"xyz", 3));  TEST_EQUAL(s8, u8"(xyz)(xyz)(xyz)");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"abc", u8"xyz", 4));  TEST_EQUAL(s8, u8"(xyz)(xyz)(xyz)");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"abc", u8"∀∃∇", 0));  TEST_EQUAL(s8, u8"(abc)(abc)(abc)");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"abc", u8"∀∃∇", 1));  TEST_EQUAL(s8, u8"(∀∃∇)(abc)(abc)");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"abc", u8"∀∃∇", 2));  TEST_EQUAL(s8, u8"(∀∃∇)(∀∃∇)(abc)");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"abc", u8"∀∃∇", 3));  TEST_EQUAL(s8, u8"(∀∃∇)(∀∃∇)(∀∃∇)");
        s8 = u8"(abc)(abc)(abc)";  TRY(str_replace_in(s8, u8"abc", u8"∀∃∇", 4));  TEST_EQUAL(s8, u8"(∀∃∇)(∀∃∇)(∀∃∇)");
        s8 = u8"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s8, u8"∀∃∇", u8"xyz", 0));  TEST_EQUAL(s8, u8"(∀∃∇)(∀∃∇)(∀∃∇)");
        s8 = u8"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s8, u8"∀∃∇", u8"xyz", 1));  TEST_EQUAL(s8, u8"(xyz)(∀∃∇)(∀∃∇)");
        s8 = u8"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s8, u8"∀∃∇", u8"xyz", 2));  TEST_EQUAL(s8, u8"(xyz)(xyz)(∀∃∇)");
        s8 = u8"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s8, u8"∀∃∇", u8"xyz", 3));  TEST_EQUAL(s8, u8"(xyz)(xyz)(xyz)");
        s8 = u8"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s8, u8"∀∃∇", u8"xyz", 4));  TEST_EQUAL(s8, u8"(xyz)(xyz)(xyz)");

        s16 = u"";                 TRY(str_replace_in(s16, u"", u""));           TEST_EQUAL(s16, u"");
        s16 = u"(abc)";            TRY(str_replace_in(s16, u"", u""));           TEST_EQUAL(s16, u"(abc)");
        s16 = u"(abc)";            TRY(str_replace_in(s16, u"abc", u""));        TEST_EQUAL(s16, u"()");
        s16 = u"(abc)";            TRY(str_replace_in(s16, u"abc", u"xyz"));     TEST_EQUAL(s16, u"(xyz)");
        s16 = u"(abc)";            TRY(str_replace_in(s16, u"xyz", u"abc"));     TEST_EQUAL(s16, u"(abc)");
        s16 = u"(abc)(abc)";       TRY(str_replace_in(s16, u"abc", u""));        TEST_EQUAL(s16, u"()()");
        s16 = u"(abc)(abc)";       TRY(str_replace_in(s16, u"abc", u"xyz"));     TEST_EQUAL(s16, u"(xyz)(xyz)");
        s16 = u"(abc)(abc)";       TRY(str_replace_in(s16, u"xyz", u"abc"));     TEST_EQUAL(s16, u"(abc)(abc)");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"abc", u""));        TEST_EQUAL(s16, u"()()()");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"abc", u"xyz"));     TEST_EQUAL(s16, u"(xyz)(xyz)(xyz)");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"xyz", u"abc"));     TEST_EQUAL(s16, u"(abc)(abc)(abc)");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"abc", u"xyz", 0));  TEST_EQUAL(s16, u"(abc)(abc)(abc)");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"abc", u"xyz", 1));  TEST_EQUAL(s16, u"(xyz)(abc)(abc)");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"abc", u"xyz", 2));  TEST_EQUAL(s16, u"(xyz)(xyz)(abc)");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"abc", u"xyz", 3));  TEST_EQUAL(s16, u"(xyz)(xyz)(xyz)");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"abc", u"xyz", 4));  TEST_EQUAL(s16, u"(xyz)(xyz)(xyz)");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"abc", u"∀∃∇", 0));  TEST_EQUAL(s16, u"(abc)(abc)(abc)");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"abc", u"∀∃∇", 1));  TEST_EQUAL(s16, u"(∀∃∇)(abc)(abc)");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"abc", u"∀∃∇", 2));  TEST_EQUAL(s16, u"(∀∃∇)(∀∃∇)(abc)");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"abc", u"∀∃∇", 3));  TEST_EQUAL(s16, u"(∀∃∇)(∀∃∇)(∀∃∇)");
        s16 = u"(abc)(abc)(abc)";  TRY(str_replace_in(s16, u"abc", u"∀∃∇", 4));  TEST_EQUAL(s16, u"(∀∃∇)(∀∃∇)(∀∃∇)");
        s16 = u"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s16, u"∀∃∇", u"xyz", 0));  TEST_EQUAL(s16, u"(∀∃∇)(∀∃∇)(∀∃∇)");
        s16 = u"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s16, u"∀∃∇", u"xyz", 1));  TEST_EQUAL(s16, u"(xyz)(∀∃∇)(∀∃∇)");
        s16 = u"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s16, u"∀∃∇", u"xyz", 2));  TEST_EQUAL(s16, u"(xyz)(xyz)(∀∃∇)");
        s16 = u"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s16, u"∀∃∇", u"xyz", 3));  TEST_EQUAL(s16, u"(xyz)(xyz)(xyz)");
        s16 = u"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s16, u"∀∃∇", u"xyz", 4));  TEST_EQUAL(s16, u"(xyz)(xyz)(xyz)");

        s32 = U"";                 TRY(str_replace_in(s32, U"", U""));           TEST_EQUAL(s32, U"");
        s32 = U"(abc)";            TRY(str_replace_in(s32, U"", U""));           TEST_EQUAL(s32, U"(abc)");
        s32 = U"(abc)";            TRY(str_replace_in(s32, U"abc", U""));        TEST_EQUAL(s32, U"()");
        s32 = U"(abc)";            TRY(str_replace_in(s32, U"abc", U"xyz"));     TEST_EQUAL(s32, U"(xyz)");
        s32 = U"(abc)";            TRY(str_replace_in(s32, U"xyz", U"abc"));     TEST_EQUAL(s32, U"(abc)");
        s32 = U"(abc)(abc)";       TRY(str_replace_in(s32, U"abc", U""));        TEST_EQUAL(s32, U"()()");
        s32 = U"(abc)(abc)";       TRY(str_replace_in(s32, U"abc", U"xyz"));     TEST_EQUAL(s32, U"(xyz)(xyz)");
        s32 = U"(abc)(abc)";       TRY(str_replace_in(s32, U"xyz", U"abc"));     TEST_EQUAL(s32, U"(abc)(abc)");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"abc", U""));        TEST_EQUAL(s32, U"()()()");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"abc", U"xyz"));     TEST_EQUAL(s32, U"(xyz)(xyz)(xyz)");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"xyz", U"abc"));     TEST_EQUAL(s32, U"(abc)(abc)(abc)");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"abc", U"xyz", 0));  TEST_EQUAL(s32, U"(abc)(abc)(abc)");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"abc", U"xyz", 1));  TEST_EQUAL(s32, U"(xyz)(abc)(abc)");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"abc", U"xyz", 2));  TEST_EQUAL(s32, U"(xyz)(xyz)(abc)");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"abc", U"xyz", 3));  TEST_EQUAL(s32, U"(xyz)(xyz)(xyz)");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"abc", U"xyz", 4));  TEST_EQUAL(s32, U"(xyz)(xyz)(xyz)");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"abc", U"∀∃∇", 0));  TEST_EQUAL(s32, U"(abc)(abc)(abc)");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"abc", U"∀∃∇", 1));  TEST_EQUAL(s32, U"(∀∃∇)(abc)(abc)");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"abc", U"∀∃∇", 2));  TEST_EQUAL(s32, U"(∀∃∇)(∀∃∇)(abc)");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"abc", U"∀∃∇", 3));  TEST_EQUAL(s32, U"(∀∃∇)(∀∃∇)(∀∃∇)");
        s32 = U"(abc)(abc)(abc)";  TRY(str_replace_in(s32, U"abc", U"∀∃∇", 4));  TEST_EQUAL(s32, U"(∀∃∇)(∀∃∇)(∀∃∇)");
        s32 = U"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s32, U"∀∃∇", U"xyz", 0));  TEST_EQUAL(s32, U"(∀∃∇)(∀∃∇)(∀∃∇)");
        s32 = U"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s32, U"∀∃∇", U"xyz", 1));  TEST_EQUAL(s32, U"(xyz)(∀∃∇)(∀∃∇)");
        s32 = U"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s32, U"∀∃∇", U"xyz", 2));  TEST_EQUAL(s32, U"(xyz)(xyz)(∀∃∇)");
        s32 = U"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s32, U"∀∃∇", U"xyz", 3));  TEST_EQUAL(s32, U"(xyz)(xyz)(xyz)");
        s32 = U"(∀∃∇)(∀∃∇)(∀∃∇)";  TRY(str_replace_in(s32, U"∀∃∇", U"xyz", 4));  TEST_EQUAL(s32, U"(xyz)(xyz)(xyz)");

    }

}

TEST_MODULE(unicorn, string_manipulation_n_r) {

    check_pad_left();
    check_pad_right();
    check_partition();
    check_remove();
    check_replace();
    check_repeat();

}
