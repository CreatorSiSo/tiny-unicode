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

    write(cout, "\n");

    // "© bar 𝌆 baz ☃ qux Foo"
    std::vector<uint8_t> bytes = {
        0xC2, 0xA9, 0x20, 0x62, 0x61, 0x72, 0x20, 0xF0, 0x9D,
        0x8C, 0x86, 0x20, 0x62, 0x61, 0x7A, 0x20, 0xE2, 0x98,
        0x83, 0x20, 0x71, 0x75, 0x78, 0x20, 0x46, 0x6F, 0x6F,
    };
    String test_string = String::from_utf8_lossy(bytes);
    Str test_str = Str(test_string);

    write(cout, test_string) << "\n";
    write(cout, test_str) << "\n";

    // write(cout, "\n");

    // for (uint8_t byte : bytes) {
    //     write(cout, "[{:08b}]: {}\n", byte, (uint8_t)utf8_byte_kind(byte));
    // }
}
