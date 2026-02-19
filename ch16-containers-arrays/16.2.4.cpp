#include <iostream>
#include <vector>

int main() {
    std::vector<int> v ( 3 );

    std::cout << "Enter 3 integers: ";
    std::cin >> v[0];
    std::cin >> v[1];
    std::cin >> v[2];
    // apparently this works too:
    // std::cin >> v[0] >> v[1] >> v[2];

    std::cout << "The sum is: " << v[0] + v[1] + v[2] << "\n";
    std::cout << "The product is: " << v[0] * v[1] * v[2] << "\n";

    return 0;
}