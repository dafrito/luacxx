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

void qobject(LuaStack& stack, QObject* obj);

} // namespace userdata

template<>
struct UserdataName<QObject>
{
    constexpr static const char* value = "QObject";
};

template<>
struct UserdataName<lua::LuaCallable>
{
    constexpr static const char* value = "lua::LuaCallable";
};

} // namespace lua

LuaStack& operator<<(LuaStack& stack, QObject& ptr);
LuaStack& operator<<(LuaStack& stack, QObject* const & ptr);
LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<QObject>& ptr);
LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<lua::LuaCallable>& callable);

#endif
