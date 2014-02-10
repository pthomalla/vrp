#include "Node_coord_factory.h"

shared_ptr<Node_coor_base> Node_coor_factory::get_node_coor(Node_coor_base::Type /*type*/, int size){

	return shared_ptr<Node_coor_base>(new Node_coord_two_coords(size));
}
