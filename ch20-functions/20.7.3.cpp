#include "../Random.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>

void handle_input(int &i) {
    while (true) {
        std::cin >> i;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        break;
    }
}

std::vector<int> generate_squares(int start, int count, int multiplier) {
    std::vector<int> squares {};
    for (int i { 0 }; i < count; i++) {
        squares.push_back((start + i) * (start + i) * multiplier);
    }
    return squares;
}

void wrong_guess(std::vector<int> squares, int guess) {
    auto nearest { std::min_element(
        squares.begin(), squares.end(), [=](const auto &a, const auto &b) {
            return std::abs(a - guess) < std::abs(b - guess);
        }) };
    std::cout << guess << " is wrong! Try " << *nearest << " next time.\n";
}

void right_guess(std::vector<int> squares) {
    if (squares.size() > 0) {
        std::cout << "Nice! " << squares.size() << " number(s) left.\n";
        return;
    }
    std::cout << "Nice! You found all numbers, good job!\n";
}

void game_loop(std::vector<int> squares) {
    while (squares.size() > 0) {
        std::cout << "> ";
        int guess {};
        handle_input(guess);
        auto found { std::find(squares.begin(), squares.end(), guess) };
        if (found == squares.end()) {
            wrong_guess(squares, guess);
            break;
        }
        squares.erase(found);
        right_guess(squares);
    }
}

int main() {
    std::cout << "Start where? ";
    int start {};
    handle_input(start);
    std::cout << "How many? ";
    int count {};
    handle_input(count);
    int multiplier { Random::get(2, 4) };

    std::vector squares { generate_squares(start, count, multiplier) };
    std::cout << "I generated " << count
              << " square numbers. Do you know what each number is after "
                 "multiplying it by "
              << multiplier << "?\n";

    game_loop(squares);

    return 0;
}