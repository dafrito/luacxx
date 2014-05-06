#ifndef LUA_CXX_ASSERT_HEADER
#define LUA_CXX_ASSERT_HEADER

#include "type.hpp"
#include "exception.hpp"
#include "push.hpp"

namespace lua {

void assert_type(const char* category, const lua::type& type, const lua::index& source);

} // namespace lua

#endif // LUA_CXX_ASSERT_HEADER
