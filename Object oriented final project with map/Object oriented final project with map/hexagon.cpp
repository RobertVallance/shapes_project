#include "hexagon.h"

using namespace std;
using namespace polygonSpace;




// Translate the hexagon by a certain (x, y)
void Hexagon::translate(const double x_translation, const double y_translation)
{
	for (int i{ 0 }; i < 6; i++)
	{
		x_coordinates[i] += x_translation;  // translate all x points by x_translation
		y_coordinates[i] += y_translation;  // translate all y points by y_translation
	}

}


// Rescale the hexagon
void polygonSpace::Hexagon::rescale(const double enlargement)
{
	// first find centre point of hexagon (taken to be centre of mass)
	double x_centre_of_mass, y_centre_of_mass;
	double x_coords_sum{ 0.0 }, y_coords_sum{ 0.0 };

	for (int i{ 0 }; i < 6; i++)
	{
		x_coords_sum += x_coordinates[i];
		y_coords_sum += y_coordinates[i];
	}

	// centre points given below
	x_centre_of_mass = x_coords_sum / 6.0;
	y_centre_of_mass = y_coords_sum / 6.0;

	// scale up by enlargement
	for (int i{ 0 }; i < 6; i++)
	{
		x_coordinates[i] = x_centre_of_mass + enlargement*(x_coordinates[i] - x_centre_of_mass);
		y_coordinates[i] = y_centre_of_mass + enlargement*(y_coordinates[i] - y_centre_of_mass);
	}


}



// Rotate the hexagon
void polygonSpace::Hexagon::rotate(const double angle)
{
	const double pi{ 3.14159 };


	// First create our rotation matrix - a vector of vector of doubles
	vector< vector<double> > rotation_matrix(2);
	rotation_matrix[0].push_back(cos(angle*pi / 180.0));
	rotation_matrix[0].push_back(sin(angle*pi / 180.0));
	rotation_matrix[1].push_back(-sin(angle*pi / 180.0));
	rotation_matrix[1].push_back(cos(angle*pi / 180.0));


	// Now find centre point of hexagon (taken to be centre of mass)
	double x_centre_of_mass, y_centre_of_mass;
	double x_coords_sum{ 0.0 }, y_coords_sum{ 0.0 };

	for (int i{ 0 }; i < 6; i++)
	{
		x_coords_sum += x_coordinates[i];
		y_coords_sum += y_coordinates[i];
	}

	// Centre points given below
	x_centre_of_mass = x_coords_sum / 6.0;
	y_centre_of_mass = y_coords_sum / 6.0;

	// Some temporary vectors to store the co-ordinates whilst doing working.
	// Needed as rotation formula requires both x and y co-ordinates and would get a redefinition of x_coordinates after rotating x.
	// But the y_coordinates depend on the ORIGINAL x_coordinates.  Don't want to use new x_coordinates.
	vector<double> x_coordinates_temp, y_coordinates_temp;

	// Rotate the shape
	for (int i{ 0 }; i < 6; i++)
	{
		x_coordinates_temp.push_back( x_centre_of_mass + rotation_matrix[0][0] * (x_coordinates[i] - x_centre_of_mass) + rotation_matrix[0][1] * (y_coordinates[i] - y_centre_of_mass) );
		y_coordinates_temp.push_back( y_centre_of_mass + rotation_matrix[1][0] * (x_coordinates[i] - x_centre_of_mass) + rotation_matrix[1][1] * (y_coordinates[i] - y_centre_of_mass) );
		x_coordinates[i] = x_coordinates_temp[i];
		y_coordinates[i] = y_coordinates_temp[i];
	}
	
}