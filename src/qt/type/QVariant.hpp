#ifndef LUA_CXX_TYPE_QVARIANT_HPP
#define LUA_CXX_TYPE_QVARIANT_HPP

#include <functional>
#include <QVariant>

#include "push.hpp"
#include "store.hpp"

namespace lua {

void push_qvariant(lua::state* const state, const QVariant& value);
void store_qvariant(QVariant& destination, const lua::index& source);

template<>
struct Push<QVariant>
{
    static void push(lua::state* const state, const QVariant& value)
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
        throw lua::exception("Extracting QVariants is not yet allowed");
    }
};

} // namespace lua

#endif // LUA_CXX_TYPE_QVARIANT_HPP

