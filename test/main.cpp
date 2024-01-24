#include <format>
#include <iostream>

#include "../src/lib.hpp"

using tiny_unicode::Char;
using tiny_unicode::CHAR_MAX;
using tiny_unicode::CHAR_MIN;
using tiny_unicode::CHAR_REPLACEMENT;
using tiny_unicode::Str;
using tiny_unicode::String;
using tiny_unicode::write;

int main() {
    std::ostream& cout = std::cout;

    write(cout,
          "Char Min: {}, {:08x}\nChar Max: {}, {:08x}\nChar Replacement: {}, "
          "{:08x}\n",
          CHAR_MIN, (uint32_t)CHAR_MIN, CHAR_MAX, (uint32_t)CHAR_MAX,
          CHAR_REPLACEMENT, (uint32_t)CHAR_REPLACEMENT);

    write(cout, "\n");

    const Char chars[4] = {Char::from_ascii('t'), Char::from_ascii('e'),
                           Char::from_ascii('s'), Char::from_ascii('t')};
    for (auto chr : chars) {
        write(cout, "{}, {:08x}\n", chr, (uint32_t)chr);
    }

    write(cout, "\n");

    Char literal_a = 'a'_Char;
    Char literal_b = Char::from_ascii('b');
    write(cout, "{}, {}\n", literal_a, literal_b);

    // "test"
    std::vector<uint8_t> bytes = {84, 101, 115, 116};
    String test_string = String::from_utf8_lossy(bytes);
    Str test_str = Str(test_string);

    write(cout, test_string) << "\n";
    write(cout, test_str) << "\n";
}
