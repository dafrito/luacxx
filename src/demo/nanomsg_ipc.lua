demo = demo or {};

local function printf(msg, ...)
    print(string.format(msg, ...));
end;

local function nanorecv(url)
    local sock = nn_socket(AF_SP, NN_PULL);
    assert(sock >= 0);
    if nn_bind(sock, url) < 0 then
        print(nn_strerror(errno()));
    end;
    while true do
        local bytes, buf = nn_recv(sock, 0, NN_MSG, 0);
        assert(bytes >= 0);
        printf("recv: '%s'", buf);
        nn_freemsg (buf);
    end;
end;

local function nanosend(url, msg)
    local sz_msg = #msg + 1; -- include the '\0'
    local sock = nn_socket(AF_SP, NN_PUSH);
    assert(sock >= 0);
    local how = nn_connect(sock, url);
    assert(how >= 0);
    printf("sent: '%s'", msg);
    local bytes = nn_send(sock, msg, sz_msg, 0);
    assert(bytes == sz_msg);
    return nn_shutdown(sock, how);
end;

function demo.nanomsg_ipc(cmd, ...)
    require "nanomsg"
    print("ARG", cmd, ...);

    if cmd == "recv" then
        return nanorecv(...);
    end;
    if cmd == "send" then
        return nanosend(...);
    end;

    print("Usage: recv|send <url> <msg>");
    return 1;
end;
