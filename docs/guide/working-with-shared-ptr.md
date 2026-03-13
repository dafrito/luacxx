# Working With `shared_ptr`

Luacxx can work with `std::shared_ptr<T>` when you want Lua and C++ to share
ownership of the same object instead of copying a value into userdata.

This is useful when:

- the object already uses shared ownership in C++
- multiple Lua values or C++ systems may refer to the same instance
- copying the object would be incorrect or too expensive

## Include The Conversion

```cpp
#include <luacxx/convert/shared_ptr.hpp>
```

This hooks `std::shared_ptr<T>` into Luacxx's userdata system.

## What It Does

For `std::shared_ptr<T>`, Luacxx reuses the metatable information for `T`
itself:

```cpp
template <class T>
struct Metatable<std::shared_ptr<T>>
{
    static const userdata_type& info()
    {
        return Metatable<T>::info();
    }
};
```

That means a `shared_ptr<T>` userdata behaves like a `T` userdata from Lua's
point of view. The methods and metamethods you define on `T` still apply.

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

The metatable still belongs to `Counter`:

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

## Push A `shared_ptr`

```cpp
std::shared_ptr<Counter> counter = std::make_shared<Counter>(10);
lua::push(state, counter);
```

Lua now refers to the same `Counter` instance. It is not a copied value.

## Read It Back

```cpp
auto same_counter = lua::get<std::shared_ptr<Counter>>(state, -1);
same_counter->add(5);
```

Both `counter` and `same_counter` share ownership of the same object.

## Expose A Function Returning Shared Ownership

This works naturally for bound functions:

```cpp
std::shared_ptr<Counter> make_counter(int initial)
{
    return std::make_shared<Counter>(initial);
}

void open_counter(lua_State* const state)
{
    lua::thread env(state);
    env["make_counter"] = make_counter;
}
```

Lua callers receive a userdata that keeps the shared object alive.

## Important Difference From `lua::make<T>()`

`lua::make<T>()` constructs a brand new `T` directly inside Lua userdata.

`std::shared_ptr<T>` instead keeps shared ownership of an object allocated
outside that userdata payload model. The userdata represents the smart pointer,
not an independent copied `T`.

That difference matters:

- `lua::make<T>()` gives Lua its own value object
- `std::shared_ptr<T>` lets Lua share an object with C++

## Pointer Conversions

One intentional restriction in Luacxx is that shared-pointer userdata should
not be treated as `void*`:

```cpp
// shared_ptr's cannot be safely converted to void pointers
```

That protects against erasing the ownership model and recovering an unsafe raw
pointer later.

## When To Use `shared_ptr`

Prefer `shared_ptr` bindings when:

- shared lifetime is part of the API design
- objects are passed around by shared ownership already
- Lua should observe mutations made elsewhere

Prefer value userdata with `lua::make<T>()` when:

- Lua should own an independent C++ value
- copying is correct
- the object does not need shared ownership

## Related Docs

- [Binding a Class](binding-a-class.md)
- [Stack and Userdata](../reference/stack-and-userdata.md)
