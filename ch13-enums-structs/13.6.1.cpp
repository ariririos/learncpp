#include <string>
#include <string_view>
#include <iostream>

enum class Animal {
    pig,
    chicken,
    goat,
    cat,
    dog,
    duck,
};

constexpr std::string_view get_animal_name(Animal animal) {
    using enum Animal;

    switch (animal) {
        case pig:       return "pig";
        case chicken:   return "chicken";
        case goat:      return "goat";
        case cat:       return "cat";
        case dog:       return "dog";
        case duck:      return "duck";
        default:        return "???";
    }
}

void print_number_of_legs(Animal animal) {
    using enum Animal;

    int num_legs;
    switch (animal) {
        case chicken:
        case duck:
            num_legs = 2;
        break;
        case pig:       
        case goat:      
        case cat:       
        case dog:
            num_legs = 4;
        break;
        default:
            num_legs = 0;
        break;
    }

    std::cout << "A " << get_animal_name(animal) << " has " << num_legs << " legs.\n";

}

int main() {
    print_number_of_legs(Animal::cat);
    print_number_of_legs(Animal::chicken);

    return 0;
}