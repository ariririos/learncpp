#include <iostream>

class Cents {
private:
    int m_cents {};
public:
    Cents(int cents): m_cents { cents } {}
    Cents operator-() const; 
    int get_cents() const { return m_cents; }
};

Cents Cents::operator-() const {
    return -m_cents; // this implicitly converts int to a new Cents using Cents(int)
}

class Point {
private:
    double m_x {};
    double m_y {};
    double m_z {};
public:
    Point(double x=0.0, double y=0.0, double z=0.0):
        m_x { x }, m_y { y }, m_z { z }
        {}
    Point operator-() const; // returns the negative of this point
    bool operator!() const; // returns true if this point is at the origin
    double get_x() const { return m_x; }
    double get_y() const { return m_y; }
    double get_z() const { return m_z; }
};

Point Point::operator-() const {
    return { -m_x, -m_y, -m_z };
}

bool Point::operator!() const {
    return (m_x == 0.0 && m_y == 0.0 && m_z == 0.0);
}

int main() {
    const Cents nickel { 5 };
    std::cout << "A nickel of debt is worth " << (-nickel).get_cents() << " cents.\n";

    Point point {};
    if (!point) {
        std::cout << "point is set at the origin\n";
    }
    else {
        std::cout << "point is not set at the origin\n";
    }

    return 0;
}