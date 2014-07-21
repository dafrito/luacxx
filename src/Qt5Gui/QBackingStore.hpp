#ifndef LUACXX_QBACKINGSTORE_INCLUDED
#define LUACXX_QBACKINGSTORE_INCLUDED

#include "../stack.hpp"

class QBackingStore;

namespace lua {

void QBackingStore_metatable(const lua::index& mt);

template <>
struct Metatable<QBackingStore>
{
    static constexpr const char* name = "QBackingStore";

    static bool metatable(const lua::index& mt, QBackingStore* const)
    {
        lua::QBackingStore_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QBackingStore(lua_State* const);

#endif // LUACXX_QBACKINGSTORE_INCLUDED
