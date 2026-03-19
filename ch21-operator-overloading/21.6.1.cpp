#include <iostream>

class Point {
private:
    double m_x {};
    double m_y {};
    double m_z {};
public:
    Point(double x=0.0, double y=0.0, double z=0.0):
        m_x { x }, m_y { y }, m_z { z }
        {}
    Point operator+() const;
    Point operator-() const; // returns the negative of this point
    bool operator!() const; // returns true if this point is at the origin
    double get_x() const { return m_x; }
    double get_y() const { return m_y; }
    double get_z() const { return m_z; }
};

Point Point::operator+() const {
    return *this; // returning a copy by value here
}

Point Point::operator-() const {
    return { -m_x, -m_y, -m_z };
}

bool Point::operator!() const {
    return (m_x == 0.0 && m_y == 0.0 && m_z == 0.0);
}

int main() {
    Point point {};
    std::cout << "The point is Point(" << point.get_x() << ", " << point.get_y() << ", " << point.get_z() << ")\n";
    return 0;
}