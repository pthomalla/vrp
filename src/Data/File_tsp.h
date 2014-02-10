#ifndef DATA
#define DATA

#include<string>
#include<iostream>
#include<vector>
#include<stdexcept>

using namespace std;

#include "InterfaceEnum/Display_data_type.h"
#include "InterfaceEnum/Edge_data_format.h"
#include "InterfaceEnum/Edge_weight_format.h"
#include "InterfaceEnum/Edge_weight_type.h"
#include "InterfaceEnum/Node_coord_type.h"
#include "InterfaceEnum/Type.h"
#include "Node/Node_coor_base.h"
#include "Edge/Matrix.h"
#include "Display_Data.h"
#include "Adapter.h"

#include <iostream>

struct File_tsp{
	File_tsp();

	std::string name, comment;
	unsigned int dimension, capacity;
	Adapter<Type> type;
	Adapter<Edge_weight_type> edge_weight_type;
	Adapter<Edge_weight_format> edge_weight_format;
	Adapter<Edge_data_format> edge_data_format;
	Adapter<Node_coord_type> node_coord_type;
	Adapter<Display_data_type> display_data_type;
	vector<int> demand;
	vector<int> depot;
	shared_ptr<Node_coor_base> nodes;
	shared_ptr<Matrix<int>> matrix;
	vector<Display_data> display_data_section;

	shared_ptr<const Matrix<int>> get_full_matrix()const;
};

#endif
