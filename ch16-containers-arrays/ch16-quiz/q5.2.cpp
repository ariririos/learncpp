#include "../../Random.h"
#include <iostream>
#include <string_view>
#include <vector>

void ignore_extra() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool cin_failed() {
    if (!std::cin) {
        if (std::cin.eof()) {
            std::exit(0);
        }
        std::cin.clear();
        ignore_extra();
        return true;
    }
    return false;
}

template <typename T> constexpr std::size_t toUZ(T value) {
    // make sure T is an integral type
    static_assert(std::is_integral<T>() || std::is_enum<T>());
    return static_cast<std::size_t>(value);
}

namespace WordList {
    std::vector<std::string_view> words { "mystery",   "broccoli",  "account",
                                          "almost",    "spaghetti", "opinion",
                                          "beautiful", "distance",  "luggage" };
    std::string_view get_random_word() {
        return words[Random::get<std::size_t>(0, std::size(words) - 1)];
    }
}; // namespace WordList

namespace Config {
    constexpr int wrong_guesses_allowed { 6 };
}

class Session {
private:
    std::string_view m_word { WordList::get_random_word() };
    std::vector<bool> m_guesses { std::vector<bool>(
        26) }; // the instructions said it was okay
    int m_guesses_left { Config::wrong_guesses_allowed };

public:
    std::string_view get_word() const { return m_word; }

    bool get_letter(char c) const { return m_guesses[toUZ((c % 32) - 1)]; }
    void set_letter(char c) { m_guesses[toUZ((c % 32) - 1)] = true; }

    bool char_in_word(char c) const {
        for (auto w : m_word) {
            if (c == w) {
                return true;
            }
        }
        return false;
    }

    int guesses_left() const { return m_guesses_left; }
    void subtract_guess() { m_guesses_left--; }

    bool won() const {
        for (auto c : m_word) {
            if (!get_letter(c)) {
                return false;
            }
        }
        return true;
    }
};

void display_state(const Session &s) {
    std::cout << "\nThe word: ";
    for (auto c : s.get_word()) {
        if (s.get_letter(c)) {
            std::cout << c;
        } else {
            std::cout << "_";
        }
    }

    std::cout << "\tWrong guesses: ";
    for (int i { 0 }; i < s.guesses_left(); i++) {
        std::cout << "+";
    }
    for (char c { 'a' }; c <= 'z'; c++) {
        if (s.get_letter(c) && !s.char_in_word(c)) {
            std::cout << c;
        }
    }

    std::cout << "\n";
}

void get_guess(Session &s) {
    char c {};
    std::cout << "Enter your next letter: ";
    std::cin >> c;

    if (cin_failed() || c < 'a' || c > 'z') {
        std::cout << "That wasn't a valid input, try again\n";
        ignore_extra();
        return;
    }

    if (s.get_letter(c)) {
        std::cout << "You already guessed that. Try again.\n";
        return;
    }

    ignore_extra();

    s.set_letter(c);

    if (s.char_in_word(c)) {
        std::cout << "Yes, '" << c << "' is in the word!\n";
    } else {
        std::cout << "No, '" << c << "' is not in the word!\n";
        s.subtract_guess();
    }
}

void game_loop(Session &s) {
    while (!s.won() &&
           s.guesses_left()) { // .guesses_left() shouldn't go negative
        display_state(s);
        get_guess(s);
    }

    display_state(s);
    if (s.won()) {
        std::cout << "You win!\n";
    } else {
        std::cout << "You lost! The word was: " << s.get_word() << "\n";
    }
}

int main() {
    std::cout << "Welcome to C++man (a variant of Hangman)\n";
    std::cout << "To win: guess the word. To lose: run out of pluses.\n";
    std::cout << "\n";

    Session session {};
    game_loop(session);

    return 0;
}