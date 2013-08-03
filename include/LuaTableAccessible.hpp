#ifndef LUA_TABLE_ACCESSIBLE_HPP
#define LUA_TABLE_ACCESSIBLE_HPP

#include <lua.hpp>
#include <functional>

#include "LuaStack.hpp"
#include "LuaAccessible.hpp"

class LuaStack;

template <class Key, class ParentAccessible>
class LuaTableAccessible : public LuaAccessible
{
    ParentAccessible _parent;
    const Key key;
public:
    const LuaAccessible& parent() const
    {
        return lua::retrieveAccessor(_parent);
    }

    LuaAccessible& parent()
    {
        return lua::retrieveAccessor(_parent);
    }

    LuaTableAccessible(const ParentAccessible& parent, const Key& key) :
        _parent(parent),
        key(key)
    {}

    void push(LuaStack& stack) const
    {
        parent().push(stack);
        stack.get(key);
        stack.remove(-2);
    }

    void store(LuaStack& stack) const
    {
        // [value]
        stack.pushCopy();
        // [value, value]
        parent().push(stack);
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

