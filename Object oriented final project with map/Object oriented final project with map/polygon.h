#pragma once
#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
//#include <windows.h> - WINDOWS ONLY

using namespace std;

namespace polygonSpace
{
	// Abstract base class for general polygon
	class Polygon
	{	

	protected:
		// member variables common to all shapes
		static int number_polygons;
		string polygon_name;
		int number_sides;
		vector<double> x_coordinates, y_coordinates;
	
	public:
		
		// member functions
		
		virtual ~Polygon() { cout << "Destroying Polygon\n"; number_polygons--;} // Destructor
		
		// Get the data
		int get_number_polygons();			// return total number of polygons
		string get_polygon_name() const;	// return the name of the polygon
		int get_number_sides() const;		// return total number of sides
		double get_perimeter() const;		// return shape perimeter
		double get_area();					// return shape area (must be non-self intersecting)
		void get_coordinates() const;		// return the polygon co-ordinates
		void get_info();				// get info (co-ordinates, perimeter) on the shape and total number of shapes
		
		// Set the data
		void put_in_polygon_name(const string name);					// user puts in the polygon name
		void put_in_coordinates(const vector<double> &coordinates);		// user puts in the co-ordinates
		void put_in_number_sides(const int num_sides);					// user puts in number of sides (used for other polygon)
		
		// Pure virtual functions for shape transformations
		virtual void translate(const double x_translation, const double y_translation) = 0;	  // translate the shape by (x,y)
		virtual void rescale(const double enlargement) = 0;		// rescale the shape by a factor about it centre
		virtual void rotate(const double angle) = 0;			// rotate the shape about its centre clockwise (angle in degrees)

		// Function to ensure shape not self-interesecting by ordering the points clockwise
		void sort_points_clockwise();

		// Friend functions for overloading input and output operators
		friend ostream & operator<<(ostream &os, const polygonSpace::Polygon &poly);
		friend istream & operator>>(istream &is, polygonSpace::Polygon &poly);




	};


}

#endif
