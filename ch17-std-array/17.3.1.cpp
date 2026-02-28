#include <array>
#include <iostream>

template <typename T, auto N> void print_array(const std::array<T, N> &arr) {
    std::cout << "The array (";
    bool first { true };
    for (const auto &e : arr) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << e;
        first = false;
    }
    std::cout << ") has length " << N << "\n";
}

int main() {
    constexpr std::array arr1 { 1, 4, 9, 16 };
    print_array(arr1);

    constexpr std::array arr2 { 'h', 'e', 'l', 'l', 'o' };
    print_array(arr2);
}