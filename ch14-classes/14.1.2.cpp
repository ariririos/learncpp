#include <iostream>
#include <string_view>

struct Cat {
    std::string_view name { "cat" };
    int num_legs { 4 };
};

struct Dog {
    std::string_view name { "dog" };
    int num_legs { 4 };
};

struct Chicken {
    std::string_view name { "chicken" };
    int num_legs { 2 };
};

struct Snake {
    std::string_view name { "snake" };
    int num_legs { 0 };
};

int main() {
    constexpr Snake animal;

    std::cout << "A " << animal.name << " has " << animal.num_legs << " legs\n";

    return 0;
}