#include "QPushButton.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QAbstractButton.hpp"
#include "QMenu.hpp"

namespace lua {

void QPushButton_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractButton_metatable(state, pos);

    lua::index mt(state, pos);
    mt["autoDefault"] = &QPushButton::autoDefault;
    mt["isDefault"] = &QPushButton::isDefault;
    mt["isFlat"] = &QPushButton::isFlat;
    mt["menu"] = &QPushButton::menu;
    mt["setAutoDefault"] = &QPushButton::setAutoDefault;
    mt["setDefault"] = &QPushButton::setDefault;
    mt["setFlat"] = &QPushButton::setFlat;
    mt["setMenu"] = &QPushButton::setMenu;
}

} // namespace lua

int QPushButton_new(lua_State* const state)
{
    // QPushButton(QWidget * parent = 0)
    // QPushButton(const QString & text, QWidget * parent = 0)
    // QPushButton(const QIcon & icon, const QString & text, QWidget * parent = 0)
    lua::make<QPushButton>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Widgets_QPushButton(lua_State* const state)
{
    lua::thread env(state);

    env["QPushButton"] = lua::value::table;
    env["QPushButton"]["new"] = QPushButton_new;
    auto t = env["QPushButton"];

    return 0;
}
