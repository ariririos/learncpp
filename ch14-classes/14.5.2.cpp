#include <iostream>

class Point3D {
public:
    void set_values(int x, int y, int z) {
        m_x = x;
        m_y = y;
        m_z = z;
    }
    void print() const {
        std::cout << "<" << m_x << ", " << m_y << ", " << m_z << ">\n";
    }
    bool is_equal(const Point3D& other) const {
        return (m_x == other.m_x) && (m_y == other.m_y) && (m_z == other.m_z);
    }
private:
    int m_x {};
    int m_y {};
    int m_z {};
};

int main() {
    Point3D point;
    point.set_values(1, 2, 3);

    point.print();

    Point3D point1 {};
	point1.set_values(1, 2, 3);

	Point3D point2 {};
	point2.set_values(1, 2, 3);

	std::cout << "point 1 and point 2 are" << (point1.is_equal(point2) ? "" : " not") << " equal\n";

	Point3D point3 {};
	point3.set_values(3, 4, 5);

	std::cout << "point 1 and point 3 are" << (point1.is_equal(point3) ? "" : " not") << " equal\n";

    return 0;
}