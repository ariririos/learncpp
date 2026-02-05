#include <iostream>

int main()
{
    int x{ 1 }; 
    int& ref{ x };

    std::cout << x << ref << '\n'; // 11

    int y{ 2 };
    ref = y;
    y = 3; // NOLINT

    std::cout << x << ref << '\n'; // 22

    x = 4;

    std::cout << x << ref << '\n'; // 44

    return 0;
}