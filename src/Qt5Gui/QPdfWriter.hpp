#ifndef luacxx_QPdfWriter_INCLUDED
#define luacxx_QPdfWriter_INCLUDED

#include "../stack.hpp"

#include <QPdfWriter>

namespace lua {

void QPdfWriter_metatable(lua_State* const state, const int mt);

template <>
struct Metatable<QPdfWriter>
{
    static const userdata_type& info()
    {
        static userdata_type _info("QPdfWriter");
        _info.add_cast<QPagedPaintDevice, QPdfWriter>();
        _info.add_cast<QObject, QPdfWriter>();
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, void* const)
    {
        lua::QPdfWriter_metatable(state, mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QPdfWriter(lua_State* const);

#endif // luacxx_QPdfWriter_INCLUDED
