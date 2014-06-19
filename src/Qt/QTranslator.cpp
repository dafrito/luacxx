#include "QTranslator.hpp"
#include "../type/function.hpp"
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

void lua::QTranslator_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);

    mt["isEmpty"] = &QLocale::isEmpty;
    mt["load"] = QLocale_load;
    mt["translate"] = &QLocale::translate;
}

int QTranslator_new(lua_State* const state)
{
    lua::make<QTranslator>(state);
    return 1;
}

int luaopen_luacxx_QTranslator(lua_State* const state)
{
    lua::thread env(state);

    env["QTranslator"] = lua::value::table;
    env["QTranslator"]["new"] = QTranslator_new;

    return 0;
}
