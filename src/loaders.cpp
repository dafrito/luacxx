#include "loaders.hpp"
#include <fstream>
#include <sstream>

using namespace std;

namespace lua
{
	void load_file(Lua& lua, const string& file)
	{
		ifstream f(file, ios::in);
		lua(f, file);
	}

	void load_string(Lua& lua, const string& input)
	{
		std::istringstream stream(input);
		lua(stream, "string input");
	}
}

