#include "QSizeF.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QSizeF>

int QSizeF_scale(lua_State* const state)
{
    return 0;
}

int QSizeF_scaled(lua_State* const state)
{
    return 0;
}

std::string QSizeF_tostring(QSizeF* const size)
{
    std::stringstream str("QSizeF");
    str << "QSizeF(" << size->width() << ", " << size->height() << ")";
    return str.str();
}

void lua::QSizeF_metatable(const lua::index& mt)
{
    mt["boundedTo"] = &QSizeF::boundedTo;
    mt["expandedTo"] = &QSizeF::expandedTo;
    mt["height"] = &QSizeF::height;
    mt["isEmpty"] = &QSizeF::isEmpty;
    mt["isNull"] = &QSizeF::isNull;
    mt["isValid"] = &QSizeF::isValid;
    //mt["rheight"] = &QSizeF::rheight;
    //mt["rwidth"] = &QSizeF::rwidth;
    mt["scale"] = QSizeF_scale;
    mt["scaled"] = QSizeF_scaled;
    mt["setHeight"] = &QSizeF::setHeight;
    mt["setWidth"] = &QSizeF::setWidth;
    mt["transpose"] = &QSizeF::transpose;
    mt["transposed"] = &QSizeF::transposed;
    mt["width"] = &QSizeF::width;
    mt["__tostring"] = QSizeF_tostring;
}

int QSizeF_new(lua_State* const state)
{
    if (lua_gettop(state) > 1) {
        lua::make<QSizeF>(state, lua::get<qreal>(state, 2), lua::get<qreal>(state, 3));
    } else {
        lua::make<QSizeF>(state);
    }
    return 1;
}

int luaopen_luacxx_QSizeF(lua_State* const state)
{
    lua::thread env(state);

    env["QSizeF"] = lua::value::table;
    env["QSizeF"]["new"] = QSizeF_new;

    return 0;
}
