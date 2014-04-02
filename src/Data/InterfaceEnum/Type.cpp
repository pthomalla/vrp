//TO DO  poprawiæ Type::totype :(
#include "Type.h"
#include <algorithm>

const char* Type::typeNames[] = { "TSP", "ATSP", "SOP", "HCP", "CVRP", "TOUR", "INVALID" };

Type::Enum Type::to_Enum(string type){
	int wynik = 0;
	std::find_if(typeNames, typeNames +6, 
		[&](const char * name){if (type == name)return true; wynik++; return false; });
	return (Enum)wynik;
}

string Type::to_string(Type::Enum type){
	return typeNames[type];
}
