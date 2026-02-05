#include <iostream>
#include <string>

int main() {

    using namespace std::string_literals;

    std::cout << "Enter your full name: ";
    std::string name {};
    std::getline(std::cin >> std::ws, name);

    std::cout << "Enter your favorite color: ";
    std::string color {};
    std::getline(std::cin >> std::ws, color);

    std::cout << name << "'s favorite color is " << color << "\n";

    size_t length { name.length() };
    std::cout << "Length of name was: " << length << "\n";

    ptrdiff_t length2 { static_cast<int>(std::ssize(name)) };

    std::cout << "Length of name was also: " << length2 << "\n";

    std::cout << "foo\n";
    std::cout << "goo\n"s;

    return 0;
}