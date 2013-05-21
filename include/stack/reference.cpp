class LuaReferenceAccessible : public LuaAccessible
{

    class RawLuaReference
    {
        int ref;
        lua_State* const _state;

        lua_State* luaState() const
        {
            return _state;
        }

    public:
        RawLuaReference(lua_State* state) :
            _state(state)
        {
            lua_pushinteger(luaState(), 0);
            ref = luaL_ref(luaState(), LUA_REGISTRYINDEX);

            // Push an integer first, then set to nil to prevent
            // Lua from returning LUA_REFNIL for nil values.
            lua_pushnil(luaState());
            store();
        }

        void push() const
        {
            lua_rawgeti(luaState(), LUA_REGISTRYINDEX, ref);
        }

        void store() const
        {
            lua_rawseti(luaState(), LUA_REGISTRYINDEX, ref);
        }

        ~RawLuaReference()
        {
            luaL_unref(luaState(), LUA_REGISTRYINDEX, ref);
        }
    };

    std::shared_ptr<RawLuaReference> _reference;

public:
    LuaReferenceAccessible(lua_State* state) :
        _reference(new RawLuaReference(state))
    {
    }

    LuaReferenceAccessible(const LuaReferenceAccessible& other) :
        _reference(other._reference)
    {
    }

    void push(LuaStack&) const;
    void store(LuaStack& stack) const;
};

typedef LuaValue<LuaReferenceAccessible> LuaReference;
