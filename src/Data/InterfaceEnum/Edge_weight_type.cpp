#include "Edge_weight_type.h"
#include <algorithm>

const char * Edge_weight_type::typeNames[] = 
{ "EXPLICIT", "DUC_2D", "EUC_3D", "MAX_2D", "MAX_3D", 
  "MAN_2D", "MAN_3D", "CEIL_2D", "GEO", "ATT", 
  "XRAY1", "XRAY2", "SPECIAL", "INVALID" 
};

Edge_weight_type::Enum Edge_weight_type::to_Enum(string edge_weight_type){
	int wynik = 0;
	std::find_if(typeNames, typeNames + 13,
		[&](const char * name){if (edge_weight_type == name)return true; wynik++; return false; });
	return (Enum)wynik;
}

string Edge_weight_type::to_string(Edge_weight_type::Enum edge_weight_type){
	return typeNames[edge_weight_type];
}
