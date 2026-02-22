#ifndef luacxx_QInputMethodEvent_INCLUDED
#define luacxx_QInputMethodEvent_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QInputMethodEvent>

// http://qt-project.org/doc/qt-5/qinputmethodevent.html

LUA_METATABLE_BUILT(QInputMethodEvent)
LUA_METATABLE_NAMED(QInputMethodEvent::Attribute)
LUA_METATABLE_ENUM(QInputMethodEvent::AttributeType)

extern "C" int luaopen_Qt5Gui_QInputMethodEvent(lua_State* const);

#endif // luacxx_QInputMethodEvent_INCLUDED
