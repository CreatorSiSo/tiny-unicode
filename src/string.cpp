#include "string.hpp"

#include <cstring>

namespace tiny_unicode {

enum class ByteKind {
    Invalid = 0,
    One = 1,
    Two = 2,
    Three = 3,
    Four = 4,
    Follow = 5,
};

static constexpr auto utf8_byte_kind(uint8_t byte) -> ByteKind {
    // First bit is zero
    if ((byte >> 7) == 0b0) {
        return ByteKind::One;
    }

    // First bit is one and second bit is zero
    if ((byte >> 6) == 0b10) {
        return ByteKind::Follow;
    }

    // First two bits are one and third bit is zero
    if ((byte >> 5) == 0b110) {
        return ByteKind::Two;
    }

    // First three bits are one and fourth bit is zero
    if ((byte >> 4) == 0b1110) {
        return ByteKind::Three;
    }

    // First four bits are one and the fifth is zero
    if ((byte >> 3) == 0b11110) {
        return ByteKind::Four;
    }

    return ByteKind::Invalid;
}

auto String::from_utf8(vector<uint8_t>&& bytes) -> std::optional<String> {
    for (uint8_t byte : bytes) {
        if (utf8_byte_kind(byte) == ByteKind::Invalid) return {};
    }
    return String(std::move(bytes));
}

auto String::from_utf8_lossy(span<uint8_t> bytes) -> String {
    // UTF-8 bytes for the replacement character U+FFFD
    constexpr std::array<uint8_t, 3> replacement = {0xEF, 0xBF, 0xBD};

    vector<uint8_t> copied(bytes.size_bytes());
    for (uint8_t byte : bytes) {
        if (utf8_byte_kind(byte) == ByteKind::Invalid)
            copied.insert(copied.end(), replacement.begin(), replacement.end());
        else
            copied.push_back(byte);
    }

    return String(std::move(copied));
}

auto String::as_bytes() const -> span<const uint8_t> { return m_data; }

auto String::as_bytes_mut_unsafe() -> vector<uint8_t>& { return m_data; }

String::String(vector<uint8_t>&& bytes) : m_data(bytes) {}

}  // namespace tiny_unicode
