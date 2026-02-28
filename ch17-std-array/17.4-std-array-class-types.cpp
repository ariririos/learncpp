#include <array>
#include <iostream>
#include <string_view>

struct House {
    int number {};
    int stories {};
    int rooms_per_story {};
};

struct Student {
    int id {};
    std::string_view name {};
};

constexpr std::array students { Student { 0, "Alex" }, Student { 1, "Joe" },
                                Student { 2, "Bob" } };

const Student *find_student_by_id(int id) {
    for (auto &s : students) {
        if (s.id == id) {
            return &s;
        }
    }
    // no matching id found
    return nullptr;
}

int main() {
    std::array<House, 3> houses {};
    houses[0] = { 13, 1, 7 };
    houses[1] = { 14, 2, 5 };
    houses[2] = { 15, 2, 4 };

    for (const auto &house : houses) {
        std::cout << "House number " << house.number << " has "
                  << (house.stories * house.rooms_per_story) << " rooms.\n";
    }

    constexpr std::array houses2 { House { 13, 1, 7 }, House { 14, 2, 5 },
                                   House { 15, 2, 4 } };

    for (const auto &house : houses2) {
        std::cout << "House number " << house.number << " has "
                  << (house.stories * house.rooms_per_story) << " rooms.\n";
    }

    // if we want to omit the element type, we have to use double braces
    // the reason is brace elision: with aggregate initializers, you can omit the second set of braces when initializing with scalar values, or with class types or arrays where the type is explicitly named with each element
    constexpr std::array<House, 3> houses3 {
        { { 13, 4, 30 }, { 14, 3, 10 }, { 15, 3, 40 } }
    };

    for (const auto &house : houses3) {
        std::cout << "House number " << house.number << " has "
                  << (house.stories * house.rooms_per_story) << " rooms.\n";
    }

    constexpr std::string_view nobody { "nobody" };
    const Student *s1 { find_student_by_id(1) };
    std::cout << "You found: " << (s1 ? s1->name : nobody) << "\n";
    const Student *s2 { find_student_by_id(3) };
    std::cout << "You found: " << (s2 ? s2->name : nobody) << "\n";

    return 0;
}