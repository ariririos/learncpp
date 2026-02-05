#include <algorithm>
#include <cmath>
#include <iostream>

template <typename T> constexpr T const_abs(T x) { return (x < 0 ? -x : x); }

constexpr bool approx_eq_rel(double a, double b, double rel_epsilon) {
    return (std::abs(a - b) <=
            (std::max(std::abs(a), std::abs(b)) * rel_epsilon));
}

constexpr bool approx_eq_abs_rel(double a, double b, double abs_epsilon,
                                 double rel_epsilon) {
    if (std::abs(a - b) <= abs_epsilon) {
        return true;
    }

    return approx_eq_rel(a, b, rel_epsilon);
}

int main() {
    constexpr double a { 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 +
                         0.1 };
    constexpr double rel_eps { 1e-8 };
    constexpr double abs_eps { 1e-12 };

    std::cout << std::boolalpha;

    std::cout << approx_eq_rel(a, 1.0, rel_eps) << "\n";
    std::cout << approx_eq_rel(a - 1.0, 0.0, rel_eps) << "\n";
    std::cout << approx_eq_abs_rel(a, 1.0, abs_eps, rel_eps) << "\n";
    std::cout << approx_eq_abs_rel(a, 1.0, abs_eps, rel_eps) << "\n";

    return 0;
}