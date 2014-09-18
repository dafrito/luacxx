#include "nanomsg.hpp"
#include "thread.hpp"

#include <nanomsg/bus.h>
#include <nanomsg/ipc.h>
#include <nanomsg/inproc.h>
#include <nanomsg/pair.h>
#include <nanomsg/pipeline.h>
#include <nanomsg/pubsub.h>
#include <nanomsg/reqrep.h>
#include <nanomsg/survey.h>
#include <nanomsg/tcp.h>

#include <cstring>

int nn_symbol_properties_index(lua_State* const state)
{
    auto self = lua::get<nn_symbol_properties*>(state, 1);

    auto name = lua::get<const char*>(state, 2);
    if (!strcmp(name, "value")) {
        lua::push(state, self->value);
        return 1;
    }
    if (!strcmp(name, "name")) {
        lua::push(state, self->name);
        return 1;
    }
    if (!strcmp(name, "ns")) {
        lua::push(state, self->ns);
        return 1;
    }
    if (!strcmp(name, "type")) {
        lua::push(state, self->type);
        return 1;
    }
    if (!strcmp(name, "unit")) {
        lua::push(state, self->unit);
        return 1;
    }
    return 0;
}

void lua::nn_symbol_properties_metatable(const lua::index& mt)
{
    mt["__index"] = nn_symbol_properties_index;
}

int nn_symbol_properties_new(lua_State* const state)
{
    lua::make<nn_symbol_properties>(state);
    return 1;
}

int nn_pollfd_index(lua_State* const state)
{
    auto self = lua::get<nn_pollfd*>(state, 1);

    auto name = lua::get<const char*>(state, 2);
    if (!strcmp(name, "fd")) {
        lua::push(state, self->fd);
        return 1;
    }
    if (!strcmp(name, "events")) {
        lua::push(state, self->events);
        return 1;
    }
    if (!strcmp(name, "revents")) {
        lua::push(state, self->revents);
        return 1;
    }
    return 0;
}

void lua::nn_pollfd_metatable(const lua::index& mt)
{
    mt["__index"] = nn_pollfd_index;
}

int nn_pollfd_new(lua_State* const state)
{
    lua::make<nn_pollfd>(state);
    return 1;
}

int nn_iovec_index(lua_State* const state)
{
    auto self = lua::get<nn_iovec*>(state, 1);

    auto name = lua::get<const char*>(state, 2);
    if (!strcmp(name, "iov_base")) {
        lua::push(state, self->iov_base);
        return 1;
    }
    if (!strcmp(name, "iov_len")) {
        lua::push(state, self->iov_len);
        return 1;
    }
    return 0;
}

void lua::nn_iovec_metatable(const lua::index& mt)
{
    mt["__index"] = nn_iovec_index;
}

int nn_iovec_new(lua_State* const state)
{
    lua::make<nn_iovec>(state);
    return 1;
}

int nn_msghdr_index(lua_State* const state)
{
    auto self = lua::get<nn_msghdr*>(state, 1);

    auto name = lua::get<const char*>(state, 2);
    if (!strcmp(name, "msg_iov")) {
        lua::push(state, self->msg_iov);
        return 1;
    }
    if (!strcmp(name, "msg_iovlen")) {
        lua::push(state, self->msg_iovlen);
        return 1;
    }
    if (!strcmp(name, "msg_control")) {
        lua::push(state, self->msg_control);
        return 1;
    }
    if (!strcmp(name, "msg_controllen")) {
        lua::push(state, self->msg_controllen);
        return 1;
    }
    return 0;
}

void lua::nn_msghdr_metatable(const lua::index& mt)
{
    mt["__index"] = nn_msghdr_index;
}

int nn_msghdr_new(lua_State* const state)
{
    lua::make<nn_msghdr>(state);
    return 1;
}

int nn_cmsghdr_index(lua_State* const state)
{
    auto self = lua::get<nn_cmsghdr*>(state, 1);

    auto name = lua::get<const char*>(state, 2);
    if (!strcmp(name, "cmsg_len")) {
        lua::push(state, self->cmsg_len);
        return 1;
    }
    if (!strcmp(name, "cmsg_level")) {
        lua::push(state, self->cmsg_level);
        return 1;
    }
    if (!strcmp(name, "cmsg_type")) {
        lua::push(state, self->cmsg_type);
        return 1;
    }
    return 0;
}

void lua::nn_cmsghdr_metatable(const lua::index& mt)
{
    mt["__index"] = nn_cmsghdr_index;
}

int nn_cmsghdr_new(lua_State* const state)
{
    lua::make<nn_msghdr>(state);
    return 1;
}

int _NN_CMSG_FIRSTHDR(lua_State* const state)
{
    lua::push(state, NN_CMSG_FIRSTHDR(
        lua::get<nn_msghdr*>(state, 1)
    ));
    return 1;
}

int _NN_CMSG_NXTHDR(lua_State* const state)
{
    lua::push(state, NN_CMSG_NXTHDR(
        lua::get<nn_msghdr*>(state, 1),
        lua::get<nn_msghdr*>(state, 2)
    ));
    return 1;
}

int _NN_CMSG_DATA(lua_State* const state)
{
    lua::push(state, NN_CMSG_DATA(
        lua::get<nn_msghdr*>(state, 1)
    ));
    return 1;
}

int _NN_CMSG_SPACE(lua_State* const state)
{
    lua::push(state, NN_CMSG_SPACE(
        lua::get<size_t>(state, 1)
    ));
    return 1;
}

int _NN_CMSG_LEN(lua_State* const state)
{
    lua::push(state, NN_CMSG_LEN(
        lua::get<size_t>(state, 1)
    ));
    return 1;
}

int _nn_symbol(lua_State* const state)
{
    int value;
    auto name = nn_symbol(lua::get<int>(state, 1), &value);
    lua::push(state, name, value);
    return 2;
}

int void_tostring(lua_State* const state)
{
    lua::push(state,
        *static_cast<const char**>(lua_touserdata(state, 1))
    );
    return 1;
}

int _nn_freemsg(lua_State* const state)
{
    nn_freemsg(*reinterpret_cast<void**>(lua_touserdata(state, 1)));
    return 0;
}

int _nn_recv(lua_State* const state)
{
    void* buf = nullptr;
    lua::push(state, nn_recv(
        lua::get<int>(state, 1),
        &buf,
        NN_MSG,
        lua::get<int>(state, 4)
    ));

    lua::Construct<void*>::construct(state, buf);
    lua_getmetatable(state, -1);
    lua::index(state, -1)["__tostring"] = void_tostring;
    lua_pop(state, 1);

    return 2;
}

int _nn_send(lua_State* const state)
{
    if (lua_type(state, 2) == LUA_TUSERDATA) {
        lua::push(state, nn_send(
            lua::get<int>(state, 1),
            lua::get<void*>(state, 2),
            lua::get<size_t>(state, 3),
            lua::get<int>(state, 4)
        ));
        return 1;
    }
    lua::push(state, nn_send(
        lua::get<int>(state, 1),
        lua::get<const char*>(state, 2),
        lua::get<size_t>(state, 3),
        lua::get<int>(state, 4)
    ));
    return 1;
}

int _errno(lua_State* const state)
{
    lua::push(state, errno);
    return 1;
}

int luaopen_nanomsg(lua_State* const state)
{
    lua::thread env(state);

    env["errno"] = _errno;
    env["EADDRNOTAVAIL"] = EADDRNOTAVAIL;
    env["EADDRINUSE"] = EADDRINUSE;
    env["EAGAIN"] = EAGAIN;
    env["EBADF"] = EBADF;
    env["EFAULT"] = EFAULT;
    env["EFSM"] = EFSM;
    env["EINTR"] = EINTR;
    env["EINVAL"] = EINVAL;
    env["EMFILE"] = EMFILE;
    env["ENAMETOOLONG"] = ENAMETOOLONG;
    env["ENODEV"] = ENODEV;
    env["ENOMEM"] = ENOMEM;
    env["ENOTSUP"] = ENOTSUP;
    env["EPROTONOSUPPORT"] = EPROTONOSUPPORT;
    env["ETERM"] = ETERM;
    env["ETIMEDOUT"] = ETIMEDOUT;

    // http://nanomsg.org/v0.4/nn_allocmsg.3.html
    env["nn_allocmsg"] = nn_allocmsg;

    // http://nanomsg.org/v0.4/nn_bind.3.html
    env["nn_bind"] = nn_bind;
    env["NN_SOCKADDR_MAX"] = NN_SOCKADDR_MAX;

    // http://nanomsg.org/v0.4/nn_close.3.html
    env["nn_close"] = nn_close;

    // http://nanomsg.org/v0.4/nn_cmsg.3.html
    env["nn_cmsghdr"] = lua::value::table;
    env["nn_cmsghdr"]["new"] = nn_cmsghdr_new;

    env["NN_CMSG_FIRSTHDR"] = _NN_CMSG_FIRSTHDR;
    env["NN_CMSG_NXTHDR"] = _NN_CMSG_NXTHDR;
    env["NN_CMSG_DATA"] = _NN_CMSG_DATA;
    env["NN_CMSG_SPACE"] = _NN_CMSG_SPACE;
    env["NN_CMSG_LEN"] = _NN_CMSG_LEN;

    // http://nanomsg.org/v0.4/nn_connect.3.html
    env["nn_connect"] = nn_connect;

    // http://nanomsg.org/v0.4/nn_device.3.html
    env["nn_device"] = nn_device;

    // http://nanomsg.org/v0.4/nn_env.3.html
    // n/a

    // http://nanomsg.org/v0.4/nn_errno.3.html
    env["nn_errno"] = nn_errno;

    // http://nanomsg.org/v0.4/nn_freemsg.3.html
    env["nn_freemsg"] = _nn_freemsg;

    // http://nanomsg.org/v0.4/nn_getsockopt.3.html
    env["nn_getsockopt"] = nn_getsockopt;

    env["NN_DOMAIN"] = NN_DOMAIN;
    env["NN_PROTOCOL"] = NN_PROTOCOL;
    env["NN_LINGER"] = NN_LINGER;
    env["NN_SNDBUF"] = NN_SNDBUF;
    env["NN_RCVBUF"] = NN_RCVBUF;
    env["NN_SNDTIMEO"] = NN_SNDTIMEO;
    env["NN_RCVTIMEO"] = NN_RCVTIMEO;
    env["NN_RECONNECT_IVL"] = NN_RECONNECT_IVL;
    env["NN_RECONNECT_IVL_MAX"] = NN_RECONNECT_IVL_MAX;
    env["NN_SNDPRIO"] = NN_SNDPRIO;
    env["NN_RCVPRIO"] = NN_RCVPRIO;
    env["NN_IPV4ONLY"] = NN_IPV4ONLY;
    env["NN_SNDFD"] = NN_SNDFD;
    env["NN_RCVFD"] = NN_RCVFD;
    env["NN_SOCKET_NAME"] = NN_SOCKET_NAME;

    env["ENOPROTOOPT"] = ENOPROTOOPT;

    // http://nanomsg.org/v0.4/nn_poll.3.html
    env["nn_poll"] = nn_poll;

    env["nn_pollfd"] = lua::value::table;
    env["nn_pollfd"]["new"] = nn_pollfd_new;

    env["NN_POLLIN"] = NN_POLLIN;
    env["NN_POLLOUT"] = NN_POLLOUT;

    // http://nanomsg.org/v0.4/nn_reallocmsg.3.html
    env["nn_reallocmsg"] = nn_reallocmsg;

    // http://nanomsg.org/v0.4/nn_recvmsg.3.html
    env["nn_recvmsg"] = nn_recvmsg;

    env["nn_msghdr"] = lua::value::table;
    env["nn_msghdr"]["new"] = nn_msghdr_new;

    env["nn_iovec"] = lua::value::table;
    env["nn_iovec"]["new"] = nn_iovec_new;

    env["NN_DONTWAIT"] = NN_DONTWAIT;

    // http://nanomsg.org/v0.4/nn_recv.3.html
    env["nn_recv"] = _nn_recv;

    // http://nanomsg.org/v0.4/nn_send.3.html
    env["nn_send"] = _nn_send;

    // http://nanomsg.org/v0.4/nn_sendmsg.3.html
    env["nn_sendmsg"] = nn_sendmsg;

    // http://nanomsg.org/v0.4/nn_setsockopt.3.html
    env["nn_setsockopt"] = nn_setsockopt;

    env["NN_LINGER"] = NN_LINGER;
    env["NN_SNDBUF"] = NN_SNDBUF;
    env["NN_RCVBUF"] = NN_RCVBUF;
    env["NN_SNDTIMEO"] = NN_SNDTIMEO;
    env["NN_RCVTIMEO"] = NN_RCVTIMEO;
    env["NN_RECONNECT_IVL"] = NN_RECONNECT_IVL;
    env["NN_RECONNECT_IVL_MAX"] = NN_RECONNECT_IVL_MAX;
    env["NN_SNDPRIO"] = NN_SNDPRIO;
    env["NN_RCVPRIO"] = NN_RCVPRIO;
    env["NN_IPV4ONLY"] = NN_IPV4ONLY;
    env["NN_SOCKET_NAME"] = NN_SOCKET_NAME;

    // http://nanomsg.org/v0.4/nn_shutdown.3.html
    env["nn_shutdown"] = nn_shutdown;

    // http://nanomsg.org/v0.4/nn_socket.3.html
    env["nn_socket"] = nn_socket;

    env["AF_SP"] = AF_SP;
    env["AF_SP_RAW"] = AF_SP_RAW;

    // http://nanomsg.org/v0.4/nn_strerror.3.html
    env["nn_strerror"] = nn_strerror;

    // http://nanomsg.org/v0.4/nn_symbol.3.html
    env["nn_symbol"] = _nn_symbol;

    // http://nanomsg.org/v0.4/nn_symbol_info.3.html
    env["nn_symbol_info"] = nn_symbol_info;

    env["nn_symbol_properties"] = lua::value::table;
    env["nn_symbol_properties"]["new"] = nn_symbol_properties_new;

    env["NN_NS_NAMESPACE"] = NN_NS_NAMESPACE;
    env["NN_NS_VERSION"] = NN_NS_VERSION;
    env["NN_NS_DOMAIN"] = NN_NS_DOMAIN;
    env["NN_NS_TRANSPORT"] = NN_NS_TRANSPORT;
    env["NN_NS_PROTOCOL"] = NN_NS_PROTOCOL;
    env["NN_NS_OPTION_LEVEL"] = NN_NS_OPTION_LEVEL;
    env["NN_NS_SOCKET_OPTION"] = NN_NS_SOCKET_OPTION;
    env["NN_NS_TRANSPORT_OPTION"] = NN_NS_TRANSPORT_OPTION;
    env["NN_NS_OPTION_TYPE"] = NN_NS_OPTION_TYPE;
    env["NN_NS_FLAG"] = NN_NS_FLAG;
    env["NN_NS_ERROR"] = NN_NS_ERROR;
    env["NN_NS_LIMIT"] = NN_NS_LIMIT;

    env["NN_TYPE_NONE"] = NN_TYPE_NONE;
    env["NN_TYPE_INT"] = NN_TYPE_INT;
    env["NN_TYPE_STR"] = NN_TYPE_STR;

    env["NN_UNIT_NONE"] = NN_UNIT_NONE;
    env["NN_UNIT_BYTES"] = NN_UNIT_BYTES;
    env["NN_UNIT_MILLISECONDS"] = NN_UNIT_MILLISECONDS;
    env["NN_UNIT_PRIORITY"] = NN_UNIT_PRIORITY;
    env["NN_UNIT_BOOLEAN"] = NN_UNIT_BOOLEAN;

    // http://nanomsg.org/v0.4/nn_term.3.html
    env["term"] = nn_term;

    // http://nanomsg.org/v0.4/nn_bus.3.html
    env["NN_PROTO_BUS"] = NN_PROTO_BUS;

    env["NN_BUS"] = NN_BUS;

    // http://nanomsg.org/v0.4/nn_inproc.3.html
    env["NN_INPROC"] = NN_INPROC;

    // http://nanomsg.org/v0.4/nn_ipc.3.html
    env["NN_IPC"] = NN_IPC;

    // http://nanomsg.org/v0.4/nn_pair.3.html
    env["NN_PROTO_PAIR"] = NN_PROTO_PAIR;

    env["NN_PAIR"] = NN_PAIR;

    // http://nanomsg.org/v0.4/nn_pipeline.3.html
    env["NN_PROTO_PIPELINE"] = NN_PROTO_PIPELINE;

    env["NN_PUSH"] = NN_PUSH;
    env["NN_PULL"] = NN_PULL;

    // http://nanomsg.org/v0.4/nn_pubsub.3.html
    env["NN_PROTO_PUBSUB"] = NN_PROTO_PUBSUB;

    env["NN_PUB"] = NN_PUB;
    env["NN_SUB"] = NN_SUB;

    env["NN_SUB_SUBSCRIBE"] = NN_SUB_SUBSCRIBE;
    env["NN_SUB_UNSUBSCRIBE"] = NN_SUB_UNSUBSCRIBE;

    // http://nanomsg.org/v0.4/nn_reqrep.3.html
    env["NN_PROTO_REQREP"] = NN_PROTO_REQREP;

    env["NN_REQ"] = NN_REQ;
    env["NN_REP"] = NN_REP;

    env["NN_REQ_RESEND_IVL"] = NN_REQ_RESEND_IVL;

    // http://nanomsg.org/v0.4/nn_survey.3.html
    env["NN_PROTO_SURVEY"] = NN_PROTO_SURVEY;

    env["NN_SURVEYOR"] = NN_SURVEYOR;
    env["NN_RESPONDENT"] = NN_RESPONDENT;

    env["NN_SURVEYOR_DEADLINE"] = NN_SURVEYOR_DEADLINE;

    // http://nanomsg.org/v0.4/nn_tcp.3.html
    env["NN_TCP"] = NN_TCP;
    env["NN_TCP_NODELAY"] = NN_TCP_NODELAY;

    return 0;
}
