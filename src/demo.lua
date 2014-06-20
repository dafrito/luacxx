require "acme.qt_window"
require "acme.quat_benchmark"
require "acme.ncurses_getch"
require "acme.nanomsg_ipc";

-- Change this to run any other demo
acme.quat_benchmark(...);
return acme.nanomsg_ipc(select(3, ...));
