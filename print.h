#include <iostream>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++" // you're not supposed to overload operator,
#define print(x, ...) { std::cout << #x << " = " << x; __VA_OPT__(std::cout , __VA_ARGS__;) std::cout << std::endl; }


template <typename T>
std::ostream& operator,(std::ostream& out, const T& t) {
    out << " " << t;
    return out;
}

std::ostream& operator,(std::ostream& out, std::ostream&(*f)(std::ostream&)) {
    out << f;
    return out;
}
#pragma GCC diagnostic pop