#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <string_view>

enum Color {
    black,
    red,
    blue
};

constexpr std::string_view get_color_name(Color color) {
    switch (color) {
        case black: return "black";
        case red:   return "red";
        case blue:  return "blue";
        default:    return "???";
    }
}

std::ostream& operator<<(std::ostream& out, Color color) {
    out << get_color_name(color);

    return out;
}

enum Pet {
    cat,    // 0
    dog,    // 1
    pig,    // 2
    whale,  // 3
};

constexpr std::string_view get_pet_name(Pet pet) {
    switch (pet) {
        case cat:   return "cat";
        case dog:   return "dog";
        case pig:   return "pig";
        case whale: return "whale";
        default:    return "???";
    }
}

constexpr std::optional<Pet> get_pet_from_string(std::string_view sv) {
    if (sv == "cat")    return cat;
    if (sv == "dog")    return dog;
    if (sv == "pig")    return pig;
    if (sv == "whale")  return whale;

    return {};
}

std::istream& operator>>(std::istream& in, Pet& pet) {
    std::string s {};
    in >> s;

    std::optional<Pet> match { get_pet_from_string(s) }; // match isn't a keyword

    if (match) {
        pet = *match;
        return in;
    }

    // by this point input must be invalid
    // so set input stream to fail state
    in.setstate(std::ios_base::failbit);

    // on extraction failure operator >> zero-initializes fundamental types
    pet = {};

    return in;
}

int main() {
    Color shirt { blue };
    std::cout << "Your shirt is " << shirt << "\n";

    std::cout << "Enter a pet: cat, dog, pig, or whale: ";
    Pet pet {};
    std::cin >> pet;

    if (std::cin) {
        std::cout << "You chose: " << get_pet_name(pet) << "\n";
    }
    else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid pet\n";
    }

    return 0;
}