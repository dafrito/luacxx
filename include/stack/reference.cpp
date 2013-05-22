class LuaReferenceAccessible : public LuaAccessible
{

    class RawLuaReference
    {
        int ref;
        mutable int lastType;
        lua_State* const _state;

        lua_State* luaState() const
        {
            return _state;
        }

    public:
        RawLuaReference(lua_State* state) :
            _state(state)
        {
            auto before = lua_gettop(luaState());
            lua_pushinteger(luaState(), 0);
            ref = luaL_ref(luaState(), LUA_REGISTRYINDEX);
            lastType = type();

            // Push an integer first, then set to nil to prevent
            // Lua from returning LUA_REFNIL for nil values.
            lua_pushnil(luaState());
            store();
            auto after = lua_gettop(luaState());
            assert(before == after);
        }

        int type() const
        {
            lua_rawgeti(luaState(), LUA_REGISTRYINDEX, ref);
            auto currentType = lua_type(luaState(), -1);
            lua_pop(luaState(), 1);
            return currentType;
        }

        void push() const
        {
            assert(lastType == type());
            lua_rawgeti(luaState(), LUA_REGISTRYINDEX, ref);
        }

        void store() const
        {
            lua_rawseti(luaState(), LUA_REGISTRYINDEX, ref);
            lastType = type();
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
