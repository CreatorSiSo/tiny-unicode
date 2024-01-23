#include <format>
#include <iostream>

#include "../src/lib.hpp"

using tiny_unicode::Char;
using tiny_unicode::CHAR_MAX;
using tiny_unicode::CHAR_MIN;
using tiny_unicode::CHAR_REPLACEMENT;

int main() {
    std::cout << std::format(
        "Char Min: {}, {:08x}\nChar Max: {}, {:08x}\nChar Replacement: {}, "
        "{:08x}\n",
        CHAR_MIN, (uint32_t)CHAR_MIN, CHAR_MAX, (uint32_t)CHAR_MAX,
        CHAR_REPLACEMENT, (uint32_t)CHAR_REPLACEMENT);

    std::cout << std::endl;

    const Char chars[4] = {Char::from_ascii('t'), Char::from_ascii('e'),
                           Char::from_ascii('s'), Char::from_ascii('t')};
    for (auto chr : chars) {
        std::cout << std::format("{}, {:08x}\n", chr, (uint32_t)chr);
    }

    std::cout << std::endl;

    Char literal_a = 'a'_Char;
    Char literal_b = Char::from_ascii('b');
    std::cout << std::format("{}, {}\n", literal_a, literal_b);
}
