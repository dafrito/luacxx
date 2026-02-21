#include "luacxx/algorithm.hpp"

lua::error::error(lua_State* const state, const std::string& what) :
    std::runtime_error("lua::error"),
    _what(what),
    _traceback(what.size())
{
    std::stringstream str;
    str << lua::traceback(state, 1) << std::endl;
    str << "stack: " << lua::dump(state) << std::endl;
    set_traceback(str.str());
}
