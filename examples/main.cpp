////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Simple UTF library for C++
// version 1.0
//
////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
//
// Copyright (c) 2022 Yury Kalmykov <y_kalmykov@mail.ru>.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/sutfcpplib/utf_string.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
// constant data
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

constexpr const char raw_char[] = "\x41\xc2\xa9\xe2\x86\x90\xf0\x9f\x98\x82\x42\xc2\xae\xe2\x9c\x85\xf0\x9f\xa5\xb3";
constexpr const wchar_t raw_wchar[] = L"\U00000041\U000000a9\U00002190\U0001f602\U00000042\U000000ae\U00002705\U0001f973";
constexpr const sutf::char8s_t raw_utf8[] = { 0x41, 0xc2, 0xa9, 0xe2, 0x86, 0x90, 0xf0, 0x9f, 0x98, 0x82, 0x42, 0xc2, 0xae, 0xe2, 0x9c, 0x85, 0xf0, 0x9f, 0xa5, 0xb3, 0x00 };
constexpr const char16_t raw_utf16[] = u"\U00000041\U000000a9\U00002190\U0001f602\U00000042\U000000ae\U00002705\U0001f973";
constexpr const char32_t raw_utf32[] = U"\U00000041\U000000a9\U00002190\U0001f602\U00000042\U000000ae\U00002705\U0001f973";

constexpr auto str_char = std::string_view(raw_char);
constexpr auto str_wchar = std::wstring_view(raw_wchar);
constexpr auto str_utf8 = std::basic_string_view(raw_utf8);
constexpr auto str_utf16 = std::u16string_view(raw_utf16);
constexpr auto str_utf32 = std::u32string_view(raw_utf32);



////////////////////////////////////////////////////////////////////////////////////////////////////
// standalone routines
////////////////////////////////////////////////////////////////////////////////////////////////////

static void code_point_support() noexcept
{
    using namespace sutf;

    // get next codepoint position

    constexpr const char* raw_beg_it = raw_char;
    constexpr const auto raw_end_it = code_point_next(raw_beg_it);
    
    static_assert(raw_end_it - raw_beg_it == 1); // number of code units representing code point 'a' in UTF-8 encoding.

    constexpr auto str_beg_it = std::cbegin(str_utf16);
    constexpr auto str_end_it = code_point_next(str_beg_it);

    static_assert(raw_end_it - raw_beg_it == 1); // number of code units representing code point 'a' in UTF-16 encoding.



    // calculate number of code point in specified bounds

    static_assert(code_point_count(std::cbegin(raw_utf16), std::cend(raw_utf16) - 1) == 8); // number of code points in UTF-16 string.
    static_assert(code_point_count(str_utf32) == 8); // number of code points in UTF-32 string.



    // read next code point from position

    static_assert(code_point_read(raw_utf16) == 0x00000041); // read next code point from UTF-16 string.
    static_assert(code_point_read(std::cbegin(str_utf32)) == 0x00000041); // read next code point from UTF-32 string.



    // calculate number of code unit 

    static_assert(code_unit_count<char>(0x0001f973) == 4); // number of code units representing specified code point in UTF-8 encoding.
    static_assert(code_unit_count<char16_t>(0x0001f973) == 2); // number of code units representing specified code point in UTF-16 encoding.
    static_assert(code_unit_count<char32_t>(0x0001f973) == 1); // number of code units representing specified code point in UTF-32 encoding.

    static_assert(code_unit_count<char>(raw_utf32) == 20); // number of code units representing UFT-32 string in UTF-8 encoding.
    static_assert(code_unit_count<char16_t>(str_utf8) == 10); // number of code units representing UFT-8 string in UTF-16 encoding.
    static_assert(code_unit_count<char32_t>(str_utf16) == 8); // number of code units representing UFT-16 string in UTF-32 encoding.



    // convert code point of different formats

    std::string dst_utf8(code_unit_count<char>(raw_utf32), '\0');
    std::u16string dst_utf16(code_unit_count<char16_t>(raw_utf8), u'\0');
    std::u32string dst_utf32(code_unit_count<char32_t>(raw_utf16), U'\0');

    // write code point in UTF-8 format.
    assert(code_point_write(std::begin(dst_utf8), 0x0001f973) == std::begin(dst_utf8) + 4);
    // write code point in UTF-16 format.
    assert(code_point_write(std::begin(dst_utf16), 0x0001f973) == std::begin(dst_utf16) + 2);
    // write code point in UTF-32 format.
    assert(code_point_write(std::begin(dst_utf32), 0x0001f973) == std::begin(dst_utf32) + 1);

    // convert UFT-32 code point range to UTF-8 encoding.
    assert(code_point_convert(std::cbegin(str_utf32), std::cend(str_utf32), std::begin(dst_utf8)) == std::end(dst_utf8));
    // convert UFT-8 code point range to UTF-16 encoding.
    assert(code_point_convert(std::cbegin(str_utf8), std::cend(str_utf8), std::begin(dst_utf16)) == std::end(dst_utf16));
    // convert UFT-16 code point range to UTF-32 encoding.
    assert(code_point_convert(std::cbegin(str_utf16), std::cend(str_utf16), std::begin(dst_utf32)) == std::end(dst_utf32)); 
}



////////////////////////////////////////////////////////////////////////////////////////////////////
static void string_support() noexcept
{
    using namespace sutf;

    // convert any string to UTF-8 string

    assert(to_string(str_char) == str_char);
    assert(to_string(str_wchar) == str_char);
    assert(to_string(str_utf8) == str_char);
    assert(to_string(str_utf16) == str_char);
    assert(to_string(str_utf32) == str_char);



    // convert any string to UTF-16/UTF-32 string

    assert(to_wstring(str_char) == str_wchar);
    assert(to_wstring(str_wchar) == str_wchar);
    assert(to_wstring(str_utf8) == str_wchar);
    assert(to_wstring(str_utf16) == str_wchar);
    assert(to_wstring(str_utf32) == str_wchar);



    // convert any string to UTF-8 string

    assert(to_u8string(str_char) == str_utf8);
    assert(to_u8string(str_wchar) == str_utf8);
    assert(to_u8string(str_utf8) == str_utf8);
    assert(to_u8string(str_utf16) == str_utf8);
    assert(to_u8string(str_utf32) == str_utf8);



    // convert any string to UTF-16 string

    assert(to_u16string(str_char) == str_utf16);
    assert(to_u16string(str_wchar) == str_utf16);
    assert(to_u16string(str_utf8) == str_utf16);
    assert(to_u16string(str_utf16) == str_utf16);
    assert(to_u16string(str_utf32) == str_utf16);



    // convert any string to UTF-32 string

    assert(to_u32string(str_char) == str_utf32);
    assert(to_u32string(str_wchar) == str_utf32);
    assert(to_u32string(str_utf8) == str_utf32);
    assert(to_u32string(str_utf16) == str_utf32);
    assert(to_u32string(str_utf32) == str_utf32);



    // convert to string type specified by template type

    assert(to_anystring<char16_t>(str_utf32) == str_utf16);



    // transcode any outstanding buffers

    std::string dst_utf8(code_unit_count<char>(raw_utf32), '\0');
    std::u16string dst_utf16(code_unit_count<char16_t>(raw_utf8), u'\0');
    std::u32string dst_utf32(code_unit_count<char32_t>(raw_utf16), U'\0');

    assert(convert(raw_utf32, dst_utf8) == dst_utf8.size());
    assert(convert(str_utf8, dst_utf16) == dst_utf16.size());
    assert(convert(raw_utf16, dst_utf32) == dst_utf32.size());



    // try to convert buffer to insufficient size buffer

    try {
        
        char small[1];
        convert(raw_utf32, small);
        assert(false);

    } catch (const std::length_error&) {
    } 
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// module main entry point
////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    code_point_support();
    string_support();

    return 1;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// End of main.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////
