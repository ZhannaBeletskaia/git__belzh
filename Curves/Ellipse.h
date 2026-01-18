#pragma once
#include "BaseCurve.h"
class Ellipse :
    public BaseCurve
{
public: 
    Ellipse(long long id, std::string name, Vector3D point3D, double minorRadius, double majorRadius);

    Vector3D getFirstDerivative(double t) const override;
    Vector3D getPoint3D(double t) const override;

private:
    double minorRadius;
    double majorRadius;
};

