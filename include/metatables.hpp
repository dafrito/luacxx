#ifndef LUA_METATABLES_HPP
#define LUA_METATABLES_HPP

#include <memory>
#include "LuaUserdata.hpp"
#include "LuaStack.hpp"
#include "LuaEnvironment.hpp"

class LuaStack;
class QObject;

namespace lua {
namespace metatable {

void qobject(LuaStack& stack, const std::shared_ptr<QObject>& obj);

template <class Target>
LuaStack& convertFromUserdata(LuaStack& stack, std::shared_ptr<Target>& callable, const char* expectedType)
{
    callable.reset();
    LuaUserdata* userdata;
    stack >> userdata;
    if (userdata && userdata->dataType() == expectedType) {
        callable = std::shared_ptr<Target>(
            userdata->data(),
            static_cast<Target*>(userdata->rawData())
        );
    }
    return stack;
}

} // namespace metatable
} // namespace lua

LuaStack& operator <<(LuaStack& stack, const std::shared_ptr<QObject>& ptr);
LuaStack& operator >>(LuaStack& stack, std::shared_ptr<QObject>& ptr);

LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<lua::LuaCallable>& callable);
LuaStack& operator>>(LuaStack& stack, std::shared_ptr<lua::LuaCallable>& callable);

#endif
