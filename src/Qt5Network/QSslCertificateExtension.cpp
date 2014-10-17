#include "QSslCertificateExtension.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QSslCertificateExtension>
#include "../Qt5Core/QVariant.hpp"

bool operator==(const QSslCertificateExtension& first, const QSslCertificateExtension& second)
{
    return first.oid() == second.oid();
}

void lua::QSslCertificateExtension_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["isCritical"] = &QSslCertificateExtension::isCritical;
    mt["isSupported"] = &QSslCertificateExtension::isSupported;
    mt["name"] = &QSslCertificateExtension::name;
    mt["oid"] = &QSslCertificateExtension::oid;
    mt["swap"] = &QSslCertificateExtension::swap;
    mt["value"] = &QSslCertificateExtension::value;
}

int QSslCertificateExtension_new(lua_State* const state)
{
    if (lua::size(state) == 1) {
        // QSslCertificateExtension()
        lua::make<QSslCertificateExtension>(state);
    } else {
        // QSslCertificateExtension(const QSslCertificateExtension & other)
        lua::make<QSslCertificateExtension>(state,
            lua::get<const QSslCertificateExtension&>(state, 2)
        );
    }

    return 1;
}

int luaopen_luacxx_QSslCertificateExtension(lua_State* const state)
{
    lua::thread env(state);

    env["QSslCertificateExtension"] = lua::value::table;
    env["QSslCertificateExtension"]["new"] = QSslCertificateExtension_new;
    auto t = env["QSslCertificateExtension"];

    return 0;
}
