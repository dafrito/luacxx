#ifndef LUACXX_QEVENTFILTER_INCLUDED
#define LUACXX_QEVENTFILTER_INCLUDED

/*

=head1 NAME

#include <luacxx/Qt5Core/QEventFilter.hpp> - forwards a QObject's events to a Lua delegate

=head1 SYNOPSIS

    require "luacxx.QEventFilter";

    local supported_events = {
        resize = function(width, height)

        end,
    };

    local filter = QEventFilter:new(function(event)
        local event_type = event:type();
        local handler = supported_events[event_type];
        if handler then
            -- Return false if you want Qt to have a look, too.
            return handler(...);
        end;

        -- Didn't handle it, so let Qt know.
        return false;
    end);

=head1 DESCRIPTION

*/

#include "Qt5Core.hpp"

#include "../reference.hpp"
#include "../algorithm.hpp"

#include <QObject>

class QEventFilter : public QObject
{

lua::reference _target;

public:

/*

=head4 filter = QEventFilter:new(delegate?)

Creates a new filter with the given delegate, if one is given.

*/

QEventFilter(lua_State* const state) :
    QObject(),
    _target(state)
{
}

QEventFilter(lua_State* const state, QObject* const parent) :
    QObject(parent),
    _target(state)
{
}

/*

=head4 function QEventFilter:setDelegate(callable)

Sets the given callable as the delegate for future events received
by this filter.

*/

void setDelegate(const lua::index& source);

bool eventFilter(QObject* watched, QEvent* event);

}; // class QEventFilter

LUA_METATABLE_BUILT(QEventFilter);

extern "C" int luaopen_Qt5Core_QEventFilter(lua_State* const);

#endif // LUACXX_QEVENTFILTER_INCLUDED

// vim: set ts=4 sw=4 :
