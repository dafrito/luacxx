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

template <class Target>
LuaIndex& convertUserdata(LuaIndex& index, Target*& obj, const char* expectedType)
{
    obj = nullptr;
    LuaUserdata* userdata;
    index >> userdata;
    if (userdata && userdata->dataType() == expectedType) {
        obj = static_cast<Target*>(userdata->rawData());
    }
    return index;
}

template <class Target>
LuaIndex& convertUserdata(LuaIndex& index, Target& obj, const char* expectedType)
{
    Target* ptr = nullptr;
    convertUserdata(index, ptr, expectedType);
    if (!ptr) {
        throw LuaException(
            std::string("Userdata is not of type: ") + expectedType
        );
    }
    obj = *ptr;
    return index;
}

template <class Target>
LuaIndex& convertUserdata(LuaIndex& index, std::shared_ptr<Target>& callable, const char* expectedType)
{
    callable.reset();
    LuaUserdata* userdata;
    index >> userdata;
    if (userdata && userdata->isShared() && userdata->dataType() == expectedType) {
        callable = std::shared_ptr<Target>(
            userdata->data(),
            static_cast<Target*>(userdata->rawData())
        );
    }
    return index;
}

} // namespace userdata
} // namespace lua

LuaStack& operator<<(LuaStack& stack, QObject& ptr);
LuaStack& operator<<(LuaStack& stack, QObject* const & ptr);

LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<QObject>& ptr);
LuaIndex& operator>>(LuaIndex& index, std::shared_ptr<QObject>& ptr);

LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<lua::LuaCallable>& callable);
LuaIndex& operator>>(LuaIndex& index, std::shared_ptr<lua::LuaCallable>& callable);

#endif
