#include <iostream>

class Animal {
protected:
    std::string m_name {};
    std::string m_speak {};

    Animal(std::string_view name, std::string_view speak)
        : m_name { name }, m_speak { speak } {}

    // to prevent slicing (covered later)
    Animal(const Animal &) = delete;
    Animal &operator=(const Animal &) = delete;

public:
    std::string_view get_name() const { return m_name; }
    std::string_view speak() const { return m_speak; }
};

class Cat : public Animal {
public:
    Cat(std::string_view name) : Animal { name, "Meow" } {}
};

class Dog : public Animal {
public:
    Dog(std::string_view name) : Animal { name, "Woof" } {}
};

int main() {

    const Cat fred { "Fred" };
    const Cat misty { "Misty" };
    const Cat zeke { "Zeke" };

    const Dog garbo { "Garbo" };
    const Dog pooky { "Pooky" };
    const Dog truffle { "Truffle" };

    // Set up an array of pointers to animals, and set those pointers to our Cat and Dog objects
    const auto animals { std::to_array<const Animal *>(
        { &fred, &garbo, &misty, &pooky, &truffle, &zeke }) };

    // Before C++20, with the array size being explicitly specified
    // const std::array<const Animal*, 6> animals{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };

    for (const auto animal : animals) {
        std::cout << animal->get_name() << " says " << animal->speak() << '\n';
    }

    // this is a suboptimal solution because we can't then change what Cats and Dogs say after they're constructed without further changing Animal with a function to update m_speak; Cats and Dogs must have the same interface, or we must change Animal to support every possible member and function we want either Cat or Dog to have; and we couldn't, for example, have cats meow twice when speak() is called, since they always speak m_speak
    return 0;
}