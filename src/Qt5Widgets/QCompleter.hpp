#ifndef luacxx_QCompleter_INCLUDED
#define luacxx_QCompleter_INCLUDED

#include "../stack.hpp"

class QCompleter;

namespace lua {

void QCompleter_metatable(const lua::index& mt);

template <>
struct Metatable<QCompleter>
{
    static constexpr const char* name = "QCompleter";

    static bool metatable(const lua::index& mt, QCompleter* const)
    {
        lua::QCompleter_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QCompleter(lua_State* const);

#endif // luacxx_QCompleter_INCLUDED
