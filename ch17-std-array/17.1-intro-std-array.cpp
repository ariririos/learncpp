#include <array>
#include <iostream>
#include <vector>

void foo(const int length) {
    // std::array<int, length> f {}; // won't work, length is a runtime constant
}
int main() {
    std::array<int, 5> a {}; // std::array of 5 ints
    std::vector<int> b(5);   // std::vector of 5 ints

    // the length of a std::array must be a constant expression
    constexpr int len { 8 };
    std::array<int, len> c {};
    enum Colors { red, green, blue, max_colors };
    std::array<int, max_colors> d {};
#define DAYS_PER_WEEK 7
    std::array<int, DAYS_PER_WEEK>
        e {}; // avoid! use a constexpr variable instead

    int num_students {};
    // std::array<int, num_students> {}; // won't work, num_students is non-const
    foo(7);

    std::array<int, 0>
        arr {}; // empty arrays are allowed but will produce undefined behavior if accessing any elements

    // std::array is an aggregate so it uses aggregate initialization, it doesn't have any constructors
    std::array<int, 6> fibonacci = {
        0, 1, 1, 2, 3, 5
    }; // copy-list initialization
    std::array<int, 5> primes { 2, 3, 5, 7,
                                11 }; // list initialization, preferred

    // if a std::array is defined without an initializer, the elements will be default-initialized, meaning most likely uninitialized
    // so we should value initialize it if not using any initializers:
    std::array<int, 5> f; // bad, ints left uninitialized
    std::array<int, 5>
        g {}; // preferred, members value initialized, meaning ints are zero-initialized
    // if more initializers are provided than the defined length, it's an error; if fewer are provided, the rest are value initialized
    // std::array<int, 4> h { 1, 2, 3, 4, 5 }; // error: excess initializers
    std::array<int, 4> i { 1, 2 }; // b[2] and b[3] are value initialized

    // const and constexpr (!) are fine:
    const std::array<int, 5> primes2 { 2, 3, 5, 7, 11 };
    constexpr std::array<int, 5> primes3 { 2, 3, 5, 7, 11 };
    // if using a non-constexpr std::array, prefer a std::vector

    // CTAD is supported:
    constexpr std::array a1 { 9, 7, 5, 3, 1 };
    constexpr std::array a2 { 9.7, 7.31 };
    // but you can't provide just one of the template arguments normally:
    // constexpr std::array<int> a2 { 9, 7, 5, 3, 1 }; // error: too few template arguments
    // constexpr std::array<5> a3 { 9, 7, 5, 3, 1 }; // same problem
    // but in c++20 you can use std::to_array (which uses template argument deduction as a function) to omit the length:
    constexpr auto my_array_1 { std::to_array<int, 5>(
        { 9, 7, 5, 3, 1 }) }; // nothing deduced
    constexpr auto my_array_2 { std::to_array<int>(
        { 9, 7, 5, 3, 1 }) }; // size deduced
    constexpr auto my_array_3 { std::to_array(
        { 9, 7, 5, 3, 1 }) }; // size and type deduced
    // but a temporary std::array is created and then copied into our variable, avoid using unless necessary, like with a list of shorts (no way to specify literals of type short):
    constexpr auto short_array { std::to_array<short>({ 9, 7, 5, 3, 1 }) };

    // std::array supports operator[]:
    std::cout << primes[3];
    // std::cout << primes[9]; // out of bounds, undefined behavior
    return 0;
}