class LuaReferenceAccessible : public LuaAccessible
{

    class RawLuaReference
    {
        constexpr static int NIL_VALUE = 0xdead;

        int ref;
        mutable int _type;
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

            lua_pushinteger(luaState(), NIL_VALUE);
            ref = luaL_ref(luaState(), LUA_REGISTRYINDEX);
            _type = LUA_TNIL;
            assert(isNil());

            auto after = lua_gettop(luaState());
            assert(before == after);
        }

        int type() const
        {
            lua_rawgeti(luaState(), LUA_REGISTRYINDEX, ref);
            auto currentType = lua_type(luaState(), -1);
            if (currentType == LUA_TNUMBER && lua_tonumber(luaState(), -1) == NIL_VALUE && _type == LUA_TNIL) {
                currentType = LUA_TNIL;
            }
            lua_pop(luaState(), 1);
            return currentType;
        }

        bool isNil() const
        {
            return type() == LUA_TNIL;
        }


        void push() const
        {
            assert(_type == type());
            if (isNil()) {
                lua_pushnil(luaState());
                return;
            }
            lua_rawgeti(luaState(), LUA_REGISTRYINDEX, ref);
        }

        void storeNil() const
        {
            lua_pushinteger(luaState(), NIL_VALUE);
            lua_rawseti(luaState(), LUA_REGISTRYINDEX, ref);
            _type = LUA_TNIL;
            assert(isNil());
        }

        void store() const
        {
            if (lua_type(luaState(), -1) == LUA_TNIL) {
                storeNil();

                // Pop the nil value that was on the stack
                lua_pop(luaState(), 1);

                return;
            }

            lua_rawseti(luaState(), LUA_REGISTRYINDEX, ref);
            _type = type();
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
