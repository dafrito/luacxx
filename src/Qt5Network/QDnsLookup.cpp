#include "QDnsLookup.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QList.hpp"
#include "QDnsHostAddressRecord.hpp"
#include "QDnsDomainNameRecord.hpp"
#include "QDnsMailExchangeRecord.hpp"
#include "QDnsServiceRecord.hpp"
#include "QDnsTextRecord.hpp"
#include "QHostAddress.hpp"

// http://doc.qt.io/qt-5/qdnslookup.html

namespace lua {

void QDnsLookup_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    // FIXME (no equals methods) Qt5Network DNS classes
    //mt["canonicalNameRecords"] = &QDnsLookup::canonicalNameRecords;
    mt["error"] = &QDnsLookup::error;
    mt["errorString"] = &QDnsLookup::errorString;
    //mt["hostAddressRecords"] = &QDnsLookup::hostAddressRecords;
    mt["isFinished"] = &QDnsLookup::isFinished;
    //mt["mailExchangeRecords"] = &QDnsLookup::mailExchangeRecords;
    mt["name"] = &QDnsLookup::name;
    //mt["nameServerRecords"] = &QDnsLookup::nameServerRecords;
    mt["nameserver"] = &QDnsLookup::nameserver;
    //mt["pointerRecords"] = &QDnsLookup::pointerRecords;
    //mt["serviceRecords"] = &QDnsLookup::serviceRecords;
    mt["setName"] = &QDnsLookup::setName;
    mt["setNameserver"] = &QDnsLookup::setNameserver;
    mt["setType"] = &QDnsLookup::setType;
    //mt["textRecords"] = &QDnsLookup::textRecords;
    mt["type"] = &QDnsLookup::type;
}

} // namespace lua

int QDnsLookup_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        // QDnsLookup()
        lua::push(state, new QDnsLookup);
        break;
    case 1:
        // QDnsLookup(QObject * parent)
        lua::push(state, new QDnsLookup(
            lua::get<QObject*>(state, 1)
        ));
        break;
    case 2:
        // QDnsLookup(Type type, const QString & name)
        lua::push(state, new QDnsLookup(
            lua::get<QDnsLookup::Type>(state, 1),
            lua::get<QString>(state, 2)
        ));
        break;
    case 3:
        if (lua::is_type<QHostAddress>(state, 3)) {
            // QDnsLookup(Type type, const QString & name, const QHostAddress & nameserver)
            lua::push(state, new QDnsLookup(
                lua::get<QDnsLookup::Type>(state, 1),
                lua::get<QString>(state, 2),
                lua::get<const QHostAddress&>(state, 3)
            ));
        } else {
            // QDnsLookup(Type type, const QString & name, QObject * parent = 0)
            lua::push(state, new QDnsLookup(
                lua::get<QDnsLookup::Type>(state, 1),
                lua::get<QString>(state, 2),
                lua::get<QObject*>(state, 3)
            ));
        }
        break;
    case 4:
    default:
        // QDnsLookup(Type type, const QString & name, const QHostAddress & nameserver, QObject * parent = 0)
        lua::push(state, new QDnsLookup(
            lua::get<QDnsLookup::Type>(state, 1),
            lua::get<QString>(state, 2),
            lua::get<const QHostAddress&>(state, 3),
            lua::get<QObject*>(state, 4)
        ));
    }

    return 1;
}

int luaopen_Qt5Network_QDnsLookup(lua_State* const state)
{
    lua::thread env(state);

    env["QDnsLookup"] = lua::value::table;
    env["QDnsLookup"]["new"] = QDnsLookup_new;
    auto t = env["QDnsLookup"];

    // enum QDnsLookup::Error
    t["NoError"] = QDnsLookup::NoError;
    t["ResolverError"] = QDnsLookup::ResolverError;
    t["OperationCancelledError"] = QDnsLookup::OperationCancelledError;
    t["InvalidRequestError"] = QDnsLookup::InvalidRequestError;
    t["InvalidReplyError"] = QDnsLookup::InvalidReplyError;
    t["ServerFailureError"] = QDnsLookup::ServerFailureError;
    t["ServerRefusedError"] = QDnsLookup::ServerRefusedError;
    t["NotFoundError"] = QDnsLookup::NotFoundError;

    // enum QDnsLookup::Type
    t["A"] = QDnsLookup::A;
    t["AAAA"] = QDnsLookup::AAAA;
    t["ANY"] = QDnsLookup::ANY;
    t["CNAME"] = QDnsLookup::CNAME;
    t["MX"] = QDnsLookup::MX;
    t["NS"] = QDnsLookup::NS;
    t["PTR"] = QDnsLookup::PTR;
    t["SRV"] = QDnsLookup::SRV;
    t["TXT"] = QDnsLookup::TXT;

    return 0;
}
