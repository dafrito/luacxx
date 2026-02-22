#include "QSqlError.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"

namespace lua {

void QSqlError_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["databaseText"] = &QSqlError::databaseText;
    mt["driverText"] = &QSqlError::driverText;
    mt["isValid"] = &QSqlError::isValid;
    mt["nativeErrorCode"] = &QSqlError::nativeErrorCode;
    mt["text"] = &QSqlError::text;
    mt["type"] = &QSqlError::type;
}

} // namespace lua

int QSqlError_new(lua_State* const state)
{
    if (lua::is_type<QSqlError>(state, 1)) {
        //  QSqlError(const QSqlError & other)
        lua::make<QSqlError>(state,
            lua::get<const QSqlError&>(state, 1)
        );
    } else {
        switch (lua_gettop(state)) {
        case 0:
            lua::make<QSqlError>(state);
            break;
        case 1:
            lua::make<QSqlError>(state,
                lua::get<QString>(state, 1)
            );
            break;
        case 2:
            lua::make<QSqlError>(state,
                lua::get<QString>(state, 1),
                lua::get<QString>(state, 2)
            );
            break;
        case 3:
        default:
            // QSqlError(const QString & driverText = QString(), const QString & databaseText = QString(), ErrorType type = NoError, const QString & code = QString())
            lua::make<QSqlError>(state,
                lua::get<QString>(state, 1),
                lua::get<QString>(state, 2),
                lua::get<QSqlError::ErrorType>(state, 3),
                lua::get<QString>(state, 4)
            );
            break;
        }
    }

    return 1;
}

int luaopen_Qt5Sql_QSqlError(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlError"] = lua::value::table;
    env["QSqlError"]["new"] = QSqlError_new;
    auto t = env["QSqlError"];

    // enum QSqlError::ErrorType
    t["NoError"] = QSqlError::NoError;
    t["ConnectionError"] = QSqlError::ConnectionError;
    t["StatementError"] = QSqlError::StatementError;
    t["TransactionError"] = QSqlError::TransactionError;
    t["UnknownError"] = QSqlError::UnknownError;

    return 0;
}
