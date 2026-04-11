#include <algorithm>
#include <iostream>
#include <vector>

class Point {
private:
    int m_x {};
    int m_y {};

public:
    Point(int x, int y) : m_x { x }, m_y { y } {}

    friend std::ostream &operator<<(std::ostream &out, const Point &p) {
        out << "Point(" << p.m_x << ", " << p.m_y << ")";
        return out;
    }
};

class Shape {
public:
    virtual std::ostream &print(std::ostream &out) const = 0;
    virtual ~Shape() {}
    friend std::ostream &operator<<(std::ostream &out, const Shape &s) {
        return s.print(out);
    }
};

class Triangle : public Shape {
private:
    Point m_p1;
    Point m_p2;
    Point m_p3;

public:
    Triangle(const Point &p1, const Point &p2, const Point &p3)
        : m_p1 { p1 }, m_p2 { p2 }, m_p3 { p3 } {}
    std::ostream &print(std::ostream &out) const override {
        out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ")";
        return out;
    }
};

class Circle : public Shape {
private:
    Point m_center;
    int m_radius {};

public:
    Circle(const Point &center, int radius)
        : m_center { center }, m_radius { radius } {}
    std::ostream &print(std::ostream &out) const override {
        out << "Circle(" << m_center << ", radius " << m_radius << ")";
        return out;
    }
    int get_radius() const { return m_radius; }
};

int get_largest_radius(const std::vector<Shape *> &v) {
    int largest_radius {};
    for (const auto *shape : v) {
        if (auto *circle { dynamic_cast<const Circle *>(shape) }) {
            largest_radius = std::max(largest_radius, circle->get_radius());
        }
    }
    return largest_radius;
}

int main() {
    std::vector<Shape *> v { new Circle { Point { 1, 2 }, 7 },
                             new Triangle { Point { 1, 2 }, Point { 3, 4 },
                                            Point { 5, 6 } },
                             new Circle { Point { 7, 8 }, 3 } };

    for (const auto *shape : v) {
        std::cout << *shape << "\n";
    }

    std::cout << "The largest radius is: " << get_largest_radius(v)
              << '\n'; // write this function

    for (const auto *shape : v) {
        delete shape;
    }

    return 0;
}