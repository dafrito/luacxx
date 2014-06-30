#ifndef LUACXX_TYPE_QCHAR_INCLUDED
#define LUACXX_TYPE_QCHAR_INCLUDED

#include <QChar>

#include "../luacxx/convert/string.hpp"
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
    static void store(QChar& destination, const lua::index& source)
    {
        destination = lua::get<QString>(source).at(0);
    }
};

} // namespace lua

#endif // LUACXX_TYPE_QCHAR_INCLUDED
