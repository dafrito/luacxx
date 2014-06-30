#ifndef LUACXX_QOBJECT_INCLUDED
#define LUACXX_QOBJECT_INCLUDED

#include <QObject>

#include "../luacxx/stack.hpp"
#include "../luacxx/algorithm.hpp"
#include "../luacxx/type/standard.hpp"

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

void qmetamethod_metatable(const lua::index& mt);

template <>
struct Metatable<QMetaMethod>
{
    static constexpr const char* name = "QMetaMethod";

    static bool metatable(const lua::index& mt, const QMetaMethod* const)
    {
        lua::qmetamethod_metatable(mt);
        return true;
    }
};

} // namespace lua

#endif // LUACXX_QOBJECT_INCLUDED
