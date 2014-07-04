#!/usr/bin/env luacxx

require "acme.qt_window"
require "acme.quat_benchmark"
require "acme.ncurses_getch"
require "acme.nanorecv";
require "acme.nanosend";

local name = select(3, ...);

if name and acme[name] then
    print("Running " .. name);
    local runner = acme[name];
    if runner ~= nil then
        return runner(select(4, ...));
    end;
end;

if name then
    print(name .. " not found.");
end;

print("These are the available programs:");
for name, _ in pairs(acme) do
    print("", name);
end;
print("\nRun one by passing the program name as an argument, like this:");
print("\tmake run-ncurses_getch");
