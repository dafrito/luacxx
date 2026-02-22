#ifndef luacxx_Value_INCLUDED
#define luacxx_Value_INCLUDED

#include "../stack.hpp"

#include <llvm/IR/Value>

LUA_METATABLE_BUILT_WITH(llvm::Value, llvm_Value_metatable)

extern "C" int luaopen_luacxx_Value(lua_State* const);

#endif // luacxx_Value_INCLUDED
