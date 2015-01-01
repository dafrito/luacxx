#include "QInputMethodEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QList.hpp"

// http://qt-project.org/doc/qt-5/qinputmethodevent.html

int QInputMethodEvent_setCommitString(lua_State* const state)
{
    auto self = lua::get<QInputMethodEvent*>(state, 1);

    // void     setCommitString(const QString & commitString, int replaceFrom = 0, int replaceLength = 0)
    switch (lua_gettop(state)) {
    case 2:
        self->setCommitString(
            lua::get<QString>(state, 2)
        );
        break;
    case 3:
        self->setCommitString(
            lua::get<QString>(state, 2),
            lua::get<int>(state, 3)
        );
        break;
    case 4:
    default:
        self->setCommitString(
            lua::get<QString>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4)
        );
        break;
    }

    return 1;
}

namespace lua {

void QInputMethodEvent_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO mt["attributes"] = &QInputMethodEvent::attributes;
    mt["commitString"] = &QInputMethodEvent::commitString;
    mt["preeditString"] = &QInputMethodEvent::preeditString;
    mt["replacementLength"] = &QInputMethodEvent::replacementLength;
    mt["replacementStart"] = &QInputMethodEvent::replacementStart;
    mt["setCommitString"] = QInputMethodEvent_setCommitString;
}

} // namespace lua

int QInputMethodEvent_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        // QInputMethodEvent()
        lua::make<QInputMethodEvent>(state);
        break;
    case 1:
        // QInputMethodEvent(const QInputMethodEvent & other)
        lua::make<QInputMethodEvent>(state,
            lua::get<const QInputMethodEvent&>(state, 1)
        );
        break;
    case 2:
    default:
        // QInputMethodEvent(const QString & preeditText, const QList<Attribute> & attributes)
        /* TODO lua::make<QInputMethodEvent>(state,
            lua::get<QString>(state, 1),
            lua::get<const QList<QInputMethodEvent::Attribute>>(state, 2)
        );*/
        break;
    }

    return 1;
}

int luaopen_Qt5Gui_QInputMethodEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QInputMethodEvent"] = lua::value::table;
    env["QInputMethodEvent"]["new"] = QInputMethodEvent_new;
    auto t = env["QInputMethodEvent"];

    // enum QInputMethodEvent::AttributeType
    t["TextFormat"] = QInputMethodEvent::TextFormat;
    t["Cursor"] = QInputMethodEvent::Cursor;
    t["Language"] = QInputMethodEvent::Language;
    t["Ruby"] = QInputMethodEvent::Ruby;
    t["Selection"] = QInputMethodEvent::Selection;

    return 0;
}
