#include "QDate.hpp"
#include "../thread.hpp"

#include "Qt.hpp"

int QDate_getDate(lua_State* const state)
{
    return 0;
}
int QDate_toString(lua_State* const state)
{
    return 0;
}
int QDate_isValid(lua_State* const state)
{
    return 0;
}
int QDate_weekNumber(lua_State* const state)
{
    return 0;
}

void lua::QDate_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["addDays"] = &QDate::addDays;
    mt["addMonths"] = &QDate::addMonths;
    mt["addYears"] = &QDate::addYears;
    mt["day"] = &QDate::day;
    mt["dayOfWeek"] = &QDate::dayOfWeek;
    mt["dayOfYear"] = &QDate::dayOfYear;
    mt["daysInMonth"] = &QDate::daysInMonth;
    mt["daysInYear"] = &QDate::daysInYear;
    mt["daysTo"] = &QDate::daysTo;
    mt["getDate"] = QDate_getDate;
    mt["isNull"] = &QDate::isNull;
    mt["isValid"] = QDate_isValid;
    mt["month"] = &QDate::month;
    mt["setDate"] = &QDate::setDate;
    mt["toJulianDay"] = &QDate::toJulianDay;
    mt["toString"] = QDate_toString;
    mt["weekNumber"] = QDate_weekNumber;
    mt["year"] = &QDate::year;
}

int QDate_new(lua_State* const state)
{
    if (lua_gettop(state) > 1) {
        // QDate(int y, int m, int d)
        lua::make<QDate>(state,
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4)
        );
    } else {
        // QDate()
        lua::make<QDate>(state);
    }

    return 1;
}

int QDate_longDayName(lua_State* const state)
{
    return 0;
}
int QDate_longMonthName(lua_State* const state)
{
    return 0;
}
int QDate_shortDayName(lua_State* const state)
{
    return 0;
}
int QDate_shortMonthName(lua_State* const state)
{
    return 0;
}

int QDate_fromString(lua_State* const state)
{
    return 0;
}
int QDate_isValid_static(lua_State* const state)
{
    return 0;
}

int luaopen_luacxx_QDate(lua_State* const state)
{
    lua::thread env(state);

    env["QDate"] = lua::value::table;
    env["QDate"]["new"] = QDate_new;
    auto t = env["QDate"];

    t["currentDate"] = &QDate::currentDate;
    t["fromJulianDay"] = &QDate::fromJulianDay;
    t["fromString"] = QDate_fromString;
    t["isLeapYear"] = &QDate::isLeapYear;
    t["isValid"] = QDate_isValid_static;
    t["longDayName"] = QDate_longDayName;
    t["longMonthName"] = QDate_longMonthName;
    t["shortDayName"] = QDate_shortDayName;
    t["shortMonthName"] = QDate_shortMonthName;

    // enum QDate::MonthNameType
    t["DateFormat"] = QDate::DateFormat;
    t["StandaloneFormat"] = QDate::StandaloneFormat;

    return 0;
}
