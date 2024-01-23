#pragma once

#include <cstdint>
#include <vector>

#include "char.hpp"

namespace tiny_unicode {

struct String {
   private:
    std::vector<uint8_t> m_data;
};

}  // namespace tiny_unicode
