#include <functional>
#include <iostream>

int foo() { return 5; }
int goo() { return 6; }
int hoo(int x) { return x; }

void print([[maybe_unused]] int x) { std::cout << "print(int)\n"; }

void print([[maybe_unused]] int x, [[maybe_unused]] int y = 10) {
    std::cout << "print(int, int)\n";
}

bool ascending(int x, int y) { return x > y; }
bool descending(int x, int y) { return x < y; }

// we can also provide defaults for function arguments
void selection_sort(int *array, int size,
                    bool (*comparison_fn)(int, int) = ascending) {
    // could also be written as:
    // void selection_sort(int *array, int size, bool comparison_fn(int, int) = ascending) {
    if (!array || !comparison_fn) {
        return;
    }

    for (int start_index { 0 }; start_index < (size - 1); start_index++) {
        int best_index { start_index };

        for (int current_index { start_index + 1 }; current_index < size;
             current_index++) {
            if (comparison_fn(array[best_index], array[current_index])) {
                best_index = current_index;
            }
        }

        std::swap(array[start_index], array[best_index]);
    }
}

void print_array(int *array, int size) {
    if (!array) {
        return;
    }

    for (int index { 0 }; index < size; index++) {
        std::cout << array[index] << " ";
    }

    std::cout << "\n";
}

int main() {
    // function names are lvalues because functions are stored at a specific address in memory
    [[maybe_unused]] int (
        *fcn_ptr)(); // a pointer to a function that takes no parameters and returns an int (parens required because `int* fcn_ptr()` would be interpreted as a forward declaration for a function that takes no params and returns an int pointer)

    [[maybe_unused]] int (*const fcn_ptr2)() {
        nullptr
    }; // const pointer to a function

    [[maybe_unused]] int (*fcn_ptr3)() { &foo };
    fcn_ptr3 = &goo;
    // double (*fcn_ptr4)() { &foo }; // won't work, return types must match
    // int (*fcn_ptr4)(int) { &foo }; // won't work, parameter types must match

    // operator& isn't necessary to get the address of a function because function names will be implicitly converted to function pointers
    [[maybe_unused]] int (*fcn_ptr5)() { foo };
    // void* v_ptr { foo }; // not allowed

    int (*fcn_ptr6)(int) { hoo };
    (*fcn_ptr6)(5); // calls hoo(5) through fcn_ptr6
    fcn_ptr6(5);    // same thing with an implicit dereference
    // the implicit dereference method looks just like a normal function call because normal function names are pointers to functions already
    (*hoo)(5); // for example

    // function pointers should be checked for nullptr like any other pointer
    if (fcn_ptr6) {
        fcn_ptr6(5);
    }

    // one major difference between function pointers and regular function calls is that **default arguments don't work for functions called through function pointers**
    // default arguments work by rewriting function calls at compile time so they don't apply at runtime through a function pointer
    // this means we can use a function pointer to disambiguate a function call that default arguments would otherwise makes ambiguous
    // print(1); // won't compile, ambiguous
    using vnptr = void (*)(int);
    vnptr pi { print };
    pi(1); // calls print(int)

    // same thing as a one-liner:
    static_cast<void (*)(int)>(print)(1); // same thing

    // we can use function pointers for callback functions
    int array[] { 3, 7, 9, 5, 6, 1, 8, 2, 4 };
    selection_sort(array, 9, descending);
    print_array(array, 9);
    selection_sort(array, 9, ascending);
    print_array(array, 9);

    // std::function also allows declaring a function pointer
    [[maybe_unused]] std::function<int()> fcn_ptr7 {
        &foo
    }; // function pointer that returns an int and takes no parameters

    [[maybe_unused]] std::function fcn_ptr8 {
        &foo
    }; // using CTAD to infer template arguments

    // auto also works for declaring a function pointer
    [[maybe_unused]] auto fcn_ptr9 { foo };
    return 0;
}