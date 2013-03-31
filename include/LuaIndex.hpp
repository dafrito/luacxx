#ifndef LUAINDEX_HEADER
#define LUAINDEX_HEADER

class LuaStack;

class LuaIndex
{
    LuaStack& _stack;

    int _pos;
    int _direction;
public:
    LuaIndex(LuaStack& stack, const int pos, const int direction = 1);

    LuaStack& stack() const;
    int pos() const;
    LuaIndex& operator++(int);
    LuaIndex& operator++();
    LuaIndex& operator--(int);
    LuaIndex& operator--();
};

#endif // LUAINDEX_HEADER
