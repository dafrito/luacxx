#include "Bootstrapper.hpp"

Bootstrapper::Bootstrapper() :
    _mainWidget()
{
}

QWidget& Bootstrapper::mainWidget()
{
    return _mainWidget;
}

// vim: set ts=4 sw=4 :
