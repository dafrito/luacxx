#include "QDateTime.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QDate.hpp"
#include "QTime.hpp"
#include "QTimeZone.hpp"
#include "Qt.hpp"

int QDateTime_toString(lua_State* const state)
{
    return 0;
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
    // QDateTime()
    // QDateTime(const QDate & date)
    // QDateTime(const QDate & date, const QTime & time, Qt::TimeSpec spec = Qt::LocalTime)
    // QDateTime(const QDate & date, const QTime & time, Qt::TimeSpec spec, int offsetSeconds)
    // QDateTime(const QDate & date, const QTime & time, const QTimeZone & timeZone)
    // QDateTime(const QDateTime & other)
    lua::make<QDateTime>(state);
    // TODO Set up object-specific methods

    return 1;
}

int QDateTime_fromMSecsSinceEpoch(lua_State* const state)
{
    return 0;
}
int QDateTime_fromString(lua_State* const state)
{
    return 0;
}
int QDateTime_fromTime_t(lua_State* const state)
{
    return 0;
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
