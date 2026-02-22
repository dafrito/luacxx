#ifndef luacxx_QWidget_INCLUDED
#define luacxx_QWidget_INCLUDED

#include "../stack.hpp"

#include <QWidget>

#include "../Qt5Core/QObject.hpp"

LUA_METATABLE_INHERIT(QWidget, QObject);

#endif // luacxx_QWidget_INCLUDED
