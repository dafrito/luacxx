#ifndef LUACXX_CONVERT_VOID_INCLUDED
#define LUACXX_CONVERT_VOID_INCLUDED

#include "../stack.hpp"

namespace lua {

template <>
struct Push<void*>
{
    static void push(lua_State* const state, void* const source)
    {
        lua_pushlightuserdata(state, source);
    }
};

template <>
struct Store<void*>
{
    static void store(void*& destination, const lua::index& source)
    {
        if (lua_islightuserdata(source.state(), source.pos())) {
            destination = lua_touserdata(source.state(), source.pos());
            return;
        }

        // It's a full userdata, so retrieve the underlying value
        auto userdata_block = lua::get<lua::userdata_block*>(source);
        if (!userdata_block) {
            destination = nullptr;
            return;

        }

        void* block = lua_touserdata(source.state(), source.pos());
        switch (userdata_block->storage()) {
        case lua::userdata_storage::value:
            destination = block;
            break;
        case lua::userdata_storage::pointer:
            destination = *reinterpret_cast<void**>(block);
            break;
        case lua::userdata_storage::shared_ptr:
            throw std::logic_error("shared_ptr's cannot be safely converted to void pointers");
        }
    }
};
} // namespace lua

#endif // LUACXX_CONVERT_VOID_INCLUDED
