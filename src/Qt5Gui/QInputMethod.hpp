#ifndef LUACXX_QINPUTMETHOD_INCLUDED
#define LUACXX_QINPUTMETHOD_INCLUDED

#include "../luacxx/stack.hpp"
#include <QInputMethod>

namespace lua {

void QInputMethod_metatable(const lua::index& mt);

template <>
struct Metatable<QInputMethod>
{
    static constexpr const char* name = "QInputMethod";

    static bool metatable(const lua::index& mt, QInputMethod* const)
    {
        lua::QInputMethod_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QInputMethod(lua_State* const);

#endif // LUACXX_QINPUTMETHOD_INCLUDED
