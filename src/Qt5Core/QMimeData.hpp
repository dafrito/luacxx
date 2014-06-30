#ifndef LUACXX_QMIMEDATA_INCLUDED
#define LUACXX_QMIMEDATA_INCLUDED

#include "../luacxx/stack.hpp"

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

extern "C" int luaopen_Qt5Core_QMimeData(lua_State* const);

#endif // LUACXX_QMIMEDATA_INCLUDED
