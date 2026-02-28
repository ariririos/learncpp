#include <array>
#include <functional>
#include <iostream>

int main() {
    // we can't put references directly into an array
    // but we can use a reference wrapper instead
    // std::reference_wrapper behaves like a modifiable lvalue reference to T, but:
    // - operator= allows you to reseat the wrapper and make it point at a different object
    // - std::reference_wrapper<T> will implicitly convert to T&
    // - you can use .get() to get the T& out to modify the object being pointed at
    int x { 1 };
    int y { 2 };
    int z { 3 };

    std::array<std::reference_wrapper<int>, 3> arr { x, y, z };
    arr[1].get() = 5;

    std::cout << arr[1] << y << "\n"; // prints 55

    // std::ref and std::cref allow creating a std::reference_wrapper / const std::reference_wrapper:
    auto ref { std::ref(x) };
    auto cref { std::cref(x) };
    std::cout << ref << cref << "\n";

    return 0;
}