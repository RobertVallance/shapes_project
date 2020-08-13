#pragma once
#ifndef PENTAGON_H
#define PENTAGON_H

#include "polygon.h"

using namespace std;

namespace polygonSpace
{
	// Derived class for isosceles triangle
	class Pentagon : public polygonSpace::Polygon
	{
	public:

		// Default constructor
		Pentagon() { number_polygons++; x_coordinates.push_back(0); y_coordinates.push_back(0); number_sides = 5; }

		// Parameterised constructor 1 - reads in 6 doubles
		Pentagon(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5)
		{
			number_polygons++;
			number_sides = 5;
			x_coordinates.push_back(x1);
			x_coordinates.push_back(x2);
			x_coordinates.push_back(x3);
			x_coordinates.push_back(x4);
			x_coordinates.push_back(x5);
			y_coordinates.push_back(y1);
			y_coordinates.push_back(y2);
			y_coordinates.push_back(y3);
			y_coordinates.push_back(y4);
			y_coordinates.push_back(y5);

		}

		// Parameterised constructor 2 - reads in vector of doubles
		Pentagon(vector<double> coords)
		{
			number_polygons++;
			number_sides = 5;
			for (int i{ 0 }; i < 10; i += 2)
			{
				x_coordinates.push_back(coords[i]);
				y_coordinates.push_back(coords[i + 1]);

			}
		}

		// Parameterised constructor 3 - reads in radius, centre point and angle rotated by and constructs shape automaticaly
		Pentagon(double radius, double x_centre, double y_centre, double angle)
		{
			number_polygons++;
			number_sides = 5;
			double pi{ 3.14159265 };
			x_coordinates.clear(); y_coordinates.clear();
			for (int i{ 0 }; i < 5; i++)
			{
				x_coordinates.push_back(x_centre + radius*sin(2.0*pi*i/5.0 + angle*pi/180.0));
				y_coordinates.push_back(y_centre + radius*cos(2.0*pi*i/5.0 + angle*pi/180.0));
			}

			cout << *this;


		}

		// Destructor
		~Pentagon() { cout << "Destroying Pentagon\n"; }

		// Other member functions
		void translate(const double x_translation, const double y_translation);
		void rescale(const double enlargement);
		void rotate(const double angle);


	};
}

#endif