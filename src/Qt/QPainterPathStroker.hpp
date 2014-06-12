#ifndef LUA_CXX_QPAINTERPATHSTROKER_INCLUDED
#define LUA_CXX_QPAINTERPATHSTROKER_INCLUDED

#include "../stack.hpp"

class QPainterPathStroker;

namespace lua {

void QPainterPathStroker_metatable(const lua::index& mt);

template <>
struct Metatable<QPainterPathStroker>
{
    static constexpr const char* name = "QPainterPathStroker";

    static bool metatable(const lua::index& mt, QPainterPathStroker* const)
    {
        lua::QPainterPathStroker_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QPainterPathStroker(lua::state* const);

#endif // LUA_CXX_QPAINTERPATHSTROKER_INCLUDED
