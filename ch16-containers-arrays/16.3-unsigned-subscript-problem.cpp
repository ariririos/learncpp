#include <iostream>
#include <vector>

// containers are indexed with unsigned integers
// reminder: sign conversions are narrowing conversions, except when constexpr

void foo(unsigned int) {}

int main() {
    int s { 5 };
    // unsigned int u { s }; // won't compile, list initialization disallows
    // narrowing
    foo(s); // fine, copy initialization allows narrowing // -Wsign-conversion

    constexpr int t { 5 };
    [[maybe_unused]] unsigned int u {
        t
    }; // this is fine because the compiler can ensure a safe conversion or
       // error otherwise, not considered narrowing
    foo(t); // also not considered narrowing

    // std::vector and other containers have a nested type `size_type`, usually
    // the same as `size_t`, which is usually an unsigned long {,long} all of
    // the standard library containers (except std:array) use std::allocator to
    // allocate memory, from which they derive their `size_type`, which is
    // defined as size_t; it would only differ if using a different allocator

    std::vector prime { 2, 3, 5, 7, 11 };

    std::cout << "length: " << prime.size() << "\n";

    // std::vector and most other containers only have a size() function unlike
    // std::string{,_view}, which have a length() function that does the same
    // thing and std::size() (c++17) does the same thing as size() on
    // containers:
    std::cout << "length: " << std::size(prime) << "\n";
    // std::size() can also be used on non-decayed C-style arrays so it
    // sometimes preferred esp. when writing template code that can accept
    // either containers or non-decayed C-style arrays

    // storing the size is likely to result in a sign conversion warning which
    // can be suppressed with a static_cast:
    int length { static_cast<int>(prime.size()) };
    std::cout << "length: " << length << "\n";

    // std::ssize (c++20) returns the length as a large *signed* integral type,
    // usually std::ptrdiff_t
    std::cout << "length: " << std::ssize(prime) << "\n";

    // we should still static_cast if putting the result of std::ssize in an int
    // because it may still be a narrowing conversion: int length2 {
    // std::ssize(prime) }; // won't compile, in this case it's a long-to-int
    // narrowing conversion
    int length2 { static_cast<int>(std::ssize(prime)) };
    std::cout << "length: " << length2 << "\n";
    // or we could just use `auto`:
    auto length3 { std::ssize(prime) };
    std::cout << "length: " << length3 << "\n";

    // there is no bounds checking with operator[]:
    std::cout << "prime[3]: " << prime[3] << "\n";
    std::cout << "prime[9]: " << prime[9]
              << "\n"; // asserts out if in debug, undefined behavior in prod
    // the index can be non-const

    // .at(idx) returns a reference to element at idx; it does runtime bounds
    // checking and throws an exception for out of bounds accesses:
    std::cout << "prime.at(3): " << prime.at(3) << "\n";
    std::cout << "prime.at(9): " << prime.at(9) << "\n";
    // the index can also be non-const

    // the compiler can implicitly convert a constexpr signed int to std::size_t
    // without it being a narrowing conversion:
    std::cout << prime[3]
              << "\n"; // int -> std::size_t, not a narrowing conversion
    constexpr int index { 3 };
    std::cout
        << prime[index]
        << "\n"; // constexpr int -> std::size_t, not a narrowing conversion

    // indexes can be non-const:
    std::size_t index2 { 3 };
    std::cout << prime[index2]
              << "\n"; // operator[] expects a std::size_t so no conversion
    int index3 { 3 };
    std::cout
        << prime[index3]
        << "\n"; // but this is likely to warn about a narrowing conversion
    // each indexing operation with this int will cause a warning, it's easier to just use a size_t, or index the underlying C-style array directly:
    std::cout << prime.data()[index3] << "\n";
    // C-style arrays can be indexed with signed or unsigned types

    return 0;
}