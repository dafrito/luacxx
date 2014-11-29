#include "QSqlField.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QVariant.hpp"
#include "../Qt5Core/QString.hpp"

namespace lua {

void QSqlField_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["clear"] = &QSqlField::clear;
    mt["defaultValue"] = &QSqlField::defaultValue;
    mt["isAutoValue"] = &QSqlField::isAutoValue;
    mt["isGenerated"] = &QSqlField::isGenerated;
    mt["isNull"] = &QSqlField::isNull;
    mt["isReadOnly"] = &QSqlField::isReadOnly;
    mt["isValid"] = &QSqlField::isValid;
    mt["length"] = &QSqlField::length;
    mt["name"] = &QSqlField::name;
    mt["precision"] = &QSqlField::precision;
    mt["requiredStatus"] = &QSqlField::requiredStatus;
    mt["setAutoValue"] = &QSqlField::setAutoValue;
    mt["setDefaultValue"] = &QSqlField::setDefaultValue;
    mt["setGenerated"] = &QSqlField::setGenerated;
    mt["setLength"] = &QSqlField::setLength;
    mt["setName"] = &QSqlField::setName;
    mt["setPrecision"] = &QSqlField::setPrecision;
    mt["setReadOnly"] = &QSqlField::setReadOnly;
    mt["setRequired"] = &QSqlField::setRequired;
    mt["setRequiredStatus"] = &QSqlField::setRequiredStatus;
    mt["setType"] = &QSqlField::setType;
    mt["setValue"] = &QSqlField::setValue;
    mt["type"] = &QSqlField::type;
    mt["value"] = &QSqlField::value;
}

} // namespace lua

int QSqlField_new(lua_State* const state)
{
    if (lua::is_type<QSqlField>(state, 1)) {
        // QSqlField(const QSqlField & other)
        lua::make<QSqlField>(state, lua::get<const QSqlField&>(state, 1));
    } else {
        switch (lua_gettop(state)) {
        case 0:
            // QSqlField()
            lua::make<QSqlField>(state);
            break;
        case 1:
            // QSqlField(const QString & fieldName)
            lua::make<QSqlField>(state,
                lua::get<QString>(state, 1)
            );
            break;
        case 2:
        default:
            // QSqlField(const QString & fieldName, QVariant::Type type)
            lua::make<QSqlField>(state,
                lua::get<QString>(state, 1),
                lua::get<QVariant::Type>(state, 2)
            );
            break;
        }
    }

    return 1;
}

int luaopen_Qt5Sql_QSqlField(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlField"] = lua::value::table;
    env["QSqlField"]["new"] = QSqlField_new;
    auto t = env["QSqlField"];

    // enum QSqlField::RequiredStatus
    t["Required"] = QSqlField::Required;
    t["Optional"] = QSqlField::Optional;
    t["Unknown"] = QSqlField::Unknown;

    return 0;
}
