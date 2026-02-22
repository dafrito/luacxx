#include "QGraphicsProxyWidget.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QWidget.hpp"
#include "QGraphicsWidget.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "QGraphicsItem.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/Qt.hpp"

#include <QGraphicsProxyWidget>

void lua::QGraphicsProxyWidget_metatable(lua_State* const state, const int pos)
{
    lua::QGraphicsWidget_metatable(state, pos);

    lua::index mt(state, pos);
    mt["createProxyForChildWidget"] = &QGraphicsProxyWidget::createProxyForChildWidget;
    mt["setWidget"] = &QGraphicsProxyWidget::setWidget;
    mt["subWidgetRect"] = &QGraphicsProxyWidget::subWidgetRect;
    mt["widget"] = &QGraphicsProxyWidget::widget;
}

int QGraphicsProxyWidget_new(lua_State* const state)
{
    // QGraphicsProxyWidget(QGraphicsItem * parent = 0, Qt::WindowFlags wFlags = 0)
    switch (lua_gettop(state)) {
    case 0:
        lua::push(state, new QGraphicsProxyWidget);
        break;
    case 1:
        lua::push(state, new QGraphicsProxyWidget(lua::get<QGraphicsItem*>(state, 1)));
        break;
    default:
        lua::push(state, new QGraphicsProxyWidget(
            lua::get<QGraphicsItem*>(state, 1),
            lua::get<Qt::WindowFlags>(state, 2)
        ));
        break;
    }
    return 1;
}

int luaopen_Qt5Widgets_QGraphicsProxyWidget(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsProxyWidget"] = lua::value::table;
    env["QGraphicsProxyWidget"]["new"] = QGraphicsProxyWidget_new;
    auto t = env["QGraphicsProxyWidget"];

    return 0;
}
