#include <iostream>
#include <utility>
#define print(x, ...) { std::cout << #x << " = " << x; __VA_OPT__(std::cout , __VA_ARGS__;) std::cout << std::endl; }

template <typename T>
std::ostream& operator,(std::ostream& out, const T& t) {
    out << " " << t;
    return out;
}

std::ostream& operator,(std::ostream& out, std::ostream&(*f)(std::ostream&)) {
    out << f;
    return out;
}

enum class Animals {
    chicken,    // 0
    dog,        // 1
    cat,        // 2
    elephant,   // 3
    duck,       // 4
    snake,      // 5
    max_animals
};

template<typename T>
constexpr auto operator+(T a) noexcept {
    return std::to_underlying(a);
}

enum class Color3 {
    black,
    red,
    blue
};

constexpr std::string_view get_color(Color3 color) {
    using enum Color3;

    switch (color) {
        case black: return "black";
        case red:   return "red";
        case blue:  return "blue";
        default:    return "???";
    }
}

int main() {
    // unscoped enumerators can be compared 
    enum Color {
        red,
        blue
    };

    enum Fruit {
        banana,
        apple,
    };

    Color color { red };
    Fruit fruit { banana };

    // compared as enums
    if (color == fruit) { // NOLINT
        std::cout << "color and fruit are equal.\n";
    }
    else {
        std::cout << "color and fruit are not equal.\n";
    }

    // scoped enums

    enum class Color2 {
        red,
        blue
    };

    enum class Fruit2 {
        banana,
        apple
    };

    Color2 color2 { Color2::red };
    [[maybe_unused]] Fruit2 fruit2 { Fruit2::banana };

    // if (color2 == fruit2) { // won't compile, can't compare different types
    // std::cout << Color2::red << "\n"; // won't compile, no conversion to int, no operator overload

    if (color2 == Color2::red) {
        std::cout << "color2 is red\n";
    }

    // print(color2); // doesn't work, no implicit conversion
    print(static_cast<int>(color));
    print(std::to_underlying(color));
    
    enum class Pet {
        cat,    // 0
        dog,    // 1
        pig,    // 2
        whale,  // 3
    };

    std::cout << "Enter a pet(0=cat, 1=dog, 2=pig, 3=whale): ";

    int input {};
    std::cin >> input;

    Pet pet { static_cast<Pet>(input) };

    print(static_cast<int>(pet));

    Pet pet2 { 1 };

    print(static_cast<int>(pet2));

    print(+Animals::elephant);

    print(get_color(Color3::blue));

    return 0;
}