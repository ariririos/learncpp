#ifndef VECTOR_3D_H
#define VECTOR_3D_H
#include "./15.9.1-3-Point3d.h"

class Vector3d {
private:
    double m_x {};
    double m_y {};
    double m_z {};
public:
    Vector3d(double x, double y, double z);
    void print() const;
    friend void Point3d::move_by_vector(const Vector3d& v);
};
#endif