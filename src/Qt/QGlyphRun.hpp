#ifndef LUA_CXX_QGLYPHRUN_INCLUDED
#define LUA_CXX_QGLYPHRUN_INCLUDED

#include "../stack.hpp"

class QGlyphRun;

namespace lua {

void QGlyphRun_metatable(const lua::index& mt);

template <>
struct Metatable<QGlyphRun>
{
    static constexpr const char* name = "QGlyphRun";

    static bool metatable(const lua::index& mt, QGlyphRun* const)
    {
        lua::QGlyphRun_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QGlyphRun(lua::state* const);

#endif // LUA_CXX_QGLYPHRUN_INCLUDED
