#include "QResizeEvent.hpp"

#include "../Qt5Core/QEvent.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../luacxx/convert/callable.hpp"
#include "../luacxx/thread.hpp"

void lua::QResizeEvent_metatable(const lua::index& mt)
{
    lua::QEvent_metatable(mt);

    mt["oldSize"] = &QResizeEvent::oldSize;
    mt["size"] = &QResizeEvent::size;
}
