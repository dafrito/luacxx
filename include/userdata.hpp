#ifndef LUA_USERDATA_HPP
#define LUA_USERDATA_HPP

#include <memory>
#include "LuaUserdata.hpp"
#include "LuaStack.hpp"
#include "LuaEnvironment.hpp"
#include "LuaException.hpp"

class LuaStack;
class QObject;

namespace lua {

namespace userdata {

void qobject(LuaStack& stack, QObject& obj);

} // namespace userdata

template<>
struct UserdataType<QObject>
{
    constexpr static const char* name = "QObject";

    static void initialize(LuaStack& stack, QObject& obj)
    {
        lua::userdata::qobject(stack, obj);
    }
};

} // namespace lua

#endif
