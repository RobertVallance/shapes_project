#pragma once
#ifndef HEXAGON_H
#define HEXAGON_H

#include "polygon.h"

using namespace std;

namespace polygonSpace
{
	// Derived class for isosceles triangle
	class Hexagon : public polygonSpace::Polygon
	{

	public:

		// Default constructor
		Hexagon() { number_polygons++; x_coordinates.push_back(0); y_coordinates.push_back(0); number_sides = 6; }

		// Parameterised constructor 1 - reads in 6 doubles
		Hexagon(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6)
		{
			number_polygons++;
			number_sides = 6;
			x_coordinates.push_back(x1);
			x_coordinates.push_back(x2);
			x_coordinates.push_back(x3);
			x_coordinates.push_back(x4);
			x_coordinates.push_back(x5);
			x_coordinates.push_back(x6);
			y_coordinates.push_back(y1);
			y_coordinates.push_back(y2);
			y_coordinates.push_back(y3);
			y_coordinates.push_back(y4);
			y_coordinates.push_back(y5);
			y_coordinates.push_back(y6);

		}

		// Parameterised constructor 2 - reads in vector of doubles
		Hexagon(vector<double> coords)
		{
			number_polygons++;
			number_sides = 6;
			for (int i{ 0 }; i < 12; i += 2)
			{
				x_coordinates.push_back(coords[i]);
				y_coordinates.push_back(coords[i + 1]);

			}
		}

		// Parameterised constructor 3 - reads in radius, centre point and angle rotated by and constructs shape automaticaly
		Hexagon(double radius, double x_centre, double y_centre, double angle)
		{
			number_polygons++;
			number_sides = 6;
			double pi{ 3.14159265 };
			x_coordinates.clear(); y_coordinates.clear();
			for (int i{ 0 }; i < 6; i++)
			{
				x_coordinates.push_back(x_centre + radius*sin(2.0*pi*i/6 + angle*pi/180.0));
				y_coordinates.push_back(y_centre + radius*cos(2.0*pi*i/6 + angle*pi/180.0));
			}
			
			cout << *this;



		}

		// Destructor
		~Hexagon() { cout << "Destroying Hexagon\n"; }

		// Other member functions
		void translate(const double x_translation, const double y_translation);
		void rescale(const double enlargement);
		void rotate(const double angle);

	};
}

#endif