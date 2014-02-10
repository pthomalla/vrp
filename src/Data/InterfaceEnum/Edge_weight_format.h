#ifndef EDGE_WEIGHT_FORMAT
#define EDGE_WEIGHT_FORMAT
#include <string>
using namespace std;

struct  Edge_weight_format {
	enum Enum{ FUNCTION, FULL_MATRIX, UPPER_ROW, LOWER_ROW, UPPER_DIAG_ROW, LOWER_DIAG_ROW, UPPER_COL, LOWER_COL, UPPER_DIAG_COL, LOWER_DIAG_COL, INVALID };

	static const char *  typeNames[];

	static Enum to_Enum(const string &edge_weight_format);
    static string to_string(Enum edge_weight_format);
};

#endif
