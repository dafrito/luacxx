#ifndef LUA_CXX_QCOREAPPLICATION_INCLUDED
#define LUA_CXX_QCOREAPPLICATION_INCLUDED

#include "../stack.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <cstring>

class QCoreApplication;

namespace lua {

class QCoreApplicationArgs {
    int _argc;
    char** _argv;

public:
    QCoreApplicationArgs(const int $argc) :
        _argc($argc),
        _argv(new char*[$argc])
    {
        memset(_argv, 0, sizeof(char*) * _argc);
    }

    void set(int index, const char* value)
    {
        if (index < 0 || index >= argc()) {
            throw std::logic_error("Index must be [0, argc()]");
        }
        if (_argv[index]) {
            free(_argv[index]);
        }
        _argv[index] = strdup(value);
    }

    void clear()
    {
        for (int i = 0; i < _argc; ++i) {
            if (_argv[i]) {
                free(_argv[i]);
            }
            _argv[i] = nullptr;
        }

    }

    std::string dump()
    {
        std::stringstream str;

        str << "QCoreApplication arguments: [";
        for (int i = 0; i < argc(); ++i) {
            if (i > 0) {
                str << ", ";
            }
            str << '"' << _argv[i] << '"';
        }
        str << ']';

        return str.str();
    }

    int& argc()
    {
        return _argc;
    }

    char** const argv()
    {
        return _argv;
    }

    ~QCoreApplicationArgs()
    {
        clear();
        delete[] _argv;
    }
};

QCoreApplicationArgs* save_arguments(lua::index arg);

template <class App>
int QCoreApplication_new(lua::state* const state)
{
    // Save the initial arguments into a userdata
    auto arguments = lua::save_arguments(lua::index(state, 2));

    // Create the application
    lua::make<App>(state, arguments->argc(), arguments->argv());

    // Save the arguments table within the metatable
    lua_getmetatable(state, -1);
    lua_pushvalue(state, -3);
    // [..., arguments, application, app_mt, arguments]
    lua_setfield(state, -2, "__arguments");
    lua_pop(state, 1);
    // [..., arguments, application]

    // Only return the application
    lua_replace(state, 1);
    lua_settop(state, 1);
    return 1;
}

void QCoreApplication_metatable(const lua::index& mt);

template <>
struct Metatable<QCoreApplication>
{
    static constexpr const char* name = "QCoreApplication";

    static bool metatable(const lua::index& mt, QCoreApplication* const)
    {
        lua::QCoreApplication_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QCoreApplication(lua::state* const);

#endif // LUA_CXX_QCOREAPPLICATION_INCLUDED
