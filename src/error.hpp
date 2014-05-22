#ifndef LUA_CXX_ERROR_HEADER
#define LUA_CXX_ERROR_HEADER

#include <stdexcept>
#include <string>

namespace lua {

class error : public std::runtime_error
{
    std::string _what;
    unsigned int _traceback;

public:
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

    const bool has_traceback() const
    {
        return _what.size() <= _traceback;
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
            _what = _what.substr(0, _traceback) + "\n" + traceback;
        }
    }
};

} // namespace lua

#endif // LUA_ERROR_HEADER
