#include "Edge_weight_format.h"
#include <algorithm>

const char *Edge_weight_format::typeNames[] = 
{ 
	"FUNCTION", "FULL_MATRIX", "UPPER_ROW", 
	"LOWER_ROW", "UPPER_DIAG_ROW", "LOWER_DIAG_ROW","UPPER_COL", 
	"LOWER_COL", "UPPER_DIAG_COL", "LOWER_DIAG_COL",
	"INVALID" 
};

Edge_weight_format::Enum Edge_weight_format::to_Enum(const string &edge_weight_format){
	int wynik = 0;
	std::find_if(typeNames, typeNames + 10,
		[&](const char * name){if (edge_weight_format == name)return true; wynik++; return false; });
	return (Enum)wynik;
}

string Edge_weight_format::to_string(Edge_weight_format::Enum edge_weight_format){
	return typeNames[edge_weight_format];
}