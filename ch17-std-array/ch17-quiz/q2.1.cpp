#include <array>
#include <iostream>

namespace Potion {
    enum Type { healing, mana, speed, invisibility, max_potion };
    constexpr std::array types { healing, mana, speed, invisibility };
    constexpr std::array costs { 20, 30, 12, 50 };
    constexpr std::array<std::string_view, max_potion> names { "healing",
                                                               "mana", "speed",
                                                               "invisibility" };
    static_assert(std::size(types) == max_potion);
    static_assert(std::size(costs) == max_potion);
    static_assert(std::size(names) == max_potion);
} // namespace Potion

void shop() {
    std::cout << "Here is our selection for today:\n";
    for (const auto &potion : Potion::types) {
        std::cout << potion << ") " << Potion::names[potion] << " costs "
                  << Potion::costs[potion] << "\n";
    }
}

int main() {
    shop();
    return 0;
}