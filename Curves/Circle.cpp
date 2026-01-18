#include "Circle.h"

Circle::Circle(long long id, std::string name, Vector3D point3D, double rad) 
	: BaseCurve(id, name, point3D), radius(rad)
{
    if (radius <= 0) {
        throw std::invalid_argument("Circle radius must be positive");
    }
}

Vector3D Circle::getFirstDerivative(double t) const
{
    return Vector3D{
        -radius * sin(t),
        radius * cos(t),
        0.0
    };
}

Vector3D Circle::getPoint3D(double t) const
{
    const Vector3D& point3D = getPoint();
    return {
        point3D.x + radius * cos(t),
        point3D.y + radius * sin(t),
        point3D.z
    };
}

double Circle::getRadius()
{
    return radius;
}
