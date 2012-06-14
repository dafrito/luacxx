#include "Lua.hpp"
#include "LuaStack.hpp"
#include "LuaException.hpp"
#include "LuaReference.hpp"

namespace
{
    class QLuaCallable : public QObject, public lua::LuaCallable
    {
    public:
        QLuaCallable(QObject* const parent, const lua::LuaCallable& func) :
            QObject(parent),
            lua::LuaCallable(func)
        {}
    };
}

int LuaStack::invokeWrappedFunction(lua_State* state)
{
    void* p = lua_touserdata(state, lua_upvalueindex(1));
    Lua* lua = static_cast<Lua*>(p);
    p = lua_touserdata(state, lua_upvalueindex(2));
    QLuaCallable* func = static_cast<QLuaCallable*>(p);
    // Push all upvalues unto the stack.
    int i = 3;
    while (!lua_isnone(state, lua_upvalueindex(i))) {
        lua_pushvalue(state, lua_upvalueindex(i));
        lua_insert(state, 1);
        i++;
    }
    LuaStack stack(*lua);
    stack.grab();
    (*func)(*lua, stack);
    stack.disown();
    return lua_gettop(state);
}

LuaStack::LuaStack(Lua& lua) :
    lua(lua),
    _offset(lua_gettop(lua.state))
{
}

LuaStack& LuaStack::offset(int offset)
{
    if(offset < 0)
        throw LuaException(&lua, "Offset must be non-negative");
    if(offset > lua_gettop(lua.state))
        throw LuaException(&lua, "Offset must be less than the top of lua's stack");
    _offset = offset;
    return (*this);
}

int LuaStack::size() const
{
    return lua_gettop(lua.state) - offset();
}

LuaStack& LuaStack::pop(int count)
{
    if(count > size())
        throw LuaException(&lua, "Refusing to pop elements not managed by this stack");
    lua_pop(lua.state, count);
    return (*this);
}

LuaStack& LuaStack::shift(int count)
{
    while(count-- > 0) {
        // TODO We need to check if the offset is being moved here.
        lua_remove(lua.state, 1);
    }
    return (*this);
}

void LuaStack::checkPos(int pos) const
{
    if (isMagicalPos(pos))
        return;
    const int top=lua_gettop(lua.state);
    if (pos == 0)
        throw LuaException(&lua, "Stack position must not be zero");
    // Convert relative positions to absolute ones.
    if (pos < 0)
        pos += top;
    if (pos < offset())
        throw LuaException(&lua, "Stack position is not managed by this stack");
    if (pos > top)
        throw LuaException(&lua, "Stack position is beyond the top of the lua stack");
}

LuaStack& LuaStack::replace(int pos)
{
    checkPos(pos);
    if (empty())
        throw LuaException(&lua, "Stack must not be empty when replacing elements");
    lua_replace(lua.state, pos);
    return (*this);
}

LuaStack& LuaStack::swap(int a, int b)
{
    checkPos(a);
    checkPos(b);

    lua_pushvalue(lua.state, b);
    lua_pushvalue(lua.state, a - 1);
    // Stack is now [..., b, a]

    // Replace b by popping the copy of a
    lua_replace(lua.state, b - 2);

    // Replace a by popping the copy of b
    lua_replace(lua.state, a - 1);
}

bool LuaStack::isMagicalPos(const int& pos) const
{
    return pos == LUA_GLOBALSINDEX;
}

lua::Type LuaStack::type(int pos) const
{
    checkPos(pos);
    return lua::convert_lua_type(lua_type(lua.state, pos));
}

std::string LuaStack::typestring(int pos) const
{
    checkPos(pos);
    return std::string(lua_typename(lua.state, lua_type(lua.state, pos)));
}

LuaStack& LuaStack::to(const char** sink, int pos)
{
    checkPos(pos);
    *sink = lua_tostring(lua.state, pos);
    return (*this);
}

const char* LuaStack::cstring(int pos)
{
    checkPos(pos);
    return lua_tostring(lua.state, pos);
}

std::string LuaStack::string(int pos)
{
    checkPos(pos);
    return std::string(cstring(pos));
}

QString LuaStack::qstring(int pos)
{
    checkPos(pos);
    QString str;
    to(&str, pos);
    return str;
}

LuaStack& LuaStack::to(std::string* const sink, int pos)
{
    checkPos(pos);
    *sink = lua_tostring(lua.state, pos);
    return (*this);
}

LuaStack& LuaStack::to(QString* const sink, int pos)
{
    checkPos(pos);
    *sink = lua_tostring(lua.state, pos);
    return (*this);
}

QObject* LuaStack::object(int pos)
{
    checkPos(pos);
    QObject* ptr;
    to(&ptr, pos);
    return ptr;
}

LuaReference LuaStack::save()
{
    checkPos(-1);
    return LuaReference(lua);
}

LuaStack& LuaStack::to(bool* sink, int pos)
{
    checkPos(pos);
    *sink = lua_toboolean(lua.state, pos);
    return (*this);
}

LuaStack& LuaStack::to(QVariant* const sink, int pos)
{
    checkPos(pos);
    switch(type(pos)) {
    case lua::NIL:
        sink->clear();
        break;
    case lua::BOOLEAN:
        sink->setValue(boolean(pos));
        break;
    case lua::NUMBER:
        sink->setValue(number(pos));
        break;
    case lua::STRING:
        sink->setValue(qstring(pos));
        break;
    case lua::LIGHTUSERDATA:
        sink->setValue(object());
        break;
    case lua::TABLE:
    case lua::FUNCTION:
    case lua::THREAD:
    default:
        throw LuaException(&lua, std::string("Type not supported: ") + typestring(pos));
    }
    return (*this);
}

bool LuaStack::boolean(int pos)
{
    bool b;
    to(&b, pos);
    return b;
}

LuaStack& LuaStack::to(lua_Number* sink, int pos)
{
    checkPos(pos);
    *sink = lua_tonumber(lua.state, pos);
    return (*this);
}

LuaStack& LuaStack::to(short* sink, int pos)
{
    checkPos(pos);
    *sink = lua_tointeger(lua.state, pos);
    return (*this);
}

LuaStack& LuaStack::to(int* sink, int pos)
{
    checkPos(pos);
    *sink = lua_tointeger(lua.state, pos);
    return (*this);
}

LuaStack& LuaStack::to(long* sink, int pos)
{
    checkPos(pos);
    *sink = lua_tonumber(lua.state, pos);
    return (*this);
}

LuaStack& LuaStack::to(float* sink, int pos)
{
    checkPos(pos);
    *sink = lua_tonumber(lua.state, pos);
    return (*this);
}

LuaStack& LuaStack::to(QObject** const sink, int pos)
{
    checkPos(pos);
    if (lua_islightuserdata(lua.state, pos)) {
        *sink = static_cast<QObject*>(lua_touserdata(lua.state, pos));
    } else {
        *sink = 0;
    }
    return *this;
}

double LuaStack::number(int pos)
{
    double b;
    to(&b, pos);
    return b;
}

LuaStack& LuaStack::global(const char* name)
{
    lua_getglobal(lua.state, name);
    return (*this);
}

LuaStack& LuaStack::global(const std::string& name)
{
    global(name.c_str());
    return (*this);
}

LuaStack& LuaStack::global(const QString& name)
{
    global(name.toAscii().data());
    return (*this);
}

LuaStack& LuaStack::pushedSet(int tablePos)
{
    checkPos(tablePos);
    lua_settable(lua.state, tablePos);
    return (*this);
}

LuaStack& LuaStack::push(const char* value)
{
    lua_pushstring(lua.state, value);
    return (*this);
}

LuaStack& LuaStack::push(const char* value, int len)
{
    lua_pushlstring(lua.state, value, len);
    return (*this);
}

LuaStack& LuaStack::push(const QChar& value)
{
    char v = value.toAscii();
    return push(&v, 1);
}

LuaStack& LuaStack::push(const QString& value)
{
    return push(value.toAscii().data());
}

LuaStack& LuaStack::push(const std::string& value)
{
    return push(value.c_str());
}

LuaStack& LuaStack::push(const lua_Number& value)
{
    lua_pushnumber(lua.state, value);
    return (*this);
}

LuaStack& LuaStack::push(const short& value)
{
    lua_pushinteger(lua.state, value);
    return (*this);
}

LuaStack& LuaStack::push(const int& value)
{
    lua_pushinteger(lua.state, value);
    return (*this);
}

LuaStack& LuaStack::push(const long& value)
{
    lua_pushnumber(lua.state, value);
    return (*this);
}

LuaStack& LuaStack::push(const float& value)
{
    lua_pushnumber(lua.state, value);
    return (*this);
}

LuaStack& LuaStack::push(void* const p)
{
    lua_pushlightuserdata(lua.state, p);
    return (*this);
}

LuaStack& LuaStack::push(const bool& b)
{
    lua_pushboolean(lua.state, b);
    return (*this);
}

LuaStack& LuaStack::push(void(*p)(Lua& lua, LuaStack& stack), const int closed)
{
    return this->push(lua::LuaCallable(p), closed);
}

LuaStack& LuaStack::push(const lua::LuaCallable& f, const int closed)
{
    if (closed > 0) {
        checkPos(-closed);
    }
    push(&lua);
    push(new QLuaCallable(&lua, f));
    lua_insert(lua.state, -2-closed);
    lua_insert(lua.state, -2-closed);
    lua_pushcclosure(lua.state, invokeWrappedFunction, 2 + closed);
    return (*this);
}

LuaStack& LuaStack::push(QObject* const obj)
{
    lua_pushlightuserdata(lua.state, obj);
    return (*this);
}

LuaStack& LuaStack::push(const QVariant& variant)
{
    switch (variant.type()) {
    case QVariant::Invalid:
        return pushNil();
    case QVariant::Bool:
        return push(variant.toBool());
    case QVariant::Char:
        return push(variant.toChar());
    case QVariant::Int:
        return push(variant.toInt());
    case QVariant::Double:
    case QVariant::UInt:
        return push(variant.toDouble());
    default:
        throw LuaException(&lua, std::string("Type not supported: ") + variant.typeName());
    }
    return (*this);
}

LuaStack& LuaStack::push(const LuaValue& value)
{
    value.push(*this);
    return *this;
}

LuaStack& LuaStack::pushNewTable()
{
    lua_newtable(lua.state);
    return (*this);
}

LuaStack& LuaStack::pushNil()
{
    lua_pushnil(lua.state);
    return (*this);
}

bool LuaStack::isNil(const int pos)
{
    checkPos(pos);
    return lua_isnil(lua.state, pos) == 1;
}

LuaStack::~LuaStack()
{
    if (size() > 0)
        lua_pop(lua.state, size());
}
