#include "LuaStack.hpp"

#include "LuaEnvironment.hpp"
#include "LuaException.hpp"
#include "LuaValue.hpp"
#include "LuaUserdata.hpp"
#include <sstream>

LuaStack::LuaStack(lua_State* const lua) :
    _lua(lua),
    _parent(0),
    _locked(false),
    _offset(lua_gettop(luaState())),
    _top(0),
    _rawUserdata(0),
    _acceptsStackUserdata(false)
{
}

LuaStack::LuaStack(LuaStack& parent) :
    _lua(parent.luaState()),
    _parent(&parent),
    _locked(false),
    _offset(parent.top()),
    _top(0),
    _rawUserdata(0),
    _acceptsStackUserdata(false)
{
    _parent->lock();
}

LuaStack::LuaStack(LuaEnvironment& lua) :
    LuaStack(lua.luaState())
{
}

lua_State* LuaStack::luaState() const
{
    return _lua;
}

void LuaStack::grab()
{
    offset(0);
}

void LuaStack::grab(const int count)
{
    offset(offset() - count);
}

void LuaStack::disown()
{
    offset(top());
}

void LuaStack::offset(const int offset)
{
    if(offset < 0) {
        throw std::out_of_range("Offset must be non-negative");
    }
    if(offset > top()) {
        throw std::out_of_range("Offset must be less than the top of lua's stack");
    }
    _offset = offset;
}

unsigned int LuaStack::size() const
{
    return top() - bottom() + 1;
}

std::string LuaStack::dump()
{
    std::stringstream str;

    str << "Stack (" << size() << " ";
    if (size() == 0) {
        str << "items";
    } else if (size() == 1) {
        str << "item [" << bottom() << "]";
    } else {
        assert(size() > 1);
        str << "items [" << bottom() << ", " << top() << "]";
    }

    str << ") [";

    for (int i=1; i <= size(); ++i) {
        str << typestring(i);
        std::string info;
        switch (type(i)) {
            case lua::type::boolean:
                info = get<bool>(i) ? "true" : "false";
                break;
            case lua::type::string:
                info = get<std::string>(i);
                break;
            case lua::type::number:
                info = lua_tostring(luaState(), i);
                break;
            default:
                // Do nothing
                break;
        }
        if (info.size()) {
            str << "(";
            if (info.size() > 30) {
                info = info.substr(0, 30);
                str << info << "...";
            } else  {
                str << info;
            }
            str << ")";
        }
        if (i != size()) {
            str << ", ";
        }
    }

    str << "]";

    return str.str();
}

int LuaStack::bottom() const
{
    return offset() + 1;
}

int LuaStack::top() const
{
    if (locked()) {
        return _top;
    }
    return lua_gettop(luaState());
}

bool LuaStack::empty() const
{
    return size() == 0;
}

int LuaStack::offset() const
{
    return _offset;
}

void LuaStack::lock()
{
    if (locked()) {
        throw std::logic_error("Refusing to lock a currently locked stack");
    }
}

bool LuaStack::locked() const
{
    return _locked;
}

void LuaStack::assertUnlocked() const
{
    if (locked()) {
        throw std::logic_error("Refusing to mutate stack while stack is locked");
    }
}

void LuaStack::unlock()
{
    _locked = false;
}

LuaIndex LuaStack::begin()
{
    return LuaIndex(*this, bottom());
}

LuaIndex LuaStack::end()
{
    return LuaIndex(*this, size() + 1);
}

LuaIndex LuaStack::rbegin()
{
    return LuaIndex(*this, top(), -1);
}

LuaIndex LuaStack::rend()
{
    return LuaIndex(*this, 0, -1);
}

LuaIndex LuaStack::at(const int pos, const int direction)
{
    checkPos(pos);
    return LuaIndex(*this, pos, direction);
}

void LuaStack::pop(unsigned int count)
{
    assertUnlocked();
    if(count > size())
        throw std::out_of_range("Refusing to pop elements not managed by this stack");
    lua_pop(luaState(), count);
}

void LuaStack::shift(unsigned int count)
{
    assertUnlocked();
    while(count-- > 0) {
        // TODO We need to check if the offset is being moved here.
        lua_remove(luaState(), 1);
    }
}

void LuaStack::checkPos(int pos) const
{
    if (isMagicalPos(pos)) {
        return;
    }
    if (pos == 0) {
        throw std::out_of_range("Stack position must not be zero");
    }
    if (empty()) {
        throw std::out_of_range("Stack position must not refer to an empty stack");
    }
    // Convert relative positions to absolute ones.
    if (pos < 0) {
        pos += top();
    }
    if (pos < offset()) {
        std::stringstream str;
        str << "Stack position must not be below this stack. Position was " << pos << " but valid indices are [" << bottom() << ", " << top() << "]";
        throw std::out_of_range(str.str());
    }
    if (pos > top()) {
        std::stringstream str;
        str << "Stack position must not be above this stack. Position was " << pos << " but valid indices are [" << bottom() << ", " << top() << "]";
        throw std::out_of_range(str.str());
    }
}

void LuaStack::replace(int pos)
{
    assertUnlocked();
    checkPos(pos);
    if (empty())
        throw std::out_of_range("Stack must not be empty when replacing elements");
    lua_replace(luaState(), pos);
}

void LuaStack::remove(int pos)
{
    assertUnlocked();
    checkPos(pos);
    lua_remove(luaState(), pos);
}

void LuaStack::insert(int pos)
{
    assertUnlocked();
    checkPos(pos);
    lua_insert(luaState(), pos);
}

void LuaStack::swap(int a, int b)
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

void LuaStack::pushCopy(int pos)
{
    assertUnlocked();
    checkPos(pos);
    lua_pushvalue(luaState(), pos);
}

void LuaStack::clear()
{
    pop(size());
}

bool LuaStack::isMagicalPos(const int& pos) const
{
    return false;
}

lua::type LuaStack::type(int pos) const
{
    checkPos(pos);
    return lua::convertType(lua_type(luaState(), pos));
}

std::string LuaStack::typestring(int pos) const
{
    checkPos(pos);
    return std::string(lua_typename(luaState(), lua_type(luaState(), pos)));
}

std::string LuaStack::traceback(const int topLevel)
{
    #if LUA_VERSION_NUM >= 502
        std::string rv;
        luaL_traceback(luaState(), luaState(), NULL, topLevel);
        rv = get<std::string>();
        pop();
        return rv;
    #else
        return lua()["debug"]["traceback"]("", topLevel).get<std::string>().substr(1);
    #endif
}

void LuaStack::to(const char*& sink, int pos)
{
    checkPos(pos);
    sink = lua_tostring(luaState(), pos);
    if (!sink) {
        sink = "";
    }
}

void LuaStack::to(std::string& sink, int pos)
{
    const char* str = get<const char*>(pos);
    sink = str;
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

int LuaStack::save(int pos)
{
    checkPos(pos);

    pushCopy(pos);
    auto ref = luaL_ref(luaState(), LUA_REGISTRYINDEX);

    return ref;
}

int LuaStack::saveAndPop()
{
    return luaL_ref(luaState(), LUA_REGISTRYINDEX);
}

void LuaStack::to(bool& sink, int pos)
{
    checkPos(pos);
    sink = lua_toboolean(luaState(), pos);
}

void LuaStack::to(lua_Number& sink, int pos)
{
    checkPos(pos);
    sink = lua_tonumber(luaState(), pos);
}

void LuaStack::to(char& sink, int pos)
{
    checkPos(pos);
    size_t len = 1;
    sink = *lua_tolstring(luaState(), pos, &len);
}

void LuaStack::to(short& sink, int pos)
{
    checkPos(pos);
    sink = lua_tointeger(luaState(), pos);
}

void LuaStack::to(int& sink, int pos)
{
    checkPos(pos);
    sink = lua_tointeger(luaState(), pos);
}

void LuaStack::to(long& sink, int pos)
{
    checkPos(pos);
    sink = lua_tonumber(luaState(), pos);
}

void LuaStack::to(unsigned int& sink, int pos)
{
    checkPos(pos);
    sink = lua_tonumber(luaState(), pos);
}

void LuaStack::to(float& sink, int pos)
{
    checkPos(pos);
    sink = lua_tonumber(luaState(), pos);
}

void LuaStack::to(LuaUserdata*& sink, int pos)
{
    checkPos(pos);

    if (lua_isuserdata(luaState(), pos) == 1 && lua_islightuserdata(luaState(), pos) == 0) {
        sink = static_cast<LuaUserdata*>(lua_touserdata(luaState(), pos));
    } else {
        sink = 0;
    }
}

LuaStack& LuaStack::global(const char* name)
{
    assertUnlocked();
    lua_getglobal(luaState(), name);
    return *this;
}

LuaStack& LuaStack::global(const std::string& name)
{
    return global(name.c_str());
}

void LuaStack::pushedGet(int tablePos)
{
    assertUnlocked();
    checkPos(tablePos);
    lua_gettable(luaState(), tablePos);
}

void LuaStack::pushedSet(int tablePos)
{
    assertUnlocked();
    checkPos(tablePos);
    lua_settable(luaState(), tablePos);
}

void LuaStack::push(const char& value)
{
    push(&value, 1);
}

void LuaStack::push(const char* value)
{
    assertUnlocked();
    lua_pushstring(luaState(), value);
}

void LuaStack::push(const char* value, int len)
{
    assertUnlocked();
    lua_pushlstring(luaState(), value, len);
}

void LuaStack::push(const std::string& value)
{
    push(value.c_str());
}

void LuaStack::push(const lua_Number& value)
{
    assertUnlocked();
    lua_pushnumber(luaState(), value);
}

void LuaStack::push(const short& value)
{
    assertUnlocked();
    lua_pushinteger(luaState(), value);
}

void LuaStack::push(const int& value)
{
    assertUnlocked();
    lua_pushinteger(luaState(), value);
}

void LuaStack::push(const unsigned int& value)
{
    assertUnlocked();
    lua_pushnumber(luaState(), value);
}

void LuaStack::push(const long& value)
{
    assertUnlocked();
    lua_pushnumber(luaState(), value);
}

void LuaStack::push(const float& value)
{
    assertUnlocked();
    lua_pushnumber(luaState(), value);
}

void LuaStack::push(const bool& b)
{
    assertUnlocked();
    lua_pushboolean(luaState(), b);
}

bool LuaStack::acceptsStackUserdata() const
{
    return _acceptsStackUserdata;
}

void LuaStack::setAcceptsStackUserdata(const bool accepts)
{
    _acceptsStackUserdata = accepts;
}

void collectUserdata(LuaStack& stack)
{
    LuaUserdata* userdata = stack.get<LuaUserdata*>(1);
    userdata->~LuaUserdata();
}

void LuaStack::push(const std::shared_ptr<void>& obj, const std::string& type)
{
    push(LuaUserdata(obj, type));
}

void LuaStack::push(void* const p, const std::string& type)
{
    push(LuaUserdata(p, type));
}

// This should stay in sync with how LuaEnvironment sets this value. It's
// a wart, admittedly, to have them separated.
bool environmentAcceptsStackUserdata(lua_State* lua)
{
    lua_pushstring(lua, "acceptsStackUserdata");
    lua_gettable(lua, LUA_REGISTRYINDEX);
    auto result = lua_toboolean(lua, -1);
    lua_pop(lua, 1);
    return result;
}

void LuaStack::push(const LuaUserdata& userdata)
{
    assertUnlocked();

    if (!userdata.managed()
            && userdata.isRaw()
            && !acceptsStackUserdata()
            && !environmentAcceptsStackUserdata(luaState())) {
        throw std::logic_error("Stack does not accept raw pointers");
    }

    void* luaUserdata = lua_newuserdata(luaState(), sizeof(LuaUserdata));
    new (luaUserdata) LuaUserdata(userdata);

    if (!userdata.managed()
            && userdata.isRaw()
            && acceptsStackUserdata()
            && !environmentAcceptsStackUserdata(luaState())) {
        _rawUserdata.push_back(static_cast<LuaUserdata*>(luaUserdata));
    }

    push(lua::value::table);
    set("__gc", collectUserdata);
    setMetatable();
}


void LuaStack::pushPointer(void* const p)
{
    assertUnlocked();
    lua_pushlightuserdata(luaState(), p);
}

void LuaStack::push(lua_CFunction func, const int closed)
{
    assertUnlocked();

    if (closed > 0) {
        checkPos(-closed);
    }

    lua_pushcclosure(luaState(), func, closed);
}

int collectRawCallable(lua_State* state)
{
    void* userdata = lua_touserdata(state, -1);
    lua::LuaCallable* callable = static_cast<lua::LuaCallable*>(userdata);
    using std::function;
    callable->~function();
    return 0;
}

void LuaStack::push(void(*func)(LuaStack& stack), const int closed)
{
    assertUnlocked();

    if (closed > 0) {
        checkPos(-closed);
    }

    void* ptr = lua_newuserdata(luaState(), sizeof(lua::LuaCallable));
    new (ptr) lua::LuaCallable(func);

    // Ensure the LuaCallable gets destructed when necessary.
    //
    push(lua::value::table);
    set("__gc", collectRawCallable);
    setMetatable();

    pushPointer(luaState());

    // Invoke this twice to move both the Lua environment and the callable pointer to the top of the stack.
    lua_insert(luaState(), -2-closed);
    lua_insert(luaState(), -2-closed);

    push(invokeRawFromLua, 2 + closed);
}

void LuaStack::push(const lua::LuaCallable& f, const int closed)
{
    assertUnlocked();

    if (closed > 0) {
        checkPos(-closed);
    }

    lua::push(*this, std::make_shared<lua::LuaCallable>(f));
    pushPointer(luaState());

    // Invoke this twice to move both the Lua environment and the callable pointer to the top of the stack.
    lua_insert(luaState(), -2-closed);
    lua_insert(luaState(), -2-closed);

    push(invokeFromLua, 2 + closed);
}

// TODO Reenable LuaAccessible pushes
/*void LuaStack::push(const LuaAccessible& value)
{
    value.push(*this);
}*/

void LuaStack::push(const lua::value& value)
{
    assertUnlocked();
    switch (value) {
        case lua::value::table:
            lua_newtable(luaState());
            break;
        case lua::value::nil:
            lua_pushnil(luaState());
            break;
    }
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

void LuaStack::pushMetatable(const int pos)
{
    assertUnlocked();
    checkPos(pos);
    bool hasMeta = lua_getmetatable(luaState(), pos) != 0;
    if (!hasMeta) {
        push(lua::value::table);
        // Offset to ensure the position is set correctly
        setMetatable(pos > 0 ? pos : pos - 1);
    }
}

void LuaStack::setMetatable(const int pos)
{
    assertUnlocked();
    checkPos(pos);
    lua_setmetatable(luaState(), pos);
}


bool LuaStack::isNil(const int pos) const
{
    checkPos(pos);
    return lua_isnil(luaState(), pos) == 1;
}

LuaStack::~LuaStack()
{
    for (auto userdata : _rawUserdata) {
        userdata->reset();
    }
    if (size() > 0)
        lua_pop(luaState(), size());
    if (_parent) {
        _parent->unlock();
    }
}

int LuaStack::invokeFromLua(lua_State* state, const lua::LuaCallable* const func)
{
    void* p = lua_touserdata(state, lua_upvalueindex(2));
    lua_State* const lua = static_cast<lua_State*>(p);

    // Push all upvalues unto the stack.
    int upvalueIndex = 1;
    int i = 3;
    while (!lua_isnone(state, lua_upvalueindex(i))) {
        lua_pushvalue(state, lua_upvalueindex(i));
        lua_insert(state, upvalueIndex++);
        i++;
    }
    LuaStack stack(lua);
    stack.grab();
    try {
        (*func)(stack);
        stack.disown();
    }
    catch (LuaException& ex) {
        if (!ex.hasTraceback()) {
            ex.setTraceback(stack.traceback(1));
        }
        stack.error(ex.what());
    }
    return lua_gettop(state);
}

int LuaStack::invokeRawFromLua(lua_State* state)
{
    void* funcPtr = lua_touserdata(state, lua_upvalueindex(1));
    return invokeFromLua(state, static_cast<lua::LuaCallable*>(funcPtr));
}

int LuaStack::invokeFromLua(lua_State* state)
{
    void* userdata = lua_touserdata(state, lua_upvalueindex(1));
    LuaUserdata* funcPtr = static_cast<LuaUserdata*>(userdata);
    return invokeFromLua(state, static_cast<lua::LuaCallable*>(funcPtr->rawData()));
}

static std::string onError(LuaStack& stack)
{
    std::string error("An error occurred within Lua");
    if (!stack.empty()) {
        error = stack.get<std::string>(-1);
    }
    if (error.find("\nstack traceback:\n") != std::string::npos) {
        // Already has a traceback, so just use it directly
        return error;
    }
    error += "\n";
    error += stack.traceback(2);
    return error;
}

void LuaStack::pushedInvoke(const int numArgs)
{
    checkPos(offset() + size() - numArgs);
    assertUnlocked();
    assert(type(-(numArgs + 1)) == lua::type::function);

    // Call Lua function. LUA_MULTRET ensures all arguments are returned
    // Subtract one from the size to ignore the function itself and pass
    // the correct number of arguments
    lua::push(*this, onError);
    auto errorHandlerIndex = offset() + size() - numArgs - 1;
    lua_insert(luaState(), errorHandlerIndex);

    int result = lua_pcall(luaState(), numArgs, LUA_MULTRET, offset() + size() - numArgs - 1);

    // Be sure to remove the error handler
    lua_remove(luaState(), errorHandlerIndex);

    switch (result) {
        case 0:
            return;
        case LUA_ERRMEM:
            throw std::runtime_error("Lua memory error");
        case LUA_ERRERR:
            throw std::runtime_error("Lua error within error handler");
        case LUA_ERRRUN:
            auto fullError = get<std::string>();
            auto sep = fullError.find("\nstack traceback:\n");
            if (sep != std::string::npos) {
                auto reason = fullError.substr(0, sep);
                auto traceback = fullError.substr(sep + 1);
                LuaException ex(reason);
                ex.setTraceback(traceback);
                throw ex;
            } else {
                throw LuaException(fullError);
            }
    }
}

namespace lua {

void push(LuaStack& stack, void (*callable)(LuaStack&), const int closed)
{
    stack.push(callable, closed);
}

void push(LuaStack& stack, const lua::LuaCallable& callable, const int closed)
{
    stack.push(callable, closed);
}

void push(LuaStack& stack, lua_CFunction callable, const int closed)
{
    stack.push(callable, closed);
}

void pushAll(LuaStack& stack)
{
    // Termination case.
}

} // namespace lua
