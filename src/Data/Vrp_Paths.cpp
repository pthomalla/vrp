#define BOOST_FILESYSTEM_DEPRECATED

#include <boost/filesystem.hpp>
//#include <filesystem>
#include <stdexcept>

#include "Vrp_Paths.h"

#define VRP_EXTENSION ".vrp"
#define OPT_EXTENSION ".opt"

/* Windows
#define BASENAME(file) file.basename()
#define DIRECTORY(path) path.directory_string();
*/
//Linux
#define BASENAME( f ) f.filename().string()
#define DIRECTORY( path )  path.directory_string()
#define STRING( path ) path.string()


using namespace std;
using namespace  boost::filesystem;
//using namespace tr2::sys;

Vrp_Paths::Vrp_Paths()
{
}

Vrp_Paths::Vrp_Paths(string path_string)
{
	path path(path_string);

	if (is_directory(path))
        add_from_folder(path.string());
	else if (!is_regular_file(path))
        add_file(path.string());
}

bool Vrp_Paths::add_file(string path_string)
{
    path path(path_string);

    if (!is_regular_file(path))
		return false;

    if (path.extension() == VRP_EXTENSION)
        this->operator[]( basename(path) ).data_path = DIRECTORY(path);//.directory_string();
    else if (path.extension() == OPT_EXTENSION)
        this->operator[]( basename(path) ).result_path = path.directory_string();
	else
		return false;

	return true;
}

void Vrp_Paths::add_from_folder(string path_string)
{
	path path(path_string);
	if (!is_directory(path)) 
		throw invalid_argument(
				"invalid argument"
				"\nvoid Vrp_Paths::add_from_folder(string path)"
				"\n\tpath\t=\t"+path_string
			   );

	for (
		auto it = recursive_directory_iterator(path);
		it != recursive_directory_iterator();
		it++
		)
	{
        add_file(STRING(it->path()));
	}
	
}

