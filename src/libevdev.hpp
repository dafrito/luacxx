#ifndef LUACXX_LIBEVDEV_INCLUDED
#define LUACXX_LIBEVDEV_INCLUDED

#include "luacxx/stack.hpp"

/*

=head1 NAME

libevdev

=head1 SYNOPSIS

=head1 DESCRIPTION

=head1 INSTALLING

    yum install libevdev-devel

*/

struct libevdev;

namespace lua {

template <>
struct Metatable<libevdev>
{
    static constexpr const char* name = "libevdev";

    static bool metatable(const lua::index& mt, libevdev* const)
    {
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_evdev(lua_State* const);

#endif // LUACXX_LIBEVDEV_INCLUDED
