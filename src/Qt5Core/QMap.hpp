#ifndef luacxx_QMap_INCLUDED
#define luacxx_QMap_INCLUDED

#include "../stack.hpp"

#include <QMap>

namespace lua {

template <class K, class V>
void QMap_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
}

template <class K, class V>
struct Metatable<QMap<K, V>>
{
    static const userdata_type& info()
    {
        static userdata_type _info;
        if (!_info.has_name()) {
            std::string str("QMap<");
            str += Metatable<K>::info().name();
            str += ", ";
            str += Metatable<V>::info().name();
            str += ">";
            _info.set_name(str);
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, QMap<K, V>* const)
    {
        lua::QMap_metatable<K, V>(state, mt);
        return true;
    }
};

} // namespace lua

#endif // luacxx_QMap_INCLUDED
