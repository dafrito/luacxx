#ifndef luacxx_std_vector_INCLUDED
#define luacxx_std_vector_INCLUDED

#include "../convert/callable.hpp"

#include <vector>

namespace lua {

template <class T>
void std_vector_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
}

template <class T>
struct Metatable<std::vector<T>>
{
    static const userdata_type& info()
    {
        static userdata_type _info("std::vector<?>");
        std::string str("std::vector<");
        str += Metatable<T>::info().name();
        str += ">";
        _info.set_name(str);
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, std::vector<T>* const)
    {
        lua::std_vector_metatable<T>(state, mt);
        return true;
    }
};

}; // namespace lua

#endif // luacxx_std_vector_INCLUDED

