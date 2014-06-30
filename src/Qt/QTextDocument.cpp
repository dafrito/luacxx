#include "QTextDocument.hpp"
#include "../luacxx/type/function.hpp"
#include "../luacxx/thread.hpp"
#include "QUrl.hpp"
#include "QVariant.hpp"
#include "QVector.hpp"
#include "QTextFormat.hpp"
#include "QTextBlock.hpp"
#include "QChar.hpp"
#include "QFont.hpp"
#include "QTextCursor.hpp"
#include "QTextObject.hpp"
#include "QAbstractTextDocumentLayout.hpp"
#include "QSizeF.hpp"
#include "QTextFrame.hpp"
#include "QPagedPaintDevice.hpp"
#include "QObject.hpp"

#include <QTextDocument>

int QTextDocument_toHtml(lua_State* const state)
{
    return 0;
}

int QTextDocument_find(lua_State* const state)
{
    return 0;
}

void lua::QTextDocument_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);

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
    mt["print"] = &QAbstractSocket::print;
    mt["redo"] = &QTextDocument::redo;
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
    mt["undo"] = &QTextDocument::undo;
    mt["useDesignMetrics"] = &QTextDocument::useDesignMetrics;
}

int QTextDocument_new(lua_State* const state)
{
    if (lua_gettop(state) > 1) {
        lua::make<QTextDocument>(state,
            lua::get<QString>(state, 2)
        );
    }
    return 1;
}

int luaopen_luacxx_QTextDocument(lua_State* const state)
{
    lua::thread env(state);

    env["QTextDocument"] = lua::value::table;
    env["QTextDocument"]["new"] = QTextDocument_new;
    auto t = env["QTextDocument"];

    // enum QTextDocument::FindFlag
    // flags QTextDocument::FindFlags
    t["TextDocument"] = QQApplication>TextDocument;
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
