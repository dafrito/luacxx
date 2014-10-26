#include "QCompleter.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QObject.hpp"
#include "QWidget.hpp"
#include "../Qt5Core/QModelIndex.hpp"
#include "../Qt5Core/QAbstractItemModel.hpp"
#include "QAbstractItemView.hpp"
#include "../Qt5Core/QStringList.hpp"
#include "../Qt5Core/QFlags.hpp"

void lua::QCompleter_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["caseSensitivity"] = &QCompleter::caseSensitivity;
    mt["completionColumn"] = &QCompleter::completionColumn;
    mt["completionCount"] = &QCompleter::completionCount;
    mt["completionMode"] = &QCompleter::completionMode;
    mt["completionModel"] = &QCompleter::completionModel;
    mt["completionPrefix"] = &QCompleter::completionPrefix;
    mt["completionRole"] = &QCompleter::completionRole;
    mt["currentCompletion"] = &QCompleter::currentCompletion;
    mt["currentIndex"] = &QCompleter::currentIndex;
    mt["currentRow"] = &QCompleter::currentRow;
    mt["filterMode"] = &QCompleter::filterMode;
    mt["maxVisibleItems"] = &QCompleter::maxVisibleItems;
    mt["model"] = &QCompleter::model;
    mt["modelSorting"] = &QCompleter::modelSorting;
    mt["pathFromIndex"] = &QCompleter::pathFromIndex;
    mt["popup"] = &QCompleter::popup;
    mt["setCaseSensitivity"] = &QCompleter::setCaseSensitivity;
    mt["setCompletionColumn"] = &QCompleter::setCompletionColumn;
    mt["setCompletionMode"] = &QCompleter::setCompletionMode;
    mt["setCompletionRole"] = &QCompleter::setCompletionRole;
    mt["setCurrentRow"] = &QCompleter::setCurrentRow;
    mt["setFilterMode"] = &QCompleter::setFilterMode;
    mt["setMaxVisibleItems"] = &QCompleter::setMaxVisibleItems;
    mt["setModel"] = &QCompleter::setModel;
    mt["setModelSorting"] = &QCompleter::setModelSorting;
    mt["setPopup"] = &QCompleter::setPopup;
    mt["setWidget"] = &QCompleter::setWidget;
    mt["splitPath"] = &QCompleter::splitPath;
    mt["widget"] = &QCompleter::widget;
    mt["wrapAround"] = &QCompleter::wrapAround;
}

int QCompleter_new(lua_State* const state)
{
    // QCompleter(QObject * parent = 0)
    // QCompleter(QAbstractItemModel * model, QObject * parent = 0)
    // QCompleter(const QStringList & list, QObject * parent = 0)
    lua::make<QCompleter>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Widgets_QCompleter(lua_State* const state)
{
    lua::thread env(state);

    env["QCompleter"] = lua::value::table;
    env["QCompleter"]["new"] = QCompleter_new;
    auto t = env["QCompleter"];

    // enum QCompleter::CompletionMode
    t["PopupCompletion"] = QCompleter::PopupCompletion;
    t["InlineCompletion"] = QCompleter::InlineCompletion;
    t["UnfilteredPopupCompletion"] = QCompleter::UnfilteredPopupCompletion;

    // enum QCompleter::ModelSorting
    t["UnsortedModel"] = QCompleter::UnsortedModel;
    t["CaseSensitivelySortedModel"] = QCompleter::CaseSensitivelySortedModel;
    t["CaseInsensitivelySortedModel"] = QCompleter::CaseInsensitivelySortedModel;

    return 0;
}
