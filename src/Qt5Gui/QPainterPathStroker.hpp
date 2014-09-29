#ifndef LUACXX_QPAINTERPATHSTROKER_INCLUDED
#define LUACXX_QPAINTERPATHSTROKER_INCLUDED

#include "Qt5Gui.hpp"

#include <QPainterPathStroker>

// http://qt-project.org/doc/qt-5/qpainterpathstroker.html

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

extern "C" int luaopen_Qt5Gui_QPainterPathStroker(lua_State* const);

#endif // LUACXX_QPAINTERPATHSTROKER_INCLUDED
