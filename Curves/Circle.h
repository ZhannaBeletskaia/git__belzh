#include "BaseCurve.h"

#pragma once


class Circle : public BaseCurve
{
public:
	Circle(long long id, std::string name, Vector3D point3D, double rad);
	Vector3D getFirstDerivative(double t) const override;
	Vector3D getPoint3D(double t) const override;
	double getRadius();
	
protected:

	double radius;

};