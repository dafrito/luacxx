#ifndef luacxx_Instruction_INCLUDED
#define luacxx_Instruction_INCLUDED

#include "../../stack.hpp"

#include <llvm/IR/Instruction.h>

namespace lua {
void llvm_Instruction_metatable(lua_State* const state, const int pos);
}

LUA_METATABLE_BUILT_WITH(llvm::Instruction, llvm_Instruction_metatable)

extern "C" int luaopen_llvm_Instruction(lua_State* const);

#endif // luacxx_Instruction_INCLUDED
