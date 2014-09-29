#ifndef luacxx_QAbstractItemModel_INCLUDED
#define luacxx_QAbstractItemModel_INCLUDED

#include "../stack.hpp"

class QAbstractItemModel;

namespace lua {

void QAbstractItemModel_metatable(const lua::index& mt);

template <>
struct Metatable<QAbstractItemModel>
{
    static constexpr const char* name = "QAbstractItemModel";

    static bool metatable(const lua::index& mt, QAbstractItemModel* const)
    {
        lua::QAbstractItemModel_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QAbstractItemModel(lua_State* const);

#endif // luacxx_QAbstractItemModel_INCLUDED
