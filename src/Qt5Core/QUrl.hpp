#ifndef LUACXX_QURL_INCLUDED
#define LUACXX_QURL_INCLUDED

#include "../stack.hpp"
#include <QUrl>

namespace lua {

void QUrl_metatable(const lua::index& mt);

template <>
struct Metatable<QUrl>
{
    static constexpr const char* name = "QUrl";

    static bool metatable(const lua::index& mt, QUrl* const)
    {
        lua::QUrl_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QUrl(lua_State* const);

#endif // LUACXX_QURL_INCLUDED
