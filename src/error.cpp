#include "algorithm.hpp"

lua::error::error(lua_State* const state, const std::string& what) :
    std::runtime_error("lua::error"),
    _what(what),
    _traceback(what.size())
{
    set_traceback(lua::traceback(state, 1));
}
