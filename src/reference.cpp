#include "luacxx/reference.hpp"
#include "luacxx/thread.hpp"

lua::reference::reference(lua::thread& env) :
    _state(env.state()),
    _id(LUA_NOREF)
{
}
