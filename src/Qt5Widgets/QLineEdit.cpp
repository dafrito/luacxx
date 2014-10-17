#include "QLineEdit.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QLineEdit>

#include "QAction.hpp"
#include "QMenu.hpp"
#include "QCompleter.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QMargins.hpp"
#include "../Qt5Gui/QIcon.hpp"
#include "QValidator.hpp"

int QLineEdit_addAction(lua_State* const state)
{
    return 0;
}

int QLineEdit_cursorBackward(lua_State* const state)
{
    return 0;
}
int QLineEdit_cursorForward(lua_State* const state)
{
    return 0;
}
int QLineEdit_getTextMargins(lua_State* const state)
{
    return 0;
}
int QLineEdit_setTextMargins(lua_State* const state)
{
    return 0;
}

void lua::QLineEdit_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["addAction"] = QLineEdit_addAction;
    mt["alignment"] = &QLineEdit::alignment;
    mt["backspace"] = &QLineEdit::backspace;
    mt["completer"] = &QLineEdit::completer;
    mt["createStandardContextMenu"] = &QLineEdit::createStandardContextMenu;
    mt["cursorBackward"] = QLineEdit_cursorBackward;
    mt["cursorForward"] = QLineEdit_cursorForward;
    mt["cursorMoveStyle"] = &QLineEdit::cursorMoveStyle;
    mt["cursorPosition"] = &QLineEdit::cursorPosition;
    mt["cursorPositionAt"] = &QLineEdit::cursorPositionAt;
    mt["cursorWordBackward"] = &QLineEdit::cursorWordBackward;
    mt["cursorWordForward"] = &QLineEdit::cursorWordForward;
    mt["del"] = &QLineEdit::del;
    mt["deselect"] = &QLineEdit::deselect;
    mt["displayText"] = &QLineEdit::displayText;
    mt["dragEnabled"] = &QLineEdit::dragEnabled;
    mt["echoMode"] = &QLineEdit::echoMode;
    mt["end"] = &QLineEdit::end;
    mt["getTextMargins"] = QLineEdit_getTextMargins;
    mt["hasAcceptableInput"] = &QLineEdit::hasAcceptableInput;
    mt["hasFrame"] = &QLineEdit::hasFrame;
    mt["hasSelectedText"] = &QLineEdit::hasSelectedText;
    mt["home"] = &QLineEdit::home;
    mt["inputMask"] = &QLineEdit::inputMask;
    mt["insert"] = &QLineEdit::insert;
    mt["isClearButtonEnabled"] = &QLineEdit::isClearButtonEnabled;
    mt["isModified"] = &QLineEdit::isModified;
    mt["isReadOnly"] = &QLineEdit::isReadOnly;
    mt["isRedoAvailable"] = &QLineEdit::isRedoAvailable;
    mt["isUndoAvailable"] = &QLineEdit::isUndoAvailable;
    mt["maxLength"] = &QLineEdit::maxLength;
    mt["placeholderText"] = &QLineEdit::placeholderText;
    mt["selectedText"] = &QLineEdit::selectedText;
    mt["selectionStart"] = &QLineEdit::selectionStart;
    mt["setAlignment"] = &QLineEdit::setAlignment;
    mt["setClearButtonEnabled"] = &QLineEdit::setClearButtonEnabled;
    mt["setCompleter"] = &QLineEdit::setCompleter;
    mt["setCursorMoveStyle"] = &QLineEdit::setCursorMoveStyle;
    mt["setCursorPosition"] = &QLineEdit::setCursorPosition;
    mt["setDragEnabled"] = &QLineEdit::setDragEnabled;
    mt["setEchoMode"] = &QLineEdit::setEchoMode;
    mt["setFrame"] = &QLineEdit::setFrame;
    mt["setInputMask"] = &QLineEdit::setInputMask;
    mt["setMaxLength"] = &QLineEdit::setMaxLength;
    mt["setModified"] = &QLineEdit::setModified;
    mt["setPlaceholderText"] = &QLineEdit::setPlaceholderText;
    mt["setReadOnly"] = &QLineEdit::setReadOnly;
    mt["setSelection"] = &QLineEdit::setSelection;
    mt["setTextMargins"] = QLineEdit_setTextMargins;
    mt["setValidator"] = &QLineEdit::setValidator;
    mt["text"] = &QLineEdit::text;
    mt["textMargins"] = &QLineEdit::textMargins;
    mt["validator"] = &QLineEdit::validator;
}

int QLineEdit_new(lua_State* const state)
{
    // QLineEdit(QWidget * parent = 0)
    // QLineEdit(const QString & contents, QWidget * parent = 0)
    lua::make<QLineEdit>(state);

    return 1;
}

int luaopen_Qt5Widgets_QLineEdit(lua_State* const state)
{
    lua::thread env(state);

    env["QLineEdit"] = lua::value::table;
    env["QLineEdit"]["new"] = QLineEdit_new;

    return 0;
}
