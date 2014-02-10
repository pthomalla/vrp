#include "Node_coord_type.h"
#include <algorithm>

const char *Node_coord_type::typeNames[] = {"TWOD_COORDS", "THREED_COORDS", "NO_COORDS","INVALID" };

Node_coord_type::Enum Node_coord_type::to_Enum(string value){
	int wynik = 0;
	std::find_if(typeNames, typeNames + 3,
		[&](const char * name){if (value == name)return true; wynik++; return false; });
	return (Enum)wynik;
	
}

string Node_coord_type::to_string(Node_coord_type::Enum value){
	return typeNames[value];
}