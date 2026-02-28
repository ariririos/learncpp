#include <ios>
#include <iostream>
#include <limits>

namespace Constants {
    constexpr int squares[] { 0, 1, 4, 9 };
}

bool find_square(int input) {
    for (const auto i : Constants::squares) {
        if (i == input) {
            return true;
        }
    }
    return false;
}

int main() {
    int input {};
    while (true) {
        std::cout << "Enter a single digit integer, or -1 to quit: ";
        std::cin >> input;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (input == -1) {
            break;
        }
        if (find_square(input)) {
            std::cout << input << " is a perfect square\n";
        } else {
            std::cout << input << " is not a perfect square\n";
        }
    }

    std::cout << "Bye\n";

    return 0;
}