# luacxx

Luacxx is a modern C++ library for binding C and C++ code to Lua.

It is designed to work with the Lua C API rather than hide it. You can freely
mix raw Lua calls with Luacxx helpers for pushing values, reading values,
constructing userdata, and exposing functions.

## What It Focuses On

- Modern C++ and the standard library
- Direct interop with the Lua C API
- Low-overhead userdata and conversion support
- Extensible `Push<T>`, `Store<T>`, and `Get<T>` customizations
- CMake-first installation and consumption

## Examples

The smallest useful example is just moving primitive and standard-library
values across the Lua boundary:

```cpp
#include <cassert>
#include <string>

#include <luacxx/algorithm.hpp>
#include <luacxx/convert/numeric.hpp>
#include <luacxx/convert/string.hpp>
#include <luacxx/load.hpp>
#include <luacxx/thread.hpp>

int main()
{
    auto env = lua::create();

    env["answer"] = 42;
    env["name"] = std::string("luacxx");

    lua::run_string(env, "assert(answer == 42)");

    const auto answer = env["answer"].get<int>();
    const auto name = env["name"].get<std::string>();

    assert(answer == 42);
    assert(name == "luacxx");
}
```

For a metatable-backed class binding, see the multi-file example in
[`examples/003-counter-binding`](examples/003-counter-binding):

- [`examples/003-counter-binding/counter.hpp`](examples/003-counter-binding/counter.hpp) defines the C++ class
- [`examples/003-counter-binding/counter_lua.hpp`](examples/003-counter-binding/counter_lua.hpp) declares the Luacxx metatable and binding entry points
- [`examples/003-counter-binding/counter_lua.cpp`](examples/003-counter-binding/counter_lua.cpp) defines the metatable methods and constructor binding
- [`examples/003-counter-binding/main.cpp`](examples/003-counter-binding/main.cpp) registers the binding and exercises it from Lua

That example shows the usual “real object in userdata + explicit metatable”
path that Luacxx uses for non-primitive types.

## Build

Luacxx requires:

- C++20
- CMake 3.24 or newer
- Lua 5.2 or newer

Build and install:

```sh
cmake -S . -B build
cmake --build build
cmake --install build
```

To build the test suite:

```sh
cmake -S . -B build -DLUACXX_BUILD_TESTS=ON
cmake --build build --target luacxx_test_main
ctest --test-dir build --output-on-failure
```

## Use From CMake

After installation, consume Luacxx with CMake:

```cmake
find_package(luacxx CONFIG REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE luacxx::luacxx)
```

The exported package also declares its Lua dependency.

## Use From pkg-config

Luacxx also installs a `pkg-config` file:

```sh
pkg-config --cflags --libs luacxx
```

## Conversions

Built-in conversions include:

- numbers and characters
- `std::string`
- C strings and `std::string_view` as push-only string inputs
- `std::vector`
- `std::array`
- `std::map`
- `std::unordered_map`
- `std::optional`
- `std::tuple`
- `std::shared_ptr`

Additional types can be integrated by specializing the conversion templates.

If you want to add your own types, start with
[`docs/guide/conversion-templates.md`](docs/guide/conversion-templates.md).

## Documentation

The user guide and reference live under [`docs/`](docs/). Good entry points are:

- [`docs/index.md`](docs/index.md) for the full guide/reference index
- [`docs/guide/binding-a-primitive-type.md`](docs/guide/binding-a-primitive-type.md) for teaching Luacxx a value-like type
- [`docs/guide/binding-a-class.md`](docs/guide/binding-a-class.md) for userdata-backed classes
- [`docs/guide/working-with-shared-ptr.md`](docs/guide/working-with-shared-ptr.md) for shared-ownership bindings
- [`docs/guide/conversion-templates.md`](docs/guide/conversion-templates.md) for `Push<T>`, `Store<T>`, `Get<T>`, and `Construct<T>`
- [`docs/guide/light-userdata-and-void-p.md`](docs/guide/light-userdata-and-void-p.md) for when `void*` works and why it is limited to light userdata
- [`docs/guide/metatable-macros.md`](docs/guide/metatable-macros.md) for the quick metatable-definition macros
- [`docs/guide/luacxx-allow-missing-metatables.md`](docs/guide/luacxx-allow-missing-metatables.md) for the fallback-metatable policy and why it is off by default
- [`docs/guide/understanding-type-safety.md`](docs/guide/understanding-type-safety.md) for how userdata type checks and inheritance casts work
- [`docs/guide/understanding-userdata-memory.md`](docs/guide/understanding-userdata-memory.md) for how Luacxx stores and destroys C++ objects in userdata
- [`docs/guide/writing-bindings.md`](docs/guide/writing-bindings.md) for broader binding design guidance
- [`docs/guide/useful-lua-functions.md`](docs/guide/useful-lua-functions.md) for the Lua C API functions Luacxx leans on most
- [`docs/reference/stack-and-userdata.md`](docs/reference/stack-and-userdata.md) and [`docs/reference/thread-and-algorithms.md`](docs/reference/thread-and-algorithms.md) for API-oriented reference notes

## License

MIT
