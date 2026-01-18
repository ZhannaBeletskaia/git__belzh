#pragma once
#include "BaseCurve.h"
class Helix :
    public BaseCurve
{
public:
    Helix(long long id, std::string name, Vector3D point3D, double radius, double step);
    Vector3D getFirstDerivative(double t) const override;
    Vector3D getPoint3D(double t) const override;

private:
    double radius;
    double step;
};

