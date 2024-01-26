#pragma once

#include <cstddef>
#include <cstdint>
#include <span>

#include "string.hpp"

namespace tiny_unicode {

struct Str {
    Str(String& string);

    /// UNSAFE: Bytes have to be valid UTF-8.
    static auto from_bytes_unsafe(std::span<uint8_t> bytes) -> Str;

    auto as_bytes() const -> std::span<const uint8_t>;

   private:
    /// UNSAFE: Bytes have to be valid UTF-8.
    Str(std::span<uint8_t> data);

    std::span<uint8_t> m_data;
};

}  // namespace tiny_unicode
