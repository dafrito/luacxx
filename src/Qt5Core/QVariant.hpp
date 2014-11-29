#ifndef luacxx_Qt5Core_QVariant_INCLUDED
#define luacxx_Qt5Core_QVariant_INCLUDED

#include "Qt5Core.hpp"
#include "../enum.hpp"

#include <QVariant>

#include <functional>
#include <unordered_map>

// https://qt-project.org/doc/qt-5/qvariant.html

namespace lua {

void set_qvariant_push_handler(const int type, const std::function<void(lua_State* const, const QVariant&)>& handler);
void set_qvariant_store_handler(const int type, const std::function<void(QVariant&, const lua::index&)>& handler);
void set_qvariant_get_handler(const lua::userdata_type& info, const std::function<QVariant(const lua::index&)>& handler);

QVariant get_qvariant(lua_State* const state, const int pos);
void push_qvariant(lua_State* const state, const QVariant& value);
void store_qvariant(QVariant& destination, lua_State* const state, const int source);

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
    static void store(QVariant& destination, lua_State* const state, const int index)
    {
        store_qvariant(destination, state, index);
    }
};

template<>
struct Get<QVariant>
{
    static QVariant get(lua_State* const state, const int pos)
    {
        return get_qvariant(state, pos);
    }
};

} // namespace lua

LUA_METATABLE_BUILT(QVariant);
LUA_METATABLE_ENUM(QVariant::Type);

extern "C" int luaopen_Qt5Core_QVariant(lua_State* const);

#endif // luacxx_Qt5Core_QVariant_INCLUDED
