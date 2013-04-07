#ifndef LUA_GLOBAL_ACCESSIBLE_HPP
#define LUA_GLOBAL_ACCESSIBLE_HPP

#include <QString>
#include "LuaStack.hpp"

class LuaGlobalAccessible : public LuaAccessible
{
    const QString key;
public:
    LuaGlobalAccessible(const QString& key);
    void push(LuaStack& stack) const;
    void store(LuaStack& stack) const;
};

typedef LuaValue<LuaGlobalAccessible> LuaGlobal;

#endif // LUA_GLOBAL_ACCESSIBLE_HPP

