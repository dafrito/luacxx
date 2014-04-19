#ifndef LUAEXCEPTION_HPP
#define LUAEXCEPTION_HPP

#include <stdexcept>
#include <string>

class LuaException : public std::runtime_error
{
    const std::string _what;

    std::string _traceback;

    std::string fullMessage;

public:
    LuaException(const std::string& reason) :
        std::runtime_error("LuaException"),
        _what(reason)
    {
        fullMessage = _what;
    }

    const char* what() const noexcept
    {
        return fullMessage.c_str();
    }

    bool hasTraceback() const
    {
        return !_traceback.empty();
    }

    const std::string& traceback() const
    {
        return _traceback;
    }

    void setTraceback(const std::string& traceback)
    {
        _traceback = traceback;
        if (hasTraceback()) {
            fullMessage = _what + "\n" + _traceback;
        } else {
            fullMessage = _what;
        }
    }
};

#endif // LUAEXCEPTION_HPP
