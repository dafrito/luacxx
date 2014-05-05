#ifndef LUA_EXCEPTION_HEADER
#define LUA_EXCEPTION_HEADER

#include <stdexcept>
#include <string>

namespace lua {

class exception : public std::runtime_error
{
    std::string _what;
    std::string _traceback;

public:
    exception(const std::string& reason) :
        std::runtime_error("lua::exception"),
        _what(reason),
        _traceback()
    {
    }

    const char* what() const noexcept
    {
        if (!traceback().empty()) {
            return (_what + "\n" + traceback()).c_str();
        }
        return _what.c_str();
    }

    const std::string& traceback() const
    {
        return _traceback;
    }

    void set_traceback(const std::string& traceback)
    {
        _traceback = traceback;
    }
};

} // namespace lua

#endif // LUA_EXCEPTION_HEADER
