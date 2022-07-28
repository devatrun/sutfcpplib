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

#include <cassert>
#include <climits>
#include <cstdint>

#include <iterator>
#include <type_traits>

#if !(defined(_MSC_VER) && _MSC_VER >= 1910 && ((defined(_MSVC_LANG) && _MSVC_LANG > 201402)) || (__cplusplus > 201402))
#error "Library SUTFCPP requires a compiler that supports C++ 17!"
#endif

namespace sutf
{
////////////////////////////////////////////////////////////////////////////////////////////////////
// type definitions
////////////////////////////////////////////////////////////////////////////////////////////////////

using uint_t = std::uintptr_t;
using int_t = std::intptr_t;

#ifndef __cpp_char8_t
using char8s_t = std::uint8_t;
#else
using char8s_t = char8_t;
#endif //__cpp_char8_t



////////////////////////////////////////////////////////////////////////////////////////////////////
// is_any_of_v
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename type_t, typename... match_t>
constexpr bool is_any_of_v = std::disjunction_v<std::is_same<type_t, match_t>...>;

////////////////////////////////////////////////////////////////////////////////////////////////////
// is_any_char_v
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename type_t>
constexpr bool is_any_char_v = is_any_of_v<type_t, char, char8s_t, char16_t, wchar_t, char32_t>;

////////////////////////////////////////////////////////////////////////////////////////////////////
// is_iterator_of
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename it_t, typename... value_t>
struct is_iterator_of {

    using it_value_t = typename std::iterator_traits<it_t>::value_type;
    using it_reference_t = typename std::iterator_traits<it_t>::reference;

    template<typename it1_t>
    static constexpr bool is_non_const_v = std::is_same_v<
        std::remove_reference_t<it1_t>, std::remove_const_t<std::remove_reference_t<it1_t>>>;

    static constexpr bool value = is_any_of_v<it_value_t, value_t...> && is_non_const_v<it_t>;
};

template<typename it_t, typename... value_t>
constexpr bool is_iterator_of_v = is_iterator_of<it_t, value_t...>::value;
template<typename it_t>
constexpr bool is_any_iterator_v = is_iterator_of_v<it_t, char, char8s_t, char16_t, char32_t, wchar_t>;

////////////////////////////////////////////////////////////////////////////////////////////////////
// is_const_iterator_of
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename it_t, typename... value_t>
struct is_const_iterator_of {
    using it_value_t = typename std::iterator_traits<it_t>::value_type;

    static constexpr bool value = is_any_of_v<it_value_t, value_t...>;
};

template<typename it_t, typename... value_t>
constexpr bool is_const_iterator_of_v = is_const_iterator_of<it_t, value_t...>::value;
template<typename it_t>
constexpr bool is_any_const_iterator_v = is_const_iterator_of_v<it_t, char, wchar_t, char8s_t, char16_t, char32_t>;

////////////////////////////////////////////////////////////////////////////////////////////////////
// is_char_array_v
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename type_t>
constexpr bool is_char_array_v = false;
template<typename char_t, uint_t size>
constexpr bool is_char_array_v<char_t (&)[size]> = is_any_char_v<char_t>;
template<typename char_t, uint_t size>
constexpr bool is_char_array_v<char_t[size]> = is_any_char_v<char_t>;

////////////////////////////////////////////////////////////////////////////////////////////////////
// is_native_string_v
////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename type_t>
constexpr bool is_native_string_v = is_char_array_v<type_t>;
template<typename char_t>
constexpr bool is_native_string_v<const char_t*> = is_any_char_v<char_t>;
template<typename char_t>
constexpr bool is_native_string_v<char_t*> = is_any_char_v<char_t>;



////////////////////////////////////////////////////////////////////////////////////////////////////
// standalone routines
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char, char8s_t>, int> = 0>
constexpr it_t code_point_next(it_t it) noexcept;
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char16_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int> = 0>
constexpr it_t code_point_next(it_t it) noexcept;
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char32_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int> = 0>
constexpr it_t code_point_next(it_t it) noexcept;

template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char, char8s_t>, int> = 0>
constexpr uint_t code_point_read(it_t it) noexcept;
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char16_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int> = 0>
constexpr uint_t code_point_read(it_t it) noexcept;
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char32_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int> = 0>
constexpr uint_t code_point_read(it_t it) noexcept;

template<typename it_t, std::enable_if_t<is_iterator_of_v<it_t, char, char8s_t>, int> = 0>
constexpr it_t code_point_write(it_t it, uint_t cp) noexcept;
template<typename it_t, std::enable_if_t<is_iterator_of_v<it_t, char16_t> || (is_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int> = 0>
constexpr it_t code_point_write(it_t it, uint_t cp) noexcept;
template<typename it_t, std::enable_if_t<is_iterator_of_v<it_t, char32_t> || (is_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int> = 0>
constexpr it_t code_point_write(it_t it, uint_t cp) noexcept;

template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int> = 0>
constexpr uint_t code_point_count(it_t it, const it_t last) noexcept;
template<typename type_t>
constexpr auto code_point_count(const type_t& str) noexcept -> decltype(std::cbegin(str), std::cend(str), uint_t());

template<typename in_t, typename out_t, std::enable_if_t<is_any_const_iterator_v<in_t>, int> = 0, std::enable_if_t<is_any_iterator_v<out_t>, int> = 0>
constexpr out_t code_point_convert(in_t src, const in_t last, out_t dst) noexcept;

template<typename char_t, std::enable_if_t<std::is_same_v<char_t, char> || std::is_same_v<char_t, char8s_t>, int> = 0>
constexpr uint_t code_unit_count(uint_t cp) noexcept;
template<typename char_t, std::enable_if_t<std::is_same_v<char_t, char16_t> || (std::is_same_v<char_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int> = 0>
constexpr uint_t code_unit_count(uint_t cp) noexcept;
template<typename char_t, std::enable_if_t<std::is_same_v<char_t, char32_t> || (std::is_same_v<char_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int> = 0>
constexpr uint_t code_unit_count(uint_t cp) noexcept;
template<typename char_t, typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int> = 0>
constexpr uint_t code_unit_count(it_t it, const it_t last) noexcept;
template<typename char_t, typename type_t>
constexpr auto code_unit_count(const type_t& str) noexcept -> decltype(std::cbegin(str), std::cend(str), uint_t());



////////////////////////////////////////////////////////////////////////////////////////////////////
// implementation stuff
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace impl
{
static constexpr uint64_t utf8_size_table = 0x3a55000000000000;
static constexpr uint_t utf8_mask_table = 0x070f1f7f;
static constexpr uint64_t utf16_size_table = 0x40000000000000;
static constexpr uint_t uft16_mask_table = 0x03ffffff;

} // namespace impl



////////////////////////////////////////////////////////////////////////////////////////////////////
// standalone routines
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char, char8s_t>, int>>
constexpr it_t code_point_next(it_t it) noexcept
{
    const uint_t ch = static_cast<char8s_t>(*it);
    const uint_t offset = ((impl::utf8_size_table >> ((ch >> 3) << 1)) & 0x3) + 1;

    return it + offset;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char16_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int>>
constexpr it_t code_point_next(it_t it) noexcept
{
    const uint_t ch = static_cast<char16_t>(*it);
    const uint_t offset = ((impl::utf16_size_table >> (ch >> 10)) & 0x1) + 1;

    return it + offset;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char32_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int>>
constexpr it_t code_point_next(it_t it) noexcept
{
    return it + 1;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char, char8s_t>, int>>
constexpr uint_t code_point_read(it_t it) noexcept
{
    const uint_t size = code_point_next(it) - it;
    const uint_t ch = static_cast<char8s_t>(*it++);

    uint_t cp = ch & ((impl::utf8_mask_table >> ((size - 1) << 3)) & 0xff);

    switch (size) {
    case 4:
        cp = (cp << 6) | (static_cast<char8s_t>(*it++) & 0x3f);
    case 3:
        cp = (cp << 6) | (static_cast<char8s_t>(*it++) & 0x3f);
    case 2:
        cp = (cp << 6) | (static_cast<char8s_t>(*it++) & 0x3f);
    };

    return cp;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char16_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int>>
constexpr uint_t code_point_read(it_t it) noexcept
{
    const uint_t size = code_point_next(it) - it;
    const uint_t ch = static_cast<char16_t>(*it++);

    uint_t cp = ch & ((impl::uft16_mask_table >> ((size - 1) << 4)) & 0xffff);

    if (size == 2)
        cp = 0x10000 + (cp << 10) | (static_cast<char16_t>(*it++) & 0x03ff);

    return cp;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char32_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int>>
constexpr uint_t code_point_read(it_t it) noexcept
{
    return static_cast<uint_t>(static_cast<char32_t>(*it++));
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_iterator_of_v<it_t, char, char8s_t>, int>>
constexpr it_t code_point_write(it_t it, uint_t cp) noexcept
{
    if (cp < 0x80) {
        *it++ = static_cast<char8s_t>(cp);
    } else if (cp < 0x800) {
        *it++ = static_cast<char8s_t>(0xc0 | (cp >> 6));
        *it++ = static_cast<char8s_t>(0x80 | (cp & 0x3f));
    } else if (cp < 0x10000) {
        *it++ = static_cast<char8s_t>(0xe0 | (cp >> 12));
        *it++ = static_cast<char8s_t>(0x80 | ((cp >> 6) & 0x3f));
        *it++ = static_cast<char8s_t>(0x80 | (cp & 0x3f));
    } else if (cp < 0x110000) {
        *it++ = static_cast<char8s_t>(0xf0 | (cp >> 18));
        *it++ = static_cast<char8s_t>(0x80 | ((cp >> 12) & 0x3f));
        *it++ = static_cast<char8s_t>(0x80 | ((cp >> 6) & 0x3f));
        *it++ = static_cast<char8s_t>(0x80 | (cp & 0x3f));
    }

    return it;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_iterator_of_v<it_t, char16_t> || (is_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int>>
constexpr it_t code_point_write(it_t it, uint_t cp) noexcept
{
    if (cp < 0x10000)
        *it++ = static_cast<char16_t>(cp);
    else if (cp < 0x110000) {
        *it++ = static_cast<char16_t>(0xd800 | ((cp - 0x10000) >> 10));
        *it++ = static_cast<char16_t>(0xdc00 | ((cp - 0x10000) & 0x3ff));
    }

    return it;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_iterator_of_v<it_t, char32_t> || (is_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int>>
constexpr it_t code_point_write(it_t it, uint_t cp) noexcept
{
    *it++ = static_cast<char32_t>(cp);

    return it;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int>>
constexpr uint_t code_point_count(it_t it, const it_t last) noexcept
{
    uint_t count = 0;

    while (it != last) {

        it = code_point_next(it);
        ++count;
    }

    return count;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename type_t>
constexpr auto code_point_count(const type_t& str) noexcept -> decltype(std::cbegin(str), std::cend(str), uint_t())
{
    const auto beg = std::cbegin(str);
    auto end = std::cend(str);

    if constexpr (is_native_string_v<type_t>)
        --end;
    
    return code_point_count(beg, end);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename in_t, typename out_t, std::enable_if_t<is_any_const_iterator_v<in_t>, int>, std::enable_if_t<is_any_iterator_v<out_t>, int>>
constexpr out_t code_point_convert(in_t src, const in_t last, out_t dst) noexcept
{
    for (; src != last; src = code_point_next(src))
        dst = code_point_write(dst, code_point_read(src));

    return dst;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t, std::enable_if_t<std::is_same_v<char_t, char> || std::is_same_v<char_t, char8s_t>, int>>
constexpr uint_t code_unit_count(uint_t cp) noexcept
{
    if (cp < 0x80)
        return 1;
    if (cp < 0x800)
        return 2;
    if (cp < 0x10000)
        return 3;

    return 4;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t, std::enable_if_t<std::is_same_v<char_t, char16_t> || (std::is_same_v<char_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int>>
constexpr uint_t code_unit_count(uint_t cp) noexcept
{
    return cp < 0x10000 ? 1 : 2;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t, std::enable_if_t<std::is_same_v<char_t, char32_t> || (std::is_same_v<char_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int>>
constexpr uint_t code_unit_count(uint_t /*cp*/) noexcept
{
    return 1;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t, typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int>>
constexpr uint_t code_unit_count(it_t it, const it_t last) noexcept
{
    if constexpr (sizeof(typename std::iterator_traits<it_t>::value_type) == sizeof(char_t)) {

        return std::distance(it, last);

    } else {

        uint_t count = 0;

        while (it != last) {

            count += code_unit_count<char_t>(code_point_read(it));
            it = code_point_next(it);
        }

        return count;
    }
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t, typename type_t>
constexpr auto code_unit_count(const type_t& str) noexcept -> decltype(std::cbegin(str), std::cend(str), uint_t())
{
    const auto beg = std::cbegin(str);
    auto end = std::cend(str);

    if constexpr (is_native_string_v<type_t>)
        --end;
    
    return code_unit_count<char_t>(beg, end);
}

} // namespace sutf

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of utf_codepoint.h
////////////////////////////////////////////////////////////////////////////////////////////////////
