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
// is_iterator_of
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename it_t, typename... value_t>
struct is_iterator_of {

    using it_value_t = typename std::iterator_traits<it_t>::value_type;
    using it_reference_t = typename std::iterator_traits<it_t>::reference;

    template<typename it1_t>
    static constexpr bool is_non_const_v = std::is_same_v<
        std::remove_reference_t<it1_t>, std::remove_const_t<std::remove_reference_t<it1_t>>>;

    static constexpr bool value = std::disjunction_v<std::is_same<it_value_t, value_t>...> && is_non_const_v<it_t>;
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

    static constexpr bool value = std::disjunction_v<std::is_same<it_value_t, value_t>...>;
};

template<typename it_t, typename... value_t>
constexpr bool is_const_iterator_of_v = is_const_iterator_of<it_t, value_t...>::value;
template<typename it_t>
constexpr bool is_any_const_iterator_v = is_const_iterator_of_v<it_t, char, wchar_t, char8s_t, char16_t, char32_t>;



////////////////////////////////////////////////////////////////////////////////////////////////////
// standalone routines
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char, char8s_t>, int> = 0>
constexpr it_t codepoint_next(it_t it) noexcept;
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char16_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int> = 0>
constexpr it_t codepoint_next(it_t it) noexcept;
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char32_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int> = 0>
constexpr it_t codepoint_next(it_t it) noexcept;

template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char, char8s_t>, int> = 0>
constexpr uint_t codepoint_read(it_t it) noexcept;
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char16_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int> = 0>
constexpr uint_t codepoint_read(it_t it) noexcept;
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char32_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int> = 0>
constexpr uint_t codepoint_read(it_t it) noexcept;

template<typename it_t, std::enable_if_t<is_iterator_of_v<it_t, char, char8s_t>, int> = 0>
constexpr it_t codepoint_write(it_t it, uint_t cp) noexcept;
template<typename it_t, std::enable_if_t<is_iterator_of_v<it_t, char16_t> || (is_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int> = 0>
constexpr it_t codepoint_write(it_t it, uint_t cp) noexcept;
template<typename it_t, std::enable_if_t<is_iterator_of_v<it_t, char32_t> || (is_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int> = 0>
constexpr it_t codepoint_write(it_t it, uint_t cp) noexcept;

template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int> = 0>
constexpr uint_t codepoint_count(it_t it, const it_t last) noexcept;
template<typename type_t>
constexpr auto codepoint_count(const type_t& str) noexcept -> decltype(std::cbegin(str), std::cend(str), uint_t());

template<typename in_t, typename out_t, std::enable_if_t<is_any_const_iterator_v<in_t>, int> = 0, std::enable_if_t<is_any_iterator_v<out_t>, int> = 0>
constexpr out_t codepoint_convert(in_t src, const in_t last, out_t dst) noexcept;

template<typename char_t, std::enable_if_t<std::is_same_v<char_t, char> || std::is_same_v<char_t, char8s_t>, int> = 0>
constexpr uint_t codeunit_count(uint_t cp) noexcept;
template<typename char_t, std::enable_if_t<std::is_same_v<char_t, char16_t> || (std::is_same_v<char_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int> = 0>
constexpr uint_t codeunit_count(uint_t cp) noexcept;
template<typename char_t, std::enable_if_t<std::is_same_v<char_t, char32_t> || (std::is_same_v<char_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int> = 0>
constexpr uint_t codeunit_count(uint_t cp) noexcept;
template<typename char_t, typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int> = 0>
constexpr uint_t codeunit_count(it_t it, const it_t last) noexcept;
template<typename char_t, typename type_t>
constexpr auto codeunit_count(const type_t& str) noexcept -> decltype(std::cbegin(str), std::cend(str), uint_t());



////////////////////////////////////////////////////////////////////////////////////////////////////
// implementation stuff
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace impl
{
static constexpr char8s_t utf8_size_table[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 1
};

static constexpr char8s_t utf8_mask_table[] = {
    0x7f, 0x1f, 0x0f, 0x07
};

static constexpr char8s_t utf16_size_table[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

static constexpr uint16_t uft16_mask_table[] = {
    0xffff, 0x03ff
};

} // namespace impl

    

////////////////////////////////////////////////////////////////////////////////////////////////////
// standalone routines
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char, char8s_t>, int>>
constexpr it_t codepoint_next(it_t it) noexcept
{
    const uint_t ch = static_cast<char8s_t>(*it);
    const uint_t offset = impl::utf8_size_table[ch >> 3];

    return it + offset;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char16_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char16_t)), int>>
constexpr it_t codepoint_next(it_t it) noexcept
{
    const uint_t ch = static_cast<char16_t>(*it);
    const uint_t offset = impl::utf16_size_table[ch >> 10];

    return it + offset;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char32_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int>>
constexpr it_t codepoint_next(it_t it) noexcept
{
    return it + 1;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char, char8s_t>, int>>
constexpr uint_t codepoint_read(it_t it) noexcept
{
    const uint_t size = codepoint_next(it) - it;
    const uint_t ch = static_cast<char8s_t>(*it++);

    uint_t cp = ch & impl::utf8_mask_table[size - 1];

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
constexpr uint_t codepoint_read(it_t it) noexcept
{
    const uint_t size = codepoint_next(it) - it;
    const uint_t ch = static_cast<char16_t>(*it++);

    uint_t cp = ch & impl::uft16_mask_table[size - 1];

    if (size == 2)
        cp = 0x10000 + (cp << 10) | (static_cast<char16_t>(*it++) & 0x03ff);

    return cp;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_const_iterator_of_v<it_t, char32_t> || (is_const_iterator_of_v<it_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int>>
constexpr uint_t codepoint_read(it_t it) noexcept
{
    return static_cast<uint_t>(static_cast<char32_t>(*it++));
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_iterator_of_v<it_t, char, char8s_t>, int>>
constexpr it_t codepoint_write(it_t it, uint_t cp) noexcept
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
constexpr it_t codepoint_write(it_t it, uint_t cp) noexcept
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
constexpr it_t codepoint_write(it_t it, uint_t cp) noexcept
{
    *it++ = static_cast<char32_t>(cp);

    return it;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int>>
constexpr uint_t codepoint_count(it_t it, const it_t last) noexcept
{
    uint_t count = 0;

    while (it != last) {

        it = codepoint_next(it);
        ++count;
    }

    return count;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename type_t>
constexpr auto codepoint_count(const type_t& str) noexcept -> decltype(std::cbegin(str), std::cend(str), uint_t())
{
    return codepoint_count(std::cbegin(str), std::cend(str));
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename in_t, typename out_t, std::enable_if_t<is_any_const_iterator_v<in_t>, int>, std::enable_if_t<is_any_iterator_v<out_t>, int>>
constexpr out_t codepoint_convert(in_t src, const in_t last, out_t dst) noexcept
{
    for (; src != last; src = codepoint_next(src))
        dst = codepoint_write(dst, codepoint_read(src));

    return dst;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t, std::enable_if_t<std::is_same_v<char_t, char> || std::is_same_v<char_t, char8s_t>, int>>
constexpr uint_t codeunit_count(uint_t cp) noexcept
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
constexpr uint_t codeunit_count(uint_t cp) noexcept
{
    return cp < 0x10000 ? 1 : 2;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t, std::enable_if_t<std::is_same_v<char_t, char32_t> || (std::is_same_v<char_t, wchar_t> && sizeof(wchar_t) == sizeof(char32_t)), int>>
constexpr uint_t codeunit_count(uint_t /*cp*/) noexcept
{
    return 1;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t, typename it_t, std::enable_if_t<is_any_const_iterator_v<it_t>, int>>
constexpr uint_t codeunit_count(it_t it, const it_t last) noexcept
{
    if constexpr (sizeof(typename std::iterator_traits<it_t>::value_type) == sizeof(char_t)) {

        return std::distance(it, last);

    } else {

        uint_t count = 0;

        while (it != last) {

            count += codeunit_count<char_t>(codepoint_read(it));
            it = codepoint_next(it);
        }

        return count;
    }
}



////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename char_t, typename type_t>
constexpr auto codeunit_count(const type_t& str) noexcept -> decltype(std::cbegin(str), std::cend(str), uint_t())
{
    return codeunit_count<char_t>(std::cbegin(str), std::cend(str));
}

} // namespace sutf

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of utf_codepoint.h
////////////////////////////////////////////////////////////////////////////////////////////////////
