#include "QSql.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QFlags.hpp"

int luaopen_Qt5Sql_QSql(lua_State* const state)
{
    lua::thread env(state);

    env["QSql"] = lua::value::table;
    auto t = env["QSql"];

    // enum QSql::Location
    t["BeforeFirstRow"] = QSql::BeforeFirstRow;
    t["AfterLastRow"] = QSql::AfterLastRow;

    // enum QSql::NumericalPrecisionPolicy
    t["LowPrecisionInt32"] = QSql::LowPrecisionInt32;
    t["LowPrecisionInt64"] = QSql::LowPrecisionInt64;
    t["LowPrecisionDouble"] = QSql::LowPrecisionDouble;
    t["HighPrecision"] = QSql::HighPrecision;

    // enum QSql::ParamTypeFlag
    t["ParamType"] = lua::QFlags_new<QSql::ParamType>;

    t["In"] = QSql::In;
    t["Out"] = QSql::Out;
    t["InOut"] = QSql::InOut;
    t["Binary"] = QSql::Binary;

    // enum QSql::TableType
    t["Tables"] = QSql::Tables;
    t["SystemTables"] = QSql::SystemTables;
    t["Views"] = QSql::Views;
    t["AllTables"] = QSql::AllTables;

    return 0;
}
