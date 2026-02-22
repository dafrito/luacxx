#include "QKeyEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/QString.hpp"
#include "QKeySequence.hpp"

// http://qt-project.org/doc/qt-5/qkeyevent.html

namespace lua {

void QKeyEvent_metatable(lua_State* const state, const int pos)
{
    lua::QInputEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["count"] = &QKeyEvent::count;
    mt["isAutoRepeat"] = &QKeyEvent::isAutoRepeat;
    mt["key"] = &QKeyEvent::key;
    mt["matches"] = &QKeyEvent::matches;
    mt["modifiers"] = &QKeyEvent::modifiers;
    mt["nativeModifiers"] = &QKeyEvent::nativeModifiers;
    mt["nativeScanCode"] = &QKeyEvent::nativeScanCode;
    mt["nativeVirtualKey"] = &QKeyEvent::nativeVirtualKey;
    mt["text"] = &QKeyEvent::text;
}

} // namespace lua

int QKeyEvent_new(lua_State* const state)
{
    if (lua_gettop(state) == 3) {
        // QKeyEvent(Type type, int key, Qt::KeyboardModifiers modifiers)
        lua::make<QKeyEvent>(state,
            lua::get<QEvent::Type>(state, 1),
            lua::get<int>(state, 2),
            lua::get<Qt::KeyboardModifiers>(state, 3)
        );
    } else {
        if (lua_type(state, 4) == LUA_TNUMBER) {
            // QKeyEvent(Type type, int key, Qt::KeyboardModifiers modifiers, quint32 nativeScanCode, quint32 nativeVirtualKey, quint32 nativeModifiers, const QString & text = QString(), bool autorep = false, ushort count = 1)
            switch (lua_gettop(state)) {
            case 6:
                lua::make<QKeyEvent>(state,
                    lua::get<QEvent::Type>(state, 1),
                    lua::get<int>(state, 2),
                    lua::get<Qt::KeyboardModifiers>(state, 3),
                    lua::get<quint32>(state, 4),
                    lua::get<quint32>(state, 5),
                    lua::get<quint32>(state, 6)
                );
                break;
            case 7:
                lua::make<QKeyEvent>(state,
                    lua::get<QEvent::Type>(state, 1),
                    lua::get<int>(state, 2),
                    lua::get<Qt::KeyboardModifiers>(state, 3),
                    lua::get<quint32>(state, 4),
                    lua::get<quint32>(state, 5),
                    lua::get<quint32>(state, 6),
                    lua::get<QString>(state, 7)
                );
                break;
            case 8:
                lua::make<QKeyEvent>(state,
                    lua::get<QEvent::Type>(state, 1),
                    lua::get<int>(state, 2),
                    lua::get<Qt::KeyboardModifiers>(state, 3),
                    lua::get<quint32>(state, 4),
                    lua::get<quint32>(state, 5),
                    lua::get<quint32>(state, 6),
                    lua::get<QString>(state, 7),
                    lua::get<bool>(state, 8)
                );
                break;
            case 9:
            default:
                lua::make<QKeyEvent>(state,
                    lua::get<QEvent::Type>(state, 1),
                    lua::get<int>(state, 2),
                    lua::get<Qt::KeyboardModifiers>(state, 3),
                    lua::get<quint32>(state, 4),
                    lua::get<quint32>(state, 5),
                    lua::get<quint32>(state, 6),
                    lua::get<QString>(state, 7),
                    lua::get<bool>(state, 8),
                    lua::get<ushort>(state, 9)
                );
                break;
            }
        } else {
            // QKeyEvent(Type type, int key, Qt::KeyboardModifiers modifiers, const QString & text = QString(), bool autorep = false, ushort count = 1)
            switch (lua_gettop(state)) {
            case 4:
                lua::make<QKeyEvent>(state,
                    lua::get<QEvent::Type>(state, 1),
                    lua::get<int>(state, 2),
                    lua::get<Qt::KeyboardModifiers>(state, 3),
                    lua::get<QString>(state, 4)
                );
                break;
            case 5:
                lua::make<QKeyEvent>(state,
                    lua::get<QEvent::Type>(state, 1),
                    lua::get<int>(state, 2),
                    lua::get<Qt::KeyboardModifiers>(state, 3),
                    lua::get<QString>(state, 4),
                    lua::get<bool>(state, 5)
                );
                break;
            case 6:
            default:
                lua::make<QKeyEvent>(state,
                    lua::get<QEvent::Type>(state, 1),
                    lua::get<int>(state, 2),
                    lua::get<Qt::KeyboardModifiers>(state, 3),
                    lua::get<QString>(state, 4),
                    lua::get<bool>(state, 5),
                    lua::get<ushort>(state, 6)
                );
                break;
            }
        }
    }

    return 1;
}

int luaopen_Qt5Gui_QKeyEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QKeyEvent"] = lua::value::table;
    env["QKeyEvent"]["new"] = QKeyEvent_new;
    auto t = env["QKeyEvent"];

    return 0;
}
