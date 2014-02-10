#include "Node_coord_two_coords.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <math.h>

shared_ptr<Node_base> Node_two_coord::clone()
{
	 return shared_ptr<Node_base>(new Node_two_coord()); 
}

Node_coord_two_coords::Node_coord_two_coords(int size):Node_coor_base(size),nodes(size)
{
	nodes.shrink_to_fit();
}

Node_coord_two_coords::Type Node_coord_two_coords::coords_type() const
{
	return Node_coord_two_coords::Type::TWOD_COORDS;
}

shared_ptr<Node_base> Node_coord_two_coords::get_prototipe_node()
{
	return shared_ptr<Node_base>(new Node_two_coord);
}

void Node_coord_two_coords::add_node(shared_ptr<Node_base> node, unsigned int number)
{
	if (number >= size)
		throw out_of_range(
		"Node_coord_two_coords::add_node(shared_ptr<Node_base> node, unsigned int number):"
		"\n\tnumber\t=\t" + to_string(number) +
		"\n\tsize\t=\t" + to_string(size)
		);
	shared_ptr<Node_two_coord> ptr = dynamic_pointer_cast<Node_two_coord>(node);
	if (!ptr)
		throw out_of_range(
		"Node_coord_two_coords::add_node(shared_ptr<Node_base> node, unsigned int number):"
		"\n\tnumber\t=\t" + to_string(number) +
		"\n\tdynamic_pointer_cast<Node_two_coord>\t=\tnullptr"
		);
	nodes[number] = *ptr;
}

int dist(Node_two_coord first, Node_two_coord second)
{
	auto x = first.x - second.x;
	auto y = first.y - second.y;
	return (int) (sqrt(x*x + y*y)+0.5);
}

double tude(double arg)
{
	auto  deg = arg + 0.5;
	double min = arg - deg;
	return 3.141592*(deg + 5.0*min / 3.0) / 180.0;
}

int dist_geo(Node_two_coord first, Node_two_coord second)
{
	auto longitude_frist = tude(first.y);
	auto longitude_second = tude(second.y);
	auto latitude_first = tude(first.x);
	auto latitude_second = tude(second.y);

	auto q1 = cos(longitude_frist - longitude_second);
	auto q2 = cos(latitude_first - latitude_second);
	auto q3 = cos(latitude_first + latitude_second);
	
	return (int)(6378.388*acos(0.5*((1.0 + q1)*q2 - (1.0 - q1)*q3))*1.0);
}

shared_ptr<Matrix<int>> Node_coord_two_coords::get_full_matrix(Adapter<Edge_weight_type> type) const 
{
	shared_ptr<Matrix<int>> result(make_shared<Matrix<int>>(size));
	int(*distance)(Node_two_coord,Node_two_coord);
	switch (type)
	{
	case Edge_weight_type::GEO:
		distance = dist_geo;
		break;
	default:
		distance = dist;
	}
	for (unsigned int row = 0; row < nodes.size(); row++)
		for (unsigned int column = row + 1; column < nodes.size(); column++)
			(*result)[row][column] = (*result)[column][row] = 
			distance(nodes.at(row), nodes.at(column));

	return result;
}

