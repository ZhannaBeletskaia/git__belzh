#include <string>
#include <iostream>

#pragma once

struct Vector3D
{
	double x, y, z;
};

class BaseCurve
{
public:

	BaseCurve();
	BaseCurve(long long id, std::string name, Vector3D point3D);
	virtual Vector3D getPoint3D(double t) const = 0;
	virtual Vector3D getFirstDerivative(double t) const = 0;
	virtual ~BaseCurve() = default;

	virtual long long getID() const;
	virtual std::string getName() const;

protected:
	const Vector3D& getPoint() const { return point3D; }

private:
	Vector3D point3D;
	long long id;
	std::string name;
};

