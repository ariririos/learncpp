#include <iostream>
#include <utility>
#include <vector>

template <typename T> void print_arr(const std::vector<T> &arr) {
    std::cout << "With array ( ";
    bool first { true };
    for (const auto &e : arr) {
        if (!first) {
            std::cout << ", ";
        }
        first = false;
        std::cout << e;
    }
    std::cout << " ):\n";
}

template <typename T>
std::pair<std::size_t, std::size_t> get_min_max_idx(const std::vector<T> &arr) {
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

void ignore_extra() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool cin_failed() {
    if (!std::cin) {
        if (std::cin.eof()) {
            std::exit(0);
        }
        std::cin.clear();
        ignore_extra();
        return true;
    }
    return false;
}

std::vector<int> get_array() {
    std::vector<int> array {};
    std::cout << "Enter numbers to add (use -1 to stop): ";
    bool first { true };
    while (true) {
        int input {};
        std::cin >> input;
        if (cin_failed()) {
            std::cout << "Invalid input, try again\n";
            continue;
        }
        if (first && input == -1) {
            std::cout << "Exiting!\n";
            std::exit(0);
        }
        else if (input == -1) {
            return array;
        }
        array.push_back(input);
        first = false;
    }
    return array;
}

int main() {
    std::vector input { get_array() };

    print_min_max(input);

    return 0;
}