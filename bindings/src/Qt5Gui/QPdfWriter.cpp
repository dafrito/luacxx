#include "QPdfWriter.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QObject.hpp"
#include "../Qt5Core/QMarginsF.hpp"
#include "../Qt5Core/QIODevice.hpp"
#include "QPageSize.hpp"
#include "QPageLayout.hpp"
#include "QPagedPaintDevice.hpp"

int QPdfWriter_setPageMargins(lua_State* const state)
{
    return 0;
}
int QPdfWriter_setPageSize(lua_State* const state)
{
    return 0;
}

namespace lua {

void QPdfWriter_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);
    lua::QPagedPaintDevice_metatable(state, pos);

    lua::index mt(state, pos);
     mt["creator"] = &QPdfWriter::creator;
     mt["pageLayout"] = &QPdfWriter::pageLayout;
     mt["resolution"] = &QPdfWriter::resolution;
     mt["setCreator"] = &QPdfWriter::setCreator;
     mt["setPageLayout"] = &QPdfWriter::setPageLayout;
     mt["setPageMargins"] = QPdfWriter_setPageMargins;
     mt["setPageOrientation"] = &QPdfWriter::setPageOrientation;
     mt["setPageSize"] = QPdfWriter_setPageSize;
     mt["setResolution"] = &QPdfWriter::setResolution;
     mt["setTitle"] = &QPdfWriter::setTitle;
     mt["title"] = &QPdfWriter::title;
}

} // namespace lua

int QPdfWriter_new(lua_State* const state)
{
    if (lua::is_type<QIODevice>(state, 1)) {
        // QPdfWriter(QIODevice * device)
        lua::make<QPdfWriter>(state, lua::get<QIODevice*>(state, 1));
    } else if (lua::is_type<QString>(state, 1)) {
        // QPdfWriter(const QString & filename)
        lua::make<QPdfWriter>(state, lua::get<const QString&>(state, 1));
    } else {
        lua::make<QPdfWriter>(state, lua::get<QString>(state, 1));
    }
    return 1;
}

int luaopen_Qt5Gui_QPdfWriter(lua_State* const state)
{
    lua::thread env(state);

    env["QPdfWriter"] = lua::value::table;
    env["QPdfWriter"]["new"] = QPdfWriter_new;
    auto t = env["QPdfWriter"];

    return 0;
}
