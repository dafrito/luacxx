# Binding a Class

This guide shows the usual Luacxx pattern for exposing a C++ class as Lua
userdata with methods.

The core pieces are:

- `lua::make<T>()` to construct userdata
- `lua::get<T*>()` to recover the C++ object
- `lua::Metatable<T>` to describe the userdata type and its methods

## Example Class

```cpp
struct Counter
{
    int value;

    Counter(int initial = 0) :
        value(initial)
    {
    }

    void add(int amount)
    {
        value += amount;
    }

    int get() const
    {
        return value;
    }
};
```

## Describe The Metatable

Specialize `lua::Metatable<Counter>` so Luacxx knows the userdata name, valid
casts, and Lua-visible methods:

```cpp
template <>
struct lua::Metatable<Counter>
{
    static const lua::userdata_type& info()
    {
        static lua::userdata_type type("Counter");
        if (!type.has_casts()) {
            type.add_cast<Counter>();
        }
        return type;
    }

    static bool metatable(lua_State* const state, int pos, Counter*)
    {
        lua::index mt(state, pos);
        mt["add"] = &Counter::add;
        mt["get"] = &Counter::get;
        return true;
    }
};
```

Returning `true` lets Luacxx cache the metatable for later `Counter` values.

## Write A Constructor Function

Use `lua::make<T>()` to allocate the userdata and construct the C++ object in
place:

```cpp
int Counter_new(lua_State* const state)
{
    int initial = 0;
    if (lua_gettop(state) > 1) {
        initial = lua::get<int>(state, 2);
    }

    lua::make<Counter>(state, initial);

    lua_pushvalue(state, 1);
    lua_setmetatable(state, -2);

    lua_replace(state, 1);
    lua_settop(state, 1);
    return 1;
}
```

This version expects the metatable table in stack slot `1`, so it fits the
common `Counter:new(...)` Lua style.

## Export The Class Table

Create a Lua table for the class and install the constructor:

```cpp
int luaopen_Counter(lua_State* const state)
{
    lua::thread env(state);

    env["Counter"] = lua::value::table;
    env["Counter"]["new"] = Counter_new;

    return 0;
}
```

Lua usage:

```lua
local counter = Counter:new(10)
counter:add(5)
assert(counter:get() == 15)
```

## Reading The Object Back In C++

Inside a bound function, retrieve the userdata as a typed pointer:

```cpp
int Counter_add(lua_State* const state)
{
    auto counter = lua::get<Counter*>(state, 1);
    counter->add(lua::get<int>(state, 2));
    return 0;
}
```

This is the basic Luacxx userdata path: Lua stores the userdata, and Luacxx
recovers the in-place C++ object for you.

## Ownership And Lifetime

When you construct a value with `lua::make<T>()`, the object lives inside Lua
userdata. Luacxx arranges for the userdata to carry type information and
destruction behavior.

That makes this pattern a good fit when:

- the object has methods
- the object should have identity in Lua
- the object has non-trivial lifetime

If the type is really just a value, prefer a conversion-based binding instead.

## Common Pattern

For many classes, the binding shape is:

1. define `lua::Metatable<T>`
2. write a constructor that calls `lua::make<T>()`
3. export a class table with a `new` method
4. use `lua::get<T*>()` inside bound methods

That is enough to get a usable userdata-backed class into Lua without needing a
code generator.

## Related Docs

- [Binding a Primitive Type](binding-a-primitive-type.md)
- [Writing Bindings](writing-bindings.md)
- [Stack and Userdata](../reference/stack-and-userdata.md)
