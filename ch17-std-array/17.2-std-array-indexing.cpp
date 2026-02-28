#include <array>
#include <iostream>

void print_length(const std::array<int, 5> &arr) {
    constexpr int length { std::size(arr) };
    std::cout << "length: " << length << "\n";
}

template <auto Length>
void print_length2([[maybe_unused]] const std::array<int, Length> &arr) {
    std::cout << "length: " << Length << "\n";
}

int main() {
    // std::array has the same indexing problems as std::vector due to the unsigned index problem
    // the length of a std::array is a size_t, or a value convertible to it (constexpr so no sign conversion issues)
    // the length and indices of a std::array are *always* size_t

    // we can get the length with .size(), std::size(), or std::ssize():
    constexpr std::array arr { 9.0, 7.2, 5.4, 3.6, 1.8 };
    std::cout << "length: " << arr.size() << "\n";
    std::cout << "length: " << std::size(arr) << "\n";
    std::cout << "length: " << std::ssize(arr) << "\n";
    // the length is always returned as a constexpr, even on non-constexpr std::arrays:
    constexpr int length { std::size(
        arr) }; // no narrowing conversion due to constexpr

    std::cout << "length: " << length << "\n";
    // BUT! until c++23, these functions will return a non-constexpr value when called on a std::array function parameter passed by (const) reference:
    std::array arr2 { 9, 7, 5, 3, 1 };

    constexpr int length2 { std::size(arr2) }; // this is fine
    std::cout << "length: " << length2 << "\n";

    print_length(arr2); // but this will fail to compile
    // (looks like it's fine in gcc even with -std=c++20 but clang will error out with the same flag)

    // workaround: using a template with a non-type template parameter
    print_length2(arr2);

    // you can use .at() instead of operator[], and it'll implicitly convert constexpr values to size_t, but may issue a warning with non-constexpr values:
    std::cout << "arr2.at(0): " << arr2.at(0) << "\n";

    // std::get() will check indices at compile time using a non-type template argument:
    constexpr std::array primes { 2, 3, 5, 7, 11 };
    std::cout << std::get<3>(primes) << "\n";
    // std::cout << std::get<9>(primes) << "\n"; // error: static assertion failed

    return 0;
}