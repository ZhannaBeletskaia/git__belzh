#include <iostream>
#include <vector>
#include <fstream>
#include <sstream> 
#include "BaseCurve.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"
#include <cmath> 
#include <algorithm>
#include <iomanip>

using std::vector;
using std::unique_ptr;

const double PI = 3.14159265358979323846;
const double t = PI / 4.0;

static vector<unique_ptr<BaseCurve>> ReadFile(const std::string& filename)
{
	vector<unique_ptr<BaseCurve>> curves;

	std::ifstream fin(filename);

	if (!fin.is_open())
	{
		std::cout << "Error: couldn't open the file to read" << std::endl;
		return curves;
	}

	std::string line;
	int count = 0;
	fin >> count;
	fin.ignore();

	for (int i = 0; i < count; ++i)
	{
		char tag;
		long long id;
		std::string name;
		Vector3D point;

		std::getline(fin, line);
		std::istringstream iss(line);
		iss >> tag;
		iss >> id;
		iss >> name;
		iss >> point.x;
		iss >> point.y;
		iss >> point.z;

		switch (tag)
		{
			case 'C':
			{
				double radius;
				try
				{
					iss >> radius;
					curves.push_back(std::make_unique<Circle>(id, name, point, radius));
				}
				catch (const std::exception& e) {
					std::cerr << "Skipping invalid circle (ID: " << id
						<< "): " << e.what() << std::endl;
				}
			} break;

			case 'E':
			{
				double rMinor, rMajor;
				try
				{
					iss >> rMinor; iss >> rMajor;
					curves.push_back(std::make_unique<Ellipse>(id, name, point, rMinor, rMajor));
				}
				catch (const std::exception& e) {
					std::cerr << "Skipping invalid ellipse (ID: " << id
						<< "): " << e.what() << std::endl;
				}
			} break;

			case 'H':
			{
				double radius, step;
				try
				{
					iss >> radius; iss >> step;
					curves.push_back(std::make_unique<Helix>(id, name, point, radius, step));
				}
				catch (const std::exception& e) {
					std::cerr << "Skipping invalid helix (ID: " << id
						<< "): " << e.what() << std::endl;
				}
			} break;
			default:
				std::cerr << "Error: unknown curve type '" << tag << "'" << std::endl;
				continue; 
		}
	}

	fin.close();

	return curves;
}

vector<Circle*> FindCircles(const vector<unique_ptr<BaseCurve>>& curves)
{
	vector<Circle*> circles;

	for (const auto& it : curves)
	{
		if (auto circle = dynamic_cast<Circle*>(it.get()))
			circles.push_back(circle);
	}

	return circles;
}


int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "Введите название txt: " << argv[0] << " <file_path>" << std::endl;
		return 1;
	}

	std::string filename = argv[1];

	vector<unique_ptr<BaseCurve>> curves = ReadFile(filename);

	std::cout << "The initial container: " << std::endl << std::endl;

	for (const auto& curve : curves)
	{
		Vector3D p = curve->getPoint3D(t);
		Vector3D d = curve->getFirstDerivative(t);

		std::cout << "ID: " << curve->getID() << " ";
		std::cout << "Name: " << std::setw(18) << curve->getName() << " ";
		std::cout << "Coordinates: " << p.x << " " << p.y << " " << p.z << " ";
		std::cout << "First Derivative: " << d.x << " " << d.y << " " << d.z << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	vector<Circle*> circles = FindCircles(curves);

	std::sort(circles.begin(), circles.end(),
		[](Circle* a, Circle* b) {
			return a->getRadius() < b->getRadius();
		});

	double rSum = 0;

	std::cout << "Circles sorted by radii:" << std::endl << std::endl;
	for (auto& it : circles)
	{
		std::cout << " " << it->getID() << " " << it->getName() << " " << it->getRadius() << std::endl;
		rSum += it->getRadius();
	}

	std::cout << std::endl << "The total sum of the radii lengths is " << rSum << std::endl;



}

