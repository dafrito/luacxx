#include "QSqlRecord.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QSqlField.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QVariant.hpp"

int QSqlRecord_field(lua_State* const state)
{
    auto self = lua::get<QSqlRecord*>(state, 1);

    // QSqlField    field(int index) const
    // QSqlField    field(const QString & name) const
    if (lua_type(state, 2) == LUA_TNUMBER) {
        lua::push(state, self->field(
            lua::get<int>(state, 2)
        ));
    } else {
        lua::push(state, self->field(
            lua::get<QString>(state, 2)
        ));
    }

    return 1;
}
int QSqlRecord_isGenerated(lua_State* const state)
{
    auto self = lua::get<QSqlRecord*>(state, 1);

    // bool     isGenerated(const QString & name) const
    // bool     isGenerated(int index) const
    if (lua_type(state, 2) == LUA_TNUMBER) {
        lua::push(state, self->isGenerated(
            lua::get<int>(state, 2)
        ));
    } else {
        lua::push(state, self->isGenerated(
            lua::get<QString>(state, 2)
        ));
    }

    return 1;
}

int QSqlRecord_isNull(lua_State* const state)
{
    auto self = lua::get<QSqlRecord*>(state, 1);

    // bool     isNull(const QString & name) const
    // bool     isNull(int index) const
    if (lua_type(state, 2) == LUA_TNUMBER) {
        lua::push(state, self->isNull(
            lua::get<int>(state, 2)
        ));
    } else {
        lua::push(state, self->isNull(
            lua::get<QString>(state, 2)
        ));
    }

    return 1;
}

int QSqlRecord_setGenerated(lua_State* const state)
{
    auto self = lua::get<QSqlRecord*>(state, 1);

    // bool     setGenerated(const QString & name) const
    // bool     setGenerated(int index) const
    if (lua_type(state, 2) == LUA_TNUMBER) {
        self->setGenerated(
            lua::get<int>(state, 2),
            lua::get<bool>(state, 3)
        );
    } else {
        self->setGenerated(
            lua::get<QString>(state, 2),
            lua::get<bool>(state, 3)
        );
    }

    return 0;
}

int QSqlRecord_setNull(lua_State* const state)
{
    auto self = lua::get<QSqlRecord*>(state, 1);

    // void     setNull(int index)
    // void     setNull(const QString & name)
    if (lua_type(state, 2) == LUA_TNUMBER) {
        self->setNull(
            lua::get<int>(state, 2)
        );
    } else {
        self->setNull(
            lua::get<QString>(state, 2)
        );
    }

    return 0;
}

int QSqlRecord_setValue(lua_State* const state)
{
    auto self = lua::get<QSqlRecord*>(state, 1);

    // void     setValue(int index, const QVariant & val)
    // void     setValue(const QString & name, const QVariant & val)
    if (lua_type(state, 2) == LUA_TNUMBER) {
        self->setValue(
            lua::get<int>(state, 2),
            lua::get<const QVariant&>(state, 3)
        );
    } else {
        self->setValue(
            lua::get<QString>(state, 2),
            lua::get<const QVariant&>(state, 3)
        );
    }

    return 0;
}

int QSqlRecord_value(lua_State* const state)
{
    auto self = lua::get<QSqlRecord*>(state, 1);

    // QVariant     value(int index) const
    // QVariant     value(const QString & name) const
    if (lua_type(state, 2) == LUA_TNUMBER) {
        lua::push(state, self->value(
            lua::get<int>(state, 2)
        ));
    } else {
        lua::push(state, self->value(
            lua::get<QString>(state, 2)
        ));
    }

    return 1;
}

namespace lua {

void QSqlRecord_metatable(lua_State* const state, const int pos)
{
    lua::QSqlIndex_metatable(state, pos);

    lua::index mt(state, pos);
    mt["append"] = &QSqlRecord::append;
    mt["clear"] = &QSqlRecord::clear;
    mt["clearValues"] = &QSqlRecord::clearValues;
    mt["contains"] = &QSqlRecord::contains;
    mt["count"] = &QSqlRecord::count;
    mt["field"] = QSqlRecord_field;
    mt["fieldName"] = &QSqlRecord::fieldName;
    mt["indexOf"] = &QSqlRecord::indexOf;
    mt["insert"] = &QSqlRecord::insert;
    mt["isEmpty"] = &QSqlRecord::isEmpty;
    mt["isGenerated"] = QSqlRecord_isGenerated;
    mt["isNull"] = QSqlRecord_isNull;
    mt["keyValues"] = &QSqlRecord::keyValues;
    mt["remove"] = &QSqlRecord::remove;
    mt["replace"] = &QSqlRecord::replace;
    mt["setGenerated"] = QSqlRecord_setGenerated;
    mt["setNull"] = QSqlRecord_setNull;
    mt["setValue"] = QSqlRecord_setValue;
    mt["value"] = QSqlRecord_value;
}

} // namespace lua

int QSqlRecord_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::make<QSqlRecord>(state);
    } else {
        lua::make<QSqlRecord>(state,
            lua::get<const QSqlRecord&>(state, 1)
        );
    }

    return 1;
}

int luaopen_Qt5Sql_QSqlRecord(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlRecord"] = lua::value::table;
    env["QSqlRecord"]["new"] = QSqlRecord_new;
    auto t = env["QSqlRecord"];

    return 0;
}
