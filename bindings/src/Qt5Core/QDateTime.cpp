#include "QDateTime.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QDate.hpp"
#include "QTime.hpp"
#include "QTimeZone.hpp"
#include "Qt.hpp"

// https://qt-project.org/doc/qt-5/qdatetime.html

int QDateTime_toString(lua_State* const state)
{
    auto self = lua::get<QDateTime*>(state, 1);
    if (lua_gettop(state) == 1) {
        //  QString     toString() const
        lua::push(state, self->toString());
    } else if (lua::is_type<Qt::DateFormat>(state, 2)) {
        //  QString     toString(Qt::DateFormat format = Qt::TextDate) const
        lua::push(state, self->toString(
            lua::get<Qt::DateFormat>(state, 2)
        ));
    } else {
        //  QString     toString(const QString & format) const
        lua::push(state, self->toString(
            lua::get<QString>(state, 2)
        ));
    }
    return 1;
}

void lua::QDateTime_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

    mt["addDays"] = &QDateTime::addDays;
    mt["addMSecs"] = &QDateTime::addMSecs;
    mt["addMonths"] = &QDateTime::addMonths;
    mt["addSecs"] = &QDateTime::addSecs;
    mt["addYears"] = &QDateTime::addYears;
    mt["date"] = &QDateTime::date;
    mt["daysTo"] = &QDateTime::daysTo;
    mt["isDaylightTime"] = &QDateTime::isDaylightTime;
    mt["isNull"] = &QDateTime::isNull;
    mt["isValid"] = &QDateTime::isValid;
    mt["msecsTo"] = &QDateTime::msecsTo;
    mt["offsetFromUtc"] = &QDateTime::offsetFromUtc;
    mt["secsTo"] = &QDateTime::secsTo;
    mt["setDate"] = &QDateTime::setDate;
    mt["setMSecsSinceEpoch"] = &QDateTime::setMSecsSinceEpoch;
    mt["setOffsetFromUtc"] = &QDateTime::setOffsetFromUtc;
    mt["setTime"] = &QDateTime::setTime;
    mt["setTimeSpec"] = &QDateTime::setTimeSpec;
    mt["setTimeZone"] = &QDateTime::setTimeZone;
    mt["setTime_t"] = &QDateTime::setTime_t;
    mt["swap"] = &QDateTime::swap;
    mt["time"] = &QDateTime::time;
    mt["timeSpec"] = &QDateTime::timeSpec;
    mt["timeZone"] = &QDateTime::timeZone;
    mt["timeZoneAbbreviation"] = &QDateTime::timeZoneAbbreviation;
    mt["toLocalTime"] = &QDateTime::toLocalTime;
    mt["toMSecsSinceEpoch"] = &QDateTime::toMSecsSinceEpoch;
    mt["toOffsetFromUtc"] = &QDateTime::toOffsetFromUtc;
    mt["toString"] = QDateTime_toString;
    mt["toTimeSpec"] = &QDateTime::toTimeSpec;
    mt["toTimeZone"] = &QDateTime::toTimeZone;
    mt["toTime_t"] = &QDateTime::toTime_t;
    mt["toUTC"] = &QDateTime::toUTC;
}

int QDateTime_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        // QDateTime()
        lua::make<QDateTime>(state);
        break;
    case 1:
        if (lua::is_type<QDateTime>(state, 1)) {
            // QDateTime(const QDateTime & other)
            // QDateTime(const QDate & date)
            lua::make<QDateTime>(state,
                lua::get<const QDateTime&>(state, 1)
            );
        } else {
            // QDateTime(const QDate & date)
            lua::make<QDateTime>(state,
                lua::get<const QDate&>(state, 1)
            );
        }
        break;
    case 2:
        // QDateTime(const QDate & date, const QTime & time)
        lua::make<QDateTime>(state,
            lua::get<const QDate&>(state, 1),
            lua::get<const QTime&>(state, 2)
        );
        break;
    case 3:
        if (lua::is_type<Qt::TimeSpec>(state, 3)) {
            // QDateTime(const QDate & date, const QTime & time, Qt::TimeSpec spec)
            lua::make<QDateTime>(state,
                lua::get<const QDate&>(state, 1),
                lua::get<const QTime&>(state, 2),
                lua::get<Qt::TimeSpec>(state, 3)
            );
        } else {
            // QDateTime(const QDate & date, const QTime & time, const QTimeZone & timeZone)
            lua::make<QDateTime>(state,
                lua::get<const QDate&>(state, 1),
                lua::get<const QTime&>(state, 2),
                lua::get<const QTimeZone&>(state, 3)
            );
        }
        break;
    case 4:
    default:
        // QDateTime(const QDate & date, const QTime & time, Qt::TimeSpec spec, int offsetSeconds)
        lua::make<QDateTime>(state,
            lua::get<const QDate&>(state, 1),
            lua::get<const QTime&>(state, 2),
            lua::get<Qt::TimeSpec>(state, 3),
            lua::get<int>(state, 4)
        );
        break;
    }

    return 1;
}

int QDateTime_fromMSecsSinceEpoch(lua_State* const state)
{
    if (lua_gettop(state) == 1) {
        //  QDateTime   fromMSecsSinceEpoch(qint64 msecs)
        lua::push(state, QDateTime::fromMSecsSinceEpoch(
            lua::get<qint64>(state, 1)
        ));
    } else if (lua::is_type<QTimeZone>(state, 2)) {
        //  QDateTime   fromMSecsSinceEpoch(qint64 msecs, const QTimeZone & timeZone)
        lua::push(state, QDateTime::fromMSecsSinceEpoch(
            lua::get<qint64>(state, 1),
            lua::get<const QTimeZone&>(state, 2)
        ));
    } else if (lua_gettop(state) == 2) {
        //  QDateTime   fromMSecsSinceEpoch(qint64 msecs, Qt::TimeSpec spec)
        lua::push(state, QDateTime::fromMSecsSinceEpoch(
            lua::get<qint64>(state, 1),
            lua::get<Qt::TimeSpec&>(state, 2)
        ));
    } else {
        //  QDateTime   fromMSecsSinceEpoch(qint64 msecs, Qt::TimeSpec spec, int offsetSeconds)
        lua::push(state, QDateTime::fromMSecsSinceEpoch(
            lua::get<qint64>(state, 1),
            lua::get<Qt::TimeSpec&>(state, 2),
            lua::get<int>(state, 3)
        ));
    }
    return 1;
}

int QDateTime_fromString(lua_State* const state)
{
    if (lua_gettop(state) == 1) {
        // QDateTime    fromString(const QString & string)
        lua::push(state, QDateTime::fromString(
            lua::get<QString>(state, 1)
        ));
    } else if (lua::is_type<Qt::DateFormat>(state, 2)) {
        // QDateTime    fromString(const QString & string, Qt::DateFormat format
        lua::push(state, QDateTime::fromString(
            lua::get<QString>(state, 1),
            lua::get<Qt::DateFormat>(state, 2)
        ));
    } else {
        // QDateTime    fromString(const QString & string, const QString & format)
        lua::push(state, QDateTime::fromString(
            lua::get<QString>(state, 1),
            lua::get<QString>(state, 2)
        ));
    }
    return 1;
}
int QDateTime_fromTime_t(lua_State* const state)
{
    if (lua_gettop(state) == 1) {
        // QDateTime    fromTime_t(uint seconds)
        lua::push(state, QDateTime::fromTime_t(
            lua::get<uint>(state, 1)
        ));
    } else if (lua_gettop(state) == 3) {
        // QDateTime    fromTime_t(uint seconds, Qt::TimeSpec spec, int offsetSeconds)
        lua::push(state, QDateTime::fromTime_t(
            lua::get<uint>(state, 1),
            lua::get<Qt::TimeSpec>(state, 2),
            lua::get<int>(state, 3)
        ));
    } else if (lua::is_type<Qt::TimeSpec>(state, 2)) {
        // QDateTime    fromTime_t(uint seconds, Qt::TimeSpec spec)
        lua::push(state, QDateTime::fromTime_t(
            lua::get<uint>(state, 1),
            lua::get<Qt::TimeSpec>(state, 2)
        ));
    } else {
        // QDateTime    fromTime_t(uint seconds, const QTimeZone & timeZone)
        lua::push(state, QDateTime::fromTime_t(
            lua::get<uint>(state, 1),
            lua::get<const QTimeZone&>(state, 2)
        ));
    }
    return 1;
}

int luaopen_Qt5Core_QDateTime(lua_State* const state)
{
    lua::thread env(state);

    env["QDateTime"] = lua::value::table;
    env["QDateTime"]["new"] = QDateTime_new;
    auto t = env["QDateTime"];

    t["currentDateTime"] = &QDateTime::currentDateTime;
    t["currentDateTimeUtc"] = &QDateTime::currentDateTimeUtc;
    t["currentMSecsSinceEpoch"] = &QDateTime::currentMSecsSinceEpoch;
    t["fromMSecsSinceEpoch"] = QDateTime_fromMSecsSinceEpoch;
    t["fromString"] = QDateTime_fromString;
    t["fromTime_t"] = QDateTime_fromTime_t;

    return 0;
}
