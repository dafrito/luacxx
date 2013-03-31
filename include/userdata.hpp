#ifndef LUA_USERDATA_HPP
#define LUA_USERDATA_HPP

#include <memory>
#include "LuaUserdata.hpp"
#include "LuaStack.hpp"
#include "LuaEnvironment.hpp"

class LuaStack;
class QObject;

namespace lua {
namespace userdata {

void qobject(LuaStack& stack, QObject* obj);

template <class Target>
LuaStack& convertUserdata(LuaStack& stack, Target*& obj, const char* expectedType)
{
    obj = nullptr;
    LuaUserdata* userdata;
    stack >> userdata;
    if (userdata && userdata->dataType() == expectedType) {
        obj = static_cast<Target*>(userdata->rawData());
    }
    return stack;
}

template <class Target>
LuaStack& convertUserdata(LuaStack& stack, std::shared_ptr<Target>& callable, const char* expectedType)
{
    callable.reset();
    LuaUserdata* userdata;
    stack >> userdata;
    if (userdata && userdata->isShared() && userdata->dataType() == expectedType) {
        callable = std::shared_ptr<Target>(
            userdata->data(),
            static_cast<Target*>(userdata->rawData())
        );
    }
    return stack;
}

} // namespace userdata
} // namespace lua

LuaStack& operator<<(LuaStack& stack, QObject& ptr);
LuaStack& operator<<(LuaStack& stack, QObject* const & ptr);

LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<QObject>& ptr);
LuaStack& operator>>(LuaStack& stack, std::shared_ptr<QObject>& ptr);

LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<lua::LuaCallable>& callable);
LuaStack& operator>>(LuaStack& stack, std::shared_ptr<lua::LuaCallable>& callable);

#endif
