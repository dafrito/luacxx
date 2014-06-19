#ifndef LUA_CXX_QTEXTDOCUMENT_INCLUDED
#define LUA_CXX_QTEXTDOCUMENT_INCLUDED

#include "../stack.hpp"

class QTextDocument;

namespace lua {

void QTextDocument_metatable(const lua::index& mt);

template <>
struct Metatable<QTextDocument>
{
    static constexpr const char* name = "QTextDocument";

    static bool metatable(const lua::index& mt, QTextDocument* const)
    {
        lua::QTextDocument_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QTextDocument(lua_State* const);

#endif // LUA_CXX_QTEXTDOCUMENT_INCLUDED
