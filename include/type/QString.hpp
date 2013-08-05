#ifndef LUA_CXX_TYPE_QSTRING_HPP
#define LUA_CXX_TYPE_QSTRING_HPP

#include <QString>

#include "../LuaStack.hpp"
#include "../LuaIndex.hpp"

namespace lua {

template<>
struct Pusher<QString>
{
    static void push(LuaStack& stack, const QString& source)
    {
        lua::push(stack, source.toStdString());
    }
};

template<>
struct Storer<QString>
{
    static void store(const LuaIndex& index, QString& sink)
    {
        sink = lua::get<QString>(index);
    }
};

template<>
struct Getter<QString>
{
    static QString get(const LuaIndex& index)
    {
        return QString::fromUtf8(lua::get<const char*>(index));
    }
};

} // namespace lua

#endif // LUA_CXX_TYPE_QSTRING_HPP

