require "demo.qt_window"
require "demo.quat_benchmark"
require "demo.ncurses_getch"
require "demo.nanomsg_ipc";

-- Change this to run any other demo
demo.quat_benchmark(...);
return demo.nanomsg_ipc(select(3, ...));
