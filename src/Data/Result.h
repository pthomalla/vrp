#ifndef RESULT_H
#define RESULT_H

#include <vector>
#include <stdexcept>
#include <sstream>
#include <typeinfo>

class Result{
    std::vector<std::vector<int>> routs;
	int cost;
public:
	template<typename Stream>
	Stream& read(Stream& stream);

    const std::vector<std::vector<int>>& get_routs() const
	{
		return routs;
	}
	int get_cost() const 
	{
		return cost; 
	}

};

template<typename Stream>
Stream& Result::read(Stream& stream){
    std::string value;
    std::istringstream split;
	int node;
    std::vector<int> rout;

	while (true){
		getline(stream, value);
		if (value.empty())
            throw std::runtime_error
					(
						"Stream& Result::read(Stream& stream)"
                        "\n\tStream\t=\t" + std::string(typeid(Stream).name()) +
						"\n\tfrom strem.getline() string was empty"
			      );
		split.str(value);

		split >> value;
		if (value != "Route"){
			split >> cost;
			return stream;
		}
		split >> value; // zczytanie numeru œcie¿ki 
		while (split.good()){
			split >> node;
			rout.push_back(node);
		}

		if (!split.eof()){
            throw std::invalid_argument
				(
					"Result::read"
                    "\n\tStream\t=\t" + std::string(typeid(Stream).name()) +
					"\n\tPars:\t" + split.str()
				);
		}
		split.clear();
		routs.push_back(std::move(rout));
	}

}

template<typename Stream>
Stream& operator>>(Stream& stream, Result& result)
{
	return result.read(stream);
}

template<typename Stream>
Stream& operator<<(Stream& stream, const Result& result)
{
	int route_number = 1;
	for (auto vector : result.get_routs())
	{
		stream << "Route #" << route_number++ << ":";
		for (auto integer : vector)
		{
			stream <<" "<< integer;
		}
		stream << "\n";
	}
	stream << "cost " << result.get_cost();
	return stream;
}
#endif
