#pragma once
#ifndef ISOSCELES_TRIANGLE_H
#define ISOSCELES_TRIANGLE_H

#include "polygon.h"

using namespace std;

namespace polygonSpace
{
	// Derived class for isosceles triangle
	class IsoscelesTriangle : public polygonSpace::Polygon
	{

	public:

		// Default constructor
		IsoscelesTriangle() { number_polygons++; x_coordinates.push_back(0); y_coordinates.push_back(0); number_sides = 3; }

		// Parameterised constructor 1 - reads in 6 doubles
		IsoscelesTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
		{
			number_polygons++;
			number_sides = 3;
			x_coordinates.push_back(x1);
			x_coordinates.push_back(x2);
			x_coordinates.push_back(x3);
			y_coordinates.push_back(y1);
			y_coordinates.push_back(y2);
			y_coordinates.push_back(y3);
		}

		// Parameterised constructor 2 - reads in vector of doubles
		IsoscelesTriangle(vector<double> coords)
		{
			number_polygons++;
			number_sides = 3;
			for (int i{ 0 }; i < 6; i += 2)
			{
				x_coordinates.push_back(coords[i]);
				y_coordinates.push_back(coords[i + 1]);

			}
		}

		// Parameterised constructor 3 - reads in radius, centre point and angle rotated by and constructs shape automaticaly
		IsoscelesTriangle(double base, double height, double x_centre, double y_centre, double angle)
		{
			number_polygons++;
			number_sides = 3;
			x_coordinates.clear(); y_coordinates.clear();

			double pi{ 3.14159265 };
			x_coordinates.push_back(x_centre);
			y_coordinates.push_back(y_centre + (2.0/3.0)*height);
			x_coordinates.push_back(x_centre + (base/2.0));
			y_coordinates.push_back(y_centre - (1.0 / 3.0)*height);
			x_coordinates.push_back(x_centre + (-base / 2.0));
			y_coordinates.push_back(y_centre - (1.0 / 3.0)*height);

			this->rotate(angle);
			cout << *this;


		}


		// Destructor
		~IsoscelesTriangle() { cout << "Destroying IsoscelesTriangle\n"; }

		// Other member functions
		void translate(const double x_translation, const double y_translation);
		void rescale(const double enlargement);
		void rotate(const double angle);

	};
}

#endif