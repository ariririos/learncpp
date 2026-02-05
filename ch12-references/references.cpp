#include <iostream>

int main() {
    int x { 5 };
    int& ref { x };

    // int& invalid_ref; // wpn't compile, must be initialized

    std::cout << x << "\n";
    std::cout << ref << "\n";

    x = 6;
    std::cout << x << "\n";
    std::cout << ref << "\n";

    ref = 7;
    std::cout << x << "\n";
    std::cout << ref << "\n";

    int y { 6 };
    ref = y; // puts 6 into x, doesn't change what ref points to
    std::cout << x << "\n"; // x = 6 not 7

    const int z { 8 };
    const int& ref3 { z };
    // z = 9; // won't compile
    // ref3 = 10; // won't compile
    const int& ref4 { y }; 
    // ref4 = 11; // won't compile
    std::cout << z << "\n";
    std::cout << ref3 << "\n";
    std::cout << ref4 << "\n";

    y = 12;
    std::cout << y << "\n";
    std::cout << ref4 << "\n";

    const double a { 4.0 };
    const double& ref5 { a };
    // int& ref6 { a }; // not allowed, narrowing conversion
    const double& ref6 { 5 }; // reference to temporary created by conversion
    char c { 'a' };
    const int& ref7 { c }; // also reference to a temporary from conversion
    std::cout << c << "\n"; // a
    std::cout << ref7 << "\n"; // 97
    c = 'b';
    std::cout << c << "\n"; // b
    std::cout << ref7 << "\n"; // still 97 because ref7 has no idea what happens to c, only the temporary

    return 0;
}