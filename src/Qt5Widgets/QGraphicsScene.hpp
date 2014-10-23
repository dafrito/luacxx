#ifndef LUA_CXX_QGRAPHICSSCENE_INCLUDED
#define LUA_CXX_QGRAPHICSSCENE_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QGraphicsScene>

LUA_METATABLE_BUILT(QGraphicsScene);
LUA_METATABLE_ENUM(QGraphicsScene::ItemIndexMethod);
LUA_METATABLE_ENUM(QGraphicsScene::SceneLayer);

extern "C" int luaopen_Qt5Widgets_QGraphicsScene(lua_State* const);

#endif // LUA_CXX_QGRAPHICSSCENE_INCLUDED
