#ifndef EDGE_DATA_FORMAT
#define EDGE_DATA_FORMAT
#include <string>

using namespace std;

struct Edge_data_format{
	enum Enum{ EDGE_LIST, ADJ_LIST, INVALID };

	static const char *typeNames[];

	static Enum to_Enum(string edge_data_format);
	static string to_string(Enum edge_weight_format);
};

#endif