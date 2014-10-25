#include "log.hpp"

#include "stack.hpp"
#include "enum.hpp"
#include "algorithm.hpp"
#include "thread.hpp"
#include "convert/numeric.hpp"
#include "convert/callable.hpp"
#include "convert/const_char_p.hpp"
#include "convert/string.hpp"

#include "std/vector.hpp"

namespace lua {

void appendStrings(std::stringstream& str)
{
}

int addLogger(lua_State* const state, const lua::logger& logFunction)
{
    lua_getfield(state, LUA_REGISTRYINDEX, "luacxx.loggers");
    if (lua_type(state, -1) == LUA_TNIL) {
        lua_pop(state, 1);
        // Create our logger table since it doesn't exist.
        lua::make<std::vector<lua::logger>>(state);
        lua_pushvalue(state, -1);
        lua_setfield(state, LUA_REGISTRYINDEX, "luacxx.loggers");
    }
    // Check if the list of loggers has been destroyed. This should only
    // happen during its __gc, but it's still a dangerous moment.
    if (lua::get_userdata_block(state, -1)->destroyed()) {
        return -1;
    }

    // Add the new logging receiver
    auto loggers = lua::get<std::vector<lua::logger>*>(state, -1);
    loggers->push_back(logFunction);
    lua_pop(state, 1);
    return loggers->size() - 1;
}

void removeLogger(lua_State* const state, const int loggingPos)
{
    lua_getfield(state, LUA_REGISTRYINDEX, "luacxx.loggers");
    if (lua_type(state, -1) == LUA_TNIL) {
        lua_pop(state, 1);
        return;
    }
    // Check if the list of loggers has been destroyed. This should only
    // happen during its __gc, but it's still a dangerous moment.
    if (lua::get_userdata_block(state, -1)->destroyed()) {
        return;
    }

    auto loggers = lua::get<std::vector<lua::logger>*>(state, -1);
    loggers->at(loggingPos) = lua::logger();
    lua_pop(state, 1);
}

void dispatchLog(lua_State* const state, const LogMessageType messageType, const LogMessage& message)
{
    lua_getfield(state, LUA_REGISTRYINDEX, "luacxx.loggers");
    if (lua_type(state, -1) == LUA_TNIL) {
        goto end;
    }
    // Check if the list of loggers has been destroyed. This should only
    // happen during its __gc, but it's still a dangerous moment.
    if (lua::get_userdata_block(state, -1)->destroyed()) {
        goto end;
    }
    for (auto& logFunction : lua::get<std::vector<lua::logger>&>(state, -1)) {
        if (logFunction) {
            logFunction(state, messageType, message);
        }
    }
end:
    lua_pop(state, 1);
}


void logEnterm(lua_State* const state, const std::string& message)
{
    logEnterscm(state, std::string(), std::string(), message);
}

void logEntersm(lua_State* const state, const std::string& sender, const std::string& message)
{
    logEnterscm(state, sender, std::string(), message);
}

void logEntercm(lua_State* const state, const std::string& category, const std::string& message)
{
    logEnterscm(state, std::string(), category, message);
}

void logm(lua_State* const state, const std::string& message)
{
    logscm(state, std::string(), std::string(), message);
}

void logsm(lua_State* const state, const std::string& sender, const std::string& message)
{
    logscm(state, sender, std::string(), message);
}

void logcm(lua_State* const state, const std::string& category, const std::string& message)
{
    logscm(state, std::string(), category, message);
}

void logLeave(lua_State* const state)
{
    logLeavescm(state, std::string(), std::string(), std::string());
}

void logLeavem(lua_State* const state, const std::string& message)
{
    logLeavescm(state, std::string(), std::string(), message);
}

void LogMessage_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["sender"] = &LogMessage::sender;
    mt["category"] = &LogMessage::category;
    mt["message"] = &LogMessage::message;
}

} // namespace lua
