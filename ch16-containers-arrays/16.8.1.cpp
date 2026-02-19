#include <iostream>
#include <string_view>
#include <vector>

std::string get_name() {
    std::cout << "Enter a name: ";
    std::string input {};
    std::cin >> input;
    return input;
}

int main() {
    std::vector<std::string_view> names { "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly"};
    std::string input { get_name() };
    bool found {};
    for (auto name : names) {
        if (name == input) {
            std::cout << name << " was found\n";
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << input << " was not found\n";
    }
    return 0;
}