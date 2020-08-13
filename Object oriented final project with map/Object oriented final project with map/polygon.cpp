#include "polygon.h"
#include "other functions.h"


namespace polygonSpace
{

  // Overload insertion to output stream for vertices
  ostream & operator<<(ostream &os, const polygonSpace::Polygon &poly)
  {
    poly.get_coordinates();
    return os;
  }



  // Overload istream so can input vertices during run-time
  istream & operator>>(istream &is, polygonSpace::Polygon &poly)
  {
    is.clear();	// clears istream

    vector<double> coordinates;
    double temp_coordinate;
    //bool input_again;
    int vertex_number{ 1 };
	
    // Iterate over number sides so user inputs vertices
    for (int i{ 0 }; i < poly.number_sides*2; i+=2)
      {

	// Put in x co-ordinate of vertex number (and check valid input)
	cout << "Please type in coordinate x" << vertex_number << ": ";
	temp_coordinate = input_and_test_number<double>();
	coordinates.push_back(temp_coordinate);
		
	// Put in y co-ordinate of vertex number (and check valid input)
	cout << "Please type in coordinate y" << vertex_number << ": ";
	temp_coordinate = input_and_test_number<double>();
	coordinates.push_back(temp_coordinate);	
		
	// Go to next vertex
	vertex_number++;
	
      }


    // Put these co-odinates into our object and print them out
    poly.put_in_coordinates(coordinates);
    cout << poly;

    return is;

  }

}
 
// Define static data member
int polygonSpace::Polygon::number_polygons{ 0 };


// Return total number of polygons
int polygonSpace::Polygon::get_number_polygons()
{
	return number_polygons;
}



// Return name of polygon
string polygonSpace::Polygon::get_polygon_name() const
{
	return string(polygon_name);
}



// Return number of sides of polygon
int polygonSpace::Polygon::get_number_sides() const
{
	return number_sides;
}


// Return perimeter of polygon
double polygonSpace::Polygon::get_perimeter() const
{
	double perimeter_value{ 0 };
	double side_length;

	// add up all sides but last
	for (int i{ 0 }; i < number_sides-1; i++)
	{
		side_length = pow( (pow((x_coordinates[i+1]-x_coordinates[i]), 2.0) + pow((y_coordinates[i+1]-y_coordinates[i]), 2.0)), 0.5);
		perimeter_value += side_length;
	}
	
	// add up last side (having to go back to element 0 again)
	side_length = pow((pow((x_coordinates[0] - x_coordinates[number_sides-1]), 2.0) + pow((y_coordinates[0] - y_coordinates[number_sides-1]), 2.0)), 0.5);
	perimeter_value += side_length;

	return perimeter_value;
}



double polygonSpace::Polygon::get_area()
{

	// Use shoelace formula to calculate the area of a non-self-intersecting shape
	double first_sum{ 0 }, second_sum{ 0 };
	
	// See Wikipedia https://en.wikipedia.org/wiki/Shoelace_formula for formula
	for (int i{ 0 }; i < number_sides-1; i++)
	{
		first_sum += x_coordinates[i] * y_coordinates[i + 1];
		second_sum += x_coordinates[i+1] * y_coordinates[i];
	}

	double area = 0.5*(first_sum + x_coordinates[number_sides - 1] * y_coordinates[0] - second_sum - x_coordinates[0] * y_coordinates[number_sides - 1]);
	
	// Return positive value of result
	return abs(area);
}



// Return the co-ordinates of the polygon in a nice form
void polygonSpace::Polygon::get_coordinates() const
{

	// save current text colour (white on black bgd) - WINDOWS ONLY
	// int default_attributes = current_attributes();
	
	cout << "Co-ordinates are:\n";
	
	// choose text colour depending on number of shape sides
	// set_text_colour(number_sides); - ONLY WORKS ON WINDOWS
	
	// Print out co-ordinates
	for (int i{ 0 }; i < number_sides; i++)
	{
		cout << "(x" << i+1 << ", y" << i+1 << ") = (" << x_coordinates[i] << ", " << y_coordinates[i] << ")\n";
	}

	// Return text colour back to white on black bgd - ONLY WORKA ON WINDOWS
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_attributes);
}




// Get info on the shapes (number sides, co-ordinates, perimeter) and total number of polygons
void polygonSpace::Polygon::get_info()
{
	
	// save current text colour (white on black bgd) - WINDOWS ONLY
	//int default_attributes = current_attributes();

	// choose text colour depending on number of shape sides - WINDOWS ONLY
	// set_text_colour(number_sides);

	// Print out shape name
	cout << "\nShape name is: " << polygon_name << endl;

	// Print out number sides
	cout << "\nNumber sides is: " << number_sides << endl;
	
	// Print out co-ordinates of shapes
	get_coordinates();
	
	// Print out perimeter
	cout << "\nPerimeter of shape is " << get_perimeter() << endl;

	// Print out area
	cout << "\nArea of shape is " << get_area() << endl;
	cout << "(area valid if not self-intersecting - use Sort Points Clockwise option otherwise)" << endl;

	// Return text colour back to white on black bgd - ONLY WORKS ON WINDOWS
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_attributes);

	// Print out total number of polygons we have
	cout << "\nThis is 1 of " << number_polygons << " polygons" << endl;
}


// User puts in name of polygon
void polygonSpace::Polygon::put_in_polygon_name(const string name)
{
	polygon_name = name;
}

// Splits vector of coordinates into x_coordinates and y_coordinates and puts them into object
void polygonSpace::Polygon::put_in_coordinates(const vector<double> &coordinates)
{
	// Clear any initial entries in the vectors
	x_coordinates.clear(); y_coordinates.clear();

	for (int i{ 0 }; i < number_sides * 2; i += 2)
	{
		x_coordinates.push_back(coordinates[i]);	// Puts in x co-ordinates
		y_coordinates.push_back(coordinates[i+1]);	// Puts in y co-ordinates
	}
}


// User puts in number of sides for polygon
void polygonSpace::Polygon::put_in_number_sides(const int num_sides)
{
	number_sides = num_sides;
}



// User can have co-ordinates sorted for them in a clockwise manner - means shape is no-longer self-intersecting
void polygonSpace::Polygon::sort_points_clockwise()
{

	// First store the co-ordinates in a vector of vectors
	vector< vector<double> > coordinates(number_sides);
	
	// Want there to be a set of number_sides of vector pairs within the vector 
	for (int i{ 0 }; i < number_sides; i++)
	{
		coordinates[i].push_back(x_coordinates[i]);
		coordinates[i].push_back(y_coordinates[i]);
	}

	// Sort the co-ordinates in clockwise order
	sort(coordinates.begin(), coordinates.end(), compare_angles_clockwise);

	// Clear the old co-ordinates
	x_coordinates.clear(), y_coordinates.clear();

	// Replace with the newly sorted co-ordinates
	for (int i{ 0 }; i < number_sides; i++)
	{
		x_coordinates.push_back(coordinates[i][0]);
		y_coordinates.push_back(coordinates[i][1]);
	}


}


