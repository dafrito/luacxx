#ifndef LUACXX_ERROR_INCLUDED
#define LUACXX_ERROR_INCLUDED

#include <stdexcept>
#include <string>

#include "log.hpp"

namespace lua {

/*

=head1 NAME

lua::error - an error thrown from the Lua runtime.

=head1 SYNOPSIS

    #include <luacxx/error.hpp>
    #include <sstream>

    if (lua_type(state, -1) != LUA_TFUNCTION) {
        std::stringstream str;

        str << "A function was expected, but a "
            << lua_typename(state, lua_type(state, -1))
            << " was given.";
        throw lua::error(str.str());
    }

    // ... later on, if one is thrown

    try {
        lua::call(lua::index(state, 1), some_data, more_data);
    } catch (lua::error& ex) {
        std::cerr << "Error occurred while running function:\n"
            << ex.what()
            << '\n';
    }

=head1 DESCRIPTION

Lua-cxx will wrap and rethrow lua::errors as they propagate between the C
runtime and the Lua runtime. This object does no manipulation of the Lua state,
so it's safe to copy and use even when the condition of the Lua state is
indeterminate.

Aside from the usual what() description method typical of C++ exceptions,
lua::error allows access to the traceback via traceback(). This value must be
set manually, though throwing a lua::error that is eventually caught by this
library will have its traceback set up automatically.

*/

class error : public std::runtime_error
{
    std::string _what;
    unsigned int _traceback;

public:

/*

=head1 METHODS

=head2 lua::error(lua_State* const state, const std::string& what)

=head2 lua::error(const std::string& what)

=head2 lua::error()

*/

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

/*

=head2 std::string traceback = error.traceback();

Returns the traceback associated with this error.

=head2 error.set_traceback(const std::string& traceback)

Sets the traceback to the given string.

*/

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
