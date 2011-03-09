#include <stdexcept>

using namespace std;

class LuaException : std::runtime_error
{
private:
	const Lua& lua;
public:
	LuaException(const Lua& lua, const char* what) : std::runtime_error(what), lua(lua) {}
};
