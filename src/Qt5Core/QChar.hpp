#ifndef luacxx_QChar_INCLUDED
#define luacxx_QChar_INCLUDED

#include "Qt5Core.hpp"

#include <QChar>

#include "QString.hpp"

namespace lua {

template<>
struct Push<QChar>
{
    static void push(lua_State* const state, const QChar& source)
    {
        lua::push(state, QString(source));
    }
};

template<>
struct Store<QChar>
{
    static void store(QChar& destination, lua_State* const state, const int source)
    {
        destination = lua::get<QString>(state, source).at(0);
    }
};

} // namespace lua

LUA_METATABLE_NAMED(QChar);

#endif // luacxx_QChar_INCLUDED
