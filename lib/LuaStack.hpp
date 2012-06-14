#ifndef HEADER_LUASTACK_HPP
#define HEADER_LUASTACK_HPP

#include <QObject>
#include <QVariant>
#include <string>
#include <functional>
#include <tuple>
#include <lua.hpp>
#include "types.hpp"

class Lua;
class LuaStack;
class LuaValue;
class LuaReference;

namespace
{
    template <typename RV, typename... Args>
    class LuaWrapper;

}

namespace lua
{
    typedef std::function<void (Lua& lua, LuaStack& stack)> LuaCallable;
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
 * QOBJECT SUPPORT
 *
 * QObjects can be inserted into a Lua environment, and their methods will
 * be directly accessible from Lua. QObject properties are accessible via
 * Lua table access.
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
    static int invokeWrappedFunction(lua_State* state);

    Lua& lua;
    int _offset;

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
    LuaStack& offset(int offset);

    /**
     * Forcibly take all stack values currently on the
     * stack. These values will be controlled by this
     * instance; they will be popped when this instance
     * is destroyed.
     */
    LuaStack& grab() {
        return offset(0);
    }

    /**
     * Forcibly abandon all stack values. This
     * instance will no longer be responsible for
     * the values currently on the stack.
     */
    LuaStack& disown() {
        // FIXME I think this should be offset(offset() + size());
        return offset(size());
    }
public:
    LuaStack(Lua& lua);

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

    /**
     * Swaps the values at the two specified indices.
     */
    LuaStack& swap(int a = -1, int b = -2);

    /**
     * Pops all values that have been pushed onto
     * this stack.
     */
    LuaStack& clear()
    {
        return pop(size());
    }

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
    LuaStack& to(bool* sink, int pos = -1);
    LuaStack& to(lua_Number* sink, int pos = -1);
    LuaStack& to(const char** sink, int pos = -1);
    LuaStack& to(int* sink, int pos = -1);
    LuaStack& to(long* sink, int pos = -1);
    LuaStack& to(float* sink, int pos = -1);
    LuaStack& to(short* sink, int pos = -1);
    LuaStack& to(std::string* const sink, int pos = -1);
    LuaStack& to(QString* const sink, int pos = -1);
    LuaStack& to(QObject** const sink, int pos = -1);
    LuaStack& to(QVariant* const sink, int pos = -1);

    // A template to ensure that references will always
    // be converted to pointers.
    template <typename T>
    LuaStack& to(T& sink, int pos = -1)
    {
        return to(&sink, pos);
    }

    /**
     * Convert the topmost value to the specified type.
     */
    template<typename T>
    operator T()
    {
        T t;
        this->to(&t);
        return t;
    }

    /**
     * Converts and returns the value at the specified
     * position to a C++ value.
     */
    const char* cstring(int pos = -1);
    std::string string(int pos = -1);
    QString qstring(int pos = -1);
    lua_Number number(int pos = -1);
    bool boolean(int pos = -1);
    QObject* object(int pos = -1);

    /**
     * Saves the value at the top of this stack into
     * a Lua reference.
     */
    LuaReference save();

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
    LuaStack& push(const char* value);
    LuaStack& push(const char* value, int len);
    LuaStack& push(const QChar& value);
    LuaStack& push(const QString& value);
    LuaStack& push(const std::string& value);
    LuaStack& push(const lua_Number& value);
    LuaStack& push(void* const p);
    LuaStack& push(const bool& b);
    LuaStack& push(const int& b);
    LuaStack& push(const long& b);
    LuaStack& push(const float& b);
    LuaStack& push(const short& b);
    LuaStack& push(QObject* const obj);
    LuaStack& push(const QVariant& variant);
    LuaStack& push(const LuaValue& value);

    /**
     * Pushes the directly callable C++ function onto
     * the top of this stack. If closed > 0, then that
     * number of arguments will be pulled from the stack
     * and partially applied to the specified function.
     */
    LuaStack& push(const lua::LuaCallable& f, const int closed = 0);
    LuaStack& push(void (*p)(Lua& lua, LuaStack& stack), const int closed = 0);

    /**
     * Push a nil Lua value onto this stack.
     */
    LuaStack& pushNil();

    /**
     * Returns whether the stack value at the specified
     * position is exactly nil.
     */
    bool isNil(const int pos = -1);

    /**
     * Push an empty Lua table onto this stack.
     */
    LuaStack& pushNewTable();

    /**
     * Push the specified C++ function onto this stack.
     */
    template <typename RV, typename... Args>
    LuaStack& push(RV(*p)(Args...), const int closed = 0)
    {
        this->push(LuaWrapper<RV, Args...>(p), closed);
        return (*this);
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
        push(key);

        // Stack is now [..., t, value, key], so we need to swap
        swap();

        // Adjust tablePos since we pushed a key onto the
        // stack.
        if (!isMagicalPos(tablePos) && tablePos < 0)
            --tablePos;
        pushedSet(tablePos);
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
        push(value);
        // Since we inserted a value, we may need to relocate tablePos
        // so it still points to the table.
        if (!isMagicalPos(tablePos) && tablePos < 0)
            --tablePos;
        pushedSet(key, tablePos);
        return (*this);
    }

    /**
     * Pushes a value from the specified table, using the topmost stack
     * value as the key.
     */
    LuaStack& get(int tablePos = -1);

    /**
     * Pushes the table value within the specified table onto this stack.
     *
     * The table must be at the stack position specified by tablePos.
     */
    template <typename K>
    LuaStack& get(K key, int tablePos = -1)
    {
        checkPos(tablePos);
        push(key);
        if (!isMagicalPos(tablePos) && tablePos < 0)
            --tablePos;
        return get(tablePos);
    }

    /**
     * Set the global with the specified name to the
     * specified value.
     */
    template <typename K, typename V>
    LuaStack& setGlobal(K key, const V& value)
    {
        return set(key, value, LUA_GLOBALSINDEX);
    }

    /**
     * Set the global with the specified name to the value
     * curently at the top of this stack.
     */
    template <typename K>
    LuaStack& setGlobal(K key)
    {
        return pushedSet(key, LUA_GLOBALSINDEX);
    }

    /**
     * Push the specified C++ value onto this stack.
     */
    template <typename T>
    friend LuaStack& operator<<(LuaStack& stack, const T& value)
    {
        return stack.push(value);
    }

    /**
     * Assign to the specified C++ value, the topmost
     * value on this stack.
     */
    template <typename T>
    friend LuaStack& operator>>(LuaStack& stack, T& value)
    {
        return stack.to(&value);
    }

    ~LuaStack();

    friend class Lua;
};

template <typename T>
const bool operator==(LuaStack& stack, const T& b)
{
    T a;
    stack.to(a);
    return a == b;
}

template <typename T>
const bool operator==(const T& b, LuaStack& stack)
{
    T a;
    stack.to(a);
    return a == b;
}

template <typename T>
const bool operator!=(LuaStack& stack, const T& b)
{
    return !(stack == b);
}

template <typename T>
const bool operator!=(const T& b, LuaStack& stack)
{
    return !(stack == b);
}

namespace
{

    /**
     * For each type in the specified tuple, convert a Lua argument to that
     * type, until all types have been converted to fill the tuple.
     */
    template <unsigned NUMARGS>
    struct Filler
    {
        template <typename Tuple>
        static void fill(LuaStack& stack, Tuple& tuple)
        {
            // Populate the current C++ object with the value from Lua.
            stack.to(&std::get<NUMARGS-1>(tuple));
            stack.pop();

            // Recurse for all remaining Lua arguments.
            Filler<NUMARGS-1>::fill(stack, tuple);
        }
    };


    /**
     * No arguments need to be converted, so do nothing. This ends the
     * recursive process.
     */
    template <>
    struct Filler<0>
    {
        template <typename Tuple>
        static void fill(LuaStack&, Tuple&)
        {}
    };

    /**
     * Unpack the converted Lua arguments from the tuple. This template
     * will be recursively invoked, unpacking a single argument with
     * each invocation. The unpacked arguments will be passed back to this
     * function until no arguments remain in the tuple. When this occurs,
     * the specified C++ function will be invoked.
     */
    template <typename RV, unsigned NUMARGS>
    struct Chain
    {
        template <typename Function, typename Tuple, typename... Args>
        static void apply(LuaStack& stack, const Function& f, const Tuple& tuple, Args... args)
        {
            Chain<RV, NUMARGS-1>::apply(
                stack,
                f,
                tuple,
                std::get<NUMARGS-1>(tuple),
                args...
            );
        }
    };

    /**
     * Invoke the C++ function with all arguments in args.
     */
    template <typename RV>
    struct Chain <RV, 0>
    {
        template <typename Function, typename Tuple, typename... Args>
        static void apply(LuaStack& stack, const Function& f, const Tuple&, Args... args)
        {
            stack.push(f(args...));
        }
    };

    /**
     * Invoke the C++ function with all arguments in args.
     *
     * This special case ensures we don't attempt to push a void return value.
     */
    template <>
    struct Chain <void, 0>
    {
        template <typename Function, typename Tuple, typename... Args>
        static void apply(LuaStack&, const Function& f, const Tuple&, Args... args)
        {
            f(args...);
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
         * Argument type tuple. This will be used to construct a tuple
         * that will collect converted Lua arguments. These arguments will
         * then be passed to the underlying C++ function.
         */
        typedef std::tuple<Args...> ArgsTuple;

        /**
         * The C++ function that will eventually be invoked.
         */
        std::function<RV(Args...)> func;

    public:
        LuaWrapper(RV(*func)(Args...)) : func(func)
        {}

        void operator()(Lua&, LuaStack& stack)
        {
            ArgsTuple args;

            // Fill our tuple with arguments passed from Lua
            Filler<sizeof...(Args)>::fill(stack, args);

            // Use the filled type
            Chain<RV, sizeof...(Args)>::apply(stack, func, args);
        }
    };
}

#endif
