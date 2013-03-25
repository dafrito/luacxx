#ifndef LUAUSERDATA_HEADER
#define LUAUSERDATA_HEADER

#include <memory>
#include <QString>

namespace lua
{
    enum Metamethod
    {
        INDEX, // Index access (table[key] operator)
        NEWINDEX, // Index assignment (table[key] = value operator)
        GC, // Finalization
        CALL, // Invocation

        LEN, // Length (the # operator)

        EQ, // Equality (the == operator)
        LT, // Less-than (the < operator)
        LE, // Less-than-or-equals (the <= operator)

        CONCAT, // Concatenation (the .. operator)

        ADD, // Addition
        SUB, // Subtraction
        MUL, // Multiplication
        DIV, // Divison
        MOD, // Modulus (the % operator)
        POW, // Pow (the ^ operator)
        UNM // Unary minus (the - operator)
    };

    Metamethod convertToMetamethodConstant(const char* luaMetamethod);
    QString convertMetamethodToString(const lua::Metamethod metamethod);
} // namespace lua

class Lua;
class LuaStack;

class LuaUserdata
{
public:

    virtual void invokeMetamethod(const lua::Metamethod metamethod, Lua& lua, LuaStack& stack);

    /**
     * Whether this userdata supports the specified metamethod. If this method returns
     * false, then the Lua metatable will not attempt to use this userdata's corresponding
     * method.
     */
    virtual bool supportsMetamethod(const lua::Metamethod metamethod);

    /**
     * For userdata that map to a native C++ object, this should return
     * a pointer to that data. For those that do not have a native mapping,
     * it should return an empty pointer.
     */
    virtual std::shared_ptr<void> rawData() const;

    /**
     * Identifies the type of raw data. Clients can use this value to ensure the
     * data provided by rawData is of an expected type.
     *
     * If this userdata does not have any raw data, then this should return an empty
     * string.
     */
    virtual QString rawDataType() const;

    virtual ~LuaUserdata()
    {
    }
};

#endif // LUAUSERDATA_HEADER
