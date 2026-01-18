#include "Helix.h"

const double PI = 3.14159265358979323846;

Helix::Helix(long long id, std::string name, Vector3D point3D, double radius, double step) 
	: BaseCurve(id, name, point3D), radius{ radius }, step{ step }
{
    if (radius <= 0) {
        throw std::invalid_argument("Helix radius must be positive");
    }
}

Vector3D Helix::getFirstDerivative(double t) const
{
    return Vector3D{
       -radius * sin(t),
        radius * cos(t),
        step / (2.0 * PI)
    };
}

Vector3D Helix::getPoint3D(double t) const
{
    const Vector3D& point3D = getPoint();
    return {
        point3D.x + radius * cos(t),
        point3D.y + radius * sin(t),
        point3D.z + (step * t) / (2.0 * PI)
    };
}

