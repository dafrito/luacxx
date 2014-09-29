#include "QFrame.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QFrame>

#include "QWidget.hpp"
#include "../Qt5Core/QRect.hpp"

void lua::QFrame_metatable(const lua::index& mt)
{
    lua::QWidget_metatable(mt);

    mt["frameRect"] = &QFrame::frameRect;
    mt["frameShadow"] = &QFrame::frameShadow;
    mt["frameShape"] = &QFrame::frameShape;
    mt["frameStyle"] = &QFrame::frameStyle;
    mt["frameWidth"] = &QFrame::frameWidth;
    mt["lineWidth"] = &QFrame::lineWidth;
    mt["midLineWidth"] = &QFrame::midLineWidth;
    mt["setFrameRect"] = &QFrame::setFrameRect;
    mt["setFrameShadow"] = &QFrame::setFrameShadow;
    mt["setFrameShape"] = &QFrame::setFrameShape;
    mt["setFrameStyle"] = &QFrame::setFrameStyle;
    mt["setLineWidth"] = &QFrame::setLineWidth;
    mt["setMidLineWidth"] = &QFrame::setMidLineWidth;
}

int QFrame_new(lua_State* const state)
{
    // QFrame(QWidget * parent = 0, Qt::WindowFlags f = 0)
    lua::make<QFrame>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Widgets_QFrame(lua_State* const state)
{
    lua::thread env(state);

    env["QFrame"] = lua::value::table;
    env["QFrame"]["new"] = QFrame_new;

    return 0;
}
