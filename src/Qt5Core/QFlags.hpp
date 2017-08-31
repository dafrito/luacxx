#ifndef luacxx_QFlags_INCLUDED
#define luacxx_QFlags_INCLUDED

#include "Qt5Core.hpp"
#include "../index.hpp"

#include <QFlags>

namespace lua {

template <class T>
int QFlags_bor(lua_State* const state)
{
    auto self = lua::get<QFlags<T>>(state, 1);
    self |= lua::get<T>(state, 2);
    lua::push(state, self);
    return 1;
}

template <class T>
int QFlags_bxor(lua_State* const state)
{
    auto self = lua::get<QFlags<T>>(state, 1);
    self ^= lua::get<T>(state, 2);
    lua::push(state, self);
    return 1;
}

template <class T>
int QFlags_band(lua_State* const state)
{
    auto self = lua::get<QFlags<T>>(state, 1);
    self &= lua::get<T>(state, 2);
    lua::push(state, self);
    return 1;
}

template <class T>
int QFlags_bnot(lua_State* const state)
{
    auto self = lua::get<QFlags<T>&>(state, 1);
    lua::push(state, ~self);
    return 1;
}

template <class T>
int QFlags_value(lua_State* const state)
{
    auto& self = lua::get<QFlags<T>&>(state, 1);
    lua::push(state, static_cast<typename QFlags<T>::Int>(self));
    return 1;
}

template <class T>
int QFlags_test(lua_State* const state)
{
    auto& self = lua::get<QFlags<T>&>(state, 1);
    lua::push(state, !(!self));
    return 1;
}

template <class T>
void QFlags_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

    mt["__band"] = QFlags_band<T>;
    mt["__bor"] = QFlags_bor<T>;
    mt["__bxor"] = QFlags_bxor<T>;
    mt["__bnot"] = QFlags_bnot<T>;
    mt["value"] = QFlags_value<T>;
    mt["testFlag"] = &QFlags<T>::testFlag;

    // Equivalent to !!flag
    mt["testAny"] = QFlags_test<T>;
}

template <class T>
int QFlags_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::make<QFlags<T>>(state);
    } else if (lua::is_type<QFlags<T>>(state, 1)) {
        lua::make<QFlags<T>>(state, lua::get<const QFlags<T>&>(state, 1));
    } else if (lua::is_type<T>(state, 1)) {
        lua::make<QFlags<T>>(state, lua::get<T>(state, 1));
    }
    return 1;
}

template <class T>
struct Metatable<QFlags<T>>
{
    static const userdata_type& info()
    {
        static userdata_type _info;
        if (!_info.has_name()) {
            std::string str("QFlags<");
            str += Metatable<T>::info().name();
            str += ">";
            _info.set_name(str);

            _info.add_cast<QFlags<T>>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, QFlags<T>* const)
    {
        QFlags_metatable<T>(state, mt);
        return true;
    }
};

};

extern "C" int luaopen_Qt5Core_QFlags(lua_State* const);

#endif // luacxx_QFlags_INCLUDED
