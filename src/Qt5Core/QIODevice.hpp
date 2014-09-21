#ifndef LUACXX_QIODevice_INCLUDED
#define LUACXX_QIODevice_INCLUDED

#include "../stack.hpp"

#include <QIODevice>

namespace lua {

void QIODevice_metatable(const lua::index& mt);

template <>
struct Metatable<QIODevice>
{
    static constexpr const char* name = "QIODevice";

    static bool metatable(const lua::index& mt, QIODevice* const)
    {
        lua::QIODevice_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QIODevice(lua_State* const);

#endif // LUACXX_QIODevice_INCLUDED

