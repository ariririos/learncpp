#include "../print.h"
#include <cassert>

enum class Type { t_int, t_float, t_c_string };

void print_value(void *ptr, Type type) {
    switch (type) {
    case Type::t_int:
        std::cout << *static_cast<int *>(ptr) << "\n";
        break;
    case Type::t_float:
        std::cout << *static_cast<float *>(ptr) << "\n";
        break;
    case Type::t_c_string:
        std::cout
            << static_cast<char *>(ptr)
            << "\n"; // no dereference here so std::cout will print the whole thing rather than the one char at the start of the string
        break;
    default:
        std::cerr << "print_value(): invalid type provided\n";
        assert(false && "type not found");
        break;
    }
}

int main() {
    // a void pointer can point at objects of any data type
    int n_value { 5 };
    float f_value { 7.5f };
    struct Something {
        int n;
        float f;
    };
    Something s_value {};

    void *ptr {};
    ptr = &n_value;
    ptr = &f_value;
    ptr = &s_value;

    // a void pointer cannot be dereferenced, it needs to be cast to another pointer type first:
    ptr = &n_value;
    // std::cout << *ptr << "\n"; // illegal
    int *int_ptr { static_cast<int *>(ptr) };
    std::cout << *int_ptr << "\n"; // fine

    char sz_value[] { "Mollie " };
    print_value(&n_value, Type::t_int);
    print_value(&f_value, Type::t_float);
    print_value(
        sz_value,
        Type::
            t_c_string); // no operator& used here since sz_value is already a pointer

    // a void pointer can also be set directly to nullptr
    // no pointer arithmetic on a void pointer since the "next object" concept depends on having a defined size
    // void references aren't a thing

    // overall, **avoid** void pointers unless necessary: they circumvent type checking and C++ provides function overloading to allow functions to take different types and still be strongly typed

    return 0;
}