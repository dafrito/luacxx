#ifndef LUAEXCEPTION_HPP
#define LUAEXCEPTION_HPP

#include <stdexcept>
#include <string>

class LuaException : public std::runtime_error
{
    const std::string _what;

public:
    LuaException(const std::string& reason) :
        std::runtime_error("LuaException"),
        _what(std::string("LuaException: ") + reason)
    {}

    const char* what() const noexcept
    {
        return _what.c_str();
    }

};

#endif // LUAEXCEPTION_HPP
