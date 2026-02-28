#include <array>
#include <ios>
#include <iostream>

namespace Animal {
    enum Type { chicken, dog, cat, elephant, duck, snake, max_animals };
    struct Data {
        std::string_view name {};
        int legs {};
        std::string_view sound {};
    };
    constexpr std::array types { chicken, dog, cat, elephant, duck, snake };
    constexpr std::array data {
        Data { "chicken", 2, "cluck" }, Data { "dog", 4, "woof" },
        Data { "cat", 4, "meow" },      Data { "elephant", 4, "pawoo" },
        Data { "duck", 2, "quack" },    Data { "snake", 0, "hissss" },
    };
    static_assert(std::size(types) == max_animals);
    static_assert(std::size(data) == max_animals);
} // namespace Animal

std::ostream &operator<<(std::ostream &out, Animal::Type animal_type) {
    const Animal::Data &animal = Animal::data[animal_type];
    return out << "A " << animal.name << " has " << animal.legs
               << " legs and says " << animal.sound << ".\n";
}

std::istream &operator>>(std::istream &in, Animal::Type &animal) {
    std::string input {};
    std::getline(in >> std::ws, input);
    for (std::size_t index { 0 }; index < std::size(Animal::data); index++) {
        if (input == Animal::data[index].name) {
            animal = static_cast<Animal::Type>(index);
            return in;
        }
    }
    in.setstate(std::ios_base::failbit);
    return in;
}

int main() {
    Animal::Type animal_in {};
    std::cout << "Enter an animal: ";
    std::cin >> animal_in;
    if (!std::cin) {
        std::cin.clear();
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "That animal couldn't be found.\n";
        animal_in = Animal::max_animals;
    } else {
        std::cout << animal_in;
    }

    std::cout << "\nHere is the data for the rest of the animals:\n";

    for (const auto &type : Animal::types) {
        if (type != animal_in) {
            std::cout << type;
        }
    }

    return 0;
}