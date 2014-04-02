#ifndef NODE_COORD_FACTORY
#define NODE_COORD_FACTORY

#include "Node_coor_base.h"
#include "Node_coord_two_coords.h"

class Node_coor_factory{
public:
	static shared_ptr<Node_coor_base> get_node_coor(Node_coor_base::Type type, int size);

};

#endif