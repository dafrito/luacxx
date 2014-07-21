#ifndef luacxx_llvm_IRBuilder_INCLUDED
#define luacxx_llvm_IRBuilder_INCLUDED

#include "../../stack.hpp"

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#include <llvm/IR/IRBuilder.h>

namespace lua {

void llvm_IRBuilder_metatable(const lua::index& mt);

template <>
struct Metatable<llvm::IRBuilder<>>
{
    static constexpr const char* name = "llvm::IRBuilder";

    static bool metatable(const lua::index& mt, llvm::IRBuilder<>* const)
    {
        lua::llvm_IRBuilder_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_llvm_IRBuilder(lua_State* const);

#endif // luacxx_llvm_IRBuilder_INCLUDED
