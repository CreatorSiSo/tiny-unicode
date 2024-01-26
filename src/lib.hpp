#pragma once

#include <format>
#include <iostream>
#include <vector>

#include "char.hpp"
#include "str.hpp"
#include "string.hpp"

template <>
struct std::formatter<tiny_unicode::Char> {
    template <class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <class FmtContext>
    FmtContext::iterator format(tiny_unicode::Char chr, FmtContext& ctx) const {
        std::array<uint8_t, 4> buffer = {0, 0, 0, 0};
        auto length = chr.encode_utf8(buffer);
        // SAFETY: encode_utf8 writes valid UTF-8 data into buffer, creating Str
        // only from bytes that were written to
        auto str = tiny_unicode::Str::from_bytes_unsafe(
            std::span(buffer.data(), length));
        return std::format_to(ctx.out(), "{}", str);
    }
};

// TODO Use reference
template <>
struct std::formatter<tiny_unicode::String> {
    template <class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <class FmtContext>
    FmtContext::iterator format(tiny_unicode::String string,
                                FmtContext& ctx) const {
        return std::format_to(ctx.out(), "{}", tiny_unicode::Str(string));
    }
};

template <>
struct std::formatter<tiny_unicode::Str> {
    template <class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <class FmtContext>
    FmtContext::iterator format(tiny_unicode::Str str, FmtContext& ctx) const {
        // auto bytes = str.as_bytes();
        // // SAFETY: Library only compiles if sizeof(char) == sizeof(uint8_t)
        // return std::format_to(
        //     ctx.out(), "{}",
        //     std::string_view(reinterpret_cast<const char*>(bytes.data()),
        //                      bytes.size()));
        for (uint8_t byte : str.as_bytes()) {
            // TODO What if char is signed
            // SAFETY: Library only compiles if sizeof(char) == sizeof(uint8_t)
            std::format_to(ctx.out(), "{}", (char)byte);
        }
        return ctx.out();
    }
};

namespace tiny_unicode {

template <typename... Args>
auto write(std::ostream& out, std::format_string<Args&...> fmt, Args&&... args)
    -> std::ostream& {
    return out << std::format(fmt, args...);
}

template <typename... Args>
auto write(std::ostream& out, const String& string) -> std::ostream& {
    return out << std::format("{}", string);
}

template <typename... Args>
auto write(std::ostream& out, Str str) -> std::ostream& {
    for (uint8_t byte : str.as_bytes()) {
        // SAFETY: Library only compiles if sizeof(char) == sizeof(uint8_t)
        out << (char)byte;
    }
    return out;
}

}  // namespace tiny_unicode
