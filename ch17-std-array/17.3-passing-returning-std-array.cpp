#include <array>
#include <ios>
#include <iostream>
#include <limits>

void pass_by_ref(const std::array<int, 5> &arr) { std::cout << arr[0] << "\n"; }

template <typename T, std::size_t N>
void pass_by_ref2(const std::array<T, N> &arr) {
    static_assert(N != 0);

    std::cout << arr[0] << "\n";
}

template <typename T, auto N> void pass_by_ref3(const std::array<T, N> &arr) {
    static_assert(N != 0);

    std::cout << arr[0] << "\n";
}

template <typename T, std::size_t N>
void pass_by_ref4(const std::array<T, N> &arr) {
    std::cout << std::get<3>(arr) << "\n";
}

template <typename T, std::size_t N> std::array<T, N> input_array() {
    std::array<T, N> arr {};
    std::size_t index { 0 };
    while (index < N) {
        std::cout << "Enter value #" << index << ": ";
        std::cin >> arr[index];

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        index++;
    }
    return arr;
}

template <typename T, std::size_t N> void input_array2(std::array<T, N> &arr) {
    std::size_t index { 0 };
    while (index < N) {
        std::cout << "Enter value #" << index << ": ";
        std::cin >> arr[index];

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        index++;
    }
}

int main() {
    // std::array is passed like any other object, meaning expensive copies should be avoided by passing by const reference
    std::array arr { 9, 7, 5, 3, 1 };
    pass_by_ref(arr);

    // since CTAD doesn't work with function parameters, we have to use function templates to accept std::arrays with different types and lengths:
    pass_by_ref2(arr);
    std::array arr2 { 1, 2, 3, 4, 5, 6 };
    pass_by_ref2(arr2);
    std::array arr3 { 1.2, 3.4, 5.6, 7.8, 9.9 };
    pass_by_ref2(arr3);
    // the non-type template parameter needs to be size_t not int because templates don't do implicit conversions
    // it's possible to only template one of the two parameters, either type or length
    // and in c++20 we can use `auto` on the non-type template parameter:
    pass_by_ref3(arr);

    // instead of static_asserting on array length ourselves we can use std::get to do it for us:
    pass_by_ref4(arr);
    [[maybe_unused]] std::array arr4 { 1, 2 };
    // pass_by_ref4(arr4); // won't compile

    // returning std::array: it's not move-capable so we have to decide whether making a copy or using an out parameter is preferable
    // elements will still be moved if possible
    // make a copy if: it's not huge, the elements are cheap to copy or move, and the context isn't performance-sensitive
    std::array<int, 5> arr5 { input_array<int, 5>() };
    std::cout << "The value of element 2 is " << arr5[2] << "\n";
    // unfortunately we have to specify the template arguments because there isn't an initializer for deduction
    // or using out parameter:
    std::array<int, 5> arr6 {};
    input_array2(arr6);
    std::cout << "The value of element 2 is " << arr6[2] << "\n";
    // but it's probably better to use a std::vector since the std::array won't be constexpr in this case

    return 0;
}