#ifndef luacxx_llvm_IRBuilder_INCLUDED
#define luacxx_llvm_IRBuilder_INCLUDED

#include "../../stack.hpp"

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#include <llvm/IR/IRBuilder.h>

namespace lua {

void llvm_IRBuilder_metatable(lua_State* const state, const int pos);

} // namespace lua

LUA_METATABLE_BUILT_WITH(llvm::IRBuilder<>, lua::llvm_IRBuilder_metatable);

extern "C" int luaopen_llvm_IRBuilder(lua_State* const);

#endif // luacxx_llvm_IRBuilder_INCLUDED
