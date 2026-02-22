#include "QAbstractTextDocumentLayout.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QObject.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/QSizeF.hpp"
#include "QTextObjectInterface.hpp"
#include "QTextDocument.hpp"
#include "QTextBlock.hpp"
#include "QPainter.hpp"
#include "QTextFrame.hpp"
#include "QPaintDevice.hpp"

namespace lua {

void QAbstractTextDocumentLayout_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["anchorAt"] = &QAbstractTextDocumentLayout::anchorAt;
    mt["blockBoundingRect"] = &QAbstractTextDocumentLayout::blockBoundingRect;
    mt["document"] = &QAbstractTextDocumentLayout::document;
    mt["documentSize"] = &QAbstractTextDocumentLayout::documentSize;
    mt["draw"] = &QAbstractTextDocumentLayout::draw;
    mt["frameBoundingRect"] = &QAbstractTextDocumentLayout::frameBoundingRect;
    mt["handlerForObject"] = &QAbstractTextDocumentLayout::handlerForObject;
    mt["hitTest"] = &QAbstractTextDocumentLayout::hitTest;
    mt["pageCount"] = &QAbstractTextDocumentLayout::pageCount;
    mt["paintDevice"] = &QAbstractTextDocumentLayout::paintDevice;
    mt["registerHandler"] = &QAbstractTextDocumentLayout::registerHandler;
    mt["setPaintDevice"] = &QAbstractTextDocumentLayout::setPaintDevice;
    mt["unregisterHandler"] = &QAbstractTextDocumentLayout::unregisterHandler;
}

} // namespace lua

int luaopen_Qt5Core_QAbstractTextDocumentLayout(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractTextDocumentLayout"] = lua::value::table;
    auto t = env["QAbstractTextDocumentLayout"];

    return 0;
}
