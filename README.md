# SUTFCPP
# Simple UTF library for C++
SUTFCPP is а C++ header-only library that fills the C++17 standard gap in support for Unicode strings. The standard doesn't give us any helpers for converting strings of different widths to each other, as well as any tool for iterating by code points. The library was created to work exclusively with Unicode, without support for other encodings. Also, the library does not check the consistency of string buffers, it always assumes that strings are encoded correctly in terms of the Unicode standard.
The main features:
* easy to use: the library is header-only
* small: consists of few header files, there is no dependencies
* cross-platform: supports MSVC, GCC and CLANG C++17 compilers
* has compile time support

The library implements two level APIs:
* Low level API for codepoint and codeunit manipulations
```c++
namespace sutf
{
// get iterator to next codepoint
constexpr it_t codepoint_next(it_t it) noexcept;

// read codepoint in current position
constexpr uint_t codepoint_read(it_t it) noexcept;

// write codepoint in current position and return position of next codepoint
constexpr it_t codepoint_write(it_t it, uint_t cp) noexcept;

// calculate number of codepoints between two iterators
constexpr uint_t codepoint_count(it_t it, const it_t last) noexcept;

// calculate number of codepoints in specified buffer 
constexpr uint_t codepoint_count(const type_t& str) noexcept;

// convert codepoints on 'in' type to 'out' type.
constexpr out_t codepoint_convert(in_t src, const in_t last, out_t dst) noexcept;

// count how many codeunits occupies a given codepoint
constexpr uint_t codeunit_count<codeuint_t>(uint_t cp) noexcept;

// count how many codeunits occupies a given codepoint range
constexpr uint_t codeunit_count<codeuint_t>(it_t it, const it_t last) noexcept;

// count how many codeunits occupies a given buffer 
constexpr uint_t codeunit_count<codeuint_t>(const type_t& str) noexcept
} // namespace sutf
```
* High level API for strings and buffers
```c++
namespace sutf
{
// convert string of any type to UTF8 string
string to_string(const string_t& str);

// convert string of any type to UTF16/UTF32 string (platform specific)
wstring to_wstring(const string_t& str);

// convert string of any type to UTF8 string
u8string to_u8string(const string_t& str);

// convert string of any type to UTF16 string
u16string to_u16string(const string_t& str);

// convert string of any type to UTF32 string
u32string to_u32string(const string_t& str);

// convert codeunit buffer of 'src' type to codeunit buffer of 'dst' type
uint_t convert(const src_t& src, dst_t& dst);

} // namespace sutf
```
## Implementation
* [utf_codepoint.h](include/sutfcpplib/utf_codepoint.h) - lov level UTF support
* [utf_string.h](include/sutfcpplib/utf_string.h) - high level UTF support
## Integration
```c++
#include <sutfcpplib/utf_codepoint.h>  // Include only codeunit and codepoint support
// or
#include <slimcpplib/utf_string.h> // Include full UTF support

using namespace std::literals;
```
## String literal declarations:
```c++
// Define Unicode literal 'A©←😂B®✅🥳'':
auto str_utf8 = u8"\U00000041\U000000a9\U00002190\U0001f602\U00000042\U000000ae\U00002705\U0001f973"sv; // UTF-8 string 
auto str_utf16_or_utf32 = L"\U00000041\U000000a9\U00002190\U0001f602\U00000042\U000000ae\U00002705\U0001f973"sv; // UTF-16/UTF-32 string
auto str_utf16 = u"\U00000041\U000000a9\U00002190\U0001f602\U00000042\U000000ae\U00002705\U0001f973"sv; // UTF-16 string
auto str_utf32 = U"\U00000041\U000000a9\U00002190\U0001f602\U00000042\U000000ae\U00002705\U0001f973"sv; // UTF-32 string
```
## Limitations
* Although all methods and functions are defined using the constexpr qualifier, due to the limitations of C++ 17, working completely at compile time is only possible for code without instrinsics, since there is no implementation of [std::is_constant_evaluated()](https://en.cppreference.com/w/cpp/types/is_constant_evaluated) in the standard before C++ 20.
* The design of long integers tries to completely repeat the behavior of native integers, but still differs. For example, the propagation of integer types always occurs from a signed integer to an unsigned integer, and an implicit conversion from a larger integer to a smaller integer does not cause a warning, but a compilation error.
* Location of digits always corresponds to little-endian, regardless of the platform, which should be taken into account when serialization/deserialization. The digits themselves are always in platform natural order.
## Examples
[main.cpp](examples/main.cpp) - examples of using the main interface of the library with comments.
