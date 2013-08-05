#ifndef LUA_CXX_TYPE_QCHAR_HPP
#define LUA_CXX_TYPE_QCHAR_HPP

#include <QChar>

#include "../LuaStack.hpp"
#include "../LuaIndex.hpp"

#include "QString.hpp"

namespace lua {

template<>
struct Pusher<QChar>
{
    static void push(LuaStack& stack, const QChar& source)
    {
        lua::push(stack, QString(source));
    }
};

template<>
struct Storer<QChar>
{
    static void store(const LuaIndex& index, QChar& sink)
    {
        sink = lua::get<QChar>(index);
    }
};

template<>
struct Getter<QChar>
{
    static QChar get(const LuaIndex& index)
    {
        return lua::get<QString>(index).at(0);
    }
};

} // namespace lua

#endif // LUA_CXX_TYPE_QCHAR_HPP

