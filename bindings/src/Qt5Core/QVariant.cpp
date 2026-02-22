#include "QVariant.hpp"

#include "QChar.hpp"
#include "QString.hpp"
#include "../algorithm.hpp"
#include "../convert/string.hpp"
#include "../convert/numeric.hpp"
#include "../thread.hpp"

#include <unordered_map>
#include <QStringList>

#include "QChar.hpp"
#include "QList.hpp"
#include "QDate.hpp"
#include "QByteArray.hpp"
#include "QRect.hpp"
#include "QRectF.hpp"
#include "QSizeF.hpp"
#include "QSize.hpp"
#include "QPoint.hpp"
#include "QPointF.hpp"
#include "QString.hpp"
#include "QStringList.hpp"
#include "QUrl.hpp"
#include "QDateTime.hpp"
#include "QLocale.hpp"
#include "QRegExp.hpp"
#include "QTime.hpp"
#include "QMap.hpp"
#include "QLine.hpp"
#include "QLineF.hpp"
#include "QEasingCurve.hpp"
#include "QHash.hpp"
#include "QBitArray.hpp"

// http://doc.qt.io/qt-5/qvariant.html

int QVariant_toDouble(lua_State* const state)
{
    auto self = lua::get<QVariant*>(state, 1);

    if (lua_gettop(state) == 1) {
        bool ok;
        lua::push(state, self->toDouble(&ok));
        lua::push(state, ok);
        return 2;
    }

    lua::push(state, self->toDouble(lua::get<bool*>(state, 2)));
    return 1;
}

int QVariant_toFloat(lua_State* const state)
{
    auto self = lua::get<QVariant*>(state, 1);

    if (lua_gettop(state) == 1) {
        bool ok;
        lua::push(state, self->toFloat(&ok));
        lua::push(state, ok);
        return 2;
    }

    lua::push(state, self->toFloat(lua::get<bool*>(state, 2)));
    return 1;
}

int QVariant_toInt(lua_State* const state)
{
    auto self = lua::get<QVariant*>(state, 1);

    if (lua_gettop(state) == 1) {
        bool ok;
        lua::push(state, self->toInt(&ok));
        lua::push(state, ok);
        return 2;
    }

    lua::push(state, self->toInt(lua::get<bool*>(state, 2)));
    return 1;
}

int QVariant_toLongLong(lua_State* const state)
{
    auto self = lua::get<QVariant*>(state, 1);

    if (lua_gettop(state) == 1) {
        bool ok;
        lua::push(state, self->toLongLong(&ok));
        lua::push(state, ok);
        return 2;
    }

    lua::push(state, self->toLongLong(lua::get<bool*>(state, 2)));

    return 1;
}

int QVariant_toReal(lua_State* const state)
{
    auto self = lua::get<QVariant*>(state, 1);

    if (lua_gettop(state) == 1) {
        bool ok;
        lua::push(state, self->toReal(&ok));
        lua::push(state, ok);
        return 2;
    }

    lua::push(state, self->toReal(lua::get<bool*>(state, 2)));

    return 1;
}

int QVariant_toUInt(lua_State* const state)
{
    auto self = lua::get<QVariant*>(state, 1);

    if (lua_gettop(state) == 1) {
        bool ok;
        lua::push(state, self->toUInt(&ok));
        lua::push(state, ok);
        return 2;
    }

    lua::push(state, self->toUInt(lua::get<bool*>(state, 2)));

    return 1;
}

int QVariant_toULongLong(lua_State* const state)
{
    auto self = lua::get<QVariant*>(state, 1);

    if (lua_gettop(state) == 1) {
        bool ok;
        lua::push(state, self->toULongLong(&ok));
        lua::push(state, ok);
        return 2;
    }

    lua::push(state, self->toULongLong(lua::get<bool*>(state, 2)));

    return 1;
}

namespace lua {

void QVariant_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    //mt["canConvert"] = &QVariant::canConvert;
    mt["clear"] = &QVariant::clear;
    //mt["convert"] = &QVariant::convert;
    mt["isNull"] = &QVariant::isNull;
    mt["isValid"] = &QVariant::isValid;
    //void    setValue ( const T & value )
    mt["swap"] = &QVariant::swap;
    mt["toBitArray"] = &QVariant::toBitArray;
    mt["toBool"] = &QVariant::toBool;
    mt["toByteArray"] = &QVariant::toByteArray;
    mt["toChar"] = &QVariant::toChar;
    mt["toDate"] = &QVariant::toDate;
    mt["toDateTime"] = &QVariant::toDateTime;
    mt["toDouble"] = QVariant_toDouble;
    mt["toEasingCurve"] = &QVariant::toEasingCurve;
    mt["toFloat"] = QVariant_toFloat;
    mt["toHash"] = &QVariant::toHash;
    mt["toInt"] = QVariant_toInt;
    mt["toLine"] = &QVariant::toLine;
    mt["toLineF"] = &QVariant::toLineF;
    mt["toList"] = &QVariant::toList;
    mt["toLocale"] = &QVariant::toLocale;
    mt["toLongLong"] = QVariant_toLongLong;
    mt["toMap"] = &QVariant::toMap;
    mt["toPoint"] = &QVariant::toPoint;
    mt["toPointF"] = &QVariant::toPointF;
    mt["toReal"] = QVariant_toReal;
    mt["toRect"] = &QVariant::toRect;
    mt["toRectF"] = &QVariant::toRectF;
    mt["toRegExp"] = &QVariant::toRegExp;
    mt["toSize"] = &QVariant::toSize;
    mt["toSizeF"] = &QVariant::toSizeF;
    mt["toString"] = &QVariant::toString;
    mt["toStringList"] = &QVariant::toStringList;
    mt["toTime"] = &QVariant::toTime;
    mt["toUInt"] = QVariant_toUInt;
    mt["toULongLong"] = QVariant_toULongLong;
    mt["toUrl"] = &QVariant::toUrl;
    mt["type"] = &QVariant::type;
    mt["typeName"] = &QVariant::typeName;
    mt["userType"] = &QVariant::userType;
    //T   value () const
}

} // namespace lua

int QVariant_new(lua_State* const state)
{
    // TODO Set up constructor
    lua::make<QVariant>(state);
    return 1;
}

int luaopen_Qt5Core_QVariant(lua_State* const state)
{
    lua::thread env(state);

    env["QVariant"] = lua::value::table;
    auto t = env["QVariant"];
    t["new"] = QVariant_new;
    t["nameToType"] = QVariant::nameToType;
    t["typeToName"] = QVariant::typeToName;

    // enum QVariant::Type
    t["Invalid"] = QVariant::Invalid;
    t["BitArray"] = QVariant::BitArray;
    t["Bitmap"] = QVariant::Bitmap;
    t["Bool"] = QVariant::Bool;
    t["Brush"] = QVariant::Brush;
    t["ByteArray"] = QVariant::ByteArray;
    t["Char"] = QVariant::Char;
    t["Color"] = QVariant::Color;
    t["Cursor"] = QVariant::Cursor;
    t["Date"] = QVariant::Date;
    t["DateTime"] = QVariant::DateTime;
    t["Double"] = QVariant::Double;
    t["EasingCurve"] = QVariant::EasingCurve;
    t["Font"] = QVariant::Font;
    t["Hash"] = QVariant::Hash;
    t["Icon"] = QVariant::Icon;
    t["Image"] = QVariant::Image;
    t["Int"] = QVariant::Int;
    t["KeySequence"] = QVariant::KeySequence;
    t["Line"] = QVariant::Line;
    t["LineF"] = QVariant::LineF;
    t["List"] = QVariant::List;
    t["Locale"] = QVariant::Locale;
    t["LongLong"] = QVariant::LongLong;
    t["Map"] = QVariant::Map;
    t["Matrix"] = QVariant::Matrix;
    t["Transform"] = QVariant::Transform;
    t["Matrix4x4"] = QVariant::Matrix4x4;
    t["Palette"] = QVariant::Palette;
    t["Pen"] = QVariant::Pen;
    t["Pixmap"] = QVariant::Pixmap;
    t["Point"] = QVariant::Point;
    t["PointF"] = QVariant::PointF;
    t["Polygon"] = QVariant::Polygon;
    t["Quaternion"] = QVariant::Quaternion;
    t["Rect"] = QVariant::Rect;
    t["RectF"] = QVariant::RectF;
    t["RegExp"] = QVariant::RegExp;
    t["Region"] = QVariant::Region;
    t["Size"] = QVariant::Size;
    t["SizeF"] = QVariant::SizeF;
    t["SizePolicy"] = QVariant::SizePolicy;
    t["String"] = QVariant::String;
    t["StringList"] = QVariant::StringList;
    t["TextFormat"] = QVariant::TextFormat;
    t["TextLength"] = QVariant::TextLength;
    t["Time"] = QVariant::Time;
    t["UInt"] = QVariant::UInt;
    t["ULongLong"] = QVariant::ULongLong;
    t["Url"] = QVariant::Url;
    t["Vector2D"] = QVariant::Vector2D;
    t["Vector3D"] = QVariant::Vector3D;
    t["Vector4D"] = QVariant::Vector4D;
    t["UserType"] = QVariant::UserType;

    return 0;
}
