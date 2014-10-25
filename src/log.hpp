#ifndef luacxx_log_INCLUDED
#define luacxx_log_INCLUDED

#include <lua.hpp>
#include <string>
#include <sstream>
#include <functional>

namespace lua {

enum class LogMessageType {
LOG,
ENTER,
LEAVE,
RESET
};

class LogMessage {
std::string _sender;
std::string _category;
std::string _message;
public:

LogMessage(const std::string& sender, const std::string& category, const std::string& message) :
    _sender(sender),
    _category(category),
    _message(message)
{
}

const std::string& sender() const
{
    return _sender;
}

const std::string& category() const
{
    return _category;
}

const std::string& message() const
{
    return _message;
}

};

void appendStrings(std::stringstream& str);

template <class Arg, class... Rest>
void appendStrings(std::stringstream& str, Arg arg, Rest... rest)
{
    str << arg;
    appendStrings(str, rest...);
}

template <typename... Rest>
std::string appendStrings(Rest... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    return str.str();
}

void LogMessage_metatable(lua_State* const state, const int pos);

typedef std::function<void(lua_State* const, LogMessageType, const LogMessage&)> logger;
void addLogger(lua_State* const state, const logger&);

void dispatchLog(lua_State* const state, const LogMessageType messageType, const LogMessage& message);

void logEnterm(lua_State* const state, const std::string& message);
void logEntersm(lua_State* const state, const std::string& sender, const std::string& message);
void logEntercm(lua_State* const state, const std::string& category, const std::string& message);

template <typename... Args>
void logEnterm(lua_State* const state, Args... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    dispatchLog(state, LogMessageType::ENTER, LogMessage(std::string(), std::string(), str.str()));
}

template <typename... Args>
void logEntercm(lua_State* const state, const std::string& category, Args... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    dispatchLog(state, LogMessageType::ENTER, LogMessage(std::string(), category, str.str()));
}

template <typename... Args>
void logEntersm(lua_State* const state, const std::string& sender, Args... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    dispatchLog(state, LogMessageType::ENTER, LogMessage(sender, std::string(), str.str()));
}

template <typename... Args>
void logEnterscm(lua_State* const state, const std::string& sender, const std::string& category, Args... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    dispatchLog(state, LogMessageType::ENTER, LogMessage(sender, category, str.str()));
}

template <typename... Args>
void logEnter(lua_State* const state, const std::string& sender, const std::string& category, Args... args)
{
    lua::logEnterscm(state, sender, category, args...);
}

void logm(lua_State* const state, const std::string& message);
void logsm(lua_State* const state, const std::string& sender, const std::string& message);
void logcm(lua_State* const state, const std::string& category, const std::string& message);

template <typename... Args>
void logm(lua_State* const state, Args... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    dispatchLog(state, LogMessageType::LOG, LogMessage(std::string(), std::string(), str.str()));
}

template <typename... Args>
void logcm(lua_State* const state, const std::string& category, Args... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    dispatchLog(state, LogMessageType::LOG, LogMessage(std::string(), category, str.str()));
}

template <typename... Args>
void logsm(lua_State* const state, const std::string& sender, Args... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    dispatchLog(state, LogMessageType::LOG, LogMessage(sender, std::string(), str.str()));
}

template <typename... Args>
void logscm(lua_State* const state, const std::string& sender, const std::string& category, Args... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    dispatchLog(state, LogMessageType::LOG, LogMessage(sender, category, str.str()));
}

template <typename... Args>
void log(lua_State* const state, const std::string& sender, const std::string& category, Args... args)
{
    lua::logscm(state, sender, category, args...);
}

void logLeave(lua_State* const state);
void logLeavem(lua_State* const state, const std::string& message);
void logLeavesm(lua_State* const state, const std::string& sender, const std::string& message);
void logLeavecm(lua_State* const state, const std::string& category, const std::string& message);

template <typename... Args>
void logLeavescm(lua_State* const state, const std::string& sender, const std::string& category, Args... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    dispatchLog(state, LogMessageType::LEAVE, LogMessage(sender, category, str.str()));
}

template <typename... Args>
void logLeavem(lua_State* const state, Args... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    dispatchLog(state, LogMessageType::LEAVE, LogMessage(std::string(), std::string(), str.str()));
}

template <typename... Args>
void logLeavecm(lua_State* const state, const std::string& category, Args... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    dispatchLog(state, LogMessageType::LEAVE, LogMessage(std::string(), category, str.str()));
}

template <typename... Args>
void logLeavesm(lua_State* const state, const std::string& sender, Args... args)
{
    std::stringstream str;
    appendStrings(str, args...);
    dispatchLog(state, LogMessageType::LEAVE, LogMessage(sender, std::string(), str.str()));
}

template <typename... Args>
void logLeave(lua_State* const state, const std::string& sender, const std::string& category, Args... args)
{
    lua::logLeavescm(state, sender, category, args...);
}

} // namespace lua

extern "C" int luaopen_luacxx_logging(lua_State* const state);

#endif // luacxx_log_INCLUDED
