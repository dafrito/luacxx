#include "QAbstractItemDelegate.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QModelIndex.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QEvent.hpp"
#include "../Qt5Gui/QHelpEvent.hpp"
#include "QWidget.hpp"
#include "QStyleOptionViewItem.hpp"

#include "../Qt5Core/QAbstractItemModel.hpp"
#include "QAbstractItemView.hpp"
#include "../Qt5Gui/QPainter.hpp"

namespace lua {

void QAbstractItemDelegate_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["createEditor"] = &QAbstractItemDelegate::createEditor;
    mt["destroyEditor"] = &QAbstractItemDelegate::destroyEditor;
    mt["editorEvent"] = &QAbstractItemDelegate::editorEvent;
    mt["helpEvent"] = &QAbstractItemDelegate::helpEvent;
    mt["paint"] = &QAbstractItemDelegate::paint;
    mt["setEditorData"] = &QAbstractItemDelegate::setEditorData;
    mt["setModelData"] = &QAbstractItemDelegate::setModelData;
    mt["sizeHint"] = &QAbstractItemDelegate::sizeHint;
    mt["updateEditorGeometry"] = &QAbstractItemDelegate::updateEditorGeometry;
}

} // namespace lua

int luaopen_Qt5Widgets_QAbstractItemDelegate(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractItemDelegate"] = lua::value::table;
    auto t = env["QAbstractItemDelegate"];

    // enum QAbstractItemDelegate::EndEditHint
    t["NoHint"] = QAbstractItemDelegate::NoHint;
    t["EditNextItem"] = QAbstractItemDelegate::EditNextItem;
    t["EditPreviousItem"] = QAbstractItemDelegate::EditPreviousItem;
    t["SubmitModelCache"] = QAbstractItemDelegate::SubmitModelCache;
    t["RevertModelCache"] = QAbstractItemDelegate::RevertModelCache;

    return 0;
}
