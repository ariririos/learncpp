#include <iostream>
#include <string>
#include <string_view>

class Ball {
    std::string m_color {};
    double m_radius { 10 }; // default needed because one of the constructors won't initialize m_radius, it could just be `{}`; otherwise m_radius would get default-initialized (meaning uninitialized since it's a fundamental type)
public:
    Ball(std::string_view color, double radius)
        : m_color { color }, m_radius { radius }
        {
            // usually left empty
            // if data members were const or references, initializing them here
            // wouldn't work
        }
    Ball(std::string_view color)
        : m_color { color }
        {}
    const std::string& get_color() const { return m_color; }
    double get_radius() const { return m_radius; }
};

void print(const Ball& b) {
    std::cout << "Ball(" << b.get_color() << ", " << b.get_radius() << ")\n";
}

int main() {
    Ball blue { "blue", 10.0 };
    print(blue);

    Ball red { "red", 12.0 };
    print(red);

    Ball green { "green" };
    print(green);

    return 0;
}