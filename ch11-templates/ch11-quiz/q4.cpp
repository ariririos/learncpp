#include <iostream>

int foo(int n)
{
    return n + 10;
}

template <typename T>
int foo(T n)
{
    return n;
}

int main()
{
    std::cout << foo(1) << '\n'; // #1 - 11

    short s { 2 };
    std::cout << foo(s) << '\n'; // #2 - 2

    std::cout << foo<int>(4) << '\n'; // #3 - 4

    std::cout << foo<int>(s) << '\n'; // #4 - 2

    std::cout << foo<>(6) << '\n'; // #5 - 6

    return 0;
}