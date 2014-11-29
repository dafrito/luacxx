#ifndef luacxx_QHash_INCLUDED
#define luacxx_QHash_INCLUDED

#include "../stack.hpp"

#include <QHash>

namespace lua {

template <class K, class V>
void QHash_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
}

template <class K, class V>
struct Metatable<QHash<K, V>>
{
    static const userdata_type& info()
    {
        static userdata_type _info;
        if (!_info.has_name()) {
            std::string str("QHash<");
            str += Metatable<K>::info().name();
            str += ", ";
            str += Metatable<V>::info().name();
            str += ">";
            _info.set_name(str);
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, QHash<K, V>* const)
    {
        lua::QHash_metatable<K, V>(state, mt);
        return true;
    }
};

} // namespace lua

extern "C" int luaopen_Qt5Core_QHash(lua_State* const);

#endif // luacxx_QHash_INCLUDED
