#ifndef luacxx_QModelIndex_INCLUDED
#define luacxx_QModelIndex_INCLUDED

#include "../stack.hpp"

class QModelIndex;

namespace lua {

void QModelIndex_metatable(const lua::index& mt);

template <>
struct Metatable<QModelIndex>
{
    static constexpr const char* name = "QModelIndex";

    static bool metatable(const lua::index& mt, QModelIndex* const)
    {
        lua::QModelIndex_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QModelIndex(lua_State* const);

#endif // luacxx_QModelIndex_INCLUDED
