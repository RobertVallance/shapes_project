#include "other functions.h"

using namespace std;


// Template to check if a cin INTEGER or DOUBLE is valid.  If not, prompts user to re-enter number.
template <class T> T input_and_test_number()
{
	
	T value;
	bool input_again{ true };
	
	cin >> std::noskipws >> value; // Ask user for value and ignore new line characters

	// If value is a number betweeen -999 and 999, then it is valid so no need to input again
	if (cin) { input_again = false; }
	if (value < -999.9 || value > 999.0) { input_again = true; }
	
	cin.ignore();

	
	// While loop so user has to keep putting in a value until it is of correct form
	while (input_again)
	{
		cin.ignore(100, '\n'); cin.clear(); cin.ignore(100, '\n');
		cout << "Invalid input! Please try again: ";
		cin >> std::noskipws >> value;
		if (cin) { input_again = false; }
		if (value < -999.9 || value > 999.0) { input_again = true; }
		cin.ignore();
	}
	return value;
}


// Template to check if a getline string is a yes or no.  If not, prompts user to re-enter string.
bool test_yes_or_no()
{
	string answer;
	bool input_again;

	getline(cin, answer);
	
	// If answer is "y" or "n" (or similar) then it is valid so no need to input again
	if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes" || answer == "YES") { input_again = false; return true; }
	else if (answer == "n" || answer == "N" || answer == "no" || answer == "No" || answer == "NO") { input_again = false; return false; }
	
	// Oterwise, input is invalid so the user will need to re-enter string
	else { input_again = true; }

	// While loop so user has to keep putting in a string until it is "y" or "n" (or similar)
	while (input_again)
	{
		cout << "Invalid input! Please try again: ";
		cin.sync();
		getline(cin, answer);
		if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes" || answer == "YES") { input_again = false; return true; }
		else if (answer == "n" || answer == "N" || answer == "no" || answer == "No" || answer == "NO") { input_again = false; return false; }
	}
	
}


// returns the current attributes - WINDOWS ONLY
/*
const int current_attributes()
{
	CONSOLE_SCREEN_BUFFER_INFO current_buffer_data;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &current_buffer_data);
	return current_buffer_data.wAttributes;
}
*/


// Function to set text colour (dependent on shape type (number sides)) - ONLY WORKS ON WINDOWS
/*
void set_text_colour(int number_sides)
{
	

	if (number_sides == 3)
	{
		// Text colour is green
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	else if (number_sides == 4)
	{
		// Text colour is red
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	else if (number_sides == 5)
	{
		// Text colour is cyan
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	else if (number_sides == 6)
	{
		// Text colour is pink
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	else if (number_sides > 6)
	{
		// Text colour is yellow
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
}
*/

// Function that returns a map of added shapes.  User specifies tpye of shape and shape parameters.
map<string, polygonSpace::Polygon*> add_shape(map<string, polygonSpace::Polygon*> &polygon_map)
{
	int shape_type;
	string shape_name;

	// User inputs shape type
	cout << "Please enter the shape number (1-5) you would like. Options are:\n";
	cout << "1 Isosceles Triangle \n2 Rectangle \n3 Pentagon \n4 Hexagon \n5 Other\n";
	cout << "Number: ";

	// Tests for valid input using input_and_test_number function (with int) and also makes sure int is between 1 and 5
	shape_type = input_and_test_number<int>();
	while (shape_type < 1 || shape_type > 5) { cout << "Integer must be between 1 and 5: "; shape_type = input_and_test_number<int>(); }
	
	
	// User inputs a name for the shape
	cout << "\nPlease type in a name for this shape you chose: ";
	getline(cin, shape_name, '\n');
	
	// The following code makes sure the user inputs something for the name and that it doesn't clash with another existing name
	bool naming_fail{ true }, match{ true };
	while (naming_fail)
	{
		// If user doesn't put in name, then prompt them to again to re-enter name
		if (shape_name == "")
		{
			cin.clear(); cout << "Cannot have no name.  Please rename: "; getline(cin, shape_name);
		}

		// If user inputs a name that already exists, then prompt them again to re-enter name
		else if (match)
		{
			match = false;
			
			// Iterates over polygon_map keys to search for name clash
			for (auto shapesIt = polygon_map.begin(); shapesIt != polygon_map.end(); ++shapesIt)
			{
				if (shape_name == shapesIt->first) { match = true;  cin.clear(); cout << "Cannot have name clash.  Please rename: "; getline(cin, shape_name); break; }
			}
		}
		else { naming_fail = false; }
	}
	
	// if user wants isosceles triangle, then let them put one into map
	if (shape_type == 1)
	{
		// Relevant variables for isosceles triangle
		double base, height, x_centre, y_centre, angle; 

		// User puts in the variables, which are checked with input_and_test_number function of type double
		cout << "Please type in base length: ";
		base = input_and_test_number<double>();
		cout << "Please type in height: ";
		height = input_and_test_number<double>();
		cout << "Please type in x centre point: ";
		x_centre = input_and_test_number<double>();
		cout << "Please type in y centre point: ";
		y_centre = input_and_test_number<double>();
		cout << "Please type in clockwise angle of top point from vertical: ";
		angle = input_and_test_number<double>();
		polygon_map[shape_name] = new polygonSpace::IsoscelesTriangle(base, height, x_centre, y_centre, angle);
		polygon_map[shape_name]->put_in_polygon_name(shape_name);


	}

	// if user wants rectangle, then let them put one into map
	else if (shape_type == 2)
	{
		// Relevant variables for rectangle
		double x_extent, y_extent, x_centre, y_centre, angle;

		// User puts in the variables, which are checked with input_and_test_number function of type double
		cout << "Please type in x length: ";
		x_extent = input_and_test_number<double>();
		cout << "Please type in y length: ";
		y_extent = input_and_test_number<double>();
		cout << "Please type in x centre point: ";
		x_centre = input_and_test_number<double>();
		cout << "Please type in y centre point: ";
		y_centre = input_and_test_number<double>();
		cout << "Please type in clockwise angle shape rotated by: ";
		angle = input_and_test_number<double>();
		polygon_map[shape_name] = new polygonSpace::Rectangle(x_extent, y_extent, x_centre, y_centre, angle);
		polygon_map[shape_name]->put_in_polygon_name(shape_name);

	}

	// if user wants pentagon, then let them put one into map
	else if (shape_type == 3)
	{

		// Ask user if shape will be regular (means generates co-ordinates automatically)
		bool regular_shape;
		cout << "Will this be a regular pentagon? (y/n): ";
		regular_shape = test_yes_or_no();

		// If regular, then ask for encompassing radius, centre-point and angle to build shape (and check values sensible)
		if (regular_shape)
		{
			double radius, x_centre, y_centre, angle;
			cout << "Please type in radius: ";
			radius = input_and_test_number<double>();
			cout << "Please type in x centre point: ";
			x_centre = input_and_test_number<double>();
			cout << "Please type in y centre point: ";
			y_centre = input_and_test_number<double>();
			cout << "Please type in clockwise angle of top point from vertical: ";
			angle = input_and_test_number<double>();
			polygon_map[shape_name] = new polygonSpace::Pentagon(radius, x_centre, y_centre, angle);
			polygon_map[shape_name]->put_in_polygon_name(shape_name);
		}

		// If not a regular shape, user inputs co-ordinates manually (uses overloaded >> operator)
		else if (!regular_shape)
		{
			cout << "Inputting co-ordinates manually in order lines will be drawn.\n";
			polygon_map[shape_name] = new polygonSpace::Pentagon();
			cin >> *polygon_map[shape_name];
			polygon_map[shape_name]->put_in_polygon_name(shape_name);
		}

	}

	// if user wants hexagon, then let them put one into map
	else if (shape_type == 4)
	{

		// Ask user if shape will be regular (means generates co-ordinates automatically)
		bool regular_shape;
		cout << "Will this be a regular hexagon? (y/n): ";
		regular_shape = test_yes_or_no();

		// If regular, then ask for encompassing radius, centre-point and angle to build shape (and check values sensible)
		if (regular_shape)
		{
			double radius, x_centre, y_centre, angle;
			cout << "Please type in radius: ";
			radius = input_and_test_number<double>();
			cout << "Please type in x centre point: ";
			x_centre = input_and_test_number<double>();
			cout << "Please type in y centre point: ";
			y_centre = input_and_test_number<double>();
			cout << "Please type in clockwise angle of top point from vertical: ";
			angle = input_and_test_number<double>();
			polygon_map[shape_name] = new polygonSpace::Hexagon(radius, x_centre, y_centre, angle);
			polygon_map[shape_name]->put_in_polygon_name(shape_name);
		}

		// If not a regular shape, user inputs co-ordinates manually (uses overloaded >> operator)
		else if (!regular_shape)
		{
			cout << "Inputting co-ordinates manually in order lines will be drawn.\n";
			polygon_map[shape_name] = new polygonSpace::Hexagon();
			cin >> *polygon_map[shape_name];
			polygon_map[shape_name]->put_in_polygon_name(shape_name);
		}

	}

	// If shape type is Other, then user can generate a regular shape or add their own co-ordinates manually
	else if (shape_type == 5)
	{

		// First ask user for number of sides for shape
		int number_sides;
		cout << "Please type in number of sides for shape: ";
		number_sides = input_and_test_number<int>();
		while (number_sides < 3) { cout << "Integer must be greater than 2: "; number_sides = input_and_test_number<int>(); }

		// Ask user if shape will be regular (means generates co-ordinates automatically)
		bool regular_shape;
		cout << "Will this be a regular shape? (y/n): ";
		regular_shape = test_yes_or_no();

		// If regular, then ask for encompassing radius, centre-point and angle to build shape (and check values sensible)
		if (regular_shape)
		{
			double radius, x_centre, y_centre, angle;
			cout << "Please type in radius: ";
			radius = input_and_test_number<double>();
			cout << "Please type in x centre point: ";
			x_centre = input_and_test_number<double>();
			cout << "Please type in y centre point: ";
			y_centre = input_and_test_number<double>();
			cout << "Please type in clockwise angle of top point from vertical: ";
			angle = input_and_test_number<double>();
			polygon_map[shape_name] = new polygonSpace::OtherPolygon(number_sides, radius, x_centre, y_centre, angle);
			polygon_map[shape_name]->put_in_polygon_name(shape_name);
		}
		
		// If not a regular shape, user inputs co-ordinates manually (uses overloaded >> operator)
		else if (!regular_shape)
		{
			cout << "Inputting co-ordinates manually in order lines will be drawn.\n";
			polygon_map[shape_name] = new polygonSpace::OtherPolygon();
			polygon_map[shape_name]->put_in_number_sides(number_sides);
			cin >> *polygon_map[shape_name];
			polygon_map[shape_name]->put_in_polygon_name(shape_name);
		}

	}

	// Return filled map at end
	return polygon_map;
}


// Function to play with the shape (translate, rescale, rotate) and get info on the shape
map<string, polygonSpace::Polygon*> play_with_shape(map<string, polygonSpace::Polygon*> &polygon_map, string shape_name)
{

	// First ask the user which shape they want to edit
	cout << "Please type in the name of the shape you would like to edit.\n";
	cout << "Options are: ";
	
	// save current text colour (white on black bgd) - WINDOWS ONLY
	//int default_attributes = current_attributes();

	// Print out the shape names (using iterator over key names in map) so the user can decide
	for (auto shapesIt = polygon_map.begin(); shapesIt != polygon_map.end(); ++shapesIt)
	{
		if (shapesIt != polygon_map.begin() && shapesIt != polygon_map.end()) cout << ", ";
		// REMOVED AS ONLY WORKS WITH WINDOWS
		//set_text_colour(shapesIt->second->get_number_sides());	// sets text colour to match shape colour
		cout << shapesIt->first;
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_attributes);		// returns to white text on black bgd - WINDOWS ONLY
	}
	cout << endl;


	// user decides which shape to edit
	cout << "Name: "; getline(cin, shape_name);

	
	// The following code searches for a match between user input and key name.  If match, then continue.  If not, then re-enter.
	
	bool match;
	for (auto shapesIt = polygon_map.begin(); shapesIt != polygon_map.end(); ++shapesIt)
	{
		if (shape_name == shapesIt->first) { match = true; break; }		// If match, break out of loop
		else { match = false; }											// If no match, then pass to upcoming while loop
	}

	// While user input doesn't match key name, then keep asking user for input
	while (!match)
	{
		cin.sync();
		cout << "Please type in correct name: "; getline(cin, shape_name);
		for (auto shapesIt = polygon_map.begin(); shapesIt != polygon_map.end(); ++shapesIt)
		{
			if (shape_name == shapesIt->first) { match = true; break; }
			else { match = false; }
		}
	}	

	// Now Ask user what they want to do with the shape
	cout << "\nPlease type in (number 1-5) what you would like to do with "  << polygon_map[shape_name]->get_polygon_name() << ".\n";
	cout << "Options are:\n";
	cout << "1 Translate \n2 Rescale \n3 Rotate \n4 Get info \n5 Sort points clockwise \n";
	cout << "Number: "; 
	
	int shape_edit;
	
	// Tests for valid input using input_and_test_number function (with int) and also makes sure int is between 1 and 4
	shape_edit = input_and_test_number<int>();
	while (shape_edit < 1 || shape_edit > 5) { cout << "Integer must be between 1 and 5: "; shape_edit = input_and_test_number<int>(); }


	// If choose option 1, translate the shape by a chosen (x, y)
	if (shape_edit == 1)
	{
		double x_translation, y_translation;
		
		// Input translation co-ordinates and check they are sensible input
		cout << "\nPlease type in the coordinates x, y you would like to translate by:\n";
		cout << "x translation = "; x_translation = input_and_test_number<double>();
		cout << "y translation = "; y_translation = input_and_test_number<double>();

		// Perform transformation
		polygon_map[shape_name]->translate(x_translation, y_translation);

		// Print out co-ordinates after translation
		cout << "\nTranslated by (" << x_translation << ", " << y_translation << ").\n";
		polygon_map[shape_name]->get_coordinates();
	}

	// If choose option 2, rescale the shape by a chose factor
	else if (shape_edit == 2)
	{
		double enlargement;
		
		// Input rescaling factor and check it is a sensible input
		cout << "\nPlease type in the rescaling factor:\n";
		cout << "Enlargement = ";
		enlargement = input_and_test_number<double>();

		// Perform transformation
		polygon_map[shape_name]->rescale(enlargement);

		// Print out co-ordinates after rescaling
		cout << "\nRescaled by factor of " << enlargement << ".\n";
		polygon_map[shape_name]->get_coordinates();
	}

	// If choose option 3, rotate the shape by a certain angle clockwise (in degrees)
	else if (shape_edit == 3)
	{
		double angle;
		// Input angle and check it is a sensible input
		cout << "\nPlease type in the clockwise rotation angle (degrees):\n";
		cout << "Angle = ";
		angle = input_and_test_number<double>();

		// Perform transformation
		polygon_map[shape_name]->rotate(angle);

		// Print out co-ordinates after rotation
		cout << "\nRotated by angle " << angle << " degrees.\n";
		polygon_map[shape_name]->get_coordinates();
	}

	// Show info (co-ordinates and perimeter of shape)
	else if (shape_edit == 4)
	{
		polygon_map[shape_name]->get_info();
	}

	// Sort the points clockwise (starting in bottom left quadrant)
	else if (shape_edit == 5)
	{
		cout << "\nSorting points clockwise (from bottom left quadrant).\n";
		polygon_map[shape_name]->sort_points_clockwise();
		polygon_map[shape_name]->get_coordinates();
	}

	// Return edited map at end
	return polygon_map;
}


// Return angle of coordinates from vertical
double get_clockwise_angle(vector<double> coord)
{
	double pi{ 3.14159 };
	return atan2(coord[0]*pi/180.0, coord[1]*pi/180.0);
}


// compare the clockwise angle of two co-ordinate pairs (from the vertical)
bool compare_angles_clockwise(vector<double> &coord_i, vector<double> &coord_j)
{
	return get_clockwise_angle(coord_i) < get_clockwise_angle(coord_j);
}
