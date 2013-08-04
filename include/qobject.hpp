#ifndef LUA_CXX_QOBJECT_HPP
#define LUA_CXX_QOBJECT_HPP

#include "LuaStack.hpp"
#include <QObject>

class LuaStack;
class QObject;

namespace lua {

void qobject(LuaStack& stack, QObject& obj);

template<>
struct UserdataType<QObject>
{
    constexpr static const char* name = "QObject";

    static void initialize(LuaStack& stack, QObject& obj)
    {
        lua::qobject(stack, obj);
    }
};

} // namespace lua

#endif // LUA_CXX_QOBJECT_HPP
