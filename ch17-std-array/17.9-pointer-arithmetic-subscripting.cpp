#include "../print.h"

void print_array(const int *begin, const int *end) {
    for (; begin != end; begin++) {
        std::cout << *begin << " ";
    }
    std::cout << "\n";
}

int main() {
    // we can apply integer arithmetic operators to pointers, e.g. given `ptr`, `ptr + 1` points to the next object in memory
    int x {};
    const int *ptr { &x };

    std::cout << "Basic pointer arithmetic:\n";
    print(ptr);
    print(ptr + 1);
    print(ptr +
          2); // each address will be 4 bytes after the last given 4-byte ints
    // subtraction, increment, and decrement would work as well
    // (technically this is undefined behavior because pointer arithmetic is only defined when the pointer and the result are within the same array, or one past the end)

    std::cout << "Subscripting as pointer arithmetic:\n";
    // operator[] is implemented as pointer arithmetic
    const int arr[] { 3, 2, 1 };
    // as subscripting:
    print(&arr[0]);
    print(&arr[1]);
    print(&arr[2]);
    print(arr[0]);
    print(arr[1]);
    print(arr[2]);
    // as pointer arithmetic:
    print(arr);
    print(arr + 1);
    print(arr + 2);
    print(*arr);
    print(*(arr + 1));
    print(*(arr + 2));
    // ptr[n] is the same thing as n[ptr], technically

    std::cout << "Pointer arithmetic is based on the pointer not the array:\n";
    // pointer arithmetic isn't based on the first index of an array but on which element the pointer is pointed at
    const int arr2[] { 9, 8, 7, 6, 5 };
    const int *ptr2 { arr2 };
    print(*ptr2);
    print(ptr2[0]);
    print(*(ptr2 + 1));
    print(ptr2[1]);
    std::cout << "ptr2 = &arr2[3]\n";
    ptr2 = &arr2[3];
    print(*ptr2);
    print(ptr2[0]);
    print(*(ptr2 + 1));
    print(ptr2[1]);

    std::cout << "Negative indices:\n";
    print(*ptr2);
    print(ptr2[0]);
    print(*(ptr2 - 1));
    print(ptr2[-1]);

    std::cout << "Traversing an array with pointer arithmetic:\n";
    constexpr int arr3[] { 9, 7, 5, 3, 1 };
    const int *begin { arr3 };                 // begin points to first element
    const int *end { arr3 + std::size(arr3) }; // end points to one-past-the-end

    for (; begin != end; begin++) {
        std::cout << *begin << " ";
    }
    std::cout << "\n";
    // end is the last valid pointer within this array, and it cannot be dereferenced

    // this way of traversing the array also works in a function despite array decay:
    std::cout
        << "Iteration like this also avoids passing decayed array pointers:\n";
    const int *begin1 { arr3 };
    const int *end1 { arr3 + std::size(arr3) };
    print_array(begin1, end1);

    // range-based for-loops are usually implemented using pointer arithmetic:
    for (auto e : arr3) {
        std::cout << e << " ";
    }
    std::cout << "\n";
    /* approximately this:
    {
        auto __begin = begin-expr;
        auto __end = end-expr;

        for ( ; __begin != __end; ++__begin)
        {
            range-declaration = *__begin;
            loop-statement;
        }
    }
    */
    // let's try it:
    auto __begin = arr3;
    auto __end = arr3 + std::size(arr3);

    for (; __begin != __end; __begin++) {
        auto e = *__begin;
        std::cout << e << " ";
    }
    std::cout << "\n";

    return 0;
}