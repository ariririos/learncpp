#include "../print.h"
#include <iostream>

void print_element_zero(int arr[1000]) { std::cout << arr[0] << "\n"; }
void print_element_zero2(const int *arr) { std::cout << arr[0] << "\n"; }
void print_element_zero3(const int arr[]) { std::cout << arr[0] << "\n"; }
void print_array_size(int arr[]) {
    std::cout << sizeof(arr) << "\n"; // NOLINT
}
// void print_array_size2(int arr[]) {
//     std::cout << std::size(arr) << "\n"; // NOLINT
// }
void print_element_two(int arr[]) { std::cout << arr[2] << "\n"; }

int main() {
    // we can pass an array with the number of elements matching the function signature:
    int x[1000] { 5 };
    print_element_zero(x);
    // or one that's not even matching:
    int y[7] { 5 };
    print_element_zero(y);
    // this doesn't make a copy and it works with arrays of different sizes because of array-to-pointer conversion ("array decay")

    // arrays decay into a pointer to their first element
    int arr[5] { 9, 7, 5, 3, 1 };
    auto ptr { arr }; // type is int*
    std::cout << std::boolalpha;
    // let's prove that the type of ptr is int*
    print((typeid(ptr) == typeid(int *)));
    // and then let's prove that ptr holds the address of arr[0]
    print((&arr[0] == ptr));

    // a const array decays into a pointer-to-const (const int*)

    // but array decay doesn't happen when:
    // - passing as an argument to sizeof() or typeid()
    // - taking the address with operator&
    // - passing as a member of a class type
    // - passing by reference

    // arrays != pointers; arrays contain extra type-level information about the length, while pointers do not -- that's what the "decay" is

    // operator[] on an array is actually applied to the decayed pointer
    // we can do this directly:
    const int arr2[] { 9, 7, 5, 3, 1 };
    const int *ptr2 { arr2 };
    print(ptr2[2]); // 5

    // what this means is that C-style arrays are passed by *address* not by value, even if it syntactically looks like pass by value
    // since arrays with different lengths (e.g. int[5] and int[7]) decay into equivalent pointers (e.g. int*), we can use either
    const int primes[] { 2, 3, 5, 7, 11 };
    const int squares[] { 1, 4, 9, 25, 36, 49, 64, 81 };
    print_element_zero2(primes);
    print_element_zero2(squares);
    // since we are passing by address, the function can directly modify the arrays passed in, making it extra important to mark the parameter as const if we do not intend to make changes

    // we can use `const int arr[]` as a function parameter as well instead of a pointer to be clear that we mean to take an array:
    print_element_zero3(primes);
    print_element_zero3(squares);
    // but they are the exact same -- the compiler ignores length information passed in the square brackets anyway

    // array decay presents a few problems:
    // loss of length information means sizeof() is inconsistent between an array and a decayed array pointer:
    int arr3[] { 3, 2, 1 };
    std::cout << sizeof(arr3) << "\n"; // prints 12 assuming 4-byte ints
    print_array_size(arr3);            // prints 8 assuming 64-bit addresses
    // this won't work with std::size() or std::ssize() because they won't accept pointers
    std::cout << std::size(arr3) << "\n";
    // print_array_size2(arr3); // won't compile, see above

    // we can't confirm, statically or at runtime, what length the decayed array is, so we can't check if we are accessing an element that's out of bounds:
    int a[] { 3, 2, 1 };
    print_element_two(a); // fine
    [[maybe_unused]] int b[] { 7, 6 };
    // print_element_two(b); // undefined behavior
    [[maybe_unused]] int c { 9 };
    // print_element_two(&c); // undefined behavior

    // to get around length issues, we can: pass the array and its length as separate arguments (brittle; possible sign conversion issues; can't static_assert, so relying on runtime asserts; won't work with implicit function calls like operator<<) or use a sentinel value (if one exists; if not present, we'll just walk off the end of the array; the terminating element needs special handling, e.g. not printing the null terminator; the array length does not match the number of meaningful elements)

    // **C-style arrays should be avoided**
    // use std::string_view for read-only strings
    // use std::string for modifiable strings
    // use std::array for non-global constexpr arrays
    // use std::vector for non-constexpr arrays

    // it's okay to use C-style arrays for constexpr global / constexpr static local data, because this avoids decay (just access the variable directly) and sign conversion issues
    // it's also okay to use them when handling C-style string arguments directly in functions or classes; using a string_view requires walking the array to find the null terminator and can impact performance, and if we are passing the argument to another function that expects C-style strings, we can avoid two conversions -- to/from string_view
    return 0;
}