#include "../print.h"

int main() {
    // there are two ways to declare C-style string symbolic constants:
    const char name[] { "Alex" };
    const char *const color { "Orange" };
    print(name);
    print(color);
    // but memory is handled for these differently
    // in the first case, "Alex" is placed in (likely read-only) memory somewhere, then the program allocates memory for a C-style string of length 5, and initializes it with "Alex"; this results in two copies, one in global memory and one owned by name
    // in the second case, it's implementation-defined, but usually the compiler puts "Orange" into read-only memory and then initializes the pointer with the address of the string
    // if multiple string literals have the same value, the compiler may save memory by combining them into one shared string literal

    // type deduction with const C-style strings:
    [[maybe_unused]] auto s1 { "Alex" };  // const char*
    [[maybe_unused]] auto *s2 { "Alex" }; // const char*
    [[maybe_unused]] auto &s3 { "Alex" }; // const char(&)[5]

    // std::cout always interprets a char* as a string and keeps printing until it reaches a \0:
    int narr[] { 9, 7, 5, 3, 1 };
    char carr[] { "Hello!" };
    const char *ptr { "Alex" };
    print(narr);
    print(carr);
    print(ptr);
    // this means you can't print the address of a char normally:
    char c { 'Q' };
    print(
        &c); // will print garbage until it finds a memory address containing a '0'
    // you have to use a static cast to a void pointer to actually print an address:
    print(static_cast<const void *>(&c));

    // overall: favor constexpr std::string_view for string symbolic constants, which are just as fast and behave more consistently

    return 0;
}