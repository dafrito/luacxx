#ifndef LUAEXCEPTION_HPP
#define LUAEXCEPTION_HPP

#include <stdexcept>
#include <string>
#include <QString>

class Lua;

class LuaException : public std::runtime_error
{
    const Lua* const _lua;

public:
    LuaException(const string& reason) :
        std::runtime_error(reason),
        _lua(0)
    {}

    LuaException(const Lua* const lua, const string& reason) :
        std::runtime_error(reason),
        _lua(lua)
    {}

    LuaException(const char* reason) :
        std::runtime_error(reason),
        _lua(0)
    {}

    LuaException(const Lua* const lua, const char* reason) :
        std::runtime_error(reason),
        _lua(lua)
    {}

    explicit LuaException(const QString& reason) :
        std::runtime_error(reason.toStdString()),
        _lua(0)
    {}

    explicit LuaException(const Lua* const lua, const QString& reason) :
        std::runtime_error(reason.toStdString()),
        _lua(lua)
    {}

    const Lua* lua()
    {
        return _lua;
    }
};

#endif // LUAEXCEPTION_HPP
