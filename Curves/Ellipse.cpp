#include "Ellipse.h"

Ellipse::Ellipse(long long id, std::string name, Vector3D point3D, double radiusX, double radiusY) 
	: BaseCurve(id, name, point3D), minorRadius{ radiusX }, majorRadius{ radiusY }
{
    if (radiusX <= 0 || radiusY <= 0) {
        throw std::invalid_argument("Ellipse radii must be positive");
    }
}

Vector3D Ellipse::getFirstDerivative(double t) const
{
    return Vector3D{
        -minorRadius * sin(t),
         majorRadius* cos(t),
         0.0                 
    };
}

Vector3D Ellipse::getPoint3D(double t) const
{
    const Vector3D& point3D = getPoint();
    return {
        point3D.x + minorRadius * cos(t),
        point3D.y + majorRadius * sin(t),
        point3D.z
    };
}
