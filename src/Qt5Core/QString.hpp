#ifndef luacxx_Qt5Core_QString_INCLUDED
#define luacxx_Qt5Core_QString_INCLUDED

#include "Qt5Core.hpp"

#include <QString>

namespace lua {

template<>
struct Push<QString>
{
    static void push(lua_State* const state, const QString& source)
    {
        lua::Push<const char*>::push(state, source.toUtf8().constData());
    }
};

template<>
struct Store<QString>
{
    static void store(QString& destination, lua_State* const state, const int source)
    {
        destination = QString::fromUtf8(
            lua_tostring(state, source)
        );
    }
};

template <>
struct Get<const QString&>
{
    static QString get(lua_State* const state, const int source)
    {
        return lua::Get<QString>::get(state, source);
    }
};

} // namespace lua

#endif // luacxx_Qt5Core_QString_INCLUDED
