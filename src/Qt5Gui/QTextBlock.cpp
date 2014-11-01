#include "QTextBlock.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QTextBlockFormat.hpp"
#include "QTextDocument.hpp"
#include "QTextCharFormat.hpp"
#include "QTextLayout.hpp"
#include "QTextBlockUserData.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QVector.hpp"
#include "QTextList.hpp"

namespace lua {

void QTextBlock_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    //iterator    begin() const
    mt["blockFormat"] = &QTextBlock::blockFormat;
    mt["blockFormatIndex"] = &QTextBlock::blockFormatIndex;
    mt["blockNumber"] = &QTextBlock::blockNumber;
    mt["charFormat"] = &QTextBlock::charFormat;
    mt["charFormatIndex"] = &QTextBlock::charFormatIndex;
    mt["clearLayout"] = &QTextBlock::clearLayout;
    mt["contains"] = &QTextBlock::contains;
    mt["document"] = &QTextBlock::document;
    //iterator    end() const
    mt["firstLineNumber"] = &QTextBlock::firstLineNumber;
    mt["isValid"] = &QTextBlock::isValid;
    mt["isVisible"] = &QTextBlock::isVisible;
    mt["layout"] = &QTextBlock::layout;
    mt["length"] = &QTextBlock::length;
    mt["lineCount"] = &QTextBlock::lineCount;
    mt["next"] = &QTextBlock::next;
    mt["position"] = &QTextBlock::position;
    mt["previous"] = &QTextBlock::previous;
    mt["revision"] = &QTextBlock::revision;
    mt["setLineCount"] = &QTextBlock::setLineCount;
    mt["setRevision"] = &QTextBlock::setRevision;
    mt["setUserData"] = &QTextBlock::setUserData;
    mt["setUserState"] = &QTextBlock::setUserState;
    mt["setVisible"] = &QTextBlock::setVisible;
    mt["text"] = &QTextBlock::text;
    mt["textDirection"] = &QTextBlock::textDirection;
    //mt["textFormats"] = &QTextBlock::textFormats;
    mt["textList"] = &QTextBlock::textList;
    mt["userData"] = &QTextBlock::userData;
    mt["userState"] = &QTextBlock::userState;
}

} // namespace lua

int QTextBlock_new(lua_State* const state)
{
    if (lua_gettop(state) > 0) {
        lua::make<QTextBlock>(state, lua::get<const QTextBlock&>(state, 1));
    } else {
        lua::make<QTextBlock>(state);
    }
    return 1;
}

int luaopen_Qt5Gui_QTextBlock(lua_State* const state)
{
    lua::thread env(state);

    env["QTextBlock"] = lua::value::table;
    env["QTextBlock"]["new"] = QTextBlock_new;
    auto t = env["QTextBlock"];

    return 0;
}
