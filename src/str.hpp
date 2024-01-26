#pragma once

#include <cstddef>
#include <cstdint>
#include <span>

#include "string.hpp"

namespace tiny_unicode {

struct Str {
    // SAFETY: `Str` implements the same operations as `String`
    constexpr Str(String& string) : m_data(string.as_bytes_mut_unsafe()) {}

    /// UNSAFE: Bytes have to be valid UTF-8.
    constexpr static auto from_bytes_unsafe(std::span<uint8_t> bytes) -> Str {
        return Str(bytes);
    }

    constexpr auto as_bytes() const -> std::span<const uint8_t> {
        return m_data;
    }

   private:
    /// UNSAFE: Bytes have to be valid UTF-8.
    constexpr Str(std::span<uint8_t> data) : m_data(data) {}

    std::span<uint8_t> m_data;
};

}  // namespace tiny_unicode
