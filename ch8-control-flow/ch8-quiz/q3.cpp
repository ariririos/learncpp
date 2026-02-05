#include "../../Random.h"
#include <iostream>

namespace Limits {
    constexpr int min = 1;
    constexpr int max = 100;
    constexpr int guesses = 7;
}

int get_guess(int i) {
    std::cout << "Guess #" << i <<": ";
    int input {};
    std::cin >> input;
    return input;
}

bool get_continue() {
    while (true) {
        std::cout << "Would you like to play again (y/n)?";
        char input {};
        std::cin >> input;
        if (input == 'y') {
            return true;
        }
        else if (input == 'n') {
            return false;
        }
    }
}

bool game_loop(int answer) {
    for (int i = 0; i < Limits::guesses; i++) {
        int guess = get_guess(i + 1);
        if (guess < answer) {
            std::cout << "Your guess is too low.\n";
        }
        else if (guess > answer) {
            std::cout << "Your guess is too high.\n";
        }
        else {
            std::cout << "Correct! You win!\n";
            return get_continue();
        }
    }
    std::cout << "Sorry, you lose. The correct number was " << answer << ".\n";
    return get_continue();
}

int main() {
    while (true) {
        int answer = Random::get(Limits::min, Limits::max);
        std::cout << "Let's play a game. I'm thinking of a number between " << Limits::min << " and " << Limits::max << ". You have " << Limits::guesses << " tries to guess what it is.\n";
        if (!game_loop(answer)) {
            std::cout << "Thank you for playing.\n";
            return 0;
        }
    }
}