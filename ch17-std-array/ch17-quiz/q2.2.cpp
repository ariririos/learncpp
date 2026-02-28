#include "../../Random.h"
#include <array>
#include <iostream>
#include <vector>

namespace Constants {
    constexpr int min_init_gold { 80 };
    constexpr int max_init_gold { 120 };
} // namespace Constants

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

class Player {
private:
    std::string m_name {};
    std::array<int, Potion::max_potion> m_inventory {};
    int m_gold {};
    int randomize_gold() {
        return Random::get(Constants::min_init_gold, Constants::max_init_gold);
    }

public:
    Player(std::string_view name)
        : m_name { name }, m_gold { randomize_gold() } {}
    int gold() const { return m_gold; }
};

std::string get_name() {
    std::string name {};
    std::cout << "Enter your name: ";
    std::getline(std::cin >> std::ws, name);
    return name;
}

int main() {
    std::cout << "Welcome to Roscoe's potion emporium!\n";
    std::string player_name { get_name() };
    Player player { player_name };

    std::cout << "Hello, " << player_name << ", you have " << player.gold()
              << " gold.\n\n";

    shop();

    std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";
    return 0;
}