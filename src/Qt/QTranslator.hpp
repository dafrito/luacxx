#ifndef LUACXX_QTRANSLATOR_INCLUDED
#define LUACXX_QTRANSLATOR_INCLUDED

#include "../luacxx/stack.hpp"

class QTranslator;

namespace lua {

void QTranslator_metatable(const lua::index& mt);

template <>
struct Metatable<QTranslator>
{
    static constexpr const char* name = "QTranslator";

    static bool metatable(const lua::index& mt, QTranslator* const)
    {
        lua::QTranslator_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QTranslator(lua_State* const);

#endif // LUACXX_QTRANSLATOR_INCLUDED
