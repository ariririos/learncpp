#include <iostream>

int main() {
    int width = 5;
    int outer { 1 };
    while (outer <= width) {
        int inner { width };
        while (inner > 0) {
            if (inner <= outer) {
                std::cout << inner << " ";
            } else {
                std::cout << "  ";
            }
            inner--;
        }

        std::cout << '\n';
        outer++;
    }

    return 0;
}