### NAME

luacxx - Lua binding library for modern C++

### SYNOPSIS

    #include <luacxx/thread.hpp>
    #include <luacxx/stack.hpp>
    #include <luacxx/convert/const_char_p.hpp>
    #include <luacxx/convert/string.hpp>
    #include <luacxx/convert/char_p.hpp>
    #include <luacxx/convert/numeric.hpp>
    #include <luacxx/algorithm.hpp>
    #include <luacxx/load.hpp>

    int main() {
        // Create a new Lua environment to play with.
        auto env = lua::create();

        // Introduce a global into Lua
        env["foo"] = "No time";

        // Run some Lua code directly
        lua::run_string(env, "assert(foo == 'No time')");

        // Retrieve a global
        auto value = env["foo"].get<std::string>();
        assert(value == "No time");

        lua::run_string(env, "print(_VERSION)");

        return 0;
    }

### DESCRIPTION

Luacxx is a C++ library that helps you write Lua bindings for C++ and C code.
It also contains example bindings for several major C and C++ libraries.

*Luacxx plays well with others.* Luacxx does not try to cover up Lua's C API
or its stack-based model. In fact, Luacxx and Lua C API's can and must be
mixed freely, and Luacxx works transparently over Lua's stack, so you can work
using either one. There is absolutely no harm in mixing the two together.

*Luacxx is fast*. A binding's overhead of calling into C and converting
arguments can be significant for simple methods. Luacxx has been built
specifically for efficiency, so it has avoided much of the overhead
that plagues other bindings (and older versions of Luacxx!).

Luacxx's overhead is around that of an extra function call, which means that a
C++ binding will be faster than equivalent Lua code for all but the most
trivial of cases. For instance, this math-intensive benchmark has the
QQuaternion binding performing ~150% faster than an API-indentical quaternion
written in Lua:

    quat = QQuaternion:new(2, 3, 7, 5);
    for i=1, MAX do
        -- Do some CPU-intensive matrix math, as well as creating a temporary.
        quat = quat * QQuaternion:new(2, 2, 2, 2);
        quat:normalize();
    end

    // My numbers
    Benchmark Runs: 10000
    C++:      0.824ms ( 1.00 relative to C++)
    Lua:     21.514ms (26.10 relative to C++)
    Luacxx:  13.579ms (16.47 relative to C++)

*Luacxx is frugal*. Luacxx takes advantage of C++'s memory efficiency.
Objects pushed on the Lua stack are instantiated directly on new Lua userdata,
and with only 4 bytes of Luacxx-specific metadata appended to the end.
`lua_touserdata` works out-of-the-box, and the returned value can be cast
directly to the intended C++ type.

*Luacxx is open-ended*. Much of Luacxx is built using class templates. This
allows you to add new support for your own types without needing to recompile
Luacxx. Once a new template specialization for your type is found, all of
Luacxx's APIs will be able to use it.

*Luacxx is comprehensive*. Luacxx includes example bindings for over 150 Qt
classes, as well as automatic introspection support for QObjects. It also has
preliminary support for Gtk's introspection system, allowing any project with
GObject introspection support to work with Luacxx.

*Luacxx is not a generator*. Luacxx doesn't write header files or extra
boilerplate. Everything can be done using just a modern C++ compiler.

### OVERVIEW

This library is designed to work in tandem with Lua's existing C API, so it
does not provide a complete facade. On the contrary, I find Lua's C API to be
amazingly well-designed, so I've tried to ensure that Luacxx can be intermixed
freely with Lua's C API. In fact, most of the Lua C API has no analog in
Luacxx - I just use the original, like in the following example:

    // Add all arguments
    int add_several(lua_State* const state)
    {
        // Get each argument
        int sum = 0;
        for (int i = 1; i <= lua_gettop(state); ++i) {
            sum += lua::get<int>(state, i);
        }

        // Return the value
        lua::push(state, sum);
        lua_replace(state, 1);
        return 1;
    }

That being said, there are several places where Luacxx greatly simplify common
tasks. For instance, Lua has a number of `lua_push*` functions that can be
replaced with Luacxx's `lua::push` template and appropriate specializations. You
can extend this specialization with your own types, and Luacxx's other
features will immediately support them.

Modern C++ also adds support for variadic templates, which can be used to
provide a way to push a function of any arity into Lua without needing to write
the marshalling code yourself or running a preprocessor:

    // Standard C API is, of course, supported
    int create_foo(lua_State* const);
    lua::push(state, create_foo);

    // Fundamental types work, too
    int sum(int a, int b);
    lua::push(state, sum);

    // As do pointers to userdata and conversions to C++ strings.
    void changeTitle(QWindow* window, const std::string& title);
    lua::push(state, changeTitle);

    // Even lambdas work too, with a bit of help
    lua::push_function<int(int, int)>(state, [](int first, int second) {
        return first + second;
    });

### STYLE

STL conventions are used for naming and case, though not slavishly, to
infer that a template-heavy C++ dialect is used. However, adherance to Lua's
conventions is preferred over that of C++.

### BUILDING

    git clone https://github.com/dafrito/luacxx.git
    cd luacxx
    cmake -S . -B build
    cmake --build build -j
    # If you're ready to install, run this:
    # cmake --install build

### REQUIRED DEPENDENCIES

#### Modern C++ compiler

Luacxx depends heavily on modern C++ features for its operation. It would be a
large undertaking to remove the use of these new features, and not without a
significant loss in the expressiveness of the code.

Luacxx has been built successfully using the following compilers:

    gcc version 4.8.3 20140911 (Red Hat 4.8.3-7) (GCC)
    gcc version 4.8.3 20140624 (Red Hat 4.8.3-1) (GCC)
    clang version 3.4 (tags/RELEASE_34/final)
    Apple clang version 17.0.0 (clang-1700.6.3.2)

### Lua 5.2

Luacxx uses Lua as its underlying foundation. It would not be possible to
remove it without rewriting the project, though support for older Lua versions
be added.

Luacxx has been built successfully using the following versions:

    Lua 5.2.2  Copyright (C) 1994-2013 Lua.org, PUC-Rio
    Lua 5.4.8  Copyright (C) 1994-2025 Lua.org, PUC-Rio

### OPERATING SYSTEM SUPPORT

#### OSes that can build Luacxx without needing manually installed dependencies

Luacxx has been built on Linux, MacOS, and Windows.

    Fedora 20 (Linux 3.14.8-200.fc20.x86_64 #1 SMP Mon Jun 16 21:57:53 UTC 2014 x86_64 x86_64 x86_64 GNU/Linux)
    Darwin MacBookAir.lan 25.3.0 Darwin Kernel Version 25.3.0: Wed Jan 28 20:53:01 PST 2026; root:xnu-12377.81.4~5/RELEASE_ARM64_T8103 arm64

#### OSes that can build Luacxx with manually installed dependencies

None yet known.

#### OSes that can build Luacxx only with emulation

#### Microsoft Windows

Luacxx can be built using MinGW (and likely with Cygwin, though I haven't tried).

### GETTING IN TOUCH

Reach out at aaronfaanes@gmail.com for questions or comments, or open an issue
on Github.

### LICENSE

By default, this project uses the MIT license. The included bindings use the
license of their respective projects.

### LUA DOCUMENTATION

Lua 5.2 - http://www.lua.org/manual/5.2/manual.html

    Lua is an extension programming language designed to support general
    procedural programming with data description facilities.

LuaJIT - http://luajit.org/index.html

    LuaJIT is a Just-In-Time Compiler (JIT) for the Lua programming language.

### ALTERNATIVES

tolua++ - http://www.codenix.com/~tolua/

    tolua++ is an extended version of tolua, a tool to integrate C/C++ code
    with Lua.

tolua - http://www.tecgraf.puc-rio.br/~celes/tolua/

    tolua is a tool that greatly simplifies the integration of C/C++ code with Lua.
    Based on a cleaned header file, tolua automatically generates the binding code
    to access C/C++ features from Lua.

Luabind - http://www.rasterbar.com/products/luabind.html

    Luabind is a library that helps you create bindings between C++ and Lua. It
    has the ability to expose functions and classes, written in C++, to Lua. It
    will also supply the functionality to define classes in lua and let them
    derive from other lua classes or C++ classes. Lua classes can override
    virtual functions from their C++ baseclasses.

lqt - https://github.com/mkottman/lqt

    lqt is a Lua binding to the Qt framework. It is an automated binding
    generated from the Qt headers, and covers almost all classes and methods
    from supported Qt modules.

QtLua - http://www.nongnu.org/libqtlua/

    The QtLua library aims to make Qt4/Qt5 applications scriptable using the
    Lua scripting language. It is an alternative to the QtScript module.

LGI - https://github.com/pavouk/lgi

    LGI is gobject-introspection based dynamic Lua binding to GObject based
    libraries. It allows using GObject-based libraries directly from Lua.
