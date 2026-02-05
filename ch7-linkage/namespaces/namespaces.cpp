#include "MyMath.h"
#include <iostream>


int main() {
    using std::cout;

    cout << MyMath::add(3, 4) << "\n";

    MyMath::print_both();

    namespace Constants = MyMath::Constants::Transcendentals;

    cout << Constants::pi << "\n";

    return 0;
}