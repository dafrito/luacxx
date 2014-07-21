#include "QExposeEvent.hpp"

#include "QRegion.hpp"
#include "../Qt5Core/QEvent.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

void lua::QExposeEvent_metatable(const lua::index& mt)
{
    lua::QEvent_metatable(mt);
    mt["region"] = &QExposeEvent::region;
}
