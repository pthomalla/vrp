#ifndef TYPE_ENUM
#define TYPE_ENUM

#include <iostream>
#include <string>
using namespace std;

struct Type{
	static const char *  typeNames[];

	enum Enum{ TSP = 0, ATSP, SOP, HCP, CVRP, TOUR, INVALID };

	static Enum to_Enum(string type);
	static string to_string(Enum type);
};

#endif