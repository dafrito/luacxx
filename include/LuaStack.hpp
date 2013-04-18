#ifndef HEADER_LUASTACK_HPP
#define HEADER_LUASTACK_HPP

#include <QVariant>
#include <memory>
#include <string>
#include <sstream>
#include <functional>
#include <type_traits>
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

    const LuaAccessible& retrieveAccessor(const LuaAccessible& accessible);
    LuaAccessible& retrieveAccessor(LuaAccessible& accessible);
    const LuaAccessible& retrieveAccessor(const std::shared_ptr<LuaAccessible>& accessible);
} // namespace lua

/**
 * Represents a method to access a value from Lua.
 *
 * There's currently three methods to reliably access
 * some value in Lua:
 *
 * 1. Global access
 * 2. Reference table access
 * 3. Indexed access
 *
 * Referenced access (through luaL_ref) is the safest
 * way to store and retrieve a value; the other methods
 * are publicly accessible, so the underlying value may
 * be changed between accesses.
 */
class LuaAccessible
{
public:

    /**
     * Pushes the value held by this accessible on
     * the specified stack.
     */
    virtual void push(LuaStack& stack) const=0;

    /**
     * Sets this reference to the value on the top
     * of the specified stack.
     */
    virtual void store(LuaStack& stack) const=0;

    virtual ~LuaAccessible() {}
};

class LuaReferenceAccessible : public LuaAccessible
{

    class RawLuaReference
    {
        int ref;
        lua_State* const _state;

        lua_State* luaState() const
        {
            return _state;
        }

    public:
        RawLuaReference(lua_State* state) :
            _state(state)
        {
            ref = luaL_ref(luaState(), LUA_REGISTRYINDEX);
        }

        void push() const
        {
            lua_rawgeti(luaState(), LUA_REGISTRYINDEX, ref);
        }

        void store() const
        {
            lua_rawseti(luaState(), LUA_REGISTRYINDEX, ref);
        }

        ~RawLuaReference()
        {
            luaL_unref(luaState(), LUA_REGISTRYINDEX, ref);
        }
    };

    std::shared_ptr<RawLuaReference> _reference;

public:
    LuaReferenceAccessible(lua_State* state) :
        _reference(std::shared_ptr<RawLuaReference>(new RawLuaReference(state)))
    {
    }

    void push(LuaStack&) const;
    void store(LuaStack& stack) const;
};

typedef LuaValue<LuaReferenceAccessible> LuaReference;

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
    int size() const;

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
    void pop(int count = 1);

    /**
     * Shifts the specified number of stack values from
     * the front of this stack.
     */
    void shift(int count = 1);

    /**
     * Replaces the stack value at the specified position
     * with the value from the top of this stack.
     *
     * The topmost element will be popped.
     */
    void replace(int pos);

    void remove(int pos);

    /**
     * Swaps the values at the two specified indices.
     */
    void swap(int a = -1, int b = -2);

    void pushCopy(int pos = -1);

    /**
     * Pops all values that have been pushed onto
     * this stack.
     */
    void clear()
    {
        pop(size());
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
    LuaStack& operator<<(const bool& b);
    LuaStack& operator<<(const char& b);
    LuaStack& operator<<(const short& b);
    LuaStack& operator<<(const int& b);
    LuaStack& operator<<(const long& b);
    LuaStack& operator<<(const float& b);
    LuaStack& operator<<(const lua_Number& value);
    LuaStack& operator<<(const char* value);
    void push(const char* value, int len);
    LuaStack& operator<<(const std::string& value);

    void push(const std::shared_ptr<void>& obj, QString type);
    void push(void* const p, QString type);

    bool acceptsStackUserdata() const;
    void setAcceptsStackUserdata(const bool accepts);
    LuaStack& operator<<(const LuaUserdata& userdata);
    LuaStack& operator<<(void* p)=delete;

    LuaStack& operator<<(const LuaAccessible& value);

    LuaStack& operator<<(const lua::value& value);

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
    void push(const lua::LuaCallable& f, const int closed);
    void push(void (*p)(LuaStack& stack), const int closed);
    void push(lua_CFunction func, const int closed);

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
    bool isNil(const int pos = -1) const;

    template <class Message>
    void error(const Message& message)
    {
        *this << message;
        lua_error(luaState());
    }

    bool hasMetatable(const int pos = -1);
    void pushMetatable(const int pos = -1);
    void setMetatable(const int pos = -2);

    /**
     * Push the specified C++ function onto this stack.
     */
    template <typename RV, typename... Args>
    LuaStack& operator<<(RV(*p)(Args...))
    {
        push(p, 0);
        return *this;
    }

    template <typename RV, typename... Args>
    void push(RV(*p)(Args...), const int closed)
    {
        push(LuaWrapper<RV, Args...>(p), closed);
    }

    template <typename RV, typename... Args>
    LuaStack& operator<<(std::function<RV(Args...)> p)
    {
        push(p, 0);
        return *this;
    }

    template <typename RV, typename... Args>
    void push(std::function<RV(Args...)> p, const int closed = 0)
    {
        this->push(LuaWrapper<RV, Args...>(p), closed);
    }

    template <typename... Args>
    void invoke(Args&&... args)
    {
        LuaStack child(*this);
        child.grab(1);
        child.setAcceptsStackUserdata(true);
        child << onError;
        child.swap();
        callLua(luaState(), child, args...);
        child.disown();
    }

    static std::string onError(LuaStack& stack)
    {
        std::string error("Error while invoking Lua function: ");
        error += stack.traceback();
        return error;
    }

    static void callLua(lua_State* s, LuaStack& stack)
    {
        // Call Lua function. LUA_MULTRET ensures all arguments are returned
        // Subtract one from the size to ignore the function itself and pass
        // the correct number of arguments
        int result = lua_pcall(s, stack.size() - 2, LUA_MULTRET, stack.offset() + 1);
        switch (result) {
            case 0:
                return;
            case LUA_ERRRUN:
                throw LuaException(stack.as<std::string>());
            case LUA_ERRMEM:
                throw std::runtime_error("Lua memory error");
            case LUA_ERRERR:
                throw std::runtime_error("Lua error within error handler");
        }
    }

    template <typename Arg, typename... Rest>
    static void callLua(lua_State* s, LuaStack& stack, Arg&& arg, Rest&&... rest)
    {
        stack << arg;
        callLua(s, stack, rest...);
    }

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
    LuaStack& get(K key, int tablePos = -1)
    {
        checkPos(tablePos);
        *this << key;
        if (!isMagicalPos(tablePos) && tablePos < 0)
            --tablePos;
        pushedGet(tablePos);
        return *this;
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
    void pushedSet(int tablePos);

    /**
     * Sets the table value for the specified key to the value on top
     * of this stack.
     *
     * The table must be at the stack position specified by tablePos.
     */
    template <typename K>
    void pushedSet(K key, int tablePos)
    {
        checkPos(tablePos);
        *this << key;

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
    void set(K key, int value, int tablePos = -1)
    {
        set<K, double>(key, value, tablePos);
    }

    /**
     * Set the table value with the specified key name
     * to the specified value.
     *
     * The table must be at the stack position specified.
     */
    template <typename K, typename V>
    void set(K key, const V& value, int tablePos = -1)
    {
        checkPos(tablePos);
        *this << value;
        // Since we inserted a value, we may need to relocate tablePos
        // so it still points to the table.
        if (!isMagicalPos(tablePos) && tablePos < 0)
            --tablePos;
        pushedSet(key, tablePos);
    }

    /**
     * Set the global with the specified name to the
     * specified value.
     */
    template <typename V>
    void setGlobal(const std::string& key, const V& value)
    {
        *this << value;
        setGlobal(key);
    }

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

namespace lua {

    template <typename T>
    struct UserdataType
    {
        constexpr static const char* name = 0;
    };

    template <typename T>
    struct isUserdataType
    {
        typedef typename std::remove_const<
                typename remove_shared_ptr<
                typename std::remove_pointer<
                typename std::remove_reference<T
                >::type
                >::type
                >::type
                >::type type;

        constexpr static const bool value = UserdataType<isUserdataType::type>::name != 0;
    };

    // Handle primitive types
    template <typename Sink>
    typename std::enable_if<
        !std::is_reference<Sink>::value && !isUserdataType<Sink>::value,
        Sink
    >::type
    as(const LuaIndex& index)
    {
        typename std::remove_const<Sink>::type sink;
        index.stack().to(sink, index.pos());
        return sink;
    }

    template <typename Target>
    struct UserdataConverter
    {
        static const char* expectedName()
        {
            static_assert(UserdataType<Target>::name != 0, "Userdata name must be non-zero");
            return UserdataType<Target>::name;
        }

        static LuaUserdata* getUserdataObject(const LuaIndex& index)
        {
            LuaUserdata* const userdata(index.stack().as<LuaUserdata*>(index.pos()));
            if (!userdata) {
                std::stringstream msg;
                msg << "Userdata of type '" << expectedName() << "' must be provided at position "
                    << index.pos() << ", but provided Lua type was '" << index.stack().typestring(index.pos())
                    << "'";
                throw LuaException(msg.str());
             }
            if (userdata->dataType() != UserdataType<Target>::name) {
                std::stringstream msg;
                msg << "Userdata at position " << index.pos()
                    << " must be of type '" << expectedName() << "', but provided userdata type was '"
                    << userdata->dataType().toStdString() << "'";
                throw LuaException(msg.str());
            }
            return userdata;
        }

        template <typename Sink>
        static typename std::enable_if<
                std::is_pointer<Sink>::value,
                Target*>::type
        as(const LuaIndex& index)
        {
            return static_cast<Target*>(getUserdataObject(index)->rawData());
        }

        template <typename Sink>
        static typename std::enable_if<
                std::is_same<Sink, Target>::value,
                Target>::type
        as(const LuaIndex& index)
        {
            return Sink(as<Target&>(index));
        }

        template <typename Sink>
        static typename std::enable_if<
                !std::is_pointer<Sink>::value && std::is_constructible<Sink, std::shared_ptr<Target>>::value,
                std::shared_ptr<Target>
        >::type
        as(const LuaIndex& index)
        {
            LuaUserdata* userdata = getUserdataObject(index);
            return std::shared_ptr<Target>(
                userdata->data(),
                static_cast<Target*>(userdata->rawData())
            );
        }

        template <typename Sink>
        static typename std::enable_if<
            std::is_reference<Sink>::value,
            Target&>::type
        as(const LuaIndex& index)
        {
            LuaUserdata* userdata = getUserdataObject(index);
            if (!userdata->rawData()) {
                std::stringstream msg;
                msg << "Userdata of type '" << expectedName() << "' at position "
                    << index.pos() << " must have valid data";
                throw LuaException(msg.str());
            }
            return *static_cast<Target*>(userdata->rawData());
        }
    };

    // Handle userdata references, values, and pointers
    template <typename Sink>
    typename std::enable_if<
        isUserdataType<Sink>::value
            && !std::is_constructible<typename std::remove_reference<Sink>::type, std::shared_ptr<typename isUserdataType<Sink>::type>>::value,
        Sink
    >::type
    as(const LuaIndex& index)
    {
        return UserdataConverter<typename isUserdataType<Sink>::type>::template as<Sink>(index);
    }

    // Handle userdata shared_ptr's
    template <typename Sink>
    typename std::enable_if<
        isUserdataType<Sink>::value
            && std::is_constructible<typename std::remove_reference<Sink>::type, std::shared_ptr<typename isUserdataType<Sink>::type>>::value,
        std::shared_ptr<typename isUserdataType<Sink>::type>
    >::type
    as(const LuaIndex& index)
    {
        return UserdataConverter<typename isUserdataType<Sink>::type>::template as<Sink>(index);
    }

    // Handle const references by returning a value
    template <typename Sink>
    typename std::enable_if<
        std::is_reference<Sink>::value && !isUserdataType<Sink>::value && std::is_const<typename std::remove_reference<Sink>::type>::value,
        typename remove_qualifiers<Sink>::type
    >::type
    as(const LuaIndex& index)
    {
        return as<typename remove_qualifiers<Sink>::type>(index);
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
        static void apply(LuaIndex& index, const Callee& func, Rest... rest)
        {
            static_assert(
                        // Non-references are fine
                        !std::is_reference<Arg>::value ||
                        // References to references are fine
                        std::is_reference<decltype(lua::as<Arg>(index++))>::value ||
                        // References to const are fine
                        std::is_const<typename std::remove_reference<Arg>::type>::value,
                "Provided function must not use non-const lvalue references to refer to temporary objects");
            Invocator<Callee, RV, Remaining...>::template apply<Rest..., Arg>(
                index, func, rest..., lua::as<Arg>(index++)
            );
        }
    };

    template <typename Callee, typename RV>
    struct Invocator<Callee, RV, ArgStop>
    {
        template <typename... FullArgs>
        static void apply(LuaIndex& index, const Callee& func, FullArgs... args)
        {
            index.stack().clear();
            index.stack() << func(args...);
        }
    };

    template <typename Callee>
    struct Invocator<Callee, void, ArgStop>
    {
        template <typename... FullArgs>
        static void apply(LuaIndex& index, const Callee& func, FullArgs... args)
        {
            index.stack().clear();
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
            LuaIndex index(stack.begin());

            // We could ensure the stack.size() matches the Arg size exactly, but most
            // native Lua methods don't check for that condition, so for us to fit in,
            // we won't either.

            if (stack.size() < sizeof...(Args)) {
                std::stringstream msg;
                msg << "Function expects at least "
                    << sizeof...(Args)
                    << " argument" << (sizeof...(Args) == 1 ? "" : "s");
                if (stack.size() > 1) {
                    msg << " but only" << stack.size() << " were given";
                } else if (stack.size() > 0) {
                    msg << " but only" << stack.size() << " was given";
                } else {
                    msg << " but none were given";
                }
                throw LuaException(msg.str());
            }
            Invocator<decltype(func), RV, Args..., ArgStop>::template apply<>(index, func);
        }
    };
}

#endif
