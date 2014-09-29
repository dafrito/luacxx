#ifndef luacxx_QFileDevice_INCLUDED
#define luacxx_QFileDevice_INCLUDED

#include "../stack.hpp"

class QFileDevice;

namespace lua {

void QFileDevice_metatable(const lua::index& mt);

template <>
struct Metatable<QFileDevice>
{
    static constexpr const char* name = "QFileDevice";

    static bool metatable(const lua::index& mt, QFileDevice* const)
    {
        lua::QFileDevice_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QFileDevice(lua_State* const);

#endif // luacxx_QFileDevice_INCLUDED
