#include "QTranslator.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QLocale.hpp"
#include "QObject.hpp"

#include <QTranslator>

int QTranslator_load(lua_State* const state)
{
    //bool    load(const QString & filename, const QString & directory = QString(), const QString & search_delimiters = QString(), const QString & suffix = QString())

    //bool    load(const QLocale & locale, const QString & filename, const QString & prefix = QString(), const QString & directory = QString(), const QString & suffix = QString())

    //bool    load(const uchar * data, int len, const QString & directory = QString())
    return 0;
}

void lua::QTranslator_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);

    mt["isEmpty"] = &QTranslator::isEmpty;
    mt["load"] = QTranslator_load;
    mt["translate"] = &QTranslator::translate;
}

int QTranslator_new(lua_State* const state)
{
    if (lua_gettop(state) > 0) {
        lua::push(state, new QTranslator(lua::get<QObject*>(state, 1)));
    } else {
        lua::push(state, new QTranslator);
    }
    return 1;
}

int luaopen_Qt5Core_QTranslator(lua_State* const state)
{
    lua::thread env(state);

    env["QTranslator"] = lua::value::table;
    env["QTranslator"]["new"] = QTranslator_new;

    return 0;
}
