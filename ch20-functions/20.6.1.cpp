#include <algorithm>
#include <array>
#include <iostream>

struct Student {
    std::string name {};
    int score {};
};

int main() {
    std::array<Student, 8> arr { { { "Albert", 3 },
                                   { "Ben", 5 },
                                   { "Christine", 2 },
                                   { "Dan", 8 }, // Dan has the most points (8).
                                   { "Enchilada", 4 },
                                   { "Francis", 1 },
                                   { "Greg", 3 },
                                   { "Hagrid", 5 } } };

    const auto max_score { std::max_element(
        arr.begin(), arr.end(),
        [](const Student &a, const Student &b) { return a.score < b.score; }) };

    std::cout << max_score->name << " is the best student\n";

    return 0;
}