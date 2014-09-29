#ifndef LUACXX_NANOMSG_INCLUDED
#define LUACXX_NANOMSG_INCLUDED

#include "stack.hpp"
#include "algorithm.hpp"
#include "convert/numeric.hpp"
#include "convert/callable.hpp"
#include "convert/string.hpp"

#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

/*

nanomsg includes the following copying notice:

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom
the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.

"nanomsg" is a trademark of 250bpm s.r.o.

As much as possible, this Luacxx binding uses the same license as nanomsg
itself.

*/

namespace lua {

void nn_symbol_properties_metatable(const lua::index& mt);

template <>
struct Metatable<nn_symbol_properties>
{
    static constexpr const char* name = "nn_symbol_properties";

    static bool metatable(const lua::index& mt, nn_symbol_properties* const)
    {
        lua::nn_symbol_properties_metatable(mt);
        return true;
    }
};

void nn_req_handle_metatable(const lua::index& mt);

template <>
struct Metatable<nn_req_handle>
{
    static constexpr const char* name = "nn_req_handle";

    static bool metatable(const lua::index& mt, nn_req_handle* const)
    {
        lua::nn_req_handle_metatable(mt);
        return true;
    }
};

void nn_pollfd_metatable(const lua::index& mt);

template <>
struct Metatable<nn_pollfd>
{
    static constexpr const char* name = "nn_pollfd";

    static bool metatable(const lua::index& mt, nn_pollfd* const)
    {
        lua::nn_pollfd_metatable(mt);
        return true;
    }
};

void nn_msghdr_metatable(const lua::index& mt);

template <>
struct Metatable<nn_msghdr>
{
    static constexpr const char* name = "nn_msghdr";

    static bool metatable(const lua::index& mt, nn_msghdr* const)
    {
        lua::nn_msghdr_metatable(mt);
        return true;
    }
};

void nn_cmsghdr_metatable(const lua::index& mt);

template <>
struct Metatable<nn_cmsghdr>
{
    static constexpr const char* name = "nn_cmsghdr";

    static bool metatable(const lua::index& mt, nn_cmsghdr* const)
    {
        lua::nn_cmsghdr_metatable(mt);
        return true;
    }
};

void nn_iovec_metatable(const lua::index& mt);

template <>
struct Metatable<nn_iovec>
{
    static constexpr const char* name = "nn_iovec";

    static bool metatable(const lua::index& mt, nn_iovec* const)
    {
        lua::nn_iovec_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_nanomsg(lua_State* const);

#endif // LUACXX_NANOMSG_INCLUDED
