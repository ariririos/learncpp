#ifndef POINT_3D_H
#define POINT_3D_H

class Vector3d;
class Point3d {
private:
    double m_x {};
    double m_y {};
    double m_z {};

public:
    Point3d(double x, double y, double z);
    void print() const;
    void move_by_vector(const Vector3d &v);
};
#endif