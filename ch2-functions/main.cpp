#include "add.h"
#include <iostream>

#define EIGHT

int main() {
#ifdef SEVEN
    std::cout << "3 + 4 = " << add(3, 4) << "\n";
#endif
#ifdef EIGHT
    std::cout << "4 + 4 = " << add(4, 4) << "\n";

#endif

    return 0;
}