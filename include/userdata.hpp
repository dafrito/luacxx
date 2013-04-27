#ifndef LUA_USERDATA_HPP
#define LUA_USERDATA_HPP

#include <memory>
#include "LuaUserdata.hpp"
#include "LuaStack.hpp"
#include "LuaEnvironment.hpp"
#include "LuaException.hpp"

#include <unordered_map>

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

void qvariantPusher(const QVariant::Type& type, const std::function<void(LuaStack&, const QVariant&)>& mapper);
void qvariantStorer(const QVariant::Type& type, const std::function<void(LuaIndex&, QVariant&)>& mapper);

void pushVariant(LuaStack& stack, const QVariant& source);
void storeVariant(LuaIndex& index, QVariant& sink);

template<>
struct Pusher<QVariant>
{
    static void push(LuaStack& stack, const QVariant& variant)
    {
        pushVariant(stack, variant);
    }
};

template<>
struct Pusher<QChar>
{
    static void push(LuaStack& stack, const QChar& value)
    {
        lua::push(stack, value.toAscii());
    }
};

template<>
struct Pusher<QString>
{
    static void push(LuaStack& stack, const QString& value)
    {
        lua::push(stack, value.toStdString());
    }
};

} // namespace lua

#endif
