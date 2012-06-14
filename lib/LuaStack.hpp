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


class LuaStack
{
private:
    static int invokeWrappedFunction(lua_State* state);

    Lua& lua;
    int _offset;

    void checkPos(int pos) const;
    bool isMagicalPos(const int& pos) const;

    LuaStack& offset(int offset);
    LuaStack& grab() {
        return offset(0);
    }
    LuaStack& disown() {
        return offset(size());
    }
public:
    LuaStack(Lua& lua);

    int size() const;
    bool empty() const
    {
        return size() == 0;
    }

    int offset() const
    {
        return _offset;
    }

    LuaStack& pop(int count = 1);
    LuaStack& shift(int count = 1);
    LuaStack& replace(int pos);
    LuaStack& clear()
    {
        return pop(size());
    }

    lua::Type type(int pos = -1) const;

    std::string typestring(int pos = -1) const;

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

    template <typename T>
    LuaStack& to(T& sink, int pos = -1)
    {
        return to(&sink, pos);
    }

    const char* cstring(int pos = -1);
    std::string string(int pos = -1);
    QString qstring(int pos = -1);
    lua_Number number(int pos = -1);
    bool boolean(int pos = -1);
    QObject* object(int pos = -1);
    LuaReference save();
    LuaStack& global(const char* name);
    LuaStack& global(const std::string& name);
    LuaStack& global(const QString& name);

    LuaStack& set(const char* key, int tablePos);
    LuaStack& set(const std::string& key, int tablePos);
    LuaStack& set(const QString& key, int tablePos);

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
    LuaStack& push(const lua::LuaCallable& f, const int closed = 0);
    LuaStack& push(void (*p)(Lua& lua, LuaStack& stack), const int closed = 0);
    LuaStack& push(QObject* const obj);
    LuaStack& push(const QVariant& variant);
    LuaStack& push(const LuaValue& value);

    LuaStack& pushNil();
    bool isNil(const int pos = -1);

    LuaStack& pushNewTable();

    template <typename RV, typename... Args>
    LuaStack& push(RV(*p)(Args...), const int closed = 0)
    {
        this->push(LuaWrapper<RV, Args...>(p), closed);
        return (*this);
    }

    // We need this definition since integers can be
    // implicitly converted to booleans or numbers, which
    // is ambiguous.
    template <typename K>
    LuaStack& set(K key, int value, int tablePos)
    {
        return set<K, double>(key, value, tablePos);
    }

    template <typename K, typename V>
    LuaStack& set(K key, const V& value, int tablePos)
    {
        checkPos(tablePos);
        push(value);
        if (!isMagicalPos(tablePos))
            --tablePos;
        set(key, tablePos);
        return (*this);
    }

    template <typename K, typename V>
    LuaStack& setGlobal(K key, const V& value)
    {
        return set(key, value, LUA_GLOBALSINDEX);
    }

    template <typename K>
    LuaStack& setGlobal(K key)
    {
        return set(key, LUA_GLOBALSINDEX);
    }

    ~LuaStack();

    template <typename T>
    friend LuaStack& operator<<(LuaStack& stack, const T& value)
    {
        return stack.push(value);
    }

    template <typename T>
    friend LuaStack& operator>>(LuaStack& stack, T& value)
    {
        return stack.to(&value);
    }

    friend class Lua;
};

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
