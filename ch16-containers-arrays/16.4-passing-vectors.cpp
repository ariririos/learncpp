#include <iostream>
#include <vector>

// std::vector can be passed by value, making an expensive copy, or by const
// reference like other objects the element type is necessary
void pass_by_ref(const std::vector<int> &arr) { std::cout << arr[0] << "\n"; }

// accepts std::vector with any element type:
template <typename T> void pass_by_ref2(const std::vector<T> &arr) {
    std::cout << arr[0] << "\n";
}

// accepts any object with overloaded operator[]:
template <typename T> void pass_by_ref3(const T &arr) {
    std::cout << arr[0] << "\n";
}

// same thing as an abbreviated function template:
void pass_by_ref4(const auto &arr) { std::cout << arr[0] << "\n"; }

int main() {
    std::vector primes { 2, 3, 5, 7, 11 };
    pass_by_ref(primes);

    std::vector dbl { 1.1, 2.2, 3.3 };
    // pass_by_ref(dbl); // this won't work
    // and you can't use CTAD for function parameters, so,
    // templates!
    pass_by_ref2(dbl); // fine
    pass_by_ref3(dbl);
    pass_by_ref4(primes);

    // if we need a way to check the length of a std::vector before indexing
    // into it, we could runtime assert on .size() (non-constexpr so
    // static_assert won't work) a better option is to use std::array, which can
    // be constexpr but the best option is avoid writing functions that depend
    // on the user passing in a vector with a minimum length in the first place

    return 0;
}