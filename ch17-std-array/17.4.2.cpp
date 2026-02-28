#include <array>
#include <iostream>
#include <string_view>

struct Item {
    std::string_view name {};
    int gold {};
};

template <auto N> void print_items(const std::array<Item, N> &items) {
    for (const auto &item : items) {
        std::cout << "A " << item.name << " costs " << item.gold << " gold.\n";
    }
}

int main() {
    std::array<Item, 4> items {
        { { "sword", 5 }, { "dagger", 3 }, { "club", 2 }, { "spear", 7 } }
    };

    print_items(items);

    return 0;
}