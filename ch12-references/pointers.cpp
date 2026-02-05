#include <iostream>
#define print_expr(x) { std::cout << #x << " = " << x << "\n"; }

int main() {
    std::cout << "int x { 5 };" << "\n";
    int x { 5 };

    print_expr(x);
    print_expr(&x);
    print_expr(*&x);

    std::cout << "int* x_ptr { &x };" << "\n";
    int* x_ptr { &x };

    print_expr(x_ptr);
    print_expr(*x_ptr);

    int* ptr; // unbound
    int* ptr2 {}; // nullptr
    //  std::cout << *ptr << "\n"; // segfaults with -O2
    //  std::cout << *ptr2 << "\n"; // segfaults with no optimizations

    //  double* ptr3 { &x }; // won't compile
    double y { 5.0 };
    //  int* ptr4 { &y }; // won't compile

    std::cout << "*x_ptr = 7;" << "\n";
    *x_ptr = 7;

    print_expr(x); // 7
    print_expr(*x_ptr); // 7
    print_expr(x_ptr); // &x
    print_expr(&x);

    std::cout << "int z { 6 };" << "\n";
    int z { 6 };

    std::cout << "x_ptr = &z;" << "\n";
    x_ptr = &z;

    print_expr(x_ptr);
    print_expr(*x_ptr);
    print_expr(&z);

    std::cout << "x_ptr = &x;" << "\n";
    x_ptr = &x;

    std::cout << "int& x_ref { x };" << "\n";
    int& x_ref { x };

    print_expr(x);
    print_expr(*x_ptr);
    print_expr(x_ref);

    std::cout << "x_ref = 8;" << "\n";
    x_ref = 8;
    print_expr(x);
    print_expr(*x_ptr);
    print_expr(x_ref);

    {
        std::cout << "{\nint a { 9 }; ptr = &a; " << "\n";
        int a { 9 };
        ptr = &a;
        print_expr(*ptr);
        std::cout << "}" << "\n";
    }

    print_expr(*ptr); // dangling

    std::cout << std::boolalpha;
    print_expr(ptr);
    print_expr(ptr2);
    print_expr(static_cast<bool>(ptr == nullptr));
    print_expr(static_cast<bool>(ptr2 == nullptr));
    print_expr(static_cast<bool>(ptr));
    print_expr(static_cast<bool>(ptr2));


    const int b { 10 };
    [[maybe_unused]] const int* b_ptr { &b };
    [[maybe_unused]] const int* const b_ptr2 { &b };
    // int* b_ptr3 { &b }; // can't initialize a non-const pointer with a const variable

    // *b_ptr = 11; // not a modifiable l-value
    // *b_ptr2 = 12; // same
    // b_ptr2 = 13; // pointer itself is const, can't reassign

    return 0;
}