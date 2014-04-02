#ifndef VRP_PATHS_H
#define VRP_PATHS_H

#include <map>
#include <string>

struct Task{
	std::string data_path, result_path;
};

struct Vrp_Paths : public std::map<std::string,Task> {
	Vrp_Paths();
	Vrp_Paths(std::string);
	bool add_file(std::string path);
	void add_from_folder(std::string path);
};
#endif
