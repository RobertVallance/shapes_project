#include "other functions.h"

using namespace std;


// Use alias for our type of map of key 'string' and type 'Polygon object'
typedef map<string, polygonSpace::Polygon*> polygon_shape_map;


// main program
int main()
{
	// working to fixed number of decimal places (3 d.p.)
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(3);
	
	// map of polygons
	polygon_shape_map polygon_map;

	// Welcome messages
	cout << "WELCOME TO THE SHAPE EDITOR\n";
	cout << "We will first input some shapes and then edit them.\n\n";


	/////////////////////////////
	// ADD POLYGONS TO OUR MAP //
	/////////////////////////////

	// variables for our upcoming for while loop to add shapes
	bool continue_adding_polygons{ true };

	// if user wants to keep adding polygons, add them to our map (with add_shape function) where the key is the shape name.  Must be different each time.
	while (continue_adding_polygons)
	{

		add_shape(polygon_map);
	
		cout << "\nAdd another polygon (y/n): ";
		continue_adding_polygons = test_yes_or_no();

	}
	
	// if user says no, stop adding polygons to our map
	if (!continue_adding_polygons) cout << "Stopped adding polygons.\n";

	
	
	//////////////////////////
	// PRINT OUT OUR SHAPES //
	//////////////////////////
	
	cout << "\nThe shapes you inputted are:\n";

	// Print out shapes - note sorted by codes so use iterator!
	polygon_shape_map::iterator shapesIt;
	for (shapesIt = polygon_map.begin(); shapesIt != polygon_map.end(); ++shapesIt)
	{
		// save current text colour (white on black bgd) - ONLY WORKS ON WINDOWS
		//int default_attributes = current_attributes();

		cout << "\nShape name: ";
		//set_text_colour(shapesIt->second->get_number_sides());			// Now match text colour with shape colour - WINDOWS ONLY
		cout << shapesIt->first << endl << *shapesIt->second << endl;			// Print out shapes (names and their data)
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_attributes);	// Return text back to white on black bgd - WINDOWS ONLY
	}
	

	
	/////////////////////////////
	// PLAY AROUND WITH SHAPES //
	/////////////////////////////
	
	// some variables
	bool mess_with_shapes;
	if (!(polygon_map.empty())) { mess_with_shapes = true; }	// Just checks map not empty.  If it is then we can't continue.
	else { mess_with_shapes = false; }
	string shape_name;



	// if user wants to continue editing the shapes, then let them do so (with play_with_shape function)
	while (mess_with_shapes)
	{

		play_with_shape(polygon_map, shape_name);

		cout << "\nWould you like to edit the shapes again? (y/n) ";
		mess_with_shapes = test_yes_or_no();

	}

	// if user says no, stop adding polygons to our map
	if (!mess_with_shapes) cout << "Stopped messing with shapes.\n";
	cout << endl;

	
	
	
	//////////////////////////////////////
	// CLEAR UP MEMORY AT END OF PRORAM //
	//////////////////////////////////////s

	cout << "polygon_map has size " << polygon_map.size() << endl;
	for (shapesIt = polygon_map.begin(); shapesIt != polygon_map.end(); shapesIt++) delete shapesIt->second; 
	polygon_map.clear();
	cout << "polygon_map now has size " << polygon_map.size() << endl << endl;
	
	cout << "THANK YOU FOR USING THE SHAPE EDITOR.\n\n";

	// Stop command prompt from closing at end
	// system("pause");

	return 0;
}
