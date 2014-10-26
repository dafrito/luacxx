#include "QTextEdit.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QAbstractScrollArea.hpp"
#include "../Qt5Gui/QColor.hpp"
#include "../Qt5Gui/QFont.hpp"
#include "../Qt5Gui/QTextOption.hpp"
#include "../Qt5Gui/QTextDocument.hpp"
#include "../Qt5Gui/QTextCursor.hpp"
#include "../Qt5Gui/QTextCharFormat.hpp"
#include "../Qt5Gui/QPagedPaintDevice.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QList.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "../Qt5Core/QUrl.hpp"
#include "QTextCursor.hpp"
#include "QMenu.hpp"

namespace lua {

void QTextEdit_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractScrollArea_metatable(state, pos);

    lua::index mt(state, pos);
    mt["acceptRichText"] = &QTextEdit::acceptRichText;
    mt["alignment"] = &QTextEdit::alignment;
    mt["anchorAt"] = &QTextEdit::anchorAt;
    mt["autoFormatting"] = &QTextEdit::autoFormatting;
    mt["canPaste"] = &QTextEdit::canPaste;
    mt["createStandardContextMenu"] = &QTextEdit::createStandardContextMenu;
    mt["createStandardContextMenu"] = &QTextEdit::createStandardContextMenu;
    mt["currentCharFormat"] = &QTextEdit::currentCharFormat;
    mt["currentFont"] = &QTextEdit::currentFont;
    mt["cursorForPosition"] = &QTextEdit::cursorForPosition;
    mt["cursorRect"] = &QTextEdit::cursorRect;
    mt["cursorRect"] = &QTextEdit::cursorRect;
    mt["cursorWidth"] = &QTextEdit::cursorWidth;
    mt["document"] = &QTextEdit::document;
    mt["documentTitle"] = &QTextEdit::documentTitle;
    mt["ensureCursorVisible"] = &QTextEdit::ensureCursorVisible;
    mt["extraSelections"] = &QTextEdit::extraSelections;
    mt["find"] = QTextEdit_find;
    mt["fontFamily"] = &QTextEdit::fontFamily;
    mt["fontItalic"] = &QTextEdit::fontItalic;
    mt["fontPointSize"] = &QTextEdit::fontPointSize;
    mt["fontUnderline"] = &QTextEdit::fontUnderline;
    mt["fontWeight"] = &QTextEdit::fontWeight;
    mt["isReadOnly"] = &QTextEdit::isReadOnly;
    mt["isUndoRedoEnabled"] = &QTextEdit::isUndoRedoEnabled;
    mt["lineWrapColumnOrWidth"] = &QTextEdit::lineWrapColumnOrWidth;
    mt["lineWrapMode"] = &QTextEdit::lineWrapMode;
    mt["loadResource"] = &QTextEdit::loadResource;
    mt["mergeCurrentCharFormat"] = &QTextEdit::mergeCurrentCharFormat;
    mt["moveCursor"] = QTextEdit_moveCursor;
    mt["overwriteMode"] = &QTextEdit::overwriteMode;
    mt["placeholderText"] = &QTextEdit::placeholderText;
    mt["print"] = &QTextEdit::print;
    mt["setAcceptRichText"] = &QTextEdit::setAcceptRichText;
    mt["setAutoFormatting"] = &QTextEdit::setAutoFormatting;
    mt["setCurrentCharFormat"] = &QTextEdit::setCurrentCharFormat;
    mt["setCursorWidth"] = &QTextEdit::setCursorWidth;
    mt["setDocument"] = &QTextEdit::setDocument;
    mt["setDocumentTitle"] = &QTextEdit::setDocumentTitle;
    mt["setExtraSelections"] = &QTextEdit::setExtraSelections;
    mt["setLineWrapColumnOrWidth"] = &QTextEdit::setLineWrapColumnOrWidth;
    mt["setLineWrapMode"] = &QTextEdit::setLineWrapMode;
    mt["setOverwriteMode"] = &QTextEdit::setOverwriteMode;
    mt["setPlaceholderText"] = &QTextEdit::setPlaceholderText;
    mt["setReadOnly"] = &QTextEdit::setReadOnly;
    mt["setTabChangesFocus"] = &QTextEdit::setTabChangesFocus;
    mt["setTabStopWidth"] = &QTextEdit::setTabStopWidth;
    mt["setTextCursor"] = &QTextEdit::setTextCursor;
    mt["setTextInteractionFlags"] = &QTextEdit::setTextInteractionFlags;
    mt["setUndoRedoEnabled"] = &QTextEdit::setUndoRedoEnabled;
    mt["setWordWrapMode"] = &QTextEdit::setWordWrapMode;
    mt["tabChangesFocus"] = &QTextEdit::tabChangesFocus;
    mt["tabStopWidth"] = &QTextEdit::tabStopWidth;
    mt["textBackgroundColor"] = &QTextEdit::textBackgroundColor;
    mt["textColor"] = &QTextEdit::textColor;
    mt["textCursor"] = &QTextEdit::textCursor;
    mt["textInteractionFlags"] = &QTextEdit::textInteractionFlags;
    mt["toHtml"] = &QTextEdit::toHtml;
    mt["toPlainText"] = &QTextEdit::toPlainText;
    mt["wordWrapMode"] = &QTextEdit::wordWrapMode;
}

} // namespace lua

int QTextEdit_new(lua_State* const state)
{
    // QTextEdit(QWidget * parent = 0)
    // QTextEdit(const QString & text, QWidget * parent = 0)
    if (lua_gettop(state) == 1) {
        lua::make<QTextEdit>(state, lua::get<const QString&>(state, 1));
    } else {
        lua::make<QTextEdit>(state);
    }
    return 1;
}

int luaopen_Qt5Widgets_QTextEdit(lua_State* const state)
{
    lua::thread env(state);

    env["QTextEdit"] = lua::value::table;
    env["QTextEdit"]["new"] = QTextEdit_new;
    auto t = env["QTextEdit"];

    return 0;
}
