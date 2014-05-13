#ifndef LUA_CXX_ASSERT_HEADER
#define LUA_CXX_ASSERT_HEADER

#include "type.hpp"
#include "index.hpp"
#include "error.hpp"

#include <sstream>

namespace lua {

template <class Error = lua::error>
void assert_type(const char* category, const lua::type& expected, const lua::index& given)
{
    if (given.type() == expected) {
        return;
    }
    std::stringstream str;
    str << category;
    str << ": ";
    str << "Lua stack value at index " << given.pos() << " must be a ";
    str << lua::type_info(expected).name();
    str << " but a " << given.type().name() << " was given instead.";
    throw Error(str.str());
}

} // namespace lua

#endif // LUA_CXX_ASSERT_HEADER
