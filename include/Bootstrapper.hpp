#ifndef LUA_CXX_BOOTSTRAPPER_HEADER
#define LUA_CXX_BOOTSTRAPPER_HEADER

#include <QWidget>

class Bootstrapper
{
    QWidget _mainWidget;
public:
    Bootstrapper();

    QWidget& mainWidget();
};

#endif // LUA_CXX_BOOTSTRAPPER_HEADER


// vim: set ts=4 sw=4 :
