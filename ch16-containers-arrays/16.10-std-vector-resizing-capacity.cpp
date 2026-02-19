#include <iostream>
#include <vector>

void print_length(const std::vector<int> &v) {
    std::cout << "The length is " << v.size() << "\n";
}

void print_capacity(const std::vector<int> &v) {
    std::cout << "The capacity is " << v.capacity() << "\n";
}

void print_arr(const std::vector<int> &v) {
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

int main() {
    // resizing preserves existing elements and does default-initialization for
    // class types or zero-initialization for other types

    // vectors also have a capacity referring to how many elements have been
    // allocated in memory

    std::vector v { 0, 1, 2 };
    print_length(v);
    print_capacity(v);
    print_arr(v);

    v.resize(5); // likely need to reallocate here
    print_length(v);
    print_capacity(v);
    print_arr(v);

    v.resize(2); // probably don't need to reallocate here
    print_length(v);
    print_capacity(v);
    print_arr(v);

    // reallocation requires at least three steps:
    // - acquire new memory with enough capacity and value-initialize it
    // - copy (or move, if possible) the elements in the old memory into the new
    // memory, and free the old memory
    // - set the length and capcity to the new values

    // array indices are only valid within the array's length, *not* its
    // capacity

    // resizing a vector to be smaller will reduce its length but not its
    // capacity, unless we request a shrink with .shrink_to_fit(), in which case
    // the implementation may fulfill the request, partially fulfill it, or
    // completely ignore it:
    std::vector<int> v1(1000);
    print_length(v1);
    print_capacity(v1);
    v1.resize(0);
    print_length(v1);
    print_capacity(v1);
    v1.shrink_to_fit();
    print_length(v1);
    print_capacity(v1);

    return 0;
}