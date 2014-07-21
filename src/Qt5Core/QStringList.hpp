#ifndef LUACXX_QSTRINGLIST_INCLUDED
#define LUACXX_QSTRINGLIST_INCLUDED

#include "../stack.hpp"
#include <QStringList>

namespace lua {

void QStringList_metatable(const lua::index& mt);

template <>
struct Metatable<QStringList>
{
    static constexpr const char* name = "QStringList";

    static bool metatable(const lua::index& mt, QStringList* const)
    {
        lua::QStringList_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QStringList(lua_State* const);

#endif // LUACXX_QSTRINGLIST_INCLUDED
