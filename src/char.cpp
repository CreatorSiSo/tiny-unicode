#include "char.hpp"

namespace tiny_unicode {

// Tests

static_assert(sizeof(char) == sizeof(uint8_t));
static_assert(sizeof(Char) == sizeof(uint32_t));

// "\0"
constexpr auto valid_char = Char::from_uint32(0);
static_assert(valid_char.has_value() == true);
static_assert(valid_char.value().is_ascii() == true);
static_assert(valid_char.value().as_ascii() == '\0');

// Invalid
constexpr auto invalid_char = Char::from_uint32(0xD800);
static_assert(invalid_char.has_value() == false);

// "ༀ"
constexpr auto non_ascii_char = Char::from_uint32(0x0F00);
static_assert(non_ascii_char.has_value() == true);
static_assert(non_ascii_char.value().is_ascii() == false);
static_assert(non_ascii_char.value().as_ascii().has_value() == false);

// "a"
constexpr Char a_char = Char::from_ascii('a');
static_assert(a_char.is_ascii() == true);
static_assert(a_char.as_ascii() == std::make_optional('a'));
static_assert(a_char.as_ascii().value() == 97);
static_assert((uint32_t)a_char == 97);

// Literals

constexpr Char ascii_lit = 'f'_Char;
static_assert(ascii_lit.is_ascii() == true);
static_assert(ascii_lit.as_ascii().has_value() == true);

constexpr Char utf8_lit = u8'f'_Char;
static_assert(utf8_lit.is_ascii() == true);
static_assert(utf8_lit.as_ascii().has_value() == true);

constexpr Char utf16_lit = u'ༀ'_Char;
static_assert(utf16_lit.is_ascii() == false);
static_assert(utf16_lit.as_ascii().has_value() == false);

}  // namespace tiny_unicode
