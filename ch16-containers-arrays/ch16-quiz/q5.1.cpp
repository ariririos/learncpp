#include "../../Random.h"
#include <iostream>
#include <vector>

namespace WordList {
    std::vector<std::string_view> words { "mystery",   "broccoli",  "account",
                                          "almost",    "spaghetti", "opinion",
                                          "beautiful", "distance",  "luggage" };
    std::string_view get_random_word() {
        return words[Random::get<std::size_t>(0, std::size(words) - 1)];
    }
}; // namespace WordList

int main() {
    std::cout << "Welcome to C++man (a variant of Hangman)\n";
    std::cout << "To win: guess the word. To lose: run out of pluses.\n";
    std::cout << "\n";
    std::cout << "The word is: " << WordList::get_random_word() << "\n";

    return 0;
}