#ifndef luacxx_convert_char_p_INCLUDED
#define luacxx_convert_char_p_INCLUDED

#include "../stack.hpp"

namespace lua {

template <>
struct Push<char*>
{
    static void push(lua_State* const state, const char* const source)
    {
        lua_pushstring(state, source);
    }
};

} // namespace lua

#endif // luacxx_convert_char_p_INCLUDED
