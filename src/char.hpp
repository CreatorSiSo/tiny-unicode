#pragma once

#include <cstdint>
#include <format>
#include <optional>
#include <vector>

namespace tiny_unicode {

/**
 * @brief A unicode scalar value.
 * @link https://www.unicode.org/glossary/#unicode_scalar_value
 */
struct Char {
    /**
     * @brief Converts a `uint32_t` to a `Char`.
     *
     * Note that all `Char`s are valid `uint32_t`s, and can be cast to one.
     * However, the reverse is not true: not all valid `uint32_t`s are valid
     * `Char`s. `from_uint32()` will return an empty `std::optional` if the
     * input is not a valid value for a `Char`.
     */
    [[nodiscard]]
    static constexpr auto from_uint32(uint32_t value) -> std::optional<Char> {
        const bool in_first_range = (value >= 0) && (value <= 0xD7FF);
        const bool in_second_range = (value >= 0xE000) && (value <= 0x10FFFF);

        if (in_first_range || in_second_range)
            return Char(value);
        else
            return {};
    }

    [[nodiscard]]
    static constexpr auto from_ascii(char chr) -> Char {
        return Char(chr);
    }

    /**
     * @brief Checks if the `Char` is within the ASCII range.
     */
    constexpr auto is_ascii() const -> bool { return m_data <= 0x7F; }

    [[nodiscard]]
    constexpr auto as_ascii() const -> std::optional<char> {
        if (is_ascii())
            return (char)m_data;
        else
            return {};
    }

    /**
     * @brief
     * @param buf
     * @return Length of the encoded data in bytes (1..4)
     */
    constexpr auto encode_utf8(std::span<uint8_t> buf) const -> size_t {
        if (is_ascii()) buf[0] = m_data;
        return 1;
    }

    /**
     * @brief Converts a `uint32_t` to a `Char`.
     *
     * All `Char`s are valid `uint32_t`s, and can be cast to one.
     */
    [[nodiscard]] constexpr explicit operator uint32_t() const {
        return m_data;
    }

   private:
    [[nodiscard]] constexpr Char(uint32_t value) : m_data(value) {}

    uint32_t m_data;
};

/**
 * @brief The smallest valid code point a `Char` can have, `0x0`.
 */
constexpr Char CHAR_MIN = Char::from_ascii('\0');

/**
 * @brief The highest valid code point a `Char` can have, `0x10FFFF`.
 */
constexpr Char CHAR_MAX = Char::from_uint32(0x10FFFF).value();

/**
 * @brief `U+FFFD REPLACEMENT CHARACTER` (�) is used in Unicode to represent a
 * decoding error.
 */
constexpr Char CHAR_REPLACEMENT = Char::from_uint32(0xFFFD).value();

}  // namespace tiny_unicode

constexpr tiny_unicode::Char operator""_Char(const char literal) {
    return tiny_unicode::Char::from_ascii(literal);
}

constexpr tiny_unicode::Char operator""_Char(const char8_t literal) {
    if (const auto chr = tiny_unicode::Char::from_uint32(literal);
        chr.has_value()) {
        return *chr;
    } else {
        throw "Unreabable, compiler only passes valid unicode scalar values.";
    }
}

constexpr tiny_unicode::Char operator""_Char(const char16_t literal) {
    if (const auto chr = tiny_unicode::Char::from_uint32(literal);
        chr.has_value()) {
        return *chr;
    } else {
        throw "Unreabable, compiler only passes valid unicode scalar values.";
    }
}

constexpr tiny_unicode::Char operator""_Char(const char32_t literal) {
    if (const auto chr = tiny_unicode::Char::from_uint32(literal);
        chr.has_value()) {
        return *chr;
    } else {
        throw "Unreabable, compiler only passes valid unicode scalar values.";
    }
}
