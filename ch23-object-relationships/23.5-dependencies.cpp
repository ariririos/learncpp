#include <iostream>

class Point {
private:
    double m_x {};
    double m_y {};
    double m_z {};

public:
    Point(double x = 0.0, double y = 0.0, double z = 0.0)
        : m_x { x }, m_y { y }, m_z { z } {}
    friend std::ostream &operator<<(std::ostream &out, const Point &point);
};

std::ostream &operator<<(std::ostream &out, const Point &point) {
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z
        << ")";
    return out;
}

int main() {
    // a dependency relationship is one object invoking another's functionality for some specific task; it's always a unidirectional relationship
    // for example, our classes use std::ostream to print things to the console, but not otherwise:
    Point point1 { 2.0, 3.0, 4.0 };
    std::cout << point1;

    // in an assocation, the objects typically keep a direct link to each other, whether through pointer/reference or another form of ID; but dependencies are not typically members, only instantiated as needed or passed into a function as needed
    return 0;
}