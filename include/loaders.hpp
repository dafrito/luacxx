#ifndef LOADERS_HPP
#define LOADERS_HPP

#include <string>
#include <QFile>

#include "LuaStack.hpp"
#include "values.hpp"

class QDir;

namespace {
    LuaReference innerInvoke(LuaStack& stack)
    {
        int funcLoc = stack.top();
        stack.invoke();
        if (stack.top() >= funcLoc) {
            // A value was returned, so store it in a reference
            auto result = LuaReference(
                stack.luaState(),
                LuaReferenceAccessible(stack.luaState(), stack.save(funcLoc - stack.offset()))
            );
            stack.remove(funcLoc - stack.offset());
            return result;
        }
        // No value was returned, so just create a new nil reference.
        return LuaReference(
            stack.luaState(),
            LuaReferenceAccessible(stack.luaState())
        );
    }
}

namespace lua
{
    void loadFile(LuaStack& stack, QFile& file);
    void loadFile(LuaStack& stack, const std::string& file);
    void loadFile(LuaStack& stack, const char* file);
    void loadFile(LuaStack& stack, std::istream& stream, const std::string& name);

    void loadString(LuaStack& stack, const std::string& input);
    void loadString(LuaStack& stack, const char* input);

    /**
     * Runs every file in the directory, with optional recursion. If
     * you want to filter the files, specify a filter list on the directory
     * itself.
     */
    void runDir(LuaStack& stack, const QDir& dir, const bool recurse);

    void runDir(LuaEnvironment& lua, const QDir& dir, const bool recurse);

    template <class Input>
    LuaReference runString(LuaStack& stack, Input& runnable)
    {
        loadString(stack, runnable);
        return innerInvoke(stack);
    }

    template <class Input>
    LuaReference runFile(LuaStack& stack, Input& runnable)
    {
        loadFile(stack, runnable);
        return innerInvoke(stack);
    }

    template <class Input>
    LuaReference runString(LuaEnvironment& lua, Input& runnable)
    {
        LuaStack stack(lua);
        return runString(stack, runnable);
    }

    template <class Input>
    LuaReference runFile(LuaEnvironment& lua, Input& runnable)
    {
        LuaStack stack(lua);
        return runFile(stack, runnable);
    }

} // namespace lua

#endif // LOADERS_HPP
