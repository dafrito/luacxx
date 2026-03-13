#ifndef LUACXX_ERROR_INCLUDED
#define LUACXX_ERROR_INCLUDED

#include <stdexcept>
#include <string>

#include "log.hpp"

namespace lua {

// `lua::error` is Luacxx's main exception type for Lua-facing failures.
// See docs/guide/handling-lua-errors.md for usage and traceback notes.

class error : public std::runtime_error
{
    std::string _what;
    unsigned int _traceback;

public:

error(lua_State* const state, const std::string& what);

template <class... Rest>
error(lua_State* const state, Rest... args) :
    error(state, lua::appendStrings(args...))
{
}

error(const std::string& what) :
    std::runtime_error("lua::error"),
    _what(what),
    _traceback(what.size())
{
}

error() :
    std::runtime_error("lua::error"),
    _what("An unspecified Lua error occurred."),
    _traceback(_what.size())
{
}

virtual const char* what() const noexcept override
{
    return _what.c_str();
}

bool has_traceback() const
{
    return _what.size() <= _traceback;
}

const std::string message() const
{
    if (!has_traceback()) {
        return _what;
    }
    return _what.substr(0, _traceback);
}

const std::string traceback() const
{
    if (!has_traceback()) {
        return "";
    }
    return _what.substr(_traceback + 1);
}

void set_traceback(const std::string& traceback)
{
    if (!has_traceback()) {
        _what += "\n" + traceback;
    } else {
        _what = message() + "\n" + traceback;
    }
}

};

} // namespace lua

#endif // LUACXX_ERROR_INCLUDED
