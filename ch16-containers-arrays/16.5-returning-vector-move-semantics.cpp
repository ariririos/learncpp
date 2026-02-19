#include <iostream>
#include <vector>

std::vector<int> generate() { // return by value
    // with a named object here, mandatory copy elision won't apply
    std::vector arr1 { 1, 2, 3, 4, 5 };
    return arr1;
}

std::vector<int> do_something(std::vector<int> v2) {
    std::vector v3 { v2[0] +
                     v2[0] }; // copy 3 (initializer into v3): to construct
                              // value to be passed back to caller
    return v3;                // copy 4 (v3 into caller): to actually pass value
}

int main() {
    std::vector arr1 { 1, 2, 3, 4, 5 };
    std::vector arr2 {
        arr1
    }; // this copies the vector; arr1 continues to exist after this line so a
       // copy is the only reasonable thing to do

    arr1[0] = 6;
    arr2[0] = 7;

    std::cout << arr1[0] << arr2[0]
              << "\n"; // prints 67 because the two arrays are independent after
                       // the copy was made

    std::vector arr3 {
        generate()
    }; // the return value of generate() is inaccessible after this expression,
       // but without move semantics or copy elision, an expensive copy will be
       // made of data that will be destroyed anyway (also another cost to pay)
    arr3[0] = 7;
    std::cout << arr3[0] << "\n";

    // move semantics will move any data member that can be, and copy any
    // others; move meaning transferring ownership move semantics is invoked
    // when all of the following are true:
    // - the type of the object supports move semantics
    // - the object is being initialized with, or assigned, an rvalue
    // (temporary) object of the same type
    // - the move isn't elided
    // std::vector and std::string support moves

    // **types that support move semantics should be returned by value**, but
    // they should still be passed by const reference

    // example of how many copies are made without move semantics (pretending
    // std::vector isn't move capable):

    std::vector v1 { 5 }; // copy 1 (initializer list into v1): to construct
                          // value to pass to function
    std::cout << do_something(v1)[0]
              << "\n"; // copy 2 (v1 into function parameter): to actually pass
                       // v1 to do_something()
    std::cout << v1[0] << "\n";

    // copies 1 and 3 cannot be optimized at all, the objects to pass back and
    // forth must be constructed copy 2 (v1 into function parameter):
    // - can be passed by reference or address, we know v1 will be valid for the
    // entire function call
    // - cannot be elided, there isn't a redundant copy or move here
    // - cannot use an out parameter, we're passing something in
    // - cannot use move semantics, v1 is an lvalue and we'd end up with an
    // empty vector and undefined behavior when trying to print v1[0]
    // => the best option is to pass by const reference, avoiding a copy,
    // nullptr issues, and it works with both lvalues and rvalues copy 4
    // (do_something() return value into caller):
    // - can't return by reference or address, the object will go out of scope
    // at the end of do_something() and create a dangling pointer/reference
    // - might be elided if the compiler realizes it can move construction of v3
    // into the scope of main() and eliminate the copy
    // - an out parameter is possible if we construct v3 as an empty std::vector
    // in main and pass it by non-const reference to do_something(); but this
    // requires constructing and passing an object, won't work with objects that
    // don't support assignment, and is difficult to make work with both lvalue
    // and rvalue arguments
    // - move semantics are possible here since v3 will be destroyed at the end
    // of do_something()'s scope
    // => elision is the best option, but since it's out of our control, move
    // semantics is the second best option and just requires returning by value

    return 0;
}