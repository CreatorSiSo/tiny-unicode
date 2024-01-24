#include "str.hpp"

namespace tiny_unicode {

// SAFETY: `Str` implements the same operations as `String`
Str::Str(String& string) : m_data(string.as_bytes_mut_unsafe()) {}

auto Str::as_bytes() const -> span<const uint8_t> { return m_data; }

}  // namespace tiny_unicode
