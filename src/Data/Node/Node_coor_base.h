#ifndef NODE_COOR_BASE
#define NODE_COOR_BASE
#include <vector>
#include <memory>

#include "../InterfaceEnum/Node_coord_type.h"
#include "../Edge/Matrix.h"
#include "../Adapter.h"
#include "../InterfaceEnum/Edge_weight_type.h"

class Node_coord_two_coords;
class Node_two_coord;

class Node_base{
public:
	virtual shared_ptr<Node_base> clone() = 0;
	virtual ~Node_base(){}
};

class Node_coor_base{
	Node_coor_base();
public:
	typedef Node_coord_type::Enum Type;
	typedef Node_coord_type Coord_type;
	const unsigned int size;

	virtual shared_ptr<Matrix<int>> get_full_matrix(Adapter<Edge_weight_type> type) const = 0; 

	Node_coor_base(unsigned int nodes_):size(nodes_){}

	virtual Type coords_type() const = 0;
	virtual shared_ptr<Node_base> get_prototipe_node() = 0;
	virtual void add_node(shared_ptr<Node_base> node, unsigned int number) = 0;
    virtual ~Node_coor_base(){}
	
};


template<typename Stream>
Stream& operator>>(Stream &stream, Node_coor_base &data)
{
	unsigned int number_node;
	for (unsigned int nodes_readed = 0; nodes_readed < data.size; nodes_readed++)
	{
		auto node = data.get_prototipe_node()->clone();
		stream >> number_node;
		switch (data.coords_type())
		{
			case Node_coor_base::Type::TWOD_COORDS:
			{
                Node_two_coord* tmp = (Node_two_coord*)node.get();//dynamic_cast<Node_two_coord*>(node.get());
				if (tmp) stream >> *tmp;
				else throw logic_error
					(
					"Stream& operator>>(Stream &stream, Node_coor_base &data)"
					"\n\tStream\t=\t" + string(typeid(Stream).name())+
					"\n\tdynamic_cast<Node_two_coord*> return nullptr"
					);
				break;
			}
			case Node_coor_base::Type::THREED_COORDS:
				throw runtime_error
					(
					"Stream& operator>>(Stream &stream, Node_coor_base &data)"
					"\n\tStream\t=\t" + string(typeid(Stream).name()) +
					"\n\tTHREED_COORDS not yet implemented"
					);
				break;
			case Node_coor_base::Type::NO_COORDS:
				throw logic_error
					(
					"Stream& operator>>(Stream &stream, Node_coor_base &data)"
					"\n\tStream\t=\t" + string(typeid(Stream).name()) +
					"\n\tOption:\tNO_COORDS"
					);
				break;
			default:
				throw logic_error
					(
					"Stream& operator>>(Stream &stream, Node_coor_base &data)"
					"\n\tStream\t=\t" + string(typeid(Stream).name()) +
					"\n\tnot defind:\t" + Node_coor_base::Coord_type::to_string(data.coords_type())
					);
				break;
		}
		data.add_node(node,number_node-1);//numerujemy  od zera
	}
	return stream;
}

template<typename Stream>
Stream& operator<<(Stream &stream, const Node_coor_base &data)
{
	switch (data.coords_type()){
		case Node_coor_base::Type::TWOD_COORDS:
		{
            const Node_coord_two_coords* tmp = (const Node_coord_two_coords*)&data;//dynamic_cast<const Node_coord_two_coords*>(&data);
			if (tmp) stream << *tmp;
			else throw logic_error
				(
				"Stream& operator<<(Stream &stream, Node_coor_base &data)"
				"\n\tStream\t=\t" + string(typeid(Stream).name()) +
				"\n\tdynamic_cast<const Node_two_coord*> return nullptr"
				);
			break;
		}
		case Node_coor_base::Type::THREED_COORDS:
			throw runtime_error
				(
				"Stream& operator<<(Stream &stream, Node_coor_base &data)"
				"\n\tStream\t=\t" + string(typeid(Stream).name()) +
				"\n\tTHREED_COORDS not yet implemented"
				);
			break;
		case Node_coor_base::Type::NO_COORDS:
			throw logic_error
				(
				"Stream& operator<<(Stream &stream, Node_coor_base &data)"
				"\n\tStream\t=\t" + string(typeid(Stream).name()) +
				"\n\tOption:\tNO_COORDS"
				);
			break;
		default:
			throw logic_error
				(
				"Stream& operator<<(Stream &stream, Node_coor_base &data)"
				"\n\tStream\t=\t" + string(typeid(Stream).name()) +
				"\n\tnot defind:\t" + Node_coor_base::Coord_type::to_string(data.coords_type())
				);
			break;
	
	}
	return stream;
}

#endif
