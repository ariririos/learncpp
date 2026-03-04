#include "../print.h"
#include <cstddef>

int main() {
    // dynamically allocating a C-style array allows using a non-constexpr length
    // (it is possible to dynamically allocate a std::array but a std::vector should probably be used instead)

    // new[] and delete[] are used for dynamically allocating arrays:
    std::cout << "Enter a positive integer: ";
    std::size_t length {};
    std::cin >> length;
    {
        int *array { new int[length] {} }; // initializes to zero

        std::cout << "Allocated an array of ints of length " << length << "\n";
        array[0] = 5;
        delete[] array;
    }
    // normally would set array to nullptr but it's going out of scope here anyway
    // new[] and delete[] keep track of how much memory is allocated so they know how much to deallocate; but there's no way to access this size programatically

    // a dynamic array functions identically to a decayed fixed size array (no size information) except for needing to deallocate using delete[]

    // using an initializer list:
    auto *array2 { new int[] { 9, 7, 5, 3, 1 } };

    // there's no way to resize a dynamically allocated array other than allocating a new one, copying it over, and deleting the old one; use std::vector instead
    return 0;
}