#ifndef luacxx_QWidget_INCLUDED
#define luacxx_QWidget_INCLUDED

#include <QWidget>

#include "../Qt5Core/QObject.hpp"
#include "Qt5Widgets.hpp"
#include "../algorithm.hpp"
#include "../convert/string.hpp"

LUA_METATABLE_INHERIT(QWidget, QObject);

#endif // luacxx_QWidget_INCLUDED
