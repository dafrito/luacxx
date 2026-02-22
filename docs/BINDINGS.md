### INCLUDED BINDINGS

These are the bindings included in this repo, with their status. They are all
optional and not built by default.

#### Linux kernel

If available, bindings for the Linux kernel headers will be compiled.

    yum install kernel-headers

This binding is minimal; see linux/* for what is available.

#### Qt 5

Links to [docs](http://qt-project.org/doc/qt-5/index.html)

This binding is mostly complete for Qt5Core and Qt5Gui; see
Qt5Core/*, Qt5Gui/*, et all for what is supported.

This binding is only partially complete for Qt5Network and Qt5Widgets.

#### libevdev

If available, bindings for the evdev input library will be compiled.

    yum install libevdev-devel

This binding is complete; see libevdev.hpp for information.

#### gobject-introspection

If available, Gtk's GObject introspection model will be available to Lua.

    yum install gobject-introspection-devel

This binding is functional, but not complete. See search/GIRepository.cpp for more
details.

#### libinput

Links to [docs](http://wayland.freedesktop.org/libinput/doc/latest/index.html)

If available, bindings for the libinput input handling library will be
compiled.

    yum install mtdev-devel systemd-devel

This binding is complete; see libinput.hpp for more information.

#### ncurses

Links to [docs](http://invisible-island.net/ncurses/ncurses.html)

If available, bindings for the ncurses terminal library will be compiled.

    yum install ncurses-devel

This binding is complete; see ncurses.hpp for more information.

#### gbm

Links to [docs](http://www.mesa3d.org/)

If available, bindings for Mesa's generic buffer management will be compiled.

    yum install mesa-libgbm-devel

This binding is complete; see gbm.hpp for more information.

#### nanomsg

Links to [docs](http://nanomsg.org/)

If available, bindings for the nanomsg IPC library will be compiled.

    yum install nanomsg-devel

This binding is complete; see nanomsg.hpp for further information.

#### DRM

Links to [docs](http://dri.freedesktop.org/wiki/)

If available, bindings for the direct rendering manager will be compiled.

    yum install libdrm-devel

This binding is partially complete; see xf86drmMode.hpp for information.

#### EGL

Links to [docs](https://www.khronos.org/registry/egl/)

If available, bindings for the EGL graphics standard will be compiled.

    yum install mesa-libEGL-devel

This binding is complete; see egl.hpp for further information.
