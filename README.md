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

## Example

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
- C strings and `std::string`
- `std::vector`
- `std::array`
- `std::map`
- `std::unordered_map`
- `std::optional`
- `std::tuple`
- `std::shared_ptr`

Additional types can be integrated by specializing the conversion templates.

## Documentation

The user guide and reference live under [`docs/`](docs/):

- [`docs/index.md`](docs/index.md)
- [`docs/guide/binding-a-primitive-type.md`](docs/guide/binding-a-primitive-type.md)
- [`docs/guide/binding-a-class.md`](docs/guide/binding-a-class.md)
- [`docs/guide/working-with-shared-ptr.md`](docs/guide/working-with-shared-ptr.md)
- [`docs/guide/understanding-type-safety.md`](docs/guide/understanding-type-safety.md)
- [`docs/guide/understanding-userdata-memory.md`](docs/guide/understanding-userdata-memory.md)
- [`docs/guide/metatable-macros.md`](docs/guide/metatable-macros.md)
- [`docs/guide/luacxx-allow-missing-metatables.md`](docs/guide/luacxx-allow-missing-metatables.md)
- [`docs/guide/conversion-templates.md`](docs/guide/conversion-templates.md)
- [`docs/guide/writing-bindings.md`](docs/guide/writing-bindings.md)
- [`docs/guide/useful-lua-functions.md`](docs/guide/useful-lua-functions.md)
- [`docs/reference/stack-and-userdata.md`](docs/reference/stack-and-userdata.md)
- [`docs/reference/thread-and-algorithms.md`](docs/reference/thread-and-algorithms.md)

## License

MIT
