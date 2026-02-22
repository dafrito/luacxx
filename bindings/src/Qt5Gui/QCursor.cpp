#include "QCursor.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPoint.hpp"
#include "QPixmap.hpp"
#include "QBitmap.hpp"
#include "QScreen.hpp"
#include "../Qt5Core/Qt.hpp"

// http://qt-project.org/doc/qt-5/qcursor.html

void lua::QCursor_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["bitmap"] = &QCursor::bitmap;
    mt["hotSpot"] = &QCursor::hotSpot;
    mt["mask"] = &QCursor::mask;
    mt["pixmap"] = &QCursor::pixmap;
    mt["setShape"] = &QCursor::setShape;
    mt["shape"] = &QCursor::shape;
}

int QCursor_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QCursor ()
        lua::make<QCursor>(state);
    } else if (lua::is_type<QCursor>(state, 1)) {
        // QCursor ( const QCursor & c )
        lua::make<QCursor>(state, lua::get<const QCursor&>(state, 1));
    } else if (lua::is_type<Qt::CursorShape>(state, 1)) {
        // QCursor ( Qt::CursorShape shape )
        lua::make<QCursor>(state, lua::get<Qt::CursorShape>(state, 1));
    } else if (lua::is_type<QPixmap>(state, 1)) {
        // QCursor ( const QPixmap & pixmap, int hotX = -1, int hotY = -1 )
        switch (lua_gettop(state)) {
        case 1:
            lua::make<QCursor>(state,
                lua::get<const QPixmap&>(state, 1)
            );
            break;
        case 2:
            lua::make<QCursor>(state,
                lua::get<const QPixmap&>(state, 1),
                lua::get<int>(state, 2)
            );
            break;
        case 3:
        default:
            lua::make<QCursor>(state,
                lua::get<const QPixmap&>(state, 1),
                lua::get<int>(state, 2),
                lua::get<int>(state, 3)
            );
            break;
        }
    } else if (lua::is_type<QBitmap>(state, 1)) {
        // QCursor ( const QBitmap & bitmap, const QBitmap & mask, int hotX = -1, int hotY = -1 )
        switch (lua_gettop(state)) {
        case 2:
            lua::make<QCursor>(state,
                lua::get<const QBitmap&>(state, 1),
                lua::get<const QBitmap&>(state, 2)
            );
            break;
        case 3:
            lua::make<QCursor>(state,
                lua::get<const QBitmap&>(state, 1),
                lua::get<const QBitmap&>(state, 2),
                lua::get<int>(state, 3)
            );
            break;
        case 4:
        default:
            lua::make<QCursor>(state,
                lua::get<const QBitmap&>(state, 1),
                lua::get<const QBitmap&>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4)
            );
            break;
        }
    }

    return 1;
}

int QCursor_pos(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::push(state, QCursor::pos());
    } else {
        lua::push(state, QCursor::pos(lua::get<QScreen*>(state, 1)));
    }

    return 1;
}

int QCursor_setPos(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 1:
        // void     setPos(const QPoint & p)
        QCursor::setPos(
            lua::get<const QPoint&>(state, 1)
        );
        break;
    case 2:
        if (lua::is_type<QScreen>(state, 1)) {
            // void     setPos(QScreen * screen, const QPoint & p)
            QCursor::setPos(
                lua::get<QScreen*>(state, 1),
                lua::get<const QPoint&>(state, 2)
            );
        } else {
            // void     setPos(int x, int y)
            QCursor::setPos(
                lua::get<int>(state, 1),
                lua::get<int>(state, 2)
            );
        }
        break;
    case 3:
    default:
        // void     setPos(QScreen * screen, int x, int y)
        QCursor::setPos(
            lua::get<QScreen*>(state, 1),
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        );
        break;
    }

    return 0;
}

int luaopen_Qt5Gui_QCursor(lua_State* const state)
{
    lua::thread env(state);

    env["QCursor"] = lua::value::table;
    env["QCursor"]["new"] = QCursor_new;
    auto t = env["QCursor"];

    t["pos"] = QCursor_pos;
    t["setPos"] = QCursor_setPos;

    return 0;
}
