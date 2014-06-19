#ifndef LUA_CXX_QMIMEDATA_INCLUDED
#define LUA_CXX_QMIMEDATA_INCLUDED

#include "../stack.hpp"

class QMimeData;

namespace lua {

void QMimeData_metatable(const lua::index& mt);

template <>
struct Metatable<QMimeData>
{
    static constexpr const char* name = "QMimeData";

    static bool metatable(const lua::index& mt, QMimeData* const)
    {
        lua::QMimeData_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QMimeData(lua_State* const);

#endif // LUA_CXX_QMIMEDATA_INCLUDED
