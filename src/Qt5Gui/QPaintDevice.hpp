#ifndef LUACXX_QPAINTDEVICE_INCLUDED
#define LUACXX_QPAINTDEVICE_INCLUDED

#include "../luacxx/stack.hpp"
#include <QPaintDevice>

namespace lua {

void QPaintDevice_metatable(const lua::index& mt);

template <>
struct Metatable<QPaintDevice>
{
    static constexpr const char* name = "QPaintDevice";

    static bool metatable(const lua::index& mt, QPaintDevice* const)
    {
        lua::QPaintDevice_metatable(mt);
        return true;
    }
};

}; // namespace lua

#endif // LUACXX_QPAINTDEVICE_INCLUDED
