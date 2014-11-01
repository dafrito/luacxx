#include "QTextFrame.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QTextObject.hpp"
#include "../Qt5Core/QObject.hpp"
#include "../Qt5Core/QList.hpp"
#include "QTextCursor.hpp"
#include "QTextDocument.hpp"
#include "QTextFrameFormat.hpp"

namespace lua {

void QTextFrame_metatable(lua_State* const state, const int pos)
{
    lua::QTextObject_metatable(state, pos);

    lua::index mt(state, pos);
    //mt["begin"] = &QTextFrame::begin;
    mt["childFrames"] = &QTextFrame::childFrames;
    //mt["end"] = &QTextFrame::end;
    mt["firstCursorPosition"] = &QTextFrame::firstCursorPosition;
    mt["firstPosition"] = &QTextFrame::firstPosition;
    mt["frameFormat"] = &QTextFrame::frameFormat;
    mt["lastCursorPosition"] = &QTextFrame::lastCursorPosition;
    mt["lastPosition"] = &QTextFrame::lastPosition;
    mt["parentFrame"] = &QTextFrame::parentFrame;
    mt["setFrameFormat"] = &QTextFrame::setFrameFormat;
}

} // namespace lua

int QTextFrame_new(lua_State* const state)
{
    lua::make<QTextFrame>(state, lua::get<QTextDocument*>(state, 1));
    return 1;
}

int luaopen_Qt5Gui_QTextFrame(lua_State* const state)
{
    lua::thread env(state);

    env["QTextFrame"] = lua::value::table;
    env["QTextFrame"]["new"] = QTextFrame_new;
    auto t = env["QTextFrame"];

    return 0;
}
