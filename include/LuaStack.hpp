#ifndef HEADER_LUASTACK_HPP
#define HEADER_LUASTACK_HPP

#include <QVariant>
#include <memory>
#include <string>
#include <functional>
#include <type_traits>
#include <lua.hpp>
#include "types.hpp"

#include "LuaIndex.hpp"

class Lua;
class LuaStack;
class LuaValue;
class LuaAccessible;
class LuaUserdata;

namespace
{
    template <typename RV, typename... Args>
    class LuaWrapper;

}

namespace lua
{
    typedef std::function<void (LuaStack& stack)> LuaCallable;

    enum value {
        table,
        nil
    };
}

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
    static int invokeLuaCallable(lua_State* state);
    static int invokeRawCallable(lua_State* state);
    static int invokeCallable(lua_State* state, const lua::LuaCallable* const func);

    Lua& _lua;

    LuaStack* _parent;
    bool _locked;

    int _offset;
    int _top;

    std::vector<LuaUserdata*> _rawUserdata;

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
    LuaStack& offset(const int offset);

    /**
     * Forcibly take all stack values currently on the
     * stack. These values will be controlled by this
     * instance; they will be popped when this instance
     * is destroyed.
     */
    LuaStack& grab();

    /**
     * Forcibly abandon all stack values. This
     * instance will no longer be responsible for
     * the values currently on the stack.
     */
    LuaStack& disown();

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
    int size() const;

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
    bool empty() const
    {
        return size() == 0;
    }

    /**
     * Returns the number of ignored stack values.
     *
     * LuaStack is only responsible for stack values
     * that it has pushed. Therefore, it must remember
     * how many stack values were present before it
     * was created. offset() will return that value.
     */
    int offset() const
    {
        return _offset;
    }

    LuaIndex begin();
    LuaIndex end();
    LuaIndex rbegin();
    LuaIndex rend();

    LuaIndex at(const int pos, const int direction = 1);

    /**
     * Pops the specified number of stack values from
     * this stack.
     */
    LuaStack& pop(int count = 1);

    /**
     * Shifts the specified number of stack values from
     * the front of this stack.
     */
    LuaStack& shift(int count = 1);

    /**
     * Replaces the stack value at the specified position
     * with the value from the top of this stack.
     *
     * The topmost element will be popped.
     */
    LuaStack& replace(int pos);

    LuaStack& remove(int pos);

    /**
     * Swaps the values at the two specified indices.
     */
    LuaStack& swap(int a = -1, int b = -2);

    LuaStack& pushCopy(int pos = -1);

    /**
     * Pops all values that have been pushed onto
     * this stack.
     */
    LuaStack& clear()
    {
        return pop(size());
    }

    std::string traceback();

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
    LuaStack& to(bool& sink, int pos = -1);
    LuaStack& to(char& sink, int pos = -1);
    LuaStack& to(short& sink, int pos = -1);
    LuaStack& to(int& sink, int pos = -1);
    LuaStack& to(long& sink, int pos = -1);
    LuaStack& to(float& sink, int pos = -1);
    LuaStack& to(lua_Number& sink, int pos = -1);
    LuaStack& to(const char*& sink, int pos = -1);
    LuaStack& to(std::string& sink, int pos = -1);
    LuaStack& to(QString& sink, int pos = -1);
    LuaStack& to(LuaUserdata*& sink, int pos = -1);

    template <class Sink>
    Sink as(int pos = -1)
    {
        Sink sink;
        at(pos) >> sink;
        return sink;
    }

    void* pointer(int pos);

    /**
     * Returns the length of the table at the specified index, or
     * 0 if the value at the index is not a table.
     */
    int length(int pos = -1);

    /**
     * Saves the value at the top of this stack into
     * a Lua reference.
     */
    LuaValue save();

    /**
     * Pushes the global value with the specified
     * name onto the top of this stack.
     */
    LuaStack& global(const char* name);
    LuaStack& global(const std::string& name);
    LuaStack& global(const QString& name);

    /**
     * Pushes the C++ value onto the top of this stack.
     */
    LuaStack& operator<<(const bool& b);
    LuaStack& operator<<(const char& b);
    LuaStack& operator<<(const short& b);
    LuaStack& operator<<(const int& b);
    LuaStack& operator<<(const long& b);
    LuaStack& operator<<(const float& b);
    LuaStack& operator<<(const lua_Number& value);
    LuaStack& operator<<(const char* value);
    LuaStack& push(const char* value, int len);
    LuaStack& operator<<(const std::string& value);

    LuaStack& push(const std::shared_ptr<void>& obj, QString type);
    LuaStack& push(void* const p, QString type);
    LuaStack& operator<<(const LuaUserdata& userdata);
    LuaStack& operator<<(void* p)=delete;

    LuaStack& operator<<(const LuaValue& value);
    LuaStack& operator<<(const LuaAccessible& value);

    LuaStack& operator<<(const lua::value& value);

    /**
     * Push an unmanaged pointer onto the stack. The pointer must outlive the
     * Lua environment, otherwise subsequent access may cause segfaults.
     *
     * Since this method has potentially dangerous consequences, it is named
     * unusually.
     */
    LuaStack& pushPointer(void* const p);

    /**
     * Pushes the directly callable C++ function onto
     * the top of this stack. If closed > 0, then that
     * number of arguments will be pulled from the stack
     * and partially applied to the specified function.
     */
    LuaStack& push(const lua::LuaCallable& f, const int closed);
    LuaStack& push(void (*p)(LuaStack& stack), const int closed);
    LuaStack& push(lua_CFunction func, const int closed);

    LuaStack& operator<<(const lua::LuaCallable& f);
    LuaStack& operator<<(void (*p)(LuaStack& stack));
    LuaStack& operator<<(lua_CFunction func);

    template <class RV>
    LuaStack& operator<<(RV (*p)(LuaStack&))
    {
        return *this << lua::LuaCallable([=](LuaStack& stack) {
            RV sink(p(stack));
            stack.clear();
            stack << sink;
        });
    }

    template <class RV>
    LuaStack& operator<<(std::function<RV(LuaStack&)> func)
    {
        return *this << lua::LuaCallable([=](LuaStack& stack) {
            RV sink(func(stack));
            stack.clear();
            stack << sink;
        });
    }

    /**
     * Returns whether the stack value at the specified
     * position is exactly nil.
     */
    bool isNil(const int pos = -1);

    template <class Message>
    void error(const Message& message)
    {
        *this << message;
        lua_error(luaState());
    }

    bool hasMetatable(const int pos = -1);
    LuaStack& pushMetatable(const int pos = -1);
    LuaStack& setMetatable(const int pos = -2);

    /**
     * Push the specified C++ function onto this stack.
     */
    template <typename RV, typename... Args>
    LuaStack& operator<<(RV(*p)(Args...))
    {
        return push(p, 0);
    }

    template <typename RV, typename... Args>
    LuaStack& push(RV(*p)(Args...), const int closed)
    {
        this->push(LuaWrapper<RV, Args...>(p), closed);
        return (*this);
    }

    template <typename RV, typename... Args>
    LuaStack& operator<<(std::function<RV(Args...)> p)
    {
        return push(p, 0);
    }

    template <typename RV, typename... Args>
    LuaStack& push(std::function<RV(Args...)> p, const int closed = 0)
    {
        this->push(LuaWrapper<RV, Args...>(p), closed);
        return (*this);
    }

    /**
     * Pushes a value from the specified table, using the topmost stack
     * value as the key.
     */
    LuaStack& pushedGet(int tablePos = -1);

    /**
     * Pushes the table value within the specified table onto this stack.
     *
     * The table must be at the stack position specified by tablePos.
     */
    template <typename K>
    LuaStack& get(K key, int tablePos = -1)
    {
        checkPos(tablePos);
        *this << key;
        if (!isMagicalPos(tablePos) && tablePos < 0)
            --tablePos;
        return pushedGet(tablePos);
    }

    /**
     * Sets the table value for the specified table.
     *
     * t[k] = v
     *
     * Where tablePos specifies the location of t,
     * k is just below the top (position -2)
     * and v is at the top (position -1)
     */
    LuaStack& pushedSet(int tablePos);

    /**
     * Sets the table value for the specified key to the value on top
     * of this stack.
     *
     * The table must be at the stack position specified by tablePos.
     */
    template <typename K>
    LuaStack& pushedSet(K key, int tablePos)
    {
        checkPos(tablePos);
        *this << key;

        // Stack is now [..., t, value, key], so we need to swap
        swap();

        // Adjust tablePos since we pushed a key onto the
        // stack.
        if (!isMagicalPos(tablePos) && tablePos < 0)
            --tablePos;
        return pushedSet(tablePos);
    }

    // We need this definition since integers can be
    // implicitly converted to booleans or numbers, which
    // is ambiguous.
    template <typename K>
    LuaStack& set(K key, int value, int tablePos = -1)
    {
        return set<K, double>(key, value, tablePos);
    }

    /**
     * Set the table value with the specified key name
     * to the specified value.
     *
     * The table must be at the stack position specified.
     */
    template <typename K, typename V>
    LuaStack& set(K key, const V& value, int tablePos = -1)
    {
        checkPos(tablePos);
        *this << value;
        // Since we inserted a value, we may need to relocate tablePos
        // so it still points to the table.
        if (!isMagicalPos(tablePos) && tablePos < 0)
            --tablePos;
        pushedSet(key, tablePos);
        return (*this);
    }

    /**
     * Set the global with the specified name to the
     * specified value.
     */
    template <typename V>
    LuaStack& setGlobal(const QString& key, const V& value)
    {
        *this << value;
        return setGlobal(key);
    }

    /**
     * Set the global with the specified name to the value
     * curently at the top of this stack.
     */
    LuaStack& setGlobal(const QString& key)
    {
        assertUnlocked();
        lua_setglobal(luaState(), key.toAscii().data());
        return (*this);
    }

    ~LuaStack();

    friend class Lua;
};

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
    index.stack().to(sink, index.pos());
    return ++index;
}

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

LuaStack& operator>>(LuaStack& stack, std::shared_ptr<lua::LuaCallable>& callable);

LuaIndex& operator>>(LuaIndex& index, LuaUserdata*& sink);
LuaIndex& operator>>(LuaIndex& index, const char*& sink);

template<class Sink>
LuaIndex& operator>>(LuaIndex& index, Sink*& sink)
{
    std::shared_ptr<Sink> ptr;
    index.stack() >> ptr;

    if (ptr) {
        sink = ptr.get();
    }
    return ++index;
}

LuaStack& operator<<(LuaStack& stack, const QChar& value);
LuaStack& operator<<(LuaStack& stack, const QString& value);
LuaStack& operator<<(LuaStack& stack, const QVariant& variant);
LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<lua::LuaCallable>& callable);

namespace
{
    struct ArgStop {};

    template <typename Callee, typename RV, typename Arg, typename... Remaining>
    struct Invocator
    {
        template <typename... Rest>
        static void apply(LuaStack& stack, const Callee& func, Rest&... rest)
        {
            // Strip any const T& down to a T
            typename std::remove_const<typename std::remove_reference<Arg>::type>::type arg;
            stack.begin() >> arg;
            stack.shift();
            Invocator<Callee, RV, Remaining...>::template apply<Rest..., Arg>(stack, func, rest..., arg);
        }
    };

    template <typename Callee, typename RV>
    struct Invocator<Callee, RV, ArgStop>
    {
        template <typename... FullArgs>
        static void apply(LuaStack& stack, const Callee& func, FullArgs&... args)
        {
            stack.clear();
            stack << func(args...);
        }
    };

    template <typename Callee>
    struct Invocator<Callee, void, ArgStop>
    {
        template <typename... FullArgs>
        static void apply(LuaStack& stack, const Callee& func, FullArgs&... args)
        {
            stack.clear();
            func(args...);
        }
    };

    /**
     * LuaWrapper enables C++ functions of arbitrary complexity to be called
     * from Lua. Conceptually, the template behaves similarly to a varargs
     * function from C. However, types are preserved using variadic templates.
     * This allows us to automatically generate correct code for each
     * argument.
     *
     * This implementation was based off of:
     * http://dvandyk.wordpress.com/2010/08/15/apply-functions-to-stdtuple/
     */
    template <typename RV, typename... Args>
    class LuaWrapper
    {
        /**
         * The C++ function that will eventually be invoked.
         */
        std::function<RV(Args...)> func;

    public:
        LuaWrapper(std::function<RV(Args...)> func) : func(func)
        {}

        void operator()(LuaStack& stack)
        {
            Invocator<decltype(func), RV, Args..., ArgStop>::template apply<>(stack, func);
        }
    };
}

#endif
