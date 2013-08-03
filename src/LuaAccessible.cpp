#include "LuaAccessible.hpp"

namespace lua {
    const LuaAccessible& retrieveAccessor(const LuaAccessible& accessible)
    {
        return accessible;
    }

    LuaAccessible& retrieveAccessor(LuaAccessible& accessible)
    {
        return accessible;
    }

    const LuaAccessible& retrieveAccessor(const std::shared_ptr<LuaAccessible>& accessible)
    {
        return *accessible;
    }

} // namespace lua
