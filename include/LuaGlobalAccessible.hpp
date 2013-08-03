#ifndef LUA_GLOBAL_ACCESSIBLE_HPP
#define LUA_GLOBAL_ACCESSIBLE_HPP

#include <string>
#include "LuaAccessible.hpp"

class LuaGlobalAccessible : public LuaAccessible
{
    const std::string key;
public:
    LuaGlobalAccessible(const std::string& key);
    void push(LuaStack& stack) const;
    void store(LuaStack& stack) const;
};

#endif // LUA_GLOBAL_ACCESSIBLE_HPP

