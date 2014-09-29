#ifndef luacxx_QAction_INCLUDED
#define luacxx_QAction_INCLUDED

#include <QAction>

#include "../stack.hpp"
#include "../algorithm.hpp"
#include "../convert/string.hpp"

namespace lua {

void QAction_metatable(const lua::index& mt);

template <>
struct Metatable<QAction>
{
    static constexpr const char* name = "QAction";

    static bool metatable(const lua::index& mt, const QAction* const)
    {
        lua::QAction_metatable(mt);
        return true;
    }
};

} // namespace lua

#endif // luacxx_QAction_INCLUDED
