#include "LuaUserdata.hpp"

#include "LuaEnvironment.hpp"
#include "LuaStack.hpp"
#include "LuaException.hpp"

void LuaUserdata::invokeMetamethod(const lua::Metamethod metamethod, Lua& lua, LuaStack& stack)
{
    throw LuaException(QString("Unsupported metamethod: %1").arg(convertMetamethodToString(metamethod)));
}

bool LuaUserdata::supportsMetamethod(const lua::Metamethod metamethod)
{
    return false;
}

std::shared_ptr<void> LuaUserdata::rawData() const
{
    return std::shared_ptr<void>();
}

QString LuaUserdata::rawDataType() const
{
    return QString();
}

lua::Metamethod convertToMetamethod(const QString& luaMetamethod)
{
    if (luaMetamethod == "__index") {
        return lua::Metamethod::INDEX;
    } else if (luaMetamethod == "__newindex") {
        return lua::Metamethod::NEWINDEX;
    } else if (luaMetamethod == "__gc") {
        return lua::Metamethod::GC;
    } else if (luaMetamethod == "__call") {
        return lua::Metamethod::CALL;
    } else if (luaMetamethod == "__len") {
        return lua::Metamethod::LEN;
    } else if (luaMetamethod == "__eq") {
        return lua::Metamethod::EQ;
    } else if (luaMetamethod == "__lt") {
        return lua::Metamethod::LT;
    } else if (luaMetamethod == "__le") {
        return lua::Metamethod::LE;
    } else if (luaMetamethod == "__concat") {
        return lua::Metamethod::CONCAT;
    } else if (luaMetamethod == "__add") {
        return lua::Metamethod::ADD;
    } else if (luaMetamethod == "__sub") {
        return lua::Metamethod::SUB;
    } else if (luaMetamethod == "__mul") {
        return lua::Metamethod::MUL;
    } else if (luaMetamethod == "__div") {
        return lua::Metamethod::DIV;
    } else if (luaMetamethod == "__mod") {
        return lua::Metamethod::MOD;
    } else if (luaMetamethod == "__pow") {
        return lua::Metamethod::POW;
    } else if (luaMetamethod == "__unm") {
        return lua::Metamethod::UNM;
    }

    throw LuaException(QString("Unexpected metamethod name: " + luaMetamethod));
}

QString convertMetamethodToString(const lua::Metamethod metamethod)
{
    switch (metamethod) {
        case lua::Metamethod::INDEX:
            return "__index";
        case lua::Metamethod::NEWINDEX:
            return "__newindex";
        case lua::Metamethod::GC:
            return "__gc";
        case lua::Metamethod::CALL:
            return "__call";
        case lua::Metamethod::LEN:
            return "__len";
        case lua::Metamethod::EQ:
            return "__eq";
        case lua::Metamethod::LT:
            return "__lt";
        case lua::Metamethod::LE:
            return "__le";
        case lua::Metamethod::CONCAT:
            return "__concat";
        case lua::Metamethod::ADD:
            return "__add";
        case lua::Metamethod::SUB:
            return "__sub";
        case lua::Metamethod::MUL:
            return "__mul";
        case lua::Metamethod::DIV:
            return "__div";
        case lua::Metamethod::MOD:
            return "__mod";
        case lua::Metamethod::POW:
            return "__pow";
        case lua::Metamethod::UNM:
            return "__unm";
        default:
            throw LuaException(QString("Unrecognized metamethod constant: %1").arg(metamethod));
    }
}
