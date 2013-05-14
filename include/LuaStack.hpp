#ifndef HEADER_LUASTACK_HPP
#define HEADER_LUASTACK_HPP

#include <memory>
#include <string>
#include <sstream>
#include <functional>
#include <type_traits>

#include <QString>
#include <QVariant>

#include <lua.hpp>

#include "types.hpp"
#include "LuaIndex.hpp"
#include "LuaUserdata.hpp"
#include "LuaException.hpp"

class Lua;
class LuaStack;
class LuaUserdata;

class LuaAccessible;
class LuaReferenceAccessible;

template <class Accessible>
class LuaValue;

namespace lua
{
    typedef std::function<void (LuaStack& stack)> LuaCallable;

    enum value {
        table,
        nil
    };

    const LuaAccessible& retrieveAccessor(const LuaAccessible& accessible);
    LuaAccessible& retrieveAccessor(LuaAccessible& accessible);
    const LuaAccessible& retrieveAccessor(const std::shared_ptr<LuaAccessible>& accessible);
} // namespace lua

#include "stack/accessible.cpp"
#include "stack/reference.cpp"

/**
 * Represents a stack for manipulating a Lua environment.
 *
 * If you're familiar with Lua's C API, then this class should seem
 * very famililar. It has some advantages that I'll enumerate here:
 *
 * AUTOMATIC STACK MANANGEMENT
 *
 * This class uses the RAII idiom to manage the stack. If you use this
 * class as a local variable, it will clean up after itself when it goes
 * out of scope. This makes playing with the Lua stack very easy.
 *
 * The stack management does not coordinate between classes. You must
 * only use one stack at a time, and you must ensure that these objects
 * go out of scope in the same order they were created.
 *
 * TEMPLATE-BASED PUSH/TO METHODS
 *
 * I heavily use templates to ensure this code is as flexible as possible.
 * This means that LuaStack can handle a wide variety of objects without
 * needing an excessive amount of code.
 *
 * VARIADIC FUNCTION CALLS
 *
 * Lua and C++ can call each other's functions, with arbitrary complexity.
 *
 * BUGS AND PROBLEMS
 *
 * TODO Stack management coordination is something I've put off for a while.
 * It's pretty complicated, and it's not really that necessary in practice.
 * However, I'd prefer it if we could offer some guarantees of behavior
 * in the face of clients using stacks out-of-order.
 *
 * FIXME A lot of these methods assume that stack positions are
 * always going to be negative. This is not the case. The support
 * for positive indices is extremely spotty, so I recommend using
 * negative indices until test cases are written to establish
 * reliability.
 */
class LuaStack
{
private:
    static int invokeFromLua(lua_State* state);
    static int invokeRawFromLua(lua_State* state);
    static int invokeFromLua(lua_State* state, const lua::LuaCallable* const func);

    Lua& _lua;

    LuaStack* _parent;
    bool _locked;

    int _offset;
    int _top;

    std::vector<LuaUserdata*> _rawUserdata;
    bool _acceptsStackUserdata;

    lua_State* luaState() const;

    /**
     * Assert that the specified position is within
     * bounds of this LuaStack.
     */
    void checkPos(int pos) const;

    /**
     * Returns whether the stack position is special to
     * Lua. The globals table and the references table
     * are examples of two magical stack positions.
     */
    bool isMagicalPos(const int& pos) const;

    /**
     * Forcibly change the offset value of this instance.
     * The offset determines how many values at the
     * front of the underlying stack are skipped.
     * Changing the offset will result in taking or
     * abandoning underlying stack values, so this
     * method should be used with caution.
     */
    void offset(const int offset);

    void lock();
    bool locked() const;
    void unlock();

    void assertUnlocked() const;

public:
    LuaStack(Lua& lua);
    LuaStack(LuaStack& stack);

    Lua& lua() const;

    /**
     * Return the number of stack values that are
     * controlled by this stack.
     *
     * A "controlled" value means that LuaStack is
     * responsible for it. It was pushed using this
     * instance, and it will be popped once this
     * instance is destroyed.
     */
    unsigned int size() const;

    int bottom() const;
    int top() const;

    /**
     * Return whether there are any controlled stack
     * values from this stack.
     *
     * This does not necessarily mean the underlying
     * Lua stack is empty. It only means that LuaStack
     * is not responsible for any values currently
     * present on the stack.
     */
    bool empty() const;

    /**
     * Returns the number of ignored stack values.
     *
     * LuaStack is only responsible for stack values
     * that it has pushed. Therefore, it must remember
     * how many stack values were present before it
     * was created. offset() will return that value.
     */
    int offset() const;

    /**
     * Forcibly take all stack values currently on the
     * stack. These values will be controlled by this
     * instance; they will be popped when this instance
     * is destroyed.
     */
    void grab();

    void grab(const int count);

    /**
     * Forcibly abandon all stack values. This
     * instance will no longer be responsible for
     * the values currently on the stack.
     */
    void disown();

    LuaIndex begin();
    LuaIndex end();
    LuaIndex rbegin();
    LuaIndex rend();

    LuaIndex at(const int pos, const int direction = 1);

    /**
     * Pops the specified number of stack values from
     * this stack.
     */
    void pop(unsigned int count = 1);

    /**
     * Shifts the specified number of stack values from
     * the front of this stack.
     */
    void shift(unsigned int count = 1);

    /**
     * Replaces the stack value at the specified position
     * with the value from the top of this stack.
     *
     * The topmost element will be popped.
     */
    void replace(int pos);

    void remove(int pos);

    void insert(int pos);

    /**
     * Swaps the values at the two specified indices.
     */
    void swap(int a = -1, int b = -2);

    void pushCopy(int pos = -1);

    /**
     * Pops all values that have been pushed onto
     * this stack.
     */
    void clear();

    std::string traceback(const int topLevel = 2);

    /**
     * Returns the type of the Lua stack value at the
     * specified stack position.
     */
    lua::Type type(int pos = -1) const;

    /**
     * Returns the human-readable type name of the Lua
     * value at the specified stack position.
     */
    std::string typestring(int pos = -1) const;

    /**
     * Assigns to the specified sink value, the Lua value
     * at the specified stack position.
     */
    void to(bool& sink, int pos = -1);
    void to(char& sink, int pos = -1);
    void to(short& sink, int pos = -1);
    void to(int& sink, int pos = -1);
    void to(long& sink, int pos = -1);
    void to(float& sink, int pos = -1);
    void to(lua_Number& sink, int pos = -1);
    void to(const char*& sink, int pos = -1);
    void to(std::string& sink, int pos = -1);
    void to(QString& sink, int pos = -1);
    void to(LuaUserdata*& sink, int pos = -1);

    template <class Sink>
    Sink as(int pos = -1);

    void* pointer(int pos);

    /**
     * Returns the length of the table at the specified index, or
     * 0 if the value at the index is not a table.
     */
    int length(int pos = -1);

    /**
     * Saves the value at the specified position as a reference.
     */
    LuaReference save(int pos = -1);

    /**
     * Saves and removes the value at the specified position.
     */
    LuaReference saveAndPop();

    /**
     * Pushes the global value with the specified
     * name onto the top of this stack.
     */
    LuaStack& global(const char* name);
    LuaStack& global(const std::string& name);

    /**
     * Pushes the C++ value onto the top of this stack.
     */
    void push(const bool& b);
    void push(const char& b);
    void push(const short& b);
    void push(const int& b);
    void push(const long& b);
    void push(const float& b);
    void push(const lua_Number& value);
    void push(const char* value);
    void push(const char* value, int len);
    void push(const std::string& value);

    void push(const std::shared_ptr<void>& obj, const std::string& type);
    void push(void* const p, const std::string& type);

    bool acceptsStackUserdata() const;
    void setAcceptsStackUserdata(const bool accepts);
    void push(const LuaUserdata& userdata);
    void push(void* p)=delete;

    void push(const LuaAccessible& value);

    void push(const lua::value& value);

    /**
     * Push an unmanaged pointer onto the stack. The pointer must outlive the
     * Lua environment, otherwise subsequent access may cause segfaults.
     *
     * Since this method has potentially dangerous consequences, it is named
     * unusually.
     */
    void pushPointer(void* const p);

    /**
     * Pushes the directly callable C++ function onto
     * the top of this stack. If closed > 0, then that
     * number of arguments will be pulled from the stack
     * and partially applied to the specified function.
     */
    void push(const lua::LuaCallable& f, const int closed = 0);
    void push(void (*p)(LuaStack& stack), const int closed = 0);
    void push(lua_CFunction func, const int closed = 0);

    /**
     * Returns whether the stack value at the specified
     * position is exactly nil.
     */
    bool isNil(const int pos = -1) const;

    template <class Message>
    void error(const Message& message);

    bool hasMetatable(const int pos = -1);
    void pushMetatable(const int pos = -1);
    void setMetatable(const int pos = -2);

    template <typename... Args>
    void invoke(Args&&... args);

    void pushedInvoke(const int numArgs);

    template <typename Arg, typename... Rest>
    void pushedInvoke(const int numArgs, Arg&& arg, Rest&&... rest);

    /**
     * Pushes a value from the specified table, using the topmost stack
     * value as the key.
     */
    void pushedGet(int tablePos = -1);

    /**
     * Pushes the table value within the specified table onto this stack.
     *
     * The table must be at the stack position specified by tablePos.
     */
    template <typename K>
    LuaStack& get(K key, int tablePos = -1);

    /**
     * Sets the table value for the specified table.
     *
     * t[k] = v
     *
     * Where tablePos specifies the location of t,
     * k is just below the top (position -2)
     * and v is at the top (position -1)
     */
    void pushedSet(int tablePos);

    /**
     * Sets the table value for the specified key to the value on top
     * of this stack.
     *
     * The table must be at the stack position specified by tablePos.
     */
    template <typename K>
    void pushedSet(K key, int tablePos);

    /**
     * Set the table value with the specified key name
     * to the specified value.
     *
     * The table must be at the stack position specified.
     */
    template <typename K, typename V>
    void set(K key, const V& value, int tablePos = -1);

    /**
     * Set the global with the specified name to the
     * specified value.
     */
    template <typename V>
    void setGlobal(const std::string& key, const V& value);

    /**
     * Set the global with the specified name to the value
     * curently at the top of this stack.
     */
    void setGlobal(const std::string& key)
    {
        assertUnlocked();
        lua_setglobal(luaState(), key.c_str());
    }

    ~LuaStack();
};

namespace {
    template <typename T>
    struct remove_qualifiers
    {
        typedef typename std::remove_const<typename std::remove_reference<T>::type>::type type;
    };

    template <typename T>
    struct remove_shared_ptr
    {
        typedef T type;
    };

    template <typename T>
    struct remove_shared_ptr<std::shared_ptr<T>>
    {
        typedef T type;
    };
}

#include "stack/userdata.cpp"

namespace lua {

template <class Source>
struct Pusher
{
    static void push(LuaStack& stack, const Source& value)
    {
        stack.push(value);
    }
};

template <typename Source,
    typename std::enable_if<
        !isUserdataType<Source>::value, int
    >::type = 0>
void push(LuaStack& stack, Source& value)
{
    Pusher<typename std::remove_reference<Source>::type>::push(stack, value);
}

template <typename Source,
    typename std::enable_if<
        !isUserdataType<Source>::value, int
    >::type = 0>
void push(LuaStack& stack, const Source& value)
{
    Pusher<typename std::remove_reference<Source>::type>::push(stack, value);
}

// Handle userdata pointers and shared_ptr's
template <typename Source,
    typename std::enable_if<
        isUserdataType<Source>::value
        && (
            std::is_constructible<
                typename std::remove_reference<Source>::type,
                std::shared_ptr<typename isUserdataType<Source>::type>>
            ::value || std::is_pointer<Source>::value
        ),
    int>::type = 0>
void push(LuaStack& stack, const Source& value, const bool manuallyManaged = false)
{
    if (!value) {
        lua::push(stack, lua::value::nil);
        return;
    }
    lua::push(stack, LuaUserdata(
        value,
        UserdataType<typename isUserdataType<Source>::type>::name,
        manuallyManaged
    ));

    UserdataType<typename isUserdataType<Source>::type>::initialize(stack, *value);
}

// Handle userdata references
template <typename Source,
    typename std::enable_if<
        isUserdataType<Source>::value
        && !(
            std::is_constructible<
                typename std::remove_reference<Source>::type,
                std::shared_ptr<typename isUserdataType<Source>::type>>
            ::value || std::is_pointer<Source>::value
        ),
    int>::type = 0>
void push(LuaStack& stack, Source& value, const bool manuallyManaged = false)
{
    lua::push(stack, LuaUserdata(
        &value,
        UserdataType<typename isUserdataType<Source>::type>::name,
        manuallyManaged
    ));

    UserdataType<typename isUserdataType<Source>::type>::initialize(stack, value);
}

void push(LuaStack& stack, void (*func)(LuaStack&), const int closed = 0);
void push(LuaStack& stack, const LuaCallable& callable, const int closed = 0);
void push(LuaStack& stack, lua_CFunction callable, const int closed = 0);

// Raw LuaCallables that return useful values
template <class RV,
    typename std::enable_if<!std::is_same<RV, void>::value, int>::type = 0>
void push(LuaStack& stack, RV (*p)(LuaStack&), const int closed = 0)
{
    lua::push(stack, lua::LuaCallable([=](LuaStack& stack) {
        RV sink(p(stack));
        stack.clear();
        lua::push(stack, sink);
    }), closed);
}

// C++ LuaCallables that return useful values
template <class RV,
    typename std::enable_if<!std::is_same<RV, void>::value, int>::type = 0>
void push(LuaStack& stack, std::function<RV(LuaStack&)> func, const int closed = 0)
{
    lua::push(stack, lua::LuaCallable([=](LuaStack& stack) {
        RV sink(func(stack));
        stack.clear();
        lua::push(stack, sink);
    }), closed);
}

} // namespace lua

namespace lua {

template <typename RV, typename... Args>
void push(LuaStack& stack, RV(*p)(Args...), const int closed = 0);

template <typename RV, typename... Args>
void push(LuaStack& stack, std::function<RV(Args...)> p, const int closed = 0);

} // namespace lua

#include "stack/invocation.cpp"

namespace lua {

template <typename RV, typename... Args>
void push(LuaStack& stack, RV(*p)(Args...), const int closed)
{
    lua::push(stack, lua::LuaCallable(LuaWrapper<RV, Args...>(p)), closed);
}

template <typename RV, typename... Args>
void push(LuaStack& stack, std::function<RV(Args...)> p, const int closed)
{
    lua::push(stack, lua::LuaCallable(LuaWrapper<RV, Args...>(p)), closed);
}

void pushAll(LuaStack& stack);

template <typename Arg, typename... Values>
void pushAll(LuaStack& stack, Arg&& arg, Values&&... values)
{
    lua::push(stack, arg);
    pushAll(stack, values...);
}

} // namespace lua

template <class Sink>
Sink LuaStack::as(int pos)
{
    return lua::as<Sink>(LuaIndex(*this, pos));
}

/**
 * Assign the topmost value on the specified stack to the
 * specified C++ value.
 */
template <typename Sink>
LuaStack& operator>>(LuaStack& stack, Sink& sink)
{
    stack.rbegin() >> sink;
    return stack;
}

template <class Sink>
LuaIndex& operator>>(LuaIndex& index, Sink& sink)
{
    sink = lua::as<Sink>(index);
    return ++index;
}

// This is necessary for idioms like "stack.rbegin() >> sink" where the
// index itself is never an lvalue.
template <class Sink>
LuaIndex operator>>(const LuaIndex&& index, Sink& sink)
{
    LuaIndex realIndex(index);
    realIndex >> sink;
    return realIndex;
}

LuaIndex& operator>>(LuaIndex& index, std::string& sink);
LuaIndex& operator>>(LuaIndex& index, QString& sink);
LuaIndex& operator>>(LuaIndex& index, QVariant& sink);

LuaIndex& operator>>(LuaIndex& index, LuaUserdata*& sink);
LuaIndex& operator>>(LuaIndex& index, const char*& sink);

template <typename... Args>
void LuaStack::invoke(Args&&... args)
{
    LuaStack child(*this);
    child.grab(1);
    child.setAcceptsStackUserdata(true);
    lua::pushAll(child, args...);
    child.pushedInvoke(sizeof...(args));
    child.disown();
}

template <typename K, typename V>
void LuaStack::set(K key, const V& value, int tablePos)
{
    checkPos(tablePos);
    lua::push(*this, value);
    // Since we inserted a value, we may need to relocate tablePos
    // so it still points to the table.
    if (!isMagicalPos(tablePos) && tablePos < 0)
        --tablePos;
    pushedSet(key, tablePos);
}

template <typename V>
void LuaStack::setGlobal(const std::string& key, const V& value)
{
    lua::push(*this, value);
    setGlobal(key);
}

template <class Message>
void LuaStack::error(const Message& message)
{
    clear();
    lua::push(*this, message);
    disown();
    lua_error(luaState());
}

template <typename K>
LuaStack& LuaStack::get(K key, int tablePos)
{
    checkPos(tablePos);
    lua::push(*this, key);
    if (!isMagicalPos(tablePos) && tablePos < 0)
        --tablePos;
    pushedGet(tablePos);
    return *this;
}

template <typename K>
void LuaStack::pushedSet(K key, int tablePos)
{
    checkPos(tablePos);
    lua::push(*this, key);

    // Stack is now [..., t, value, key], so we need to swap
    swap();

    // Adjust tablePos since we pushed a key onto the
    // stack.
    if (!isMagicalPos(tablePos) && tablePos < 0)
        --tablePos;
    pushedSet(tablePos);
}

#endif
