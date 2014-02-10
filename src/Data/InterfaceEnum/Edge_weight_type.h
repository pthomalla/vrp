#ifndef EDGE_WEIGHT_TYPE
#define EDGE_WEIGHT_TYPE

#include <iostream>
#include <string>
using namespace std;

struct Edge_weight_type{
	static const char * typeNames[];
	
	enum Enum{ EXPLICIT, DUC_2D, EUC_3D, MAX_2D, MAX_3D, MAN_2D, MAN_3D, CEIL_2D, GEO, ATT, XRAY1, XRAY2, SPECIAL, INVALID};
	
	static Enum to_Enum(string edge_weight_type);
	static string to_string(Enum edge_weight_type);
};

#endif