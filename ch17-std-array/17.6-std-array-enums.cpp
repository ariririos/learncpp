#include <array>
#include <ios>
#include <iostream>
#include <string>
#include <string_view>

enum StudentNames { kenny, kyle, stan, butters, cartman, max_students };

namespace Color {
    enum Type { black, red, blue, max_colors };
    using namespace std::string_view_literals;
    constexpr std::array color_name { "black"sv, "red"sv, "blue"sv };
    static_assert(std::size(color_name) == max_colors);
    constexpr std::array types { black, red, blue };
    static_assert(std::size(types) == max_colors);
} // namespace Color

constexpr std::string_view get_color_name(Color::Type color) {
    return Color::color_name[color];
}

std::ostream &operator<<(std::ostream &out, Color::Type color) {
    return out << get_color_name(color);
}

std::istream &operator>>(std::istream &in, Color::Type &color) {
    std::string input {};
    std::getline(in >> std::ws, input);
    for (std::size_t index { 0 }; index < Color::color_name.size(); index++) {
        if (input == Color::color_name[index]) {
            color = static_cast<Color::Type>(index);
            return in;
        }
    }
    // at this point we haven't found a match, put the input stream in fail state
    in.setstate(std::ios_base::failbit);
    // on an extraction failure, operator>> zero-initializes fundamental types
    // this line will do the same thing
    // color = {};
    return in;
}

int main() {
    [[maybe_unused]] constexpr std::array test_scores { 78, 94, 66, 77 };

    // std::cout << "Cartman got a score of " << test_scores[StudentNames::cartman] << "\n"; // undefined behavior
    // static_assert(std::size(test_scores) == max_students); // compile error, static_assert fails

    auto shirt { Color::blue };
    std::cout << "Your shirt is " << shirt << "\n";

    std::cout << "Enter a new color: ";
    std::cin >> shirt;
    if (!std::cin) {
        std::cout << "Invalid\n";
    } else {
        std::cout << "Your shirt is now " << shirt << "\n";
    }

    // we can use a for loop to iterate through the colors:
    for (int i { 0 }; i < Color::max_colors; i++) {
        std::cout << static_cast<Color::Type>(i) << "\n";
    }

    // but we can create a std::array with the different enumerations and iterate over that:
    for (auto c : Color::types) {
        std::cout << c << "\n";
    }

    return 0;
}