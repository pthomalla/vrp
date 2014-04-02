#ifndef NODE_COORD_TYPE
#define NODE_COORD_TYPE

#include <string>
using namespace std;

struct Node_coord_type{
	static const char* typeNames[];

	enum Enum { TWOD_COORDS, THREED_COORDS, NO_COORDS, INVALID };

	static Enum to_Enum(string value);
	static string to_string(Enum value);

};

#endif