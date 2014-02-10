#ifndef DISPLAY_DATA_TYPE
#define DISPLAY_DATA_TYPE
#include <string>
using namespace std;

struct Display_data_type{
	enum Enum {COORD_DISPLAY, TWOD_DISPLAY, NO_DISPLAY, INVALID};
	
	static const char *typeNames[];

	static Enum to_Enum(string value);
	static string to_string(Enum value);
};

#endif