#include "../../Random.h"
#include <array>
#include <ios>
#include <iostream>
#include <limits>
#include <vector>

int char_num_to_int(char c) { return c - '0'; }

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
    int inventory(Potion::Type type) const { return m_inventory[type]; }
    bool attempt_buy(Potion::Type type) {
        if (m_gold >= Potion::costs[type]) {
            m_inventory[type]++;
            m_gold -= Potion::costs[type];
            return true;
        } else {
            return false;
        }
    }
};

std::string get_name() {
    std::string name {};
    std::cout << "Enter your name: ";
    std::getline(std::cin >> std::ws, name);
    return name;
}

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Potion::Type get_potion() {
    std::cout
        << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
    constexpr std::string_view error_text {
        "That is an invalid input. Try again: "
    };
    while (true) {
        char in {};
        std::cin >> in;
        if (!std::cin) {
            std::cin.clear();
            ignore_line();
            if (std::cin.eof()) {
                std::cout << "Bye!\n";
                std::exit(0);
            }
            std::cout << error_text;
            continue;
        }
        if (!std::cin.eof() &&
            std::cin.peek() != '\n') { // if any unextracted input
            std::cout << error_text;
            ignore_line();
            continue;
        }
        if (in == 'q') {
            return Potion::max_potion; // sentinel
        }
        int potion_num { char_num_to_int(in) };
        if (potion_num < 0 || potion_num > Potion::max_potion) {
            std::cout << error_text;
            ignore_line();
            continue;
        }
        return static_cast<Potion::Type>(potion_num);
    }
}

void print_inventory(const Player &player) {
    std::cout << "\nYour inventory contains:\n";
    for (auto &potion : Potion::types) {
        int num_potion { player.inventory(potion) };
        if (num_potion > 0) {
            std::cout << num_potion << "x of " << Potion::names[potion] << "\n";
        }
    }
    std::cout << "You escaped with " << player.gold() << " gold remaining.\n";
}

void shop_loop(Player &player) {
    while (true) {
        std::cout << "Here is our selection for today:\n";
        for (auto &potion : Potion::types) {
            std::cout << potion << ") " << Potion::names[potion] << " costs "
                      << Potion::costs[potion] << "\n";
        }
        Potion::Type potion_bought { get_potion() };
        if (potion_bought == Potion::max_potion) {
            return;
        }
        if (player.attempt_buy(potion_bought)) {
            std::cout << "You purchased a potion of "
                      << Potion::names[potion_bought] << ". You have "
                      << player.gold() << " gold left.\n\n";
        } else {
            std::cout << "You can not afford that.\n\n";
        }
    }
}

int main() {
    std::cout << "Welcome to Roscoe's potion emporium!\n";
    std::string player_name { get_name() };
    Player player { player_name };

    std::cout << "Hello, " << player_name << ", you have " << player.gold()
              << " gold.\n\n";

    shop_loop(player);
    print_inventory(player);

    std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";
    return 0;
}