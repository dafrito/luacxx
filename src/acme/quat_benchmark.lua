acme = acme or {};

local function printf(msg, ...)
    print(string.format(msg, ...));
end;

function acme.quat_benchmark()
    require "Qt5Gui.QQuaternion";
    require "Qt5Core.QElapsedTimer";
    require "Qt5Gui.QVector2D";
    require "Qt5Gui.QVector3D";
    require "Qt5Gui.QVector4D";
    require "acme.math";

    local MAX = 10000;
    print("quat_benchmark MAX=" .. MAX);
    print("");

    for i=1, 5 do
        timer = QElapsedTimer:new();
        timer:start();
        quat = QQuaternion.benchmark(MAX);
        local ctime = timer:nsecsElapsed() / 1e6;
        printf("C++: %.02fms", ctime);

        timer = QElapsedTimer:new();
        timer:start();
        quat = Quaternion(2, 3, 7, 5);
        for i=1, MAX do
            quat = quat * Quaternion(2, 2, 2, 2);
            quat:Normalize();
        end
        local luatime = timer:nsecsElapsed() / 1e6;
        printf("Lua: %.02fms (%.01f times slower than C++)", luatime, luatime/ctime);

        timer = QElapsedTimer:new();
        timer:start();
        quat = QQuaternion:new(2, 3, 7, 5);
        for i=1, MAX do
            quat = quat * QQuaternion:new(2, 2, 2, 2);
            quat:normalize();
        end
        local luacxxtime = timer:nsecsElapsed() / 1e6;
        printf("Lua-cxx: %.02fms (%.01f times slower than C++)", luacxxtime, luacxxtime/ctime);

        if luacxxtime > luatime then
            printf("Lua-cxx was %.02f times slower than Lua.", luacxxtime/luatime);
        else
            printf("Lua-cxx was %.02f times faster than Lua.", luatime/luacxxtime);
        end;
        print("");
    end;
end;
