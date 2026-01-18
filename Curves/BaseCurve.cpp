#include "BaseCurve.h"

BaseCurve::BaseCurve() : point3D{ 0.0, 0.0, 0.0 }, id{ 0 }, name{ "" }
{
}

BaseCurve::BaseCurve(long long id, std::string name, Vector3D point3D) : id{ id }, name{ name }
{
	this->point3D.x = point3D.x;
	this->point3D.y = point3D.y;
	this->point3D.z = point3D.z;
}

long long BaseCurve::getID() const
{
	return this->id;
}

std::string BaseCurve::getName() const
{
	return this->name;
}


