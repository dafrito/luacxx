#include "QAbstractItemView.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QModelIndex.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "QWidget.hpp"
#include "QAbstractItemDelegate.hpp"
#include "../Qt5Core/QAbstractItemModel.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QItemSelectionModel.hpp"
#include "../Qt5Core/QFlags.hpp"

int QAbstractItemView_itemDelegate(lua_State* const state)
{
    auto self = lua::get<QAbstractItemView*>(state, 1);

    if (lua_gettop(state) == 1) {
        lua::push(state, self->itemDelegate());
    } else {
        lua::push(state, self->itemDelegate(
            lua::get<const QModelIndex&>(state, 2)
        ));
    }

    return 1;
}

int QAbstractItemView_scrollTo(lua_State* const state)
{
    auto self = lua::get<QAbstractItemView*>(state, 1);

    // virtual void     scrollTo(const QModelIndex & index, ScrollHint hint = EnsureVisible) = 0
    if (lua_gettop(state) == 2) {
        self->scrollTo(
            lua::get<const QModelIndex&>(state, 2)
        );
    } else {
        self->scrollTo(
            lua::get<const QModelIndex&>(state, 2),
            lua::get<QAbstractItemView::ScrollHint>(state, 3)
        );
    }

    return 1;
}

void lua::QAbstractItemView_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractScrollArea_metatable(state, pos);

    lua::index mt(state, pos);
    mt["alternatingRowColors"] = &QAbstractItemView::alternatingRowColors;
    mt["autoScrollMargin"] = &QAbstractItemView::autoScrollMargin;
    mt["closePersistentEditor"] = &QAbstractItemView::closePersistentEditor;
    mt["currentIndex"] = &QAbstractItemView::currentIndex;
    mt["defaultDropAction"] = &QAbstractItemView::defaultDropAction;
    mt["dragDropMode"] = &QAbstractItemView::dragDropMode;
    mt["dragDropOverwriteMode"] = &QAbstractItemView::dragDropOverwriteMode;
    mt["dragEnabled"] = &QAbstractItemView::dragEnabled;
    mt["editTriggers"] = &QAbstractItemView::editTriggers;
    mt["hasAutoScroll"] = &QAbstractItemView::hasAutoScroll;
    mt["horizontalScrollMode"] = &QAbstractItemView::horizontalScrollMode;
    mt["iconSize"] = &QAbstractItemView::iconSize;
    mt["indexAt"] = &QAbstractItemView::indexAt;
    mt["indexWidget"] = &QAbstractItemView::indexWidget;
    mt["itemDelegate"] = QAbstractItemView_itemDelegate;
    mt["keyboardSearch"] = &QAbstractItemView::keyboardSearch;
    mt["model"] = &QAbstractItemView::model;
    mt["openPersistentEditor"] = &QAbstractItemView::openPersistentEditor;
    mt["rootIndex"] = &QAbstractItemView::rootIndex;
    mt["scrollTo"] = QAbstractItemView_scrollTo;
    mt["selectionBehavior"] = &QAbstractItemView::selectionBehavior;
    mt["selectionMode"] = &QAbstractItemView::selectionMode;
    mt["selectionModel"] = &QAbstractItemView::selectionModel;
    mt["setAlternatingRowColors"] = &QAbstractItemView::setAlternatingRowColors;
    mt["setAutoScroll"] = &QAbstractItemView::setAutoScroll;
    mt["setAutoScrollMargin"] = &QAbstractItemView::setAutoScrollMargin;
    mt["setDefaultDropAction"] = &QAbstractItemView::setDefaultDropAction;
    mt["setDragDropMode"] = &QAbstractItemView::setDragDropMode;
    mt["setDragDropOverwriteMode"] = &QAbstractItemView::setDragDropOverwriteMode;
    mt["setDragEnabled"] = &QAbstractItemView::setDragEnabled;
    mt["setDropIndicatorShown"] = &QAbstractItemView::setDropIndicatorShown;
    mt["setEditTriggers"] = &QAbstractItemView::setEditTriggers;
    mt["setHorizontalScrollMode"] = &QAbstractItemView::setHorizontalScrollMode;
    mt["setIconSize"] = &QAbstractItemView::setIconSize;
    mt["setIndexWidget"] = &QAbstractItemView::setIndexWidget;
    mt["setItemDelegate"] = &QAbstractItemView::setItemDelegate;
    mt["setItemDelegateForColumn"] = &QAbstractItemView::setItemDelegateForColumn;
    mt["setItemDelegateForRow"] = &QAbstractItemView::setItemDelegateForRow;
    mt["setModel"] = &QAbstractItemView::setModel;
    mt["setSelectionBehavior"] = &QAbstractItemView::setSelectionBehavior;
    mt["setSelectionMode"] = &QAbstractItemView::setSelectionMode;
    mt["setSelectionModel"] = &QAbstractItemView::setSelectionModel;
    mt["setTabKeyNavigation"] = &QAbstractItemView::setTabKeyNavigation;
    mt["setTextElideMode"] = &QAbstractItemView::setTextElideMode;
    mt["setVerticalScrollMode"] = &QAbstractItemView::setVerticalScrollMode;
    mt["showDropIndicator"] = &QAbstractItemView::showDropIndicator;
    mt["sizeHintForColumn"] = &QAbstractItemView::sizeHintForColumn;
    mt["sizeHintForIndex"] = &QAbstractItemView::sizeHintForIndex;
    mt["sizeHintForRow"] = &QAbstractItemView::sizeHintForRow;
    mt["tabKeyNavigation"] = &QAbstractItemView::tabKeyNavigation;
    mt["textElideMode"] = &QAbstractItemView::textElideMode;
    mt["verticalScrollMode"] = &QAbstractItemView::verticalScrollMode;
    mt["visualRect"] = &QAbstractItemView::visualRect;
}

int luaopen_Qt5Widgets_QAbstractItemView(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractItemView"] = lua::value::table;
    auto t = env["QAbstractItemView"];

    // enum QAbstractItemView::DragDropMode
    t["NoDragDrop"] = QAbstractItemView::NoDragDrop;
    t["DragOnly"] = QAbstractItemView::DragOnly;
    t["DropOnly"] = QAbstractItemView::DropOnly;
    t["DragDrop"] = QAbstractItemView::DragDrop;
    t["InternalMove"] = QAbstractItemView::InternalMove;

    // enum QAbstractItemView::EditTrigger
    t["EditTriggers"] = lua::QFlags_new<QAbstractItemView::EditTriggers>;
    t["NoEditTriggers"] = QAbstractItemView::NoEditTriggers;
    t["CurrentChanged"] = QAbstractItemView::CurrentChanged;
    t["DoubleClicked"] = QAbstractItemView::DoubleClicked;
    t["SelectedClicked"] = QAbstractItemView::SelectedClicked;
    t["EditKeyPressed"] = QAbstractItemView::EditKeyPressed;
    t["AnyKeyPressed"] = QAbstractItemView::AnyKeyPressed;
    t["AllEditTriggers"] = QAbstractItemView::AllEditTriggers;

    // enum QAbstractItemView::ScrollHint
    t["EnsureVisible"] = QAbstractItemView::EnsureVisible;
    t["PositionAtTop"] = QAbstractItemView::PositionAtTop;
    t["PositionAtBottom"] = QAbstractItemView::PositionAtBottom;
    t["PositionAtCenter"] = QAbstractItemView::PositionAtCenter;

    // enum QAbstractItemView::ScrollMode
    t["ScrollPerItem"] = QAbstractItemView::ScrollPerItem;
    t["ScrollPerPixel"] = QAbstractItemView::ScrollPerPixel;

    // enum QAbstractItemView::SelectionBehavior
    t["SelectItems"] = QAbstractItemView::SelectItems;
    t["SelectRows"] = QAbstractItemView::SelectRows;
    t["SelectColumns"] = QAbstractItemView::SelectColumns;

    // enum QAbstractItemView::SelectionMode
    t["SingleSelection"] = QAbstractItemView::SingleSelection;
    t["ContiguousSelection"] = QAbstractItemView::ContiguousSelection;
    t["ExtendedSelection"] = QAbstractItemView::ExtendedSelection;
    t["MultiSelection"] = QAbstractItemView::MultiSelection;
    t["NoSelection"] = QAbstractItemView::NoSelection;

    return 0;
}
