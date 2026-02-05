#include <bitset>
#include <cstdint>
#include <iostream>

int main() {
    [[maybe_unused]] constexpr std::uint8_t option_viewed { 0x01 };
    [[maybe_unused]] constexpr std::uint8_t option_edited { 0x02 };
    [[maybe_unused]] constexpr std::uint8_t option_favorited { 0x04 };
    [[maybe_unused]] constexpr std::uint8_t option_shared { 0x08 };
    [[maybe_unused]] constexpr std::uint8_t option_deleted { 0x10 };

    std::uint8_t my_article_flags { option_favorited };

    my_article_flags |= option_viewed;

    std::cout << std::boolalpha << "Was deleted? "
              << static_cast<bool>(my_article_flags & option_deleted) << "\n";

    my_article_flags &= ~option_favorited;

    std::cout << std::bitset<8> { my_article_flags } << '\n';

    return 0;
}