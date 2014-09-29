#ifndef luacxx_QFile_INCLUDED
#define luacxx_QFile_INCLUDED

#include "../stack.hpp"

class QFile;

namespace lua {

void QFile_metatable(const lua::index& mt);

template <>
struct Metatable<QFile>
{
    static constexpr const char* name = "QFile";

    static bool metatable(const lua::index& mt, QFile* const)
    {
        lua::QFile_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QFile(lua_State* const);

#endif // luacxx_QFile_INCLUDED
