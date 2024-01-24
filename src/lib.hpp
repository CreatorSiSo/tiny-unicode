#pragma once

#include <cstdint>
#include <format>
#include <ostream>
#include <vector>

#include "char.hpp"
#include "str.hpp"
#include "string.hpp"

namespace tiny_unicode {

template <typename... Args>
auto write(std::ostream& out, std::format_string<Args&...> fmt, Args&&... args)
    -> std::ostream& {
    return out << std::format(fmt, args...);
}

template <typename... Args>
auto write(std::ostream& out, String string) -> std::ostream& {
    auto bytes = string.as_bytes();
    out.write((char*)bytes.data(), bytes.size());
    return out;
}

template <typename... Args>
auto write(std::ostream& out, Str str) -> std::ostream& {
    auto bytes = str.as_bytes();
    out.write((char*)bytes.data(), bytes.size());
    return out;
}

}  // namespace tiny_unicode
