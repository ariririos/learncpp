#include <iostream>
#include <string_view>

enum AnimalType {
    cat,
    dog,
    chicken,
    snake
};

constexpr std::string_view animal_name(AnimalType type) {
    switch (type) {
        case cat: return "cat";
        case dog: return "dog";
        case chicken: return "chicken";
        case snake: return "snake";
        default: return "";
    }
}

constexpr int num_legs(AnimalType type) {
    switch (type) {
        case cat: return 4;
        case dog: return 4;
        case chicken: return 2;
        case snake: return 0;
        default: return 0;
    }
}

int main() {
    constexpr AnimalType animal { snake };
    std::cout << "A " << animal_name(animal) << " has " << num_legs(animal) << " legs\n";

    return 0;
}