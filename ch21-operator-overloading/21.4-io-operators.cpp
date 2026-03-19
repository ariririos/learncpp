#include <iostream>

class Point {
private:
    double m_x {};
    double m_y {};
    double m_z {};

public:
    Point(double x = 0.0, double y = 0.0, double z = 0.0)
        : m_x { x }, m_y { y }, m_z { z } {}
    double get_x() const { return m_x; }
    double get_y() const { return m_y; }
    double get_z() const { return m_z; }
    // must return std::ostream by reference because its copy constructor is deleted
    // returning a reference is fine here because it's the same reference that was passed in so it must outlive the function
    friend std::ostream &operator<<(std::ostream &out, const Point &point);
    // friend std::istream &operator>>(std::istream &in, Point &point);
};

std::ostream &operator<<(std::ostream &out, const Point &point) {
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z
        << ")";
    return out; // returning std::ostream allows chaining
}

// VERSION 1:
// std::istream &operator>>(std::istream &in, Point &point) {
//     // FIXME: partial extraction issues
//     in >> point.m_x >> point.m_y >> point.m_z;
//     return in;
// }

// VERSION 2:
// std::istream &operator>>(std::istream &in, Point &point) {
//     double x {};
//     double y {};
//     double z {};

//     // operator>> zero-initializes fundamental types on failure
//     // this behavior can be replicated by replacing the below if statement with:
//     // point = in ? Point { x, y, z } : Point {};
//     if (in >> x >> y >> z) {
//         point = Point { x, y, z };
//     }

//     return in;
// }

std::istream &operator>>(std::istream &in, Point &point) {
    double x {};
    double y {};
    double z {};

    in >> x >> y >> z;
    if (x < 0.0 || y < 0.0 || z < 0.0) {
        in.setstate(std::ios_base::failbit);
    }
    point = in ? Point { x, y, z } : Point {};

    return in;
}

int main() {
    const Point point1 { 2.0, 3.0, 4.0 };
    const Point point2 { 6.0, 7.5, 8.0 };
    std::cout << point1 << " " << point2 << "\n";

    // VERSION 1:
    // in this version, if you enter 3 points correctly, you're okay, but if you enter for example "4.0b 5.6 7.56", you end up with Point(4, 0, 3)
    // 4.0 is extracted correctly into m_x, then m_y is zero-initialized, and m_z is untouched
    // this happens because "b" is left in the buffer so the second extraction fails and m_y gets zero-initialized, then the input stream is placed into failure mode, so extraction into m_z fails immediately and is left untouched
    // std::cout << "Enter a point: ";
    // Point point { 1.0, 2.0, 3.0 };
    // std::cin >> point;
    // std::cout << "You entered: " << point << "\n";

    // transactional operations can be implemented by:
    // - only altering on success (version 2)
    // - restoring on failure by making a copy and then reverting to that copy on failure
    // - rolling back on any sub-operation failure by performing the opposite sub-operation to reverse it; used in databases where making a copy is impractical due to size and the results of sub-operations can't be stored

    // VERSION 2:
    // we can avoid partial extraction issues by making operator>> transactional
    // entering "4.0b 5.6 7.56" in this case leads to an extraction failure so point is untouched
    // std::cout << "Enter a point: ";
    // Point point { 1.0, 2.0, 3.0 };
    // std::cin >> point;
    // std::cout << "You entered: " << point << "\n";

    // VERSION 3:
    // operator>> will put std::cin failure mode if it simply fails to extract anything to a variable, but if a semantically invalid but extractable value is entered, nothing happens to std::cin
    // we can manually put std::cin into failure mode by doing `std::cin.setstate(std::ios_base::failbit)`
    std::cout << "Enter a point: ";
    Point point {};
    std::cin >> point;
    if (!std::cin) {
        std::cout << "Extraction failure\n";
    } else {
        std::cout << "You entered: " << point << "\n";
    }

    return 0;
}