#include "LuaEnvironment.hpp"
#include "LuaStack.hpp"
#include "LuaException.hpp"
#include "LuaValue.hpp"
#include "LuaReferenceAccessible.hpp"
#include "LuaAccessible.hpp"
#include "LuaUserdata.hpp"

LuaStack::LuaStack(Lua& lua) :
    _lua(lua),
    _offset(lua_gettop(luaState()))
{
}

LuaStack& LuaStack::offset(int offset)
{
    if(offset < 0)
        throw LuaException(&lua(), "Offset must be non-negative");
    if(offset > lua_gettop(luaState()))
        throw LuaException(&lua(), "Offset must be less than the top of lua's stack");
    _offset = offset;
    return (*this);
}

int LuaStack::size() const
{
    return lua_gettop(luaState()) - offset();
}

LuaStack& LuaStack::pop(int count)
{
    if(count > size())
        throw LuaException(&lua(), "Refusing to pop elements not managed by this stack");
    lua_pop(luaState(), count);
    return (*this);
}

LuaStack& LuaStack::shift(int count)
{
    while(count-- > 0) {
        // TODO We need to check if the offset is being moved here.
        lua_remove(luaState(), 1);
    }
    return (*this);
}

void LuaStack::checkPos(int pos) const
{
    if (isMagicalPos(pos))
        return;
    const int top=lua_gettop(luaState());
    if (pos == 0)
        throw LuaException(&lua(), "Stack position must not be zero");
    // Convert relative positions to absolute ones.
    if (pos < 0)
        pos += top;
    if (pos < offset())
        throw LuaException(&lua(), "Stack position is not managed by this stack");
    if (pos > top)
        throw LuaException(&lua(), "Stack position is beyond the top of the lua stack");
}

LuaStack& LuaStack::replace(int pos)
{
    checkPos(pos);
    if (empty())
        throw LuaException(&lua(), "Stack must not be empty when replacing elements");
    lua_replace(luaState(), pos);
    return (*this);
}

LuaStack& LuaStack::swap(int a, int b)
{
    checkPos(a);
    checkPos(b);

    lua_pushvalue(luaState(), b);
    lua_pushvalue(luaState(), a - 1);
    // Stack is now [..., b, a]

    // Replace b by popping the copy of a
    lua_replace(luaState(), b - 2);

    // Replace a by popping the copy of b
    lua_replace(luaState(), a - 1);
}

bool LuaStack::isMagicalPos(const int& pos) const
{
    return false;
}

lua::Type LuaStack::type(int pos) const
{
    checkPos(pos);
    return lua::convert_lua_type(lua_type(luaState(), pos));
}

std::string LuaStack::typestring(int pos) const
{
    checkPos(pos);
    return std::string(lua_typename(luaState(), lua_type(luaState(), pos)));
}

LuaStack& LuaStack::to(const char** sink, int pos)
{
    checkPos(pos);
    *sink = lua_tostring(luaState(), pos);
    return (*this);
}

const char* LuaStack::cstring(int pos)
{
    checkPos(pos);
    return lua_tostring(luaState(), pos);
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
    *sink = lua_tostring(luaState(), pos);
    return (*this);
}

LuaStack& LuaStack::to(QString* const sink, int pos)
{
    checkPos(pos);
    *sink = lua_tostring(luaState(), pos);
    return (*this);
}

LuaUserdata* LuaStack::object(int pos)
{
    checkPos(pos);
    LuaUserdata* ptr;
    to(&ptr, pos);
    return ptr;
}

void* LuaStack::pointer(int pos)
{
    checkPos(pos);
    if (lua_islightuserdata(luaState(), pos) == 1) {
        return lua_touserdata(luaState(), pos);
    }
    return nullptr;
}

int LuaStack::length(int pos)
{
    checkPos(pos);
    int length;
    #if LUA_VERSION_NUM >= 502
        length = lua_rawlen(luaState(), pos);
    #else
        length = lua_objlen(luaState(), pos);
    #endif
    return length;
}

LuaValue LuaStack::save()
{
    checkPos(-1);
    return LuaValue(
        std::shared_ptr<LuaAccessible>(
            new LuaReferenceAccessible(lua())
        )
    );
}

LuaStack& LuaStack::to(bool* sink, int pos)
{
    checkPos(pos);
    *sink = lua_toboolean(luaState(), pos);
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
    case lua::TABLE:
    case lua::FUNCTION:
    case lua::THREAD:
    default:
        throw LuaException(&lua(), std::string("Type not supported: ") + typestring(pos));
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
    *sink = lua_tonumber(luaState(), pos);
    return (*this);
}

LuaStack& LuaStack::to(short* sink, int pos)
{
    checkPos(pos);
    *sink = lua_tointeger(luaState(), pos);
    return (*this);
}

LuaStack& LuaStack::to(int* sink, int pos)
{
    checkPos(pos);
    *sink = lua_tointeger(luaState(), pos);
    return (*this);
}

LuaStack& LuaStack::to(long* sink, int pos)
{
    checkPos(pos);
    *sink = lua_tonumber(luaState(), pos);
    return (*this);
}

LuaStack& LuaStack::to(float* sink, int pos)
{
    checkPos(pos);
    *sink = lua_tonumber(luaState(), pos);
    return (*this);
}

LuaStack& LuaStack::to(LuaUserdata** sink, int pos)
{
    checkPos(pos);

    if (lua_isuserdata(luaState(), pos) == 1 && lua_islightuserdata(luaState(), pos) == 0) {
        *sink = static_cast<LuaUserdata*>(lua_touserdata(luaState(), pos));
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
    lua_getglobal(luaState(), name);
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

LuaStack& LuaStack::get(int tablePos)
{
    checkPos(tablePos);
    lua_gettable(luaState(), tablePos);
    return (*this);
}

LuaStack& LuaStack::pushedSet(int tablePos)
{
    checkPos(tablePos);
    lua_settable(luaState(), tablePos);
    return (*this);
}

LuaStack& LuaStack::push(const char* value)
{
    lua_pushstring(luaState(), value);
    return (*this);
}

LuaStack& LuaStack::push(const char* value, int len)
{
    lua_pushlstring(luaState(), value, len);
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
    lua_pushnumber(luaState(), value);
    return (*this);
}

LuaStack& LuaStack::push(const short& value)
{
    lua_pushinteger(luaState(), value);
    return (*this);
}

LuaStack& LuaStack::push(const int& value)
{
    lua_pushinteger(luaState(), value);
    return (*this);
}

LuaStack& LuaStack::push(const long& value)
{
    lua_pushnumber(luaState(), value);
    return (*this);
}

LuaStack& LuaStack::push(const float& value)
{
    lua_pushnumber(luaState(), value);
    return (*this);
}

LuaStack& LuaStack::push(const bool& b)
{
    lua_pushboolean(luaState(), b);
    return (*this);
}

void collectUserdata(LuaStack& stack)
{
    LuaUserdata* userdata = stack.object(1);
    userdata->~LuaUserdata();
}

LuaStack& LuaStack::push(const std::shared_ptr<void>& obj, QString type)
{
    return push(LuaUserdata(obj, type));
}

LuaStack& LuaStack::push(const LuaUserdata& userdata)
{
    void* luaUserdata = lua_newuserdata(luaState(), sizeof(LuaUserdata));
    new (luaUserdata) LuaUserdata(userdata);

    pushNewTable();
    set("__gc", collectUserdata);
    setMetatable();

    return (*this);
}

LuaStack& LuaStack::pushPointer(void* const p)
{
    lua_pushlightuserdata(luaState(), p);
    return (*this);
}

LuaStack& LuaStack::push(lua_CFunction func, const int closed)
{
    lua_pushcclosure(luaState(), func, closed);
}

int collectRawCallable(lua_State* state)
{
    void* userdata = lua_touserdata(state, -1);
    lua::LuaCallable* callable = static_cast<lua::LuaCallable*>(userdata);
    callable->lua::LuaCallable::~LuaCallable();
    return 0;
}

LuaStack& LuaStack::push(void(*func)(LuaStack& stack), const int closed)
{
    if (closed > 0) {
        checkPos(-closed);
    }

    void* ptr = lua_newuserdata(luaState(), sizeof(lua::LuaCallable));
    new (ptr) lua::LuaCallable(func);

    // Ensure the LuaCallable gets destructed when necessary.
    //
    pushNewTable();
    set("__gc", collectRawCallable);
    setMetatable();

    pushPointer(&lua());

    // Invoke this twice to move both the Lua environment and the callable pointer to the top of the stack.
    lua_insert(luaState(), -2-closed);
    lua_insert(luaState(), -2-closed);

    push(invokeRawCallable, 2 + closed);
    return (*this);
}

LuaStack& LuaStack::push(const lua::LuaCallable& f, const int closed)
{
    if (closed > 0) {
        checkPos(-closed);
    }

    push(LuaUserdata(std::make_shared<lua::LuaCallable>(f), "lua::LuaCallable"));
    pushPointer(&lua());

    // Invoke this twice to move both the Lua environment and the callable pointer to the top of the stack.
    lua_insert(luaState(), -2-closed);
    lua_insert(luaState(), -2-closed);

    push(invokeLuaCallable, 2 + closed);
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
        throw LuaException(&lua(), std::string("Type not supported: ") + variant.typeName());
    }
    return (*this);
}

LuaStack& LuaStack::push(const LuaValue& value)
{
    value.push(*this);
    return *this;
}

LuaStack& LuaStack::push(const LuaAccessible& value)
{
    value.push(*this);
    return *this;
}

LuaStack& LuaStack::pushNewTable()
{
    lua_newtable(luaState());
    return (*this);
}

bool LuaStack::hasMetatable(const int pos)
{
    checkPos(pos);
    bool hasMeta = lua_getmetatable(luaState(), pos) != 0;
    if (hasMeta) {
        pop();
    }
    return hasMeta;
}

LuaStack& LuaStack::pushMetatable(const int pos)
{
    checkPos(pos);
    bool hasMeta = lua_getmetatable(luaState(), pos) != 0;
    if (!hasMeta) {
        pushNewTable();
        // Offset to ensure the position is set correctly
        setMetatable(pos > 0 ? pos : pos - 1);
    }
}

LuaStack& LuaStack::setMetatable(const int pos)
{
    checkPos(pos);
    lua_setmetatable(luaState(), pos);
}


LuaStack& LuaStack::pushNil()
{
    lua_pushnil(luaState());
    return (*this);
}

bool LuaStack::isNil(const int pos)
{
    checkPos(pos);
    return lua_isnil(luaState(), pos) == 1;
}

LuaStack::~LuaStack()
{
    if (size() > 0)
        lua_pop(luaState(), size());
}

int LuaStack::invokeCallable(lua_State* state, const lua::LuaCallable* const func)
{
    void* p = lua_touserdata(state, lua_upvalueindex(2));
    Lua* lua = static_cast<Lua*>(p);

    // Push all upvalues unto the stack.
    int upvalueIndex = 1;
    int i = 3;
    while (!lua_isnone(state, lua_upvalueindex(i))) {
        lua_pushvalue(state, lua_upvalueindex(i));
        lua_insert(state, upvalueIndex++);
        i++;
    }
    LuaStack stack(*lua);
    stack.grab();
    (*func)(stack);
    stack.disown();
    return lua_gettop(state);
}

int LuaStack::invokeRawCallable(lua_State* state)
{
    void* funcPtr = lua_touserdata(state, lua_upvalueindex(1));
    return invokeCallable(state, static_cast<lua::LuaCallable*>(funcPtr));
}

int LuaStack::invokeLuaCallable(lua_State* state)
{
    void* userdata = lua_touserdata(state, lua_upvalueindex(1));
    LuaUserdata* funcPtr = static_cast<LuaUserdata*>(userdata);
    return invokeCallable(state, static_cast<lua::LuaCallable*>(funcPtr->rawData()));
}

LuaIndex begin(LuaStack& stack)
{
    return LuaIndex(stack, 1);
}

LuaIndex end(LuaStack& stack)
{
    return LuaIndex(stack, stack.size() + 1);
}

LuaStack& operator <<(LuaStack& stack, const std::shared_ptr<lua::LuaCallable>& callable)
{
    stack.push(LuaUserdata(callable, "lua::LuaCallable"));
}

LuaStack& operator >>(LuaStack& stack, std::shared_ptr<lua::LuaCallable>& callable)
{
    callable.reset();
    LuaUserdata* userdata;
    stack >> userdata;
    if (!userdata) {
        return stack;
    }
    if (userdata->dataType() != "lua::LuaCallable") {
        return stack;
    }
    callable = std::shared_ptr<lua::LuaCallable>(
        userdata->data(),
        static_cast<lua::LuaCallable*>(userdata->rawData())
    );
    return stack;
}
