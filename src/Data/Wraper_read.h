#ifndef WRAPER_READ
#define WRAPER_READ

//#include <string>
//#include <map>
#include <set>
#include <stdexcept>

#include "Node/Node_coord_factory.h"
#include "Edge/Matrix.h"
#include "File_tsp.h"

class Wraper_reader_base{
public:
	 static std::set<string> not_colon;
};

std::set<string> Wraper_reader_base::not_colon =
{ "NODE_COORD_SECTION", "DEPOT_SECTION", "DEMAND_SECTION", "EDGE_DATA_SECTION", "EDGE_WEIGHT_SECTION" ,"DISPLAY_DATA_SECTION"};


template <typename Stream>
class Wraper_reader:public Wraper_reader_base{
	void(*read)(Stream& stream, File_tsp& file);
	File_tsp* file;
public:
	Stream& start_read(Stream&);
	Wraper_reader();
	Wraper_reader(void(*)(Stream&, File_tsp&), File_tsp *f = nullptr);
	static std::map<string,Wraper_reader> pars_function;

	Wraper_reader& operator()(File_tsp* file_tsp);
};

template< typename Stream>
Wraper_reader<Stream>& Wraper_reader<Stream>::operator()(File_tsp* file_tsp)
{
	file = file_tsp;
	return *this;
}

template<typename Stream>
Wraper_reader<Stream>::Wraper_reader() : read([](Stream&, File_tsp&)->void{}), file(nullptr){}

template<typename Stream>
Wraper_reader<Stream>::Wraper_reader(void(*r)(Stream&, File_tsp&), File_tsp *f)
: read(r), file(f)
{
}

template<typename Stream>
Stream& Wraper_reader<Stream>::start_read(Stream& stream)
{
	read(stream,*file);
	return stream;
}

template<typename Stream>
Stream& operator>>(Stream& stream, Wraper_reader<Stream>& file)
{
	return file.start_read(stream);
}

template<typename Stream>
std::map<std::string,Wraper_reader<Stream>> Wraper_reader<Stream>::pars_function;


template<typename Stream>
void init()
{
	static auto& pars_function(Wraper_reader<Stream>::pars_function);

	pars_function.clear();

    typedef Wraper_reader<Stream> wra;
	pars_function["NAME"] = wra([](Stream& stream, File_tsp& file){stream >> file.name; });
	pars_function["TYPE"] = wra([](Stream& stream, File_tsp& file){stream >> file.type; });
	pars_function["COMMENT"] = wra([](Stream& stream, File_tsp& file){getline(stream, file.comment); });
	pars_function["DIMENSION"] = wra([](Stream& stream, File_tsp& file){stream >> file.dimension; });
	pars_function["CAPACITY"] = wra([](Stream& stream, File_tsp& file){stream >> file.capacity; });
	pars_function["EDGE_WEIGHT_TYPE"] = wra([](Stream& stream, File_tsp& file){stream >> file.edge_weight_type; });
	pars_function["EDGE_WEIGHT_FORMAT"] = wra([](Stream& stream, File_tsp& file){stream >> file.edge_weight_format; });
	pars_function["EDGE_DATA_FORMAT"] = wra([](Stream& stream, File_tsp& file){stream >> file.edge_data_format; });
	pars_function["NODE_COORD_TYPE"] = wra([](Stream& stream, File_tsp& file){stream >> file.node_coord_type; });
    pars_function["DISPLAY_DATA_TYPE"] = wra([](Stream& stream, File_tsp& file){stream >> file.display_data_type; });
	pars_function["DEMAND_SECTION"] = wra([](Stream& stream, File_tsp& file){
		if (file.dimension == 0) throw logic_error(
				"dimension not init"
				"\nstd::map<std::string,Wraper_reader<Stream>> Wraper_reader<Stream>::pars_function"
				"\n\tname function\t=\tDEMAND_SECTION"
				"\n\tStream\t=\t"+string(typeid(Stream).name())

			);
		file.demand.resize(file.dimension);
		unsigned int node;
		for (unsigned int i = 0; i < file.dimension; i++){
			stream >> node;
			if (node > file.dimension) throw "hwddp";
			stream >> file.demand[node - 1];
		}
	});
	pars_function["DEPOT_SECTION"] = wra([](Stream& stream, File_tsp& file){
		int node;
		stream >> node;
		do{
			file.depot.push_back(node-1);
			stream >> node;
		} while (node!=-1);
	});
	pars_function["NODE_COORD_SECTION"] = wra([](Stream& stream, File_tsp& file){
		if (file.node_coord_type == Node_coor_base::Type::TWOD_COORDS || file.node_coord_type.value == Node_coor_base::Type::INVALID)
			file.nodes = Node_coor_factory::get_node_coor(Node_coor_base::Type::TWOD_COORDS, file.dimension);
		stream >> *file.nodes;// .get();
	});
	pars_function["EDGE_WEIGHT_SECTION"] = wra([](Stream& stream, File_tsp& file){
		file.matrix = make_shared<Matrix<int>>(file.dimension,file.edge_weight_format);
		stream >> *file.matrix;
	});
	pars_function["DISPLAY_DATA_SECTION"] = wra([](Stream& stream, File_tsp& file){
		file.display_data_section.clear();
		Display_data value;
		for (unsigned int i = 0; i < file.dimension; i++)
		{ 
			stream >> value.numer >> value.first >> value.secnd; 
			file.display_data_section.push_back(value);
		}
		
	});
    pars_function["EOF"] = wra([](Stream&, File_tsp&){});

}



    template<typename Stream>
    Stream& operator>>(Stream& input, File_tsp& file)
    {
        static auto& pars_function(Wraper_reader<Stream>::pars_function);
        if (Wraper_reader<Stream>::pars_function.empty())
            init<Stream>();

        string option;
        char colon;
        while (true){
            input >> option;
            if (option.back() == ':')option.pop_back();
            else if (Wraper_reader<Stream>::not_colon.find(option) == Wraper_reader<Stream>::not_colon.end()) input >> colon;
            if (pars_function.find(option) == pars_function.end()) throw logic_error(
                "Not find option error"
                "\ntemplate<typename Stream>"
                "\nStream& operator>>(Stream& input, File_tsp& file)"
                "\n\tStream\t=\t" + string(typeid(input).name()) +
                "\n\toption\t=\t" + option
                );
            input >> pars_function[option](&file);

            if (option == "EOF") return input;
        }
    }

    template<typename Stream>
    Stream& operator<<(Stream& output,const  File_tsp& file){
        output << "NAME :\t" << file.name
            << "\nCOMMENT :\t" << file.comment
            << "\nTYPE :\t" << file.type
            << "\nDIMENSION :\t" << file.dimension
            << "\nEDGE_WEIGHT_TYPE :\t" << file.edge_weight_type
            << "\nEDGE_WEIGHT_FORMAT :\t" << file.edge_weight_format
            << "\nEDGE_DATA_FORMAT :\t"<< file.edge_data_format
            << "\nNODE_COORD_TYPE :\t"<< file.node_coord_type
            << "\nDISPLAY_DATA_TYPE :\t"<< file.display_data_type
            << "\nCAPACITY :\t" << file.capacity;

        if (file.nodes)
            output << "\nNODE_CORD_SECTION " << *file.nodes;
        else if(file.matrix)
            output << "\nMatrix :\n" << *file.matrix;

        output << "\nDEMAND_SECTION";
        for (unsigned int i = 0; i < file.demand.size(); i++)
            output <<"\n" << i+1 << "\t" << file.demand[i];

        output << "\nDEPOT_SECTION";
        for (unsigned int i = 0; i < file.depot.size(); i++)
            output << "\n\t"<<file.depot[i]+1;

        if (file.display_data_section.size() > 0)
        {
            output << "\nDISPLAY_DATA_SECTION";
            for (auto value : file.display_data_section)
                output << "\n" << value.numer << "\t" << value.first << "\t" << value.secnd;
        }

        return output;
    }

#endif
