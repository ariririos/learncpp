#include <cmath>
#include <iostream>


void get_sin_cos(double degrees, double& sin_out, double& cos_out) {
    constexpr double pi { 3.14159265358979323846 };
    double radians = degrees * pi / 180.0;
    sin_out = std::sin(radians);
    cos_out = std::cos(radians);
}

int main() {
    double sin { 0.0 };
    double cos { 0.0 };

    double degrees {};
    std::cout << "Enter degrees: ";
    std::cin >> degrees;

    get_sin_cos(degrees, sin, cos);

    std::cout << "sin(" << degrees << ") = " << sin << "\n";
    std::cout << "cos(" << degrees << ") = " << cos << "\n";

    return 0;
}