#include <iostream>
#include <iterator>

int main() {
    int array[] { 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    for (std::size_t i { 0 }; i < std::size(array) - 1; i++) {
        for (std::size_t j { 0 }; j < std::size(array) - 1; j++) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }

    for (auto e : array) {
        std::cout << e << " ";
    }
    std::cout << "\n";

    return 0;
}