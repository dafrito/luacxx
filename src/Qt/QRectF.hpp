#ifndef LUA_CXX_QRECTF_INCLUDED
#define LUA_CXX_QRECTF_INCLUDED

#include "../stack.hpp"

class QRectF;

namespace lua {

void QRectF_metatable(const lua::index& mt);

template <>
struct Metatable<QRectF>
{
    static constexpr const char* name = "QRectF";

    static bool metatable(const lua::index& mt, QRectF* const)
    {
        lua::QRectF_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QRectF(lua::state* const);

#endif // LUA_CXX_QRECTF_INCLUDED
