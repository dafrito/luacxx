#include "QHttpMultiPart.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QByteArray.hpp"
#include "QHttpPart.hpp"

// http://qt-project.org/doc/qt-5/qhttpmultipart.html

namespace lua {

void QHttpMultiPart_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["append"] = &QHttpMultiPart::append;
    mt["boundary"] = &QHttpMultiPart::boundary;
    mt["setBoundary"] = &QHttpMultiPart::setBoundary;
    mt["setContentType"] = &QHttpMultiPart::setContentType;
}

} // namespace lua

int QHttpMultiPart_new(lua_State* const state)
{
    // QHttpMultiPart(QObject * parent = 0)
    // QHttpMultiPart(ContentType contentType, QObject * parent = 0)
    switch (lua_gettop(state)) {
    case 0:
        lua::push(state, new QHttpMultiPart);
        break;
    case 1:
        if (lua::is_type<QHttpMultiPart::ContentType>(state, 1)) {
            lua::push(state, new QHttpMultiPart(lua::get<QHttpMultiPart::ContentType>(state, 1)));
        } else {
            lua::push(state, new QHttpMultiPart(lua::get<QObject*>(state, 1)));
        }
        break;
    case 2:
    default:
        lua::push(state, new QHttpMultiPart(
            lua::get<QHttpMultiPart::ContentType>(state, 1),
            lua::get<QObject*>(state, 2)
        ));
        break;
    }
    lua::make<QHttpMultiPart>(state);

    return 1;
}

int luaopen_Qt5Network_QHttpMultiPart(lua_State* const state)
{
    lua::thread env(state);

    env["QHttpMultiPart"] = lua::value::table;
    env["QHttpMultiPart"]["new"] = QHttpMultiPart_new;
    auto t = env["QHttpMultiPart"];

    // enum QHttpMultiPart::ContentType
    t["MixedType"] = QHttpMultiPart::MixedType;
    t["RelatedType"] = QHttpMultiPart::RelatedType;
    t["FormDataType"] = QHttpMultiPart::FormDataType;
    t["AlternativeType"] = QHttpMultiPart::AlternativeType;

    return 0;
}
