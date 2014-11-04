#include "QEventFilter.hpp"
#include "QObject.hpp"
#include "QEvent.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

bool QEventFilter::eventFilter(QObject* watched, QEvent* event)
{
    if (!_target.type().function()) {
        return false;
    }
    return lua::call<bool>(_target, watched, event);
}

void QEventFilter::setDelegate(const lua::index& delegate)
{
    lua::assert_type("QEventFilter:setDelegate", lua::type::function, delegate);
    _target = delegate;
}

int QEventFilter_setDelegate(lua_State* const state)
{
    auto filter = lua::get<QEventFilter*>(state, 1);
    filter->setDelegate(lua::index(state, 2));

    return 0;
}

void lua::QEventFilter_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["setDelegate"] = QEventFilter_setDelegate;
}

int QEventFilter_new(lua_State* const state)
{
    lua::push(state, new QEventFilter(state));
    return 1;
}

int luaopen_Qt5Core_QEventFilter(lua_State* const state)
{
    lua::thread env(state);

    env["QEventFilter"] = lua::value::table;
    env["QEventFilter"]["new"] = QEventFilter_new;

    return 0;
}

// vim: set ts=4 sw=4 :
