#include <iostream>
#include <string>
#include <vector>

template <typename T>
bool is_value_in_array(const std::vector<T> &arr, T value) {
    for (const auto &elem : arr) {
        if (elem == value) {
            return true;
        }
    }
    return false;
}

std::string get_name() {
    std::cout << "Enter a name: ";
    std::string input {};
    std::cin >> input;
    return input;
}

int main() {
    std::vector<std::string> names { "Alex",  "Betty", "Caroline", "Dave",
                                     "Emily", "Fred",  "Greg",     "Holly" };
    std::string input { get_name() };
    bool found { is_value_in_array(names, input) };
    if (found) {
        std::cout << input << " was found\n";
    } else {
        std::cout << input << " was not found\n";
    }
    return 0;
}