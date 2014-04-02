#include "Display_data_type.h"
#include <algorithm>

const char *Display_data_type::typeNames[] = { "COORD_DISPLAY", "TWOD_DISPLAY", "NO_DISPLAY", "INVALID" };

Display_data_type::Enum Display_data_type::to_Enum(string value){
	int wynik = 0;
	find_if(typeNames, typeNames + 3,
		[&](const char * name){if (value == name)return true; wynik++; return false; });
	return Enum(wynik);

}

string Display_data_type::to_string(Display_data_type::Enum vlaue){
	return typeNames[vlaue];
}