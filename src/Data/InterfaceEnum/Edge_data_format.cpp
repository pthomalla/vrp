#include "Edge_data_format.h"
#include <algorithm>

const char *Edge_data_format::typeNames[] = { "EDGE_LIST", "ADJ_LIST", "INVALID" };

Edge_data_format::Enum Edge_data_format::to_Enum(string value){
	int wynik = 0;
	std::find_if(typeNames, typeNames + 2,
		[&](const char * name){if (value == name)return true; wynik++; return false; });
	return (Enum)wynik;
}

string Edge_data_format::to_string(Edge_data_format::Enum value){
	return typeNames[value];
}