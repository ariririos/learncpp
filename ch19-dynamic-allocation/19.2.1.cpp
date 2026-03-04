#include <algorithm>
#include <iostream>

std::size_t get_length() {
    std::cout << "How many names would you like to enter? ";
    std::size_t length {};
    std::cin >> length;
    return length;
}

void get_names(std::string *names, std::size_t length) {
    for (std::size_t i { 0 }; i < length; i++) {
        std::cout << "Enter name #" << i + 1 << ": ";
        std::getline(std::cin >> std::ws, names[i]);
    }
}

void print_names(std::string *names, std::size_t length) {
    std::cout << "Here is your sorted list:\n";
    for (std::size_t i { 0 }; i < length; i++) {
        std::cout << "Name #" << i + 1 << ": " << names[i] << "\n";
    }
}

int main() {
    auto length { get_length() };

    auto *names { new std::string[length] {} };

    get_names(names, length);

    std::sort(names, names + length);

    print_names(names, length);

    delete[] names;

    return 0;
}