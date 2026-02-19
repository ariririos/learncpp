#include <iostream>
#include <utility>
#include <vector>

template <typename T> void print_arr(const std::vector<T> &arr) {
    std::cout << "With array ( ";
    bool first { true };
    for (const auto& e: arr) {
        if (!first) {
            std::cout << ", ";
        }
        first = false;
        std::cout << e;
    }
    std::cout << " ):\n";
}

template <typename T>
std::pair<std::size_t, std::size_t>
get_min_max_idx(const std::vector<T> &arr) {
    std::size_t min_idx {};
    std::size_t max_idx {};
    for (std::size_t i { 0 }; i < std::size(arr); i++) {
        if (arr[i] < arr[min_idx]) {
            min_idx = i;
        }
        if (arr[i] > arr[max_idx]) {
            max_idx = i;
        }
    }
    return { min_idx, max_idx };
}

template <typename T> void print_min_max(const std::vector<T> &arr) {
    print_arr(arr);
    std::pair min_max { get_min_max_idx(arr) };
    std::cout << "The min element has index " << min_max.first << " and value "
              << arr[min_max.first] << "\n";
    std::cout << "The max element has index " << min_max.second << " and value "
              << arr[min_max.second] << "\n";
}

int main() {
    std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
    std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };

    print_min_max(v1);
    print_min_max(v2);

    return 0;
}