#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>

int main() {
    short s;
    int i;
    long l;
    long long ll;
    int x { 5 };
    std::size_t size { sizeof(x) };

    std::cout << "int x { 5 }; sizeof(x) = " << size << "\n";

    std::cout << "sizeof(std::size_t) = " << sizeof(std::size_t) << "\n";

    float f { 5.0f };
    double d { 5.0 };
    long double ld { 5.0l };
    std::cout
        << std::boolalpha; // print bool as true or false rather than 1 or 0
    std::cout << "are types ieee754 compliant?" << "\n";
    std::cout << "float: " << std::numeric_limits<float>::is_iec559 << '\n';
    std::cout << "double: " << std::numeric_limits<double>::is_iec559 << '\n';
    std::cout << "long double: " << std::numeric_limits<long double>::is_iec559
              << '\n';

    float f1 { 3.4e38 };
    std::cout << f1 << "\n";
    f1 += f1;
    std::cout << "f1 + 2 = " << f1 << "\n";

    std::cout << std::setprecision(20);
    double f2 { 10.0 / 3.0 };
    std::cout << f2 << "\n";

    bool b1 { true };
    bool b2 { false };
    bool b3 {};
    std::cout << "Enter a boolean value: ";
    std::cin >> std::boolalpha;
    std::cin >> b3;
    std::cout << "b3 = " << b3 << "\n";

    return 0;
}