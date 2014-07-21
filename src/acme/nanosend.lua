acme = acme or {};

local function printf(msg, ...)
    print(string.format(msg, ...));
end;

function acme.nanosend(url, msg)
    require "nanomsg";

    if url == nil or msg == nil then
        print("USAGE: nanosend <url> <msg>");
        return;
    end;

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
