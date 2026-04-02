#include <iostream>

class Fruit {
private:
    std::string m_name {};
    std::string m_color {};

public:
    Fruit(std::string_view name, std::string_view color)
        : m_name { name }, m_color { color } {}
    const std::string &get_name() { return m_name; }
    const std::string &get_color() { return m_color; }
};

class Apple : public Fruit {
protected:
    Apple(
        std::string_view name,
        std::string_view
            color) // can't provide default values for both of these because then we have two default constructors, one public and one protected
        : Fruit { name, color } {}

public:
    Apple(std::string_view color = "red") : Fruit { "apple", color } {}
};

class Banana : public Fruit {
public:
    Banana(std::string_view color = "yellow") : Fruit { "banana", color } {}
};

class GrannySmith : public Apple {
public:
    GrannySmith() : Apple { "granny smith apple", "green" } {}
};

int main() {
    Apple a { "red" };
    Banana b {};
    GrannySmith c;

    std::cout << "My " << a.get_name() << " is " << a.get_color() << ".\n";
    std::cout << "My " << b.get_name() << " is " << b.get_color() << ".\n";
    std::cout << "My " << c.get_name() << " is " << c.get_color() << ".\n";

    return 0;
}