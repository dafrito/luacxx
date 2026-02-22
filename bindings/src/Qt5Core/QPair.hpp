#ifndef luacxx_QPair_INCLUDED
#define luacxx_QPair_INCLUDED

#include "Qt5Core.hpp"

#include <QPair>

#include "convert/const_char_p.hpp"

namespace lua {

template <class K, class V>
void QPair_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

    mt["__index"] = lua::callable([](lua_State* const state) {
        auto self = lua::get<QPair<K, V>*>(state, 1);
        auto name = lua::get<std::string>(state, 2);
        if (name == "first") {
            lua::push(state, self->first);
        } else if (name == "second") {
            lua::push(state, self->second);
        } else {
            lua_pushnil(state);
        }
        return 1;
    });
}

template <class K, class V>
struct Metatable<QPair<K, V>>
{
    static const userdata_type& info()
    {
        static userdata_type _info;
        if (!_info.has_name()) {
            std::string str("QPair<");
            str += Metatable<K>::info().name();
            str += ", ";
            str += Metatable<V>::info().name();
            str += ">";
            _info.set_name(str);

            _info.add_cast<QPair<K, V>>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, const QPair<K, V>* const)
    {
        lua::QPair_metatable<K, V>(state, mt);
        return true;
    }
};

}; // namespace lua

#endif // luacxx_QPair_INCLUDED
