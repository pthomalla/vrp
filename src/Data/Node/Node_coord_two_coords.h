#ifndef NODE_COORD_TWO_COORDS
#define NODE_COORD_TWO_COORDS

#include "Node_coor_base.h"
#include "../Edge/Matrix.h"


class Node_two_coord:public Node_base{
public :
    double x, y;
    shared_ptr<Node_base> clone() override;
};

template<typename Stream>
Stream& operator>>(Stream& stream, Node_two_coord& data)
{
	stream >> data.x >> data.y;
	return stream;
}

template<typename Stream>
Stream& operator<<(Stream& steram,const Node_two_coord& data)
{
	return steram << "(" << data.x << ", " << data.y << ")";
}

class Node_coord_two_coords :public Node_coor_base{
	
public:
	vector<Node_two_coord> nodes;
	Node_coord_two_coords(int nodes);

	shared_ptr<Matrix<int>> get_full_matrix(Adapter<Edge_weight_type> type) const override;

	Type coords_type() const override;
	shared_ptr<Node_base> get_prototipe_node() override;
	void add_node(shared_ptr<Node_base> node, unsigned int number) override;


};

template<typename Stream>
Stream& operator<<(Stream& stream, const Node_coord_two_coords& data){
	stream << Node_coord_two_coords::Coord_type::to_string(data.coords_type());
	for (unsigned int i = 0; i < data.size; i++)
	{
		stream << "\n" << i+1 <<"\t"<< data.nodes.at(i) ;
	}
	return stream;
}

#endif
