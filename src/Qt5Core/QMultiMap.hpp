#ifndef luacxx_QMultiMap_INCLUDED
#define luacxx_QMultiMap_INCLUDED

#include "../stack.hpp"

#include <QMultiMap>

namespace lua {

template <class K, class V>
void QMultiMap_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
}

template <class K, class V>
struct Metatable<QMultiMap<K, V>>
{
    static const userdata_type& info()
    {
        static userdata_type _info;
        if (!_info.has_name()) {
            std::string str("QMultiMap<");
            str += Metatable<K>::info().name();
            str += ", ";
            str += Metatable<V>::info().name();
            str += ">";
            _info.set_name(str);
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, QMultiMap<K, V>* const)
    {
        lua::QMultiMap_metatable<K, V>(state, mt);
        return true;
    }
};

}; // namespace lua

#endif // luacxx_QMultiMap_INCLUDED
