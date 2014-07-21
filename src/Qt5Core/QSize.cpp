#include "QSize.hpp"
#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"
#include "../thread.hpp"

#include <QSize>

int QSize_scale(lua_State* const state)
{
    return 0;
}

int QSize_scaled(lua_State* const state)
{
    return 0;
}

std::string QSize_tostring(QSize* const size)
{
    std::stringstream str("QSize");
    str << "QSize(" << size->width() << ", " << size->height() << ")";
    return str.str();
}

void lua::QSize_metatable(const lua::index& mt)
{
    mt["boundedTo"] = &QSize::boundedTo;
    mt["expandedTo"] = &QSize::expandedTo;
    mt["height"] = &QSize::height;
    mt["isEmpty"] = &QSize::isEmpty;
    mt["isNull"] = &QSize::isNull;
    mt["isValid"] = &QSize::isValid;
    //mt["rheight"] = &QSize::rheight;
    //mt["rwidth"] = &QSize::rwidth;
    mt["scale"] = QSize_scale;
    mt["scaled"] = QSize_scaled;
    mt["setHeight"] = &QSize::setHeight;
    mt["setWidth"] = &QSize::setWidth;
    mt["transpose"] = &QSize::transpose;
    mt["transposed"] = &QSize::transposed;
    mt["width"] = &QSize::width;

    mt["__tostring"] = QSize_tostring;
}

// QSize()
// QSize(int width, int height)
int QSize_new(lua_State* const state)
{
    if (lua_gettop(state) > 1) {
        lua::make<QSize>(state, lua::get<int>(state, 2), lua::get<int>(state, 3));
    } else {
        lua::make<QSize>(state);
    }
    return 1;
}

int luaopen_Qt5Core_QSize(lua_State* const state)
{
    lua::thread env(state);

    env["QSize"] = lua::value::table;
    env["QSize"]["new"] = QSize_new;

    return 0;
}
