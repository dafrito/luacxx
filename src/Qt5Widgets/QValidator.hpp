#ifndef luacxx_QValidator_INCLUDED
#define luacxx_QValidator_INCLUDED

#include "../stack.hpp"

class QValidator;

namespace lua {

void QValidator_metatable(const lua::index& mt);

template <>
struct Metatable<QValidator>
{
    static constexpr const char* name = "QValidator";

    static bool metatable(const lua::index& mt, QValidator* const)
    {
        lua::QValidator_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QValidator(lua_State* const);

#endif // luacxx_QValidator_INCLUDED
