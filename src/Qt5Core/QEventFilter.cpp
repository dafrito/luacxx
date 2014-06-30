#include "QEventFilter.hpp"
#include "QObject.hpp"
#include "QEvent.hpp"
#include "../luacxx/convert/callable.hpp"
#include "../luacxx/thread.hpp"

bool lua::QEventFilter::eventFilter(QObject* watched, QEvent* event)
{
    if (!_target.type().function()) {
        return false;
    }
    return lua::call<bool>(_target, watched, event);
}

void lua::QEventFilter::setDelegate(const lua::index& delegate)
{
    lua::assert_type("QEventFilter:setDelegate", lua::type::function, delegate);
    _target = delegate;
}

int QEventFilter_setDelegate(lua_State* const state)
{
    auto filter = lua::get<lua::QEventFilter*>(state, 1);
    filter->setDelegate(lua::index(state, 2));

    return 0;
}

void lua::QEventFilter_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);
    mt["setDelegate"] = QEventFilter_setDelegate;
}

int QEventFilter_new(lua_State* const state)
{
    lua::make<lua::QEventFilter>(state, state);
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
