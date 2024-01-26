#include "str.hpp"

namespace tiny_unicode {

using std::span;

// SAFETY: `Str` implements the same operations as `String`
Str::Str(String& string) : m_data(string.as_bytes_mut_unsafe()) {}

Str::Str(std::span<uint8_t> data) : m_data(data) {}

auto Str::from_bytes_unsafe(std::span<uint8_t> bytes) -> Str {
    return Str(bytes);
}

auto Str::as_bytes() const -> span<const uint8_t> { return m_data; }

}  // namespace tiny_unicode
