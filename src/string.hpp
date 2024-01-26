#pragma once

#include <cstdint>
#include <optional>
#include <span>
#include <vector>

namespace tiny_unicode {

struct String {
    static auto from_utf8(std::vector<uint8_t>&& bytes)
        -> std::optional<String>;
    static auto from_utf8_lossy(std::span<uint8_t> bytes) -> String;

    auto as_bytes() const -> std::span<const uint8_t>;

    /// UNSAFE: The underlying bytes must always represent valid UTF-8
    auto as_bytes_mut_unsafe() -> std::vector<uint8_t>&;

   private:
    /// UNSAFE: bytes must be valid UTF-8
    String(std::vector<uint8_t>&& bytes);

    std::vector<uint8_t> m_data;
};

}  // namespace tiny_unicode
