#ifndef luacxx_QApplication_INCLUDED
#define luacxx_QApplication_INCLUDED

#include "../stack.hpp"

class QApplication;

namespace lua {

void QApplication_metatable(const lua::index& mt);

template <>
struct Metatable<QApplication>
{
    static constexpr const char* name = "QApplication";

    static bool metatable(const lua::index& mt, QApplication* const)
    {
        lua::QApplication_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QApplication(lua_State* const);

#endif // luacxx_QApplication_INCLUDED
