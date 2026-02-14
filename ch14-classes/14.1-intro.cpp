#include <iostream>
#include <string_view>

enum AnimalType {
    cat,
    dog,
    chicken
};

constexpr std::string_view animal_name(AnimalType type) {
    switch (type) {
        case cat: return "cat";
        case dog: return "dog";
        case chicken: return "chicken";
        default: return "";
    }
}

constexpr int num_legs(AnimalType type) {
    switch (type) {
        case cat: return 4;
        case dog: return 4;
        case chicken: return 2;
        default: return 0;
    }
}

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

int main() {
    constexpr AnimalType animal { cat };
    std::cout << "A " << animal_name(animal) << " has " << num_legs(animal) << " legs\n";

    constexpr Cat animal2;

    std::cout << "A " << animal2.name << " has " << animal2.num_legs << " legs\n";
    
    return 0;
}