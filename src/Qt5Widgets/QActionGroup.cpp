#include "QActionGroup.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QActionGroup>

#include "../Qt5Core/QList.hpp"
#include "QAction.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Gui/QIcon.hpp"
#include "../Qt5Core/QObject.hpp"

// http://qt-project.org/doc/qt-5/qactiongroup.html

int QActionGroup_addAction(lua_State* const state)
{
    auto self = lua::get<QActionGroup*>(state, 1);

    if (lua::size(state) > 2) {
        lua::push(state, self->addAction(
            lua::get<const QIcon&>(state, 2),
            lua::Get<const QString&>::get(state, 3)
        ));
        return 1;
    }

    if (lua::is_type<QAction>(state, 2)) {
        lua::push(state, self->addAction(
            lua::get<QAction*>(state, 2)
        ));
        return 1;
    }

    lua::push(state, self->addAction(
        lua::get<const QString&>(state, 2)
    ));
    return 1;
}

void lua::QActionGroup_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["actions"] = &QActionGroup::actions;
    mt["addAction"] = QActionGroup_addAction;
    mt["checkedAction"] = &QActionGroup::checkedAction;
    mt["isEnabled"] = &QActionGroup::isEnabled;
    mt["isExclusive"] = &QActionGroup::isExclusive;
    mt["isVisible"] = &QActionGroup::isVisible;
    mt["removeAction"] = &QActionGroup::removeAction;
}

int QActionGroup_new(lua_State* const state)
{
    // QActionGroup(QObject * parent)
    lua::make<QActionGroup>(state, lua::get<QObject*>(state, 1));
    return 1;
}

int luaopen_luacxx_QActionGroup(lua_State* const state)
{
    lua::thread env(state);

    env["QActionGroup"] = lua::value::table;
    env["QActionGroup"]["new"] = QActionGroup_new;
    auto t = env["QActionGroup"];

    return 0;
}
