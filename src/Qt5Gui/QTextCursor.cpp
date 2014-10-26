#include "QTextCursor.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QTextDocument.hpp"
#include "QTextDocumentFragment.hpp"
#include "QTextList.hpp"
#include "QTextListFormat.hpp"
#include "QTextTable.hpp"
#include "QTextImage.hpp"
#include "QTextImageFormat.hpp"
#include "QTextFrame.hpp"
#include "QTextFrameFormat.hpp"
#include "QTextBlock.hpp"
#include "QTextCharFormat.hpp"
#include "QTextBlockFormat.hpp"

namespace lua {

void QTextCursor_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["anchor"] = &QTextCursor::anchor;
    mt["atBlockEnd"] = &QTextCursor::atBlockEnd;
    mt["atBlockStart"] = &QTextCursor::atBlockStart;
    mt["atEnd"] = &QTextCursor::atEnd;
    mt["atStart"] = &QTextCursor::atStart;
    mt["beginEditBlock"] = &QTextCursor::beginEditBlock;
    mt["block"] = &QTextCursor::block;
    mt["blockCharFormat"] = &QTextCursor::blockCharFormat;
    mt["blockFormat"] = &QTextCursor::blockFormat;
    mt["blockNumber"] = &QTextCursor::blockNumber;
    mt["charFormat"] = &QTextCursor::charFormat;
    mt["clearSelection"] = &QTextCursor::clearSelection;
    mt["columnNumber"] = &QTextCursor::columnNumber;
    mt["createList"] = QTextCursor_createList;
    mt["currentFrame"] = &QTextCursor::currentFrame;
    mt["currentList"] = &QTextCursor::currentList;
    mt["currentTable"] = &QTextCursor::currentTable;
    mt["deleteChar"] = &QTextCursor::deleteChar;
    mt["deletePreviousChar"] = &QTextCursor::deletePreviousChar;
    mt["document"] = &QTextCursor::document;
    mt["endEditBlock"] = &QTextCursor::endEditBlock;
    mt["hasComplexSelection"] = &QTextCursor::hasComplexSelection;
    mt["hasSelection"] = &QTextCursor::hasSelection;
    mt["insertBlock"] = QTextCursor_insertBlock;
    mt["insertFragment"] = &QTextCursor::insertFragment;
    mt["insertFrame"] = &QTextCursor::insertFrame;
    mt["insertHtml"] = &QTextCursor::insertHtml;
    mt["insertImage"] = QTextCursor_insertImage;
    mt["insertList"] = QTextCursor_insertList;
    mt["insertTable"] = QTextCursor_insertTable;
    mt["insertText"] = QTextCursor_insertText;
    mt["isCopyOf"] = &QTextCursor::isCopyOf;
    mt["isNull"] = &QTextCursor::isNull;
    mt["joinPreviousEditBlock"] = &QTextCursor::joinPreviousEditBlock;
    mt["keepPositionOnInsert"] = &QTextCursor::keepPositionOnInsert;
    mt["mergeBlockCharFormat"] = &QTextCursor::mergeBlockCharFormat;
    mt["mergeBlockFormat"] = &QTextCursor::mergeBlockFormat;
    mt["mergeCharFormat"] = &QTextCursor::mergeCharFormat;
    mt["movePosition"] = QTextCursor_movePosition;
    mt["position"] = &QTextCursor::position;
    mt["positionInBlock"] = &QTextCursor::positionInBlock;
    mt["removeSelectedText"] = &QTextCursor::removeSelectedText;
    mt["select"] = &QTextCursor::select;
    mt["selectedTableCells"] = QTextCursor_selectedTableCells;
    mt["selectedText"] = &QTextCursor::selectedText;
    mt["selection"] = &QTextCursor::selection;
    mt["selectionEnd"] = &QTextCursor::selectionEnd;
    mt["selectionStart"] = &QTextCursor::selectionStart;
    mt["setBlockCharFormat"] = &QTextCursor::setBlockCharFormat;
    mt["setBlockFormat"] = &QTextCursor::setBlockFormat;
    mt["setCharFormat"] = &QTextCursor::setCharFormat;
    mt["setKeepPositionOnInsert"] = &QTextCursor::setKeepPositionOnInsert;
    mt["setPosition"] = QTextCursor_setPosition;
    mt["setVerticalMovementX"] = &QTextCursor::setVerticalMovementX;
    mt["setVisualNavigation"] = &QTextCursor::setVisualNavigation;
    mt["swap"] = &QTextCursor::swap;
    mt["verticalMovementX"] = &QTextCursor::verticalMovementX;
    mt["visualNavigation"] = &QTextCursor::visualNavigation;
}

} // namespace lua

int QTextCursor_new(lua_State* const state)
{
    // QTextCursor()
    // QTextCursor(QTextDocument * document)
    // QTextCursor(QTextFrame * frame)
    // QTextCursor(const QTextBlock & block)
    // QTextCursor(const QTextCursor & cursor)
    lua::make<QTextCursor>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Gui_QTextCursor(lua_State* const state)
{
    lua::thread env(state);

    env["QTextCursor"] = lua::value::table;
    env["QTextCursor"]["new"] = QTextCursor_new;
    auto t = env["QTextCursor"];

    // enum QTextCursor::MoveMode
    t["MoveAnchor"] = QTextCursor::MoveAnchor;
    t["KeepAnchor"] = QTextCursor::KeepAnchor;

    // enum QTextCursor::MoveOperation
    t["NoMove"] = QTextCursor::NoMove;
    t["Start"] = QTextCursor::Start;
    t["StartOfLine"] = QTextCursor::StartOfLine;
    t["StartOfBlock"] = QTextCursor::StartOfBlock;
    t["StartOfWord"] = QTextCursor::StartOfWord;
    t["PreviousBlock"] = QTextCursor::PreviousBlock;
    t["PreviousCharacter"] = QTextCursor::PreviousCharacter;
    t["PreviousWord"] = QTextCursor::PreviousWord;
    t["Up"] = QTextCursor::Up;
    t["Left"] = QTextCursor::Left;
    t["WordLeft"] = QTextCursor::WordLeft;
    t["End"] = QTextCursor::End;
    t["EndOfLine"] = QTextCursor::EndOfLine;
    t["EndOfWord"] = QTextCursor::EndOfWord;
    t["EndOfBlock"] = QTextCursor::EndOfBlock;
    t["NextBlock"] = QTextCursor::NextBlock;
    t["NextCharacter"] = QTextCursor::NextCharacter;
    t["NextWord"] = QTextCursor::NextWord;
    t["Down"] = QTextCursor::Down;
    t["Right"] = QTextCursor::Right;
    t["WordRight"] = QTextCursor::WordRight;
    t["NextCell"] = QTextCursor::NextCell;
    t["PreviousCell"] = QTextCursor::PreviousCell;
    t["NextRow"] = QTextCursor::NextRow;
    t["PreviousRow"] = QTextCursor::PreviousRow;

    // enum QTextCursor::SelectionType
    t["Document"] = QTextCursor::Document;
    t["BlockUnderCursor"] = QTextCursor::BlockUnderCursor;
    t["LineUnderCursor"] = QTextCursor::LineUnderCursor;
    t["WordUnderCursor"] = QTextCursor::WordUnderCursor;

    return 0;
}
