#ifndef luacxx_QAbstractItemView_INCLUDED
#define luacxx_QAbstractItemView_INCLUDED

#include "../stack.hpp"

class QAbstractItemView;

namespace lua {

void QAbstractItemView_metatable(const lua::index& mt);

template <>
struct Metatable<QAbstractItemView>
{
    static constexpr const char* name = "QAbstractItemView";

    static bool metatable(const lua::index& mt, QAbstractItemView* const)
    {
        lua::QAbstractItemView_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QAbstractItemView(lua_State* const);

#endif // luacxx_QAbstractItemView_INCLUDED
