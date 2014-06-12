#ifndef LUA_CXX_QPAINTDEVICE_INCLUDED
#define LUA_CXX_QPAINTDEVICE_INCLUDED

#include "../stack.hpp"

class QPaintDevice;

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

#endif // LUA_CXX_QPAINTDEVICE_INCLUDED
