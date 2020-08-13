#pragma once
#ifndef OTHER_FUNCTIONS_H
#define OTHER_FUNCTIONS_H

#include "isosceles triangle.h"
#include "rectangle.h"
#include "pentagon.h"
#include "hexagon.h"
#include "other polygon.h"


// tests a number is correct input
template <class T> T input_and_test_number();

// returns the current attributes
const int current_attributes();

// sets text colour
void set_text_colour(int number_sides);

// tests whether an input string is "y" or "n"
bool test_yes_or_no();

// adds shapes to map
map<string, polygonSpace::Polygon*> add_shape(map<string, polygonSpace::Polygon*> &polygon_map);

// play with shapes
map<string, polygonSpace::Polygon*> play_with_shape(map<string, polygonSpace::Polygon*> &polygon_map, string shape_name);


// Return angle of coordinates from vertical
double get_clockwise_angle(vector<double> coord);


// compare the clockwise angle of two co-ordinate pairs (from the vertical)
bool compare_angles_clockwise(vector<double> &coord_i, vector<double> &coord_j);
//bool compare_angles_clockwise(double &x_coord_i, double &y_coord_i, double &x_coord_j, double &y_coord_j);

//double get_angle_coordinate(double &x_coord, double &y_coord);


#endif
