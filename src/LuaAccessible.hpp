#ifndef HEADER_LUAACCESSIBLE_HPP
#define HEADER_LUAACCESSIBLE_HPP

#include <memory>

class LuaStack;

/**
 * Represents a method to access a value from Lua.
 *
 * There's currently three methods to reliably access
 * some value in Lua:
 *
 * 1. Global access
 * 2. Reference table access
 * 3. Indexed access
 *
 * Referenced access (through luaL_ref) is the safest
 * way to store and retrieve a value; the other methods
 * are publicly accessible, so the underlying value may
 * be changed between accesses.
 */
class LuaAccessible
{
public:

    /**
     * Pushes the value held by this accessible on
     * the specified stack.
     */
    virtual void push(LuaStack& stack) const=0;

    /**
     * Sets this reference to the value on the top
     * of the specified stack.
     */
    virtual void store(LuaStack& stack) const=0;

    virtual ~LuaAccessible() {}
};

namespace lua {
    template <class Accessor>
    Accessor& retrieveAccessor(Accessor& accessible)
    {
        return accessible;
    }

    template <class Accessor>
    const Accessor& retrieveAccessor(const Accessor& accessible)
    {
        return accessible;
    }

    template <class Accessor>
    const Accessor& retrieveAccessor(const std::shared_ptr<Accessor>& accessible)
    {
        return *accessible;
    }
} // namespace lua

#endif // HEADER_LUAACCESSIBLE_HPP

