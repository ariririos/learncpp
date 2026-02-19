#include <iostream>
#include <vector>
#include <cassert>
#include <string_view>

void fizzbuzz(std::vector<int> divisors, std::vector<std::string_view> words, int max) {
    assert(divisors.size() == words.size() && "divisor and words array sizes should be the same");
    std::size_t length { divisors.size() };
    for (int i { 1 }; i <= max; i++) {
        bool matched { false };
        for (std::size_t j { 0 }; j < length; j++) {
            if (i % divisors[j] == 0) {
                matched = true;
                std::cout << words[j];
            }
        }
        if (!matched) {
            std::cout << i;
        }
        std::cout << "\n";
    }
}

int main() {
    std::vector divisors { 3, 5, 7, 11, 13, 17, 19 };
    std::vector<std::string_view> words { "fizz", "buzz", "pop", "bang", "jazz", "pow", "boom" };
    fizzbuzz(divisors, words, 150);

    return 0;
}