#ifndef LUACXX_QSURFACE_INCLUDED
#define LUACXX_QSURFACE_INCLUDED

#include "../luacxx/stack.hpp"

/*

=head1 NAME

QSurface - https://qt-project.org/doc/qt-5/qsurface.html

*/

class QSurface;

namespace lua {

void QSurface_metatable(const lua::index& mt);

template <>
struct Metatable<QSurface>
{
    static constexpr const char* name = "QSurface";

    static bool metatable(const lua::index& mt, QSurface* const)
    {
        lua::QSurface_metatable(mt);
        return true;
    }
};

}; // namespace lua

#endif // LUACXX_QSURFACE_INCLUDED
