#ifndef LUACXX_TYPE_CHAR_POINTER_INCLUDED
#define LUACXX_TYPE_CHAR_POINTER_INCLUDED

#include "../stack.hpp"

namespace lua {

template <>
struct Push<char*>
{
    static void push(lua_State* const state, const char* const source)
    {
        lua::push(state, source);
    }
};

} // namespace lua

#endif // LUACXX_TYPE_CHAR_POINTER_INCLUDED
