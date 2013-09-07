#ifndef HEADER_LUACXX_VALUES_HPP
#define HEADER_LUACXX_VALUES_HPP

#include "LuaGlobalAccessible.hpp"
#include "LuaReferenceAccessible.hpp"
#include "LuaTableAccessible.hpp"
#include "LuaProxyAccessible.hpp"
#include "LuaValue.hpp"

typedef LuaValue<LuaReferenceAccessible> LuaReference;
typedef LuaValue<LuaGlobalAccessible> LuaGlobal;
typedef LuaValue<LuaProxyAccessible> LuaProxy;

template <class Key, class ParentAccessible>
using LuaTableValue = LuaValue<LuaTableAccessible<Key, ParentAccessible>>;

#endif // HEADER_LUACXX_VALUES_HPP
