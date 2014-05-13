#ifndef LUA_CXX_ERROR_HEADER
#define LUA_CXX_ERROR_HEADER

#include <stdexcept>
#include <string>

namespace lua {

class error : public std::runtime_error
{
    std::string _what;
    std::string _traceback;

public:
    error(const std::string& reason) :
        std::runtime_error("lua::error"),
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

#endif // LUA_ERROR_HEADER
