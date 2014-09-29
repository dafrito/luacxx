#ifndef LUACXX_QOBJECT_INCLUDED
#define LUACXX_QOBJECT_INCLUDED

#include <QObject>

#include "../stack.hpp"
#include "../algorithm.hpp"
#include "../convert/string.hpp"

namespace lua {

void QObject_metatable(const lua::index& mt);

template <>
struct Metatable<QObject>
{
    static constexpr const char* name = "QObject";

    static bool metatable(const lua::index& mt, const QObject* const)
    {
        lua::QObject_metatable(mt);
        return true;
    }
};

void QMetaMethod_metatable(const lua::index& mt);

template <>
struct Metatable<QMetaMethod>
{
    static constexpr const char* name = "QMetaMethod";

    static bool metatable(const lua::index& mt, const QMetaMethod* const)
    {
        lua::QMetaMethod_metatable(mt);
        return true;
    }
};

} // namespace lua

#endif // LUACXX_QOBJECT_INCLUDED
