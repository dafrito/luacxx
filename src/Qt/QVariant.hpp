#ifndef LUA_CXX_TYPE_QVARIANT_HEADER
#define LUA_CXX_TYPE_QVARIANT_HEADER

#include "../lua-cxx/stack.hpp"

#include <QVariant>

#include <functional>
#include <unordered_map>

namespace lua {

void set_qvariant_push_handler(const int type, const std::function<void(lua_State* const, const QVariant&)>& handler);
void set_qvariant_store_handler(const int type, const std::function<void(QVariant&, const lua::index&)>& handler);

void push_qvariant(lua_State* const state, const QVariant& value);
void store_qvariant(QVariant& destination, const lua::index& source);

template<>
struct Push<QVariant>
{
    static void push(lua_State* const state, QVariant value)
    {
        push_qvariant(state, value);
    }
};

template<>
struct Store<QVariant>
{
    static void store(QVariant& destination, const lua::index& index)
    {
        store_qvariant(destination, index);
    }
};

template<>
struct Get<QVariant>
{
    static QVariant get(const lua::index& index)
    {
        throw std::logic_error("Extracting QVariants is not yet allowed");
    }
};

} // namespace lua

#endif // LUA_CXX_TYPE_QVARIANT_HEADER
