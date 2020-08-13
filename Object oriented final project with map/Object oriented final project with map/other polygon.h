#pragma once
#pragma once
#ifndef OTHER_POLYGON_H
#define OTHER_POLYGON_H

#include "polygon.h"

using namespace std;

namespace polygonSpace
{
	// Derived class for isosceles triangle
	class OtherPolygon : public polygonSpace::Polygon
	{

	public:

		// Default constructor
		OtherPolygon() { number_polygons++; x_coordinates.push_back(0); y_coordinates.push_back(0); number_sides = 0; }


		// Parameterised constructor 2 - reads in vector of doubles
		OtherPolygon(int num_sides, vector<double> coords)
		{
			number_polygons++;
			number_sides = num_sides;
			for (int i{ 0 }; i < 2*number_sides; i += 2)
			{
				x_coordinates.push_back(coords[i]);
				y_coordinates.push_back(coords[i + 1]);

			}
		}

		// Parameterised constructor 3 - reads in radius, centre point and angle rotated by and constructs shape automaticaly
		OtherPolygon(int num_sides, double radius, double x_centre, double y_centre, double angle)
		{
			number_polygons++;
			number_sides = num_sides;
			double pi{ 3.14159265 };
			x_coordinates.clear(); y_coordinates.clear();
			for (int i{ 0 }; i < num_sides; i++)
			{
				x_coordinates.push_back(x_centre + radius*sin(2.0*pi*i/num_sides + angle*pi/180.0));
				y_coordinates.push_back(y_centre + radius*cos(2.0*pi*i/num_sides + angle*pi/180.0));
			}

			cout << *this;


		}

		// Destructor
		~OtherPolygon() { cout << "Destroying OtherPolygon\n"; }

		// Other member functions
		void translate(const double x_translation, const double y_translation);
		void rescale(const double enlargement);
		void rotate(const double angle);


	};
}

#endif