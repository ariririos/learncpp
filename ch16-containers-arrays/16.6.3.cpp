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

int get_input() {
    int x {};
    do {
        std::cout << "Enter a number between 1 and 9: ";
        std::cin >> x;
        if (cin_failed()) {
            continue;
        }
        ignore_extra();
    } while (x < 1 || x > 9);
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
    std::vector arr { 4, 6, 7, 3, 8, 2, 1, 9 };

    int x { get_input() };

    print_array(arr);

    find_element_in_array(arr, x);

    return 0;
}