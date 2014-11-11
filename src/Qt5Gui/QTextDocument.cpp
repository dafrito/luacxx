#include "QTextDocument.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "../Qt5Core/QUrl.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "../Qt5Core/QVector.hpp"
#include "QTextFormat.hpp"
#include "QTextBlock.hpp"
#include "../Qt5Core/QChar.hpp"
#include "QFont.hpp"
#include "QTextCursor.hpp"
#include "QTextObject.hpp"
#include "QTextOption.hpp"
#include "QPainter.hpp"
#include "QAbstractTextDocumentLayout.hpp"
#include "../Qt5Core/QSizeF.hpp"
#include "QTextFrame.hpp"
#include "QPagedPaintDevice.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/QObject.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QByteArray.hpp"
#include "../Qt5Core/QRegExp.hpp"

#include <QTextDocument>

int QTextDocument_toHtml(lua_State* const state)
{
    auto self = lua::get<QTextDocument*>(state, 1);

    if (lua_gettop(state) == 1) {
        // QString toHtml() const
        lua::push(state, self->toHtml());
    } else {
        // QString toHtml(const QByteArray & encoding) const
        lua::push(state, self->toHtml(lua::get<const QByteArray&>(state, 2)));
    }

    return 1;
}

int QTextDocument_find(lua_State* const state)
{
    auto self = lua::get<QTextDocument*>(state, 1);

    if (lua::is_type<QRegExp>(state, 2)) {
        if (lua::is_type<QTextCursor>(state, 3)) {
            // QTextCursor     find(const QRegExp & expr, const QTextCursor & cursor, FindFlags options = 0) const
            switch (lua_gettop(state)) {
            case 3:
                lua::push(state, self->find(
                    lua::get<const QRegExp&>(state, 2),
                    lua::get<const QTextCursor&>(state, 3)
                ));
                break;
            case 4:
            default:
                lua::push(state, self->find(
                    lua::get<const QRegExp&>(state, 2),
                    lua::get<const QTextCursor&>(state, 3),
                    lua::get<QTextDocument::FindFlags>(state, 4)
                ));
                break;
            }
        } else {
            // QTextCursor     find(const QRegExp & expr, int position = 0, FindFlags options = 0) const
            switch (lua_gettop(state)) {
            case 2:
                lua::push(state, self->find(
                    lua::get<const QRegExp&>(state, 2)
                ));
                break;
            case 3:
                lua::push(state, self->find(
                    lua::get<const QRegExp&>(state, 2),
                    lua::get<int>(state, 3)
                ));
                break;
            case 4:
            default:
                lua::push(state, self->find(
                    lua::get<const QRegExp&>(state, 2),
                    lua::get<int>(state, 3),
                    lua::get<QTextDocument::FindFlags>(state, 4)
                ));
                break;
            }
        }
    } else {
        if (lua::is_type<QTextCursor>(state, 3)) {
            // QTextCursor     find(const QString & subString, const QTextCursor & cursor, FindFlags options = 0) const
            switch (lua_gettop(state)) {
            case 3:
                lua::push(state, self->find(
                    lua::get<QString>(state, 2),
                    lua::get<const QTextCursor&>(state, 3)
                ));
                break;
            case 4:
            default:
                lua::push(state, self->find(
                    lua::get<QString>(state, 2),
                    lua::get<const QTextCursor&>(state, 3),
                    lua::get<QTextDocument::FindFlags>(state, 4)
                ));
                break;
            }
        } else {
            // QTextCursor     find(const QString & subString, int position = 0, FindFlags options = 0) const
            switch (lua_gettop(state)) {
            case 2:
                lua::push(state, self->find(
                    lua::get<QString>(state, 2)
                ));
                break;
            case 3:
                lua::push(state, self->find(
                    lua::get<QString>(state, 2),
                    lua::get<int>(state, 3)
                ));
                break;
            case 4:
            default:
                lua::push(state, self->find(
                    lua::get<QString>(state, 2),
                    lua::get<int>(state, 3),
                    lua::get<QTextDocument::FindFlags>(state, 4)
                ));
                break;
            }
        }
    }

    return 1;
}

void lua::QTextDocument_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["addResource"] = &QTextDocument::addResource;
    mt["adjustSize"] = &QTextDocument::adjustSize;
    mt["allFormats"] = &QTextDocument::allFormats;
    mt["availableRedoSteps"] = &QTextDocument::availableRedoSteps;
    mt["availableUndoSteps"] = &QTextDocument::availableUndoSteps;
    mt["baseUrl"] = &QTextDocument::baseUrl;
    mt["begin"] = &QTextDocument::begin;
    mt["blockCount"] = &QTextDocument::blockCount;
    mt["characterAt"] = &QTextDocument::characterAt;
    mt["characterCount"] = &QTextDocument::characterCount;
    mt["clear"] = &QTextDocument::clear;
    mt["clearUndoRedoStacks"] = &QTextDocument::clearUndoRedoStacks;
    mt["clone"] = &QTextDocument::clone;
    mt["defaultCursorMoveStyle"] = &QTextDocument::defaultCursorMoveStyle;
    mt["defaultFont"] = &QTextDocument::defaultFont;
    mt["defaultStyleSheet"] = &QTextDocument::defaultStyleSheet;
    mt["defaultTextOption"] = &QTextDocument::defaultTextOption;
    mt["documentLayout"] = &QTextDocument::documentLayout;
    mt["documentMargin"] = &QTextDocument::documentMargin;
    mt["drawContents"] = &QTextDocument::drawContents;
    mt["end"] = &QTextDocument::end;
    mt["find"] = QTextDocument_find;
    mt["findBlock"] = &QTextDocument::findBlock;
    mt["findBlockByLineNumber"] = &QTextDocument::findBlockByLineNumber;
    mt["findBlockByNumber"] = &QTextDocument::findBlockByNumber;
    mt["firstBlock"] = &QTextDocument::firstBlock;
    mt["idealWidth"] = &QTextDocument::idealWidth;
    mt["indentWidth"] = &QTextDocument::indentWidth;
    mt["isEmpty"] = &QTextDocument::isEmpty;
    mt["isModified"] = &QTextDocument::isModified;
    mt["isRedoAvailable"] = &QTextDocument::isRedoAvailable;
    mt["isUndoAvailable"] = &QTextDocument::isUndoAvailable;
    mt["isUndoRedoEnabled"] = &QTextDocument::isUndoRedoEnabled;
    mt["lastBlock"] = &QTextDocument::lastBlock;
    mt["lineCount"] = &QTextDocument::lineCount;
    mt["markContentsDirty"] = &QTextDocument::markContentsDirty;
    mt["maximumBlockCount"] = &QTextDocument::maximumBlockCount;
    mt["metaInformation"] = &QTextDocument::metaInformation;
    mt["object"] = &QTextDocument::object;
    mt["objectForFormat"] = &QTextDocument::objectForFormat;
    mt["pageCount"] = &QTextDocument::pageCount;
    mt["pageSize"] = &QTextDocument::pageSize;
    mt["print"] = &QTextDocument::print;
    //mt["redo"] = &QTextDocument::redo;
    mt["resource"] = &QTextDocument::resource;
    mt["revision"] = &QTextDocument::revision;
    mt["rootFrame"] = &QTextDocument::rootFrame;
    mt["setBaseUrl"] = &QTextDocument::setBaseUrl;
    mt["setDefaultCursorMoveStyle"] = &QTextDocument::setDefaultCursorMoveStyle;
    mt["setDefaultFont"] = &QTextDocument::setDefaultFont;
    mt["setDefaultStyleSheet"] = &QTextDocument::setDefaultStyleSheet;
    mt["setDefaultTextOption"] = &QTextDocument::setDefaultTextOption;
    mt["setDocumentLayout"] = &QTextDocument::setDocumentLayout;
    mt["setDocumentMargin"] = &QTextDocument::setDocumentMargin;
    mt["setHtml"] = &QTextDocument::setHtml;
    mt["setIndentWidth"] = &QTextDocument::setIndentWidth;
    mt["setMaximumBlockCount"] = &QTextDocument::setMaximumBlockCount;
    mt["setMetaInformation"] = &QTextDocument::setMetaInformation;
    mt["setPageSize"] = &QTextDocument::setPageSize;
    mt["setPlainText"] = &QTextDocument::setPlainText;
    mt["setTextWidth"] = &QTextDocument::setTextWidth;
    mt["setUndoRedoEnabled"] = &QTextDocument::setUndoRedoEnabled;
    mt["setUseDesignMetrics"] = &QTextDocument::setUseDesignMetrics;
    mt["size"] = &QTextDocument::size;
    mt["textWidth"] = &QTextDocument::textWidth;
    mt["toHtml"] = QTextDocument_toHtml;
    mt["toPlainText"] = &QTextDocument::toPlainText;
    //mt["undo"] = &QTextDocument::undo;
    mt["useDesignMetrics"] = &QTextDocument::useDesignMetrics;
}

int QTextDocument_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        lua::push(state, new QTextDocument);
        break;
    case 1:
        if (lua::is_type<QString>(state, 1) || lua_isstring(state, 1)) {
            lua::push(state, new QTextDocument(lua::get<QString>(state, 1)));
        } else {
            lua::push(state, new QTextDocument(lua::get<QObject*>(state, 1)));
        }
        break;
    default:
        lua::push(state, new QTextDocument(
            lua::get<QString>(state, 1),
            lua::get<QObject*>(state, 2)
        ));
    }
    return 1;
}

int luaopen_Qt5Gui_QTextDocument(lua_State* const state)
{
    lua::thread env(state);

    env["QTextDocument"] = lua::value::table;
    env["QTextDocument"]["new"] = QTextDocument_new;
    auto t = env["QTextDocument"];

    // enum QTextDocument::FindFlag
    t["FindFlags"] = lua::QFlags_new<QTextDocument::FindFlags>;
    t["FindBackward"] = QTextDocument::FindBackward;
    t["FindCaseSensitively"] = QTextDocument::FindCaseSensitively;
    t["FindWholeWords"] = QTextDocument::FindWholeWords;

    // enum QTextDocument::MetaInformation
    t["DocumentTitle"] = QTextDocument::DocumentTitle;
    t["DocumentUrl"] = QTextDocument::DocumentUrl;

    // enum QTextDocument::ResourceType
    t["HtmlResource"] = QTextDocument::HtmlResource;
    t["ImageResource"] = QTextDocument::ImageResource;
    t["StyleSheetResource"] = QTextDocument::StyleSheetResource;
    t["UserResource"] = QTextDocument::UserResource;

    // enum QTextDocument::Stacks
    t["UndoStack"] = QTextDocument::UndoStack;
    t["RedoStack"] = QTextDocument::RedoStack;
    t["UndoAndRedoStacks"] = QTextDocument::UndoAndRedoStacks;

    return 0;
}
