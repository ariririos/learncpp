#include "23.6-IntArray.h"
#include <iostream>

int main() {
    // a container class holds multiple instances of another type; C-style arrays are the most fundamental container, but std::array and std::vector are preferred because they provide dynamic resizing, remember their size, and do bounds-checking

    // most well-defined containers have functions to:
    // - create an empty container (via a constructor)
    // - insert a new object into the container
    // - remove an object from the container
    // - report the number of objects currently in the container
    // - empty the container
    // - provide access to the stored objects
    // - (optionally) sort the container
    // some types of containers (e.g. array-like containers) will omit certain functions to discourage their use (e.g. insert/remove functions because they are slow)
    // containers implement a "member-of" type relationship

    // there are generally two types of containers, value containers (compositions that store copies of the objects they hold and manage their lifetimes) and reference containers (aggregations that store pointers/references to other objects and aren't responsible for their lifetimes)

    // containers typically only hold one type of data

    // test construction
    IntArray array(10);
    // test access
    for (int i { 0 }; i < 10; ++i) {
        array[i] = i + 1;
    }
    // test operations
    array.resize(8);
    array.insert_before(20, 5);
    array.remove(3);
    array.insert_at_end(30);
    array.insert_at_beginning(40);
    // test that copy construction and assignment don't break anything
    {
        IntArray b { array };
        b = array;
        b = b;
        array = array;
    }
    // should print 40 1 2 3 5 20 6 7 8 30
    for (int i { 0 }; i < 10; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";

    // some possible improvements to IntArray:
    // - make it a template
    // - add const versions of member functions
    // - add move constructor and assignment
    // - when doing resize or insertion, move elements rather than copy them (or use std::move_if_noexcept to move conditionally and copy otherwise)
    // - strong exception guarantee for resize and insertion operations

    // use stdlib containers instead of writing your own if possible

    return 0;
}