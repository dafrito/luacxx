#include "QSizeF.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "../algorithm.hpp"
#include "QVariant.hpp"

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
    std::stringstream str;
    str << "QSizeF(" << size->width() << ", " << size->height() << ")";
    return str.str();
}

void lua::QSizeF_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

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

int luaopen_Qt5Core_QSizeF(lua_State* const state)
{
    lua::thread env(state);

    env["QSizeF"] = lua::value::table;
    env["QSizeF"]["new"] = QSizeF_new;

    lua::set_qvariant_push_handler(QVariant::SizeF, [](lua_State* const state, const QVariant& source) {
        auto target = lua::push(state, lua::value::table);

        auto size = source.toSizeF();
        target["width"] = size.width();
        target["height"] = size.height();
    });

    lua::set_qvariant_store_handler(QVariant::SizeF, [](QVariant& sink, const lua::index& size) {
        if (!size.type().table()) {
            throw lua::error("Size must be a table");
        }

        if (lua::table::length(size) > 0) {
            sink.setValue(QSizeF(
                size[1].get<qreal>(),
                size[2].get<qreal>()
            ));
        } else {
            sink.setValue(QSizeF(
                size["width"].get<qreal>(),
                size["height"].get<qreal>()
            ));
        }
    });

    return 0;
}
