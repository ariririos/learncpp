#ifndef MYMATH_H
#define MYMATH_H

namespace MyMath {
    int add(int x, int y);
    void print();
    void print_both();
    namespace Constants {
        namespace Transcendentals {
            constexpr double pi { 3.141592653589 };
        }
    } // namespace Constants
} // namespace MyMath
#endif