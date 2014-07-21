#include "QResizeEvent.hpp"

#include "../Qt5Core/QEvent.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

void lua::QResizeEvent_metatable(const lua::index& mt)
{
    lua::QEvent_metatable(mt);

    mt["oldSize"] = &QResizeEvent::oldSize;
    mt["size"] = &QResizeEvent::size;
}
