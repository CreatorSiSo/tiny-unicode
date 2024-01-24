#pragma once

#include <cstddef>
#include <cstdint>
#include <span>

#include "string.hpp"

namespace tiny_unicode {

using std::span;

struct Str {
    Str(String& string);

    auto as_bytes() const -> span<const uint8_t>;

   private:
    span<uint8_t> m_data;
};

}  // namespace tiny_unicode
