#ifndef LUA_CXX_TYPE_QVARIANT_HPP
#define LUA_CXX_TYPE_QVARIANT_HPP

#include <functional>
#include <QVariant>

#include "../LuaStack.hpp"
#include "../LuaIndex.hpp"

namespace lua {

void qvariantPusher(const QVariant::Type& type, const std::function<void(LuaStack&, const QVariant&)>& mapper);
void qvariantStorer(const QVariant::Type& type, const std::function<void(const LuaIndex&, QVariant&)>& mapper);

void pushVariant(LuaStack& stack, const QVariant& source);
void storeVariant(const LuaIndex& index, QVariant& sink);

template<>
struct Pusher<QVariant>
{
    static void push(LuaStack& stack, const QVariant& variant)
    {
        pushVariant(stack, variant);
    }
};

template<>
struct Storer<QVariant>
{
    static void store(const LuaIndex& index, QVariant& sink)
    {
        storeVariant(index, sink);
    }
};

template<>
struct Getter<QVariant>
{
    static QVariant get(const LuaIndex& index)
    {
        throw LuaException("Extracting QVariants is not yet allowed");
    }
};

} // namespace lua

#endif // LUA_CXX_TYPE_QVARIANT_HPP

