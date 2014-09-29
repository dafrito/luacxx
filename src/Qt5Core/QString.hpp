#ifndef luacxx_Qt5Core_QString_INCLUDED
#define luacxx_Qt5Core_QString_INCLUDED

#include "../convert/string.hpp"

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

#endif // luacxx_Qt5Core_QString_INCLUDED
