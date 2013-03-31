#ifndef LUA_TABLE_ACCESSIBLE_HPP
#define LUA_TABLE_ACCESSIBLE_HPP

#include <lua.hpp>
#include "LuaAccessible.hpp"
#include "LuaEnvironment.hpp"
#include "LuaStack.hpp"

#include <functional>

template <class Key>
class LuaTableAccessible : public LuaAccessible
{
    std::shared_ptr<LuaAccessible> _parent;
    const Key key;
public:
    LuaTableAccessible(Lua& lua, const std::shared_ptr<LuaAccessible>& parent, const Key& key) :
        LuaAccessible(lua),
        _parent(parent),
        key(key)
    {}

    void push(LuaStack& stack) const
    {
        _parent->push(stack);
        stack.get(key);
        stack.remove(-2);
    }

    void store(LuaStack& stack) const
    {
        // [value]
        stack.pushCopy();
        // [value, value]
        _parent->push(stack);
        // [value, value, table]
        stack.swap();
        // [value, table, value]
        stack.pushedSet(key, -2);
        // [value, table]
        stack.pop();
        // [value]
    }
};

#endif // LUA_TABLE_ACCESSIBLE_HPP

