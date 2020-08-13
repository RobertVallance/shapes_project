#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "polygon.h"

using namespace std;

namespace polygonSpace
{
	// Derived class for isosceles triangle
	class Rectangle : public polygonSpace::Polygon
	{

	public:

		// Default constructor
		Rectangle() { number_polygons++; x_coordinates.push_back(0); y_coordinates.push_back(0); number_sides = 4; }

		// Parameterised constructor 1 - reads in 6 doubles
		Rectangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
		{
			number_polygons++;
			number_sides = 4;
			x_coordinates.push_back(x1);
			x_coordinates.push_back(x2);
			x_coordinates.push_back(x3);
			x_coordinates.push_back(x4);
			y_coordinates.push_back(y1);
			y_coordinates.push_back(y2);
			y_coordinates.push_back(y3);
			y_coordinates.push_back(y4);
		}

		// Parameterised constructor 2 - reads in vector of doubles
		Rectangle(vector<double> coords)
		{
			number_polygons++;
			number_sides = 4;
			for (int i{ 0 }; i < 8; i += 2)
			{
				x_coordinates.push_back(coords[i]);
				y_coordinates.push_back(coords[i + 1]);

			}
		}

		// Parameterised constructor 3 - reads in length, width, centre point and angle rotated by and constructs shape automaticaly
		Rectangle(double x_extent, double y_extent, double x_centre, double y_centre, double angle)
		{
			number_polygons++;
			number_sides = 4;
			x_coordinates.clear(); y_coordinates.clear();

			double pi{ 3.14159265 };
			x_coordinates.push_back( x_centre + x_extent/2.0);
			y_coordinates.push_back( y_centre + y_extent/2.0);
			x_coordinates.push_back( x_centre + x_extent/2.0);
			y_coordinates.push_back( y_centre - y_extent/2.0);
			x_coordinates.push_back( x_centre - x_extent/2.0);
			y_coordinates.push_back( y_centre - y_extent/2.0);
			x_coordinates.push_back(x_centre - x_extent / 2.0);
			y_coordinates.push_back(y_centre + y_extent / 2.0);

			this->rotate(angle);
			cout << *this;


		}



		// Destructor
		~Rectangle() { cout << "Destroying Rectangle\n"; }

		// Other member functions
		void translate(const double x_translation, const double y_translation);
		void rescale(const double enlargement);
		void rotate(const double angle);


	};
}

#endif