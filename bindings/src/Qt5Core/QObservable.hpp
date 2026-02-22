#ifndef LUACXX_QOBSERVABLE_INCLUDED
#define LUACXX_QOBSERVABLE_INCLUDED

#include "Qt5Core.hpp"

#include "../reference.hpp"
#include "../algorithm.hpp"
#include "../convert/string.hpp"
#include "QEvent.hpp"
#include <iostream>

namespace lua {

template <class Object>
class QObservable : public Object
{

lua::reference _target;

public:
    template <class... Args>
    QObservable(lua_State* const state, Args... args) :
        Object(args...),
        _target(state)
    {
    }

    bool event(QEvent* event) override
    {
        if (_target && lua::call<bool>(_target, event)) {
            return true;
        } else {
            return Object::event(event);
        }
    }

    void setDelegate(const lua::index& delegate)
    {
        _target = delegate;
    }
};

template <class T>
int QObservable_event(lua_State* const state)
{
    lua::get<QObservable<T>*>(state, 1)->setDelegate(lua::index(state, 2));
    return 0;
}

template <class T>
struct Metatable<QObservable<T>>
{
    static const userdata_type& info()
    {
        static userdata_type _info;
        if (!_info.has_name()) {
            std::string str("QObservable<");
            str += Metatable<T>::info().name();
            str += ">";
            _info.set_name(str);

            _info.add_cast<QObservable<T>>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int pos, QObservable<T>* const value)
    {
        lua::index mt(state, pos);

        mt["event"] = QObservable_event<T>;
        return lua::Metatable<T>::metatable(state, pos, value);
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QObservable(lua_State* const);

#endif // LUACXX_QOBSERVABLE_INCLUDED
