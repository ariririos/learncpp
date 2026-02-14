#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <algorithm>
#include <cctype>
#include <iterator>

enum Color {
    black,
    red,
    blue,
};

constexpr std::string_view get_color_name(Color color) {
    switch (color) {
        case black: return "black";
        case red: return "red";
        case blue: return "blue";
        default: return "???";
    }
}

enum Pet {
    cat, // 0
    dog, // 1
    pig, // 2
    whale, // 3
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

std::string to_ascii_lowercase(std::string_view sv) {
    std::string lower {};
    std::transform(sv.begin(), sv.end(), std::back_inserter(lower), [](char c) {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    });
    return lower;
}

constexpr std::optional<Pet> get_pet_from_string(std::string_view sv) {
    using namespace std::string_view_literals;

    if (sv == "cat"sv) return cat;
    if (sv == "dog"sv) return dog;
    if (sv == "pig"sv) return pig;
    if (sv == "whale"sv) return whale;

    return {};
}

int main() {
    constexpr Color shirt { blue };

    std::cout << "Your shirt is " << get_color_name(shirt) << "\n";

    std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";

    int input {};
    std::cin >> input;

    if (input < 0 || input > 3) {
        std::cout << "Invalid pet\n";
    }
    else {
        Pet pet { static_cast<Pet>(input) };
        std::cout << "You entered: " << get_pet_name(pet) << "\n";
    }

    std::cout << "Enter a pet: cat, dog, pig, or whale: ";
    std::string s {};
    std::cin >> s;

    std::optional<Pet> pet { get_pet_from_string(s) };

    if (!pet) {
        std::cout << "Invalid pet\n";
    }
    else {
        std::cout << "You entered: " << get_pet_name(*pet) << "\n";
    }

    return 0;
}