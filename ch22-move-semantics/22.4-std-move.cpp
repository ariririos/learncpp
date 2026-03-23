#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T> void my_swap_copy(T &a, T &b) {
    T tmp { a }; // copy ctor
    a = b;       // copy assign
    b = tmp;     // copy assign
}

template <typename T> void my_swap_move(T &a, T &b) {
    T tmp { std::move(a) }; // copy ctor
    a = std::move(b);       // copy assign
    b = std::move(tmp);     // copy assign
}

int main() {
    // sometimes we want to do moves when we're working with l-value references:
    std::string x { "abc" };
    std::string y { "de" };

    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';

    my_swap_copy(x, y);

    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
    // the above makes 3 copies when this would be equally possible and more efficient with 3 moves

    // std::move (from <utility>) is a function that static_casts its argument into an r-value reference so that move semantics can be invoked
    std::string a { "abc" };
    std::string b { "de" };

    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";

    my_swap_move(a, b);

    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";

    // std::move can be used to fill the elements of a container, e.g. std::vector, with l-values
    std::vector<std::string> v;

    // we need to use std::string because it's movable, std::string_view isn't
    std::string str { "Knock" };
    std::cout << "\nCopying str\n";
    v.push_back(str); // calls l-value version of push_back, which does a copy

    std::cout << "str: " << str << "\n";
    std::cout << "vector: " << v[0] << "\n";
    std::cout << "\nMoving str:\n";

    v.push_back(std::move(
        str)); // calls r-value version of push_back, which does a move
    // equivalent to:
    // v.push_back(static_cast<std::string&&>(str));
    std::cout << "str: " << str << "\n";
    std::cout << "vector: " << v[0] << " " << v[1] << "\n";

    // moved-from objects will be left in a valid but possibly indeterminate state:
    // when we move from an r-value it doesn't really matter what the r-value is left with, but when we move from an l-value it can still be used afterwards
    // the standard says that moved-from objects (of types in the stdlib) will be left "valid but unspecified", so str above could've been any valid string, not just specifically the empty string
    // we can reuse the same object that has been moved from rather than allocate a new one; we do this above in my_swap_move where we move out of a then immediately move b into it
    // we can call any function on a moved-from object that doesn't depend on its current value, e.g. operator=, clear(), or reset(), or tests its state, e.g. empty(); but we shouldn't do things like operator[] or front() that access a container's elements

    // std::move is also useful for sorting where we do a lot of swapping of elements, which we previously did using copies, or for moving resources from one smart pointer to another
    // std::move_if_noexcept() is a variant that returns a movable r-value if the object has a noexcept move constructor otherwise a copyable l-value (see 27.10)

    return 0;
}