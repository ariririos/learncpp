#include <iostream>
#include <limits>
#include <vector>

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


template <typename T>
T get_input(T low, T high) {
    T x {};
    do {
        std::cout << "Enter a number between " << low << " and " << high << ": ";
        std::cin >> x;
        if (cin_failed()) {
            continue;
        }
        ignore_extra();
    } while (x < low || x > high);
    return x;
}

template <typename T> void print_array(const std::vector<T> &arr) {
    std::size_t length { arr.size() };
    for (std::size_t i { 0 }; i < length; i++) {
        std::cout << arr[i] << " ";
    }
    if (length > 0) {
        std::cout << "\n";
    }
}

template <typename T>
void find_element_in_array(const std::vector<T> &arr, T x) {
    std::size_t length { arr.size() };
    for (std::size_t i { 0 }; i < length; i++) {
        if (arr[i] == x) {
            std::cout << "The number " << x << " has index " << i << "\n";
            return;
        }
    }
    std::cout << "The number " << x << " was not found\n";
}

int main() {
    // std::vector arr { 4, 6, 7, 3, 8, 2, 1, 9 };
    std::vector arr { 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };

    auto x { get_input(1.0, 10.0) }; // passing in high and low values allow the compiler to infer the template type

    print_array(arr);

    find_element_in_array(arr, x);

    return 0;
}