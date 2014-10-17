#include "QLayoutItem.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QLayoutItem>

#include "../Qt5Core/Qt.hpp"
#include "QSizePolicy.hpp"
#include "../Qt5Core/QRect.hpp"
#include "QLayout.hpp"
#include "../Qt5Core/QSize.hpp"

void lua::QLayoutItem_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["alignment"] = &QLayoutItem::alignment;
    mt["controlTypes"] = &QLayoutItem::controlTypes;
    mt["hasHeightForWidth"] = &QLayoutItem::hasHeightForWidth;
    mt["heightForWidth"] = &QLayoutItem::heightForWidth;
    mt["invalidate"] = &QLayoutItem::invalidate;
    mt["layout"] = &QLayoutItem::layout;
    mt["minimumHeightForWidth"] = &QLayoutItem::minimumHeightForWidth;
    mt["setAlignment"] = &QLayoutItem::setAlignment;
    mt["spacerItem"] = &QLayoutItem::spacerItem;
    mt["widget"] = &QLayoutItem::widget;
}

int luaopen_Qt5Widgets_QLayoutItem(lua_State* const state)
{
    lua::thread env(state);

    env["QLayoutItem"] = lua::value::table;

    return 0;
}
