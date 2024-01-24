#include "string.hpp"

#include <cstring>

namespace tiny_unicode {

String::String(vector<uint8_t> bytes) : m_data(bytes) {}

auto String::from_utf8(vector<uint8_t>&& bytes) -> std::optional<String> {
    // TODO Validate bytes
    return String(bytes);
}

auto String::from_utf8_lossy(span<uint8_t> bytes) -> String {
    // TODO Validate bytes
    return String(vector<uint8_t>(bytes.begin(), bytes.end()));
}

auto String::as_bytes() const -> span<const uint8_t> { return m_data; }

auto String::as_bytes_mut_unsafe() -> vector<uint8_t>& { return m_data; }

}  // namespace tiny_unicode
