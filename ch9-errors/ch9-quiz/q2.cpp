#include <iostream>

using Degree = double;
using Radian = double;

namespace Constants {
    constexpr double pi { 3.14159 };
}

Radian convert_to_radians(Degree degrees) {
    return degrees * Constants::pi / 180;
}

int main() {
    std::cout << "Enter a number of degrees: ";
    Degree degrees {};
    std::cin >> degrees;

    Radian radians { convert_to_radians(degrees) };
    std::cout << degrees << " degrees is " << radians << " radians\n";

    radians = degrees; // fine because `using` only creates aliases not distinct types // NOLINT
}