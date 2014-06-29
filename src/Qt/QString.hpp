#ifndef LUA_CXX_TYPE_QSTRING_HEADER
#define LUA_CXX_TYPE_QSTRING_HEADER

#include "../lua-cxx/type/standard.hpp"

#include <QString>

namespace lua {

template<>
struct Push<QString>
{
    static void push(lua_State* const state, const QString& source)
    {
        lua::push(state, source.toUtf8().constData());
    }
};

template<>
struct Store<QString>
{
    static void store(QString& destination, const lua::index& source)
    {
        destination = QString::fromUtf8(lua::get<const char*>(source));
    }
};

} // namespace lua

#endif // LUA_CXX_TYPE_QSTRING_HEADER
