#ifndef luacxx_QWidget_INCLUDED
#define luacxx_QWidget_INCLUDED

#include <QWidget>

#include "../stack.hpp"
#include "../algorithm.hpp"
#include "../convert/string.hpp"

namespace lua {

void QWidget_metatable(const lua::index& mt);

template <>
struct Metatable<QWidget>
{
    static constexpr const char* name = "QWidget";

    static bool metatable(const lua::index& mt, const QWidget* const)
    {
        lua::QWidget_metatable(mt);
        return true;
    }
};

} // namespace lua

#endif // luacxx_QWidget_INCLUDED
