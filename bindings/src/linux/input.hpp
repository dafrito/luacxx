#ifndef LUACXX_LINUX_INPUT_INCLUDED
#define LUACXX_LINUX_INPUT_INCLUDED

/*

=head1 NAME

linux/input.h

=head1 DIFFERENCES

The structs for this kernel header were not bound, as they are not used by
libevdev and they're a bit more difficult to bind. However, there are examples
elsewhere for structs if you want to wire them up.

*/

struct lua_State;

extern "C" int luaopen_linux_input(lua_State* const);

#endif // LUACXX_LINUX_INPUT_INCLUDED
