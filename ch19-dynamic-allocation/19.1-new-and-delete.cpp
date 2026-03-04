#include "../print.h"
int main() {
    // 3 types of memory allocation in C++:
    // - static: static and global variables, allocation happens once when the program is run and persists throughout the life of the program
    // - automatic: function parameters and local variables, allocation happens at the start of the enclosing block and freed when the block is exited
    // - dynamic: user-controlled

    // the rationale for dynamic memory allocation instead of pre-allocating a huge array:
    // - not wasting memory if the variable isn't actually used
    // - how can we tell which bits of memory are actually used
    // - the stack has a limit, approx 8MiB on linux
    // - not introducing an arbitrary limit or buffer overflows

    // a single variable can be dynamically allocated on the heap using `new`:
    new int; // dynamically allocate an integer (and discard the result)
    int *ptr {
        new int
    }; // dynamically allocate an integer and assign its address to ptr so we can access it
    *ptr = 7; // and dereference to access the memory
    // heap objects are typically slower to access than stack objects -- two steps needed, one to get the address out of the pointer and another to get the value

    // we can use direct initialization or uniform initialization:
    int *ptr1 { new int(5) };
    int *ptr2 { new int { 6 } };

    // and when we're done we use `delete` and set to nullptr:
    delete ptr;
    ptr = nullptr;
    delete ptr1;
    ptr1 = nullptr;
    delete ptr2;
    ptr2 = nullptr;
    // we set to nullptr to catch dereferences after deletion and prevent double-free bugs (deleting nullptr has no effect)

    // std::cout << *ptr; // undefined behavior

    // having multiple pointers to the same location is discouraged:
    int *ptr3 { new int {} };
    int *other_ptr { ptr3 };
    delete ptr3;
    ptr3 = nullptr;
    // at this point other_ptr is dangling
    // it's best to have just one pointer to a memory location, but if multiple are required, only one should "own" the memory and be responsible for its deletion

    // new can fail; until we get exceptions, we can use (std::nothrow) to set the pointer to nullptr on failure:
    int *value { new (std::nothrow) int {} };
    // and then we can check if new failed:
    if (!value) {
        std::cout << "Could not allocate memory\n";
    }

    // we can use nullptr checks to conditionally allocate memory:
    if (!ptr) {
        ptr = new int {};
    }
    // and deleting a nullptr has no effect, so a check like `if (ptr) { delete ptr; }` is unnecessary

    // memory will leak if the pointer containing the address of the allocated memory goes out of scope before the memory is deleted, since the address of the memory is "lost" and there's no way to delete it anymore
    // memory leaks can also occur if the memory address is lost by reassiging the pointer variable or doing a double allocation:
    int value1 { 5 };
    int *ptr4 { new int {} };
    ptr4 = &value1; // memory leak
    // we could fix this leak by inserting a delete right before the reassignment

    int *ptr5 { new int {} };
    ptr5 = new int {}; // memory leak

    return 0;
}