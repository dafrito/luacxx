#ifndef luacxx_QChar_INCLUDED
#define luacxx_QChar_INCLUDED

#include <QChar>

#include "../convert/string.hpp"
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

#endif // luacxx_QChar_INCLUDED
