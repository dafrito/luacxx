#ifndef luacxx_Qt5Core_QVariant_INCLUDED
#define luacxx_Qt5Core_QVariant_INCLUDED

#include "Qt5Core.hpp"
#include "../enum.hpp"

#include <QVariant>

// http://doc.qt.io/qt-5/qvariant.html

LUA_METATABLE_BUILT(QVariant);
LUA_METATABLE_ENUM(QVariant::Type);

namespace lua {

void set_qvariant_push_handler(const int type, const std::function<void(lua_State* const, const QVariant&)>& handler);
void set_qvariant_store_handler(const int type, const std::function<void(QVariant&, const lua::index&)>& handler);
void set_qvariant_get_handler(const lua::userdata_type& info, const std::function<QVariant(const lua::index&)>& handler);

QVariant get_qvariant(lua_State* const state, const int pos);
void push_qvariant(lua_State* const state, const QVariant& value);
void store_qvariant(QVariant& destination, lua_State* const state, const int source);

} // namespace lua

extern "C" int luaopen_Qt5Core_QVariant(lua_State* const);

#endif // luacxx_Qt5Core_QVariant_INCLUDED
