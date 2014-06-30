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

#include "../luacxx/stack.hpp"
#include "../luacxx/reference.hpp"
#include "../luacxx/algorithm.hpp"

#include <QObject>

namespace lua {

class QEventFilter : public QObject
{

lua::reference _target;

public:

/*

=head4 filter = QEventFilter:new(delegate?)

Creates a new filter with the given delegate, if one is given.

*/

QEventFilter(lua_State* const state) :
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

void QEventFilter_metatable(const lua::index& mt);

template <>
struct Metatable<lua::QEventFilter>
{
    static constexpr const char* name = "QEventFilter";

    static bool metatable(const lua::index& mt, lua::QEventFilter* const)
    {
        lua::QEventFilter_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QEventFilter(lua_State* const);

#endif // LUACXX_QEVENTFILTER_INCLUDED

// vim: set ts=4 sw=4 :
