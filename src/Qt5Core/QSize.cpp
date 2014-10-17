#include "QSize.hpp"
#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"
#include "../thread.hpp"
#include "../algorithm.hpp"
#include "QVariant.hpp"

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

void lua::QSize_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

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

    lua::set_qvariant_push_handler(QVariant::Size, [](lua_State* const state, const QVariant& source) {
        auto target = lua::push(state, lua::value::table);

        auto size = source.toSize();
        target["width"] = size.width();
        target["height"] = size.height();
    });

    lua::set_qvariant_store_handler(QVariant::Size, [](QVariant& sink, const lua::index& size) {
        if (!size.type().table()) {
            throw lua::error("Size must be a table");
        }

        if (lua::table::length(size) > 0) {
            sink.setValue(QSize(
                size[1].get<int>(),
                size[2].get<int>()
            ));
        } else {
            sink.setValue(QSize(
                size["width"].get<int>(),
                size["height"].get<int>()
            ));
        }
    });

    return 0;
}
