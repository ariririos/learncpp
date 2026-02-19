#include <iostream>
#include <vector>

template <typename T>
void print_array(const std::vector<T>& arr) {
    std::size_t length { arr.size() };
    for (std::size_t i { 0 }; i < length; i++) {
        std::cout << arr[i] << " ";
    }
    if (length > 0) {
        std::cout << "\n";
    }
}

int main() {
    std::vector arr { 4, 6, 7, 3, 8, 2, 1, 9 };

    print_array(arr);

    return 0;
}