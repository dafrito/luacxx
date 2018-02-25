#!/usr/bin/env luacxx

require "demo.qt_window"
require "demo.quat_benchmark"
require "demo.ncurses_getch"
require "demo.nanorecv";
require "demo.nanosend";
require "demo.cairo";
require "demo.Gst";

local _, _, name = ...;

if name and demo[name] then
    print("Running " .. name);
    local runner = demo[name];
    if runner ~= nil then
        return runner(select(4, ...));
    end;
end;

if name then
    print(name .. " not found.");
end;

print("These are the available programs:");
for name, _ in pairs(demo) do
    print("", name);
end;

print("\nRun one by passing the program name as an argument, like this:");
print("\tmake run-ncurses_getch");
