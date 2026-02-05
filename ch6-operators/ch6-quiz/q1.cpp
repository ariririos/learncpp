#include <iostream>
#include <string_view>

std::string_view get_quantity_phrase(int quantity) {
    if (quantity < 0) {
        return "negative";
    } else if (quantity == 0) {
        return "no";
    } else if (quantity == 1) {
        return "a single";
    } else if (quantity == 2) {
        return "a couple of";
    } else if (quantity == 3) {
        return "a few";
    } else {
        return "many";
    }
}

std::string_view get_apples_pluralized(int quantity) {
    return quantity == 1 ? "apple" : "apples";
}

int main() {
    constexpr int maryApples { 3 };
    std::cout << "Mary has " << get_quantity_phrase(maryApples) << ' '
              << get_apples_pluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples {};
    std::cin >> numApples;

    std::cout << "You have " << get_quantity_phrase(numApples) << ' '
              << get_apples_pluralized(numApples) << ".\n";

    return 0;
}