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

#pragma once

#include "utf_codepoint.h"

#include <stdexcept>
#include <string>
#include <string_view>

namespace sutf
{
////////////////////////////////////////////////////////////////////////////////////////////////////
// type definitions
////////////////////////////////////////////////////////////////////////////////////////////////////

using string = std::string;
using string_view = std::string_view;
using wstring = std::wstring;
using wstring_view = std::wstring_view;
#ifndef __cpp_char8_t
using u8string = std::basic_string<char8s_t>;
using u8string_view = std::basic_string_view<char8s_t>;
#else
using u8string = std::u8string;
using u8string_view = std::u8string_view;
#endif // __cpp_char8_t
using u16string = std::u16string;
using u16string_view = std::u16string_view;
using u32string = std::u32string;
using u32string_view = std::u32string_view;



////////////////////////////////////////////////////////////////////////////////////////////////////
// standalone routines
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// string convertors

string to_string(const string_view& str);
string to_string(const wstring_view& str);
string to_string(const u8string_view& str);
string to_string(const u16string_view& str);
string to_string(const u32string_view& str);
template<typename type_t, std::enable_if_t<is_native_string_v<type_t>, int> = 0>
string to_string(const type_t& str);
string to_string(string str);
template<typename char_t>
string to_string(const std::basic_string_view<char_t>& str);
template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int> = 0>
string to_string(it_t str, it_t last);

////////////////////////////////////////////////////////////////////////////////////////////////////
// wstring convertors

wstring to_wstring(const string_view& str);
wstring to_wstring(const wstring_view& str);
wstring to_wstring(const u8string_view& str);
wstring to_wstring(const u16string_view& str);
wstring to_wstring(const u32string_view& str);
template<typename type_t, std::enable_if_t<is_native_string_v<type_t>, int> = 0>
wstring to_wstring(const type_t& str);
wstring to_wstring(wstring str);
template<typename char_t>
wstring to_wstring(const std::basic_string_view<char_t>& str);
template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int> = 0>
wstring to_wstring(it_t str, it_t last);

////////////////////////////////////////////////////////////////////////////////////////////////////
// u8string convertors

u8string to_u8string(const string_view& str);
u8string to_u8string(const wstring_view& str);
u8string to_u8string(const u8string_view& str);
u8string to_u8string(const u16string_view& str);
u8string to_u8string(const u32string_view& str);
template<typename type_t, std::enable_if_t<is_native_string_v<type_t>, int> = 0>
u8string to_u8string(const type_t& str);
u8string to_u8string(u8string str);
template<typename char_t>
u8string to_u8string(const std::basic_string_view<char_t>& str);
template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int> = 0>
u8string to_u8string(it_t str, it_t last);

////////////////////////////////////////////////////////////////////////////////////////////////////
// u16string convertors

u16string to_u16string(const string_view& str);
u16string to_u16string(const wstring_view& str);
u16string to_u16string(const u8string_view& str);
u16string to_u16string(const u16string_view& str);
u16string to_u16string(const u32string_view& str);
template<typename type_t, std::enable_if_t<is_native_string_v<type_t>, int> = 0>
u16string to_u16string(const type_t& str);
u16string to_u16string(u16string str);
template<typename char_t>
u16string to_u16string(const std::basic_string_view<char_t>& str);
template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int> = 0>
u16string to_u16string(it_t str, it_t last);

////////////////////////////////////////////////////////////////////////////////////////////////////
// u32string convertors

u32string to_u32string(const string_view& str);
u32string to_u32string(const wstring_view& str);
u32string to_u32string(const u8string_view& str);
u32string to_u32string(const u16string_view& str);
u32string to_u32string(const u32string_view& str);
template<typename type_t, std::enable_if_t<is_native_string_v<type_t>, int> = 0>
u32string to_u32string(const type_t& str);
u32string to_u32string(u32string str);
template<typename char_t>
u32string to_u32string(const std::basic_string_view<char_t>& str);
template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int> = 0>
u32string to_u32string(it_t str, it_t last);

////////////////////////////////////////////////////////////////////////////////////////////////////
// basic_string convertors

template<typename chardst_t, typename charsrc_t>
std::basic_string<chardst_t> to_anystring(const std::basic_string_view<charsrc_t>& str);
template<typename char_t, typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int> = 0>
std::basic_string<char_t> to_anystring(it_t str, it_t last);
template<typename char_t>
std::basic_string<char_t> to_anystring(std::basic_string<char_t> str);

template<typename type_t>
auto convert(const string_view& src, type_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t());
template<typename type_t>
auto convert(const wstring_view& src, type_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t());
template<typename type_t>
auto convert(const u8string_view& src, type_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t());
template<typename type_t>
auto convert(const u16string_view& src, type_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t());
template<typename type_t>
auto convert(const u32string_view& src, type_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t());
template<typename typesrc_t, typename typedst_t, std::enable_if_t<is_native_string_v<typesrc_t>, int> = 0>
auto convert(const typesrc_t& src, typedst_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t());
template<typename char_t, typename type_t>
auto convert(const std::basic_string_view<char_t>& src, type_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t());



////////////////////////////////////////////////////////////////////////////////////////////////////
// standalone routines
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// string convertors

inline string to_string(const string_view& str)
{
    return to_string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline string to_string(const wstring_view& str)
{
    return to_string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline string to_string(const u8string_view& str)
{
    return to_string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
inline string to_string(const u16string_view& str)
{
    return to_string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline string to_string(const u32string_view& str)
{
    return to_string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename type_t, std::enable_if_t<is_native_string_v<type_t>, int>>
inline string to_string(const type_t& str)
{
    if constexpr (is_char_array_v<type_t>)
        return to_string(std::basic_string_view(str, std::size(str) - 1));
    else
        return to_string(std::basic_string_view(str));
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline string to_string(string str)
{
    return str;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t>
inline string to_string(const std::basic_string_view<char_t>& str)
{
    return to_anystring<char>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int>>
inline string to_string(it_t str, it_t last)
{
    return to_anystring<char>(str, last);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// wstring convertors

inline wstring to_wstring(const string_view& str)
{
    return to_wstring<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline wstring to_wstring(const wstring_view& str)
{
    return to_wstring<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline wstring to_wstring(const u8string_view& str)
{
    return to_wstring<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
inline wstring to_wstring(const u16string_view& str)
{
    return to_wstring<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline wstring to_wstring(const u32string_view& str)
{
    return to_wstring<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename type_t, std::enable_if_t<is_native_string_v<type_t>, int>>
inline wstring to_wstring(const type_t& str)
{
    if constexpr (is_char_array_v<type_t>)
        return to_wstring(std::basic_string_view(str, std::size(str) - 1));
    else
        return to_wstring(std::basic_string_view(str));
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline wstring to_wstring(wstring str)
{
    return str;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t>
inline wstring to_wstring(const std::basic_string_view<char_t>& str)
{
    return to_anystring<wchar_t>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int>>
inline wstring to_wstring(it_t str, it_t last)
{
    return to_anystring<wchar_t>(str, last);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// u8string convertors

inline u8string to_u8string(const string_view& str)
{
    return to_u8string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u8string to_u8string(const wstring_view& str)
{
    return to_u8string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u8string to_u8string(const u8string_view& str)
{
    return to_u8string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
inline u8string to_u8string(const u16string_view& str)
{
    return to_u8string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u8string to_u8string(const u32string_view& str)
{
    return to_u8string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename type_t, std::enable_if_t<is_native_string_v<type_t>, int>>
inline u8string to_u8string(const type_t& str)
{
    if constexpr (is_char_array_v<type_t>)
        return to_u8string(std::basic_string_view(str, std::size(str) - 1));
    else
        return to_u8string(std::basic_string_view(str));
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u8string to_u8string(u8string str)
{
    return str;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t>
inline u8string to_u8string(const std::basic_string_view<char_t>& str)
{
    return to_anystring<char8s_t>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int>>
inline u8string to_u8string(it_t str, it_t last)
{
    return to_anystring<char8s_t>(str, last);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// u16string convertors

inline u16string to_u16string(const string_view& str)
{
    return to_u16string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u16string to_u16string(const wstring_view& str)
{
    return to_u16string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u16string to_u16string(const u8string_view& str)
{
    return to_u16string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u16string to_u16string(const u16string_view& str)
{
    return to_u16string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u16string to_u16string(const u32string_view& str)
{
    return to_u16string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename type_t, std::enable_if_t<is_native_string_v<type_t>, int>>
inline u16string to_u16string(const type_t& str)
{
    if constexpr (is_char_array_v<type_t>)
        return to_u16string(std::basic_string_view(str, std::size(str) - 1));
    else
        return to_u16string(std::basic_string_view(str));
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u16string to_u16string(u16string str)
{
    return str;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t>
inline u16string to_u16string(const std::basic_string_view<char_t>& str)
{
    return to_anystring<char16_t>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int>>
inline u16string to_u16string(it_t str, it_t last)
{
    return to_anystring<char16_t>(str, last);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// u32string convertors

inline u32string to_u32string(const string_view& str)
{
    return to_u32string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u32string to_u32string(const wstring_view& str)
{
    return to_u32string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u32string to_u32string(const u8string_view& str)
{
    return to_u32string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u32string to_u32string(const u16string_view& str)
{
    return to_u32string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u32string to_u32string(const u32string_view& str)
{
    return to_u32string<typename std::iterator_traits<decltype(std::cbegin(str))>::value_type>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename type_t, std::enable_if_t<is_native_string_v<type_t>, int>>
inline u32string to_u32string(const type_t& str)
{
    if constexpr (is_char_array_v<type_t>)
        return to_u32string(std::basic_string_view(str, std::size(str) - 1));
    else
        return to_u32string(std::basic_string_view(str));
}



////////////////////////////////////////////////////////////////////////////////////////////////////
inline u32string to_u32string(u32string str)
{
    return str;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t>
inline u32string to_u32string(const std::basic_string_view<char_t>& str)
{
    return to_anystring<char32_t>(str);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int>>
inline u32string to_u32string(it_t str, it_t last)
{
    return to_anystring<char32_t>(str, last);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// basic_string convertors

template<typename chardst_t, typename charsrc_t>
inline std::basic_string<chardst_t> to_anystring(const std::basic_string_view<charsrc_t>& str)
{
    return to_anystring<chardst_t>(str.cbegin(), str.cend());
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t, typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int>>
inline std::basic_string<char_t> to_anystring(it_t str, it_t last)
{
    std::basic_string<char_t> out;
    out.resize(code_unit_count<char_t>(str, last));

    code_point_convert(str, last, out.begin());

    return out;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename type_t>
inline auto convert(const string_view& src, type_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t())
{
    return convert<typename std::iterator_traits<decltype(std::cbegin(src))>::value_type, type_t>(src, dst);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename type_t>
inline auto convert(const wstring_view& src, type_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t())
{
    return convert<typename std::iterator_traits<decltype(std::cbegin(src))>::value_type, type_t>(src, dst);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename type_t>
inline auto convert(const u8string_view& src, type_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t())
{
    return convert<typename std::iterator_traits<decltype(std::cbegin(src))>::value_type, type_t>(src, dst);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename type_t>
inline auto convert(const u16string_view& src, type_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t())
{
    return convert<typename std::iterator_traits<decltype(std::cbegin(src))>::value_type, type_t>(src, dst);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename type_t>
inline auto convert(const u32string_view& src, type_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t())
{
    return convert<typename std::iterator_traits<decltype(std::cbegin(src))>::value_type, type_t>(src, dst);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename typesrc_t, typename typedst_t, std::enable_if_t<is_native_string_v<typesrc_t>, int>>
inline auto convert(const typesrc_t& src, typedst_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t())
{
    if constexpr (is_char_array_v<typesrc_t>)
        return convert(std::basic_string_view(src, std::size(src) - 1), dst);
    else
        return convert(std::basic_string_view(src), dst);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t, typename type_t>
inline auto convert(const std::basic_string_view<char_t>& src, type_t& dst) -> decltype(std::begin(dst), std::end(dst), uint_t())
{
    using chardst_t = typename std::iterator_traits<decltype(std::begin(dst))>::value_type;
    const uint_t dst_size = code_unit_count<chardst_t>(src);

    if (std::size(dst) < dst_size)
        throw std::length_error("Destination buffer doesn't fit on the specified string after convertion.");

    code_point_convert(src.cbegin(), src.cend(), std::begin(dst));

    return dst_size;
}

} // namespace sutf

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of utf_codepoint.h
////////////////////////////////////////////////////////////////////////////////////////////////////
