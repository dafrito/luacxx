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

std::unordered_map<int, std::function<void(lua_State* const, const QVariant&)>>& qvariant_push_handler()
{
    static std::unordered_map<int, std::function<void(lua_State* const, const QVariant&)>> _rv;
    return _rv;
}

std::unordered_map<int, std::function<void(QVariant&, const lua::index&)>>& qvariant_store_handler()
{
    static std::unordered_map<int, std::function<void(QVariant&, const lua::index&)>> _rv;
    return _rv;
}

namespace std {
    template<>
    class hash<QVariant::Type>
    {
    public:
        size_t operator()(const QVariant::Type& value) const
        {
            return static_cast<int>(value);
        }
    };
}

void lua::set_qvariant_push_handler(const int type, const std::function<void(lua_State* const, const QVariant&)>& handler)
{
    qvariant_push_handler()[type] = handler;
}

void lua::set_qvariant_store_handler(const int type, const std::function<void(QVariant&, const lua::index&)>& handler)
{
    qvariant_store_handler()[type] = handler;
}

void lua::push_qvariant(lua_State* const state, const QVariant& value)
{
    switch (value.userType()) {
        case QVariant::Invalid:
            lua::push(state, lua::value::nil);
            break;
        case QVariant::Bool:
            lua::push(state, value.toBool());
            break;
        case QVariant::Char:
            lua::push(state, value.toChar());
            break;
        case QVariant::Int:
        {
            lua::push(state, value.toInt());
            break;
        }
        case QVariant::Double:
        case QVariant::UInt:
            lua::push(state, value.toDouble());
            break;
        case QVariant::String:
            lua::push(state, value.toString());
            break;
        case QVariant::Hash:
        {
            auto hash = value.toHash();

            auto table = lua::push(state, lua::value::table);
            for (auto i = hash.begin(); i != hash.end(); ++i) {
                lua::table::set(table, i.key(), i.value());
            }

            break;
        }
        case QVariant::StringList:
        {
            auto list = value.toStringList();

            auto table = lua::push(state, lua::value::table);
            for (int i = 0; i < list.size(); ++i) {
                lua::table::set(table, i + 1, list[i]);
            }

            break;
        }
        default:
        {
            auto converter = qvariant_push_handler().find(value.userType());
            if (converter != qvariant_push_handler().end()) {
                converter->second(state, value);
            } else {
                throw lua::error(state, std::string("No handler exists to push QVariant type: ") + value.typeName());
            }
        }
    }
}

void lua::store_qvariant(QVariant& destination, lua_State* const state, const int pos)
{
    lua::index source(state, pos);
    switch (destination.userType()) {
        case QVariant::Invalid:
            throw lua::error("A QVariant must have a valid type");
            destination.clear();
            break;
        case QVariant::Bool:
            destination.setValue(lua::get<bool>(source));
            break;
        case QVariant::Char:
            destination.setValue(lua::get<char>(source));
            break;
        case QVariant::Int:
        case QVariant::UInt:
            destination.setValue(lua::get<int>(source));
            break;
        case QVariant::Double:
            destination.setValue(lua::get<double>(source));
            break;
        case QVariant::String:
            destination.setValue(lua::get<QString>(source));
            break;
        case QVariant::StringList:
        {
            auto state = source.state();
            QStringList items;

            auto length = lua_rawlen(state, source.pos());
            for (unsigned int i = 1; i <= length; ++i) {
                lua::push(state, i);
                lua_gettable(state, source.pos());
                items << lua::get<QString>(state, -1);
                lua_pop(state, 1);
            }

            destination.setValue(items);
            break;
        }
        case QVariant::Hash:
        {
            QHash<QString, QVariant> hash;

            auto state = source.state();

            lua::push(state, lua::value::nil);
            while (lua_next(state, source.pos()) != 0) {
                auto key = lua::get<QString>(state, -2);
                auto value = lua::get<QVariant>(state, -1);

                hash[key] = value;

                lua_pop(state, 1);
            }

            destination.setValue(hash);
            break;
        }
        default:
        {
            auto converter = qvariant_store_handler().find(destination.userType());
            if (converter != qvariant_store_handler().end()) {
                converter->second(destination, source);
            } else {
                throw lua::error(state, std::string("No QVariant handler exists to store type: ") + destination.typeName());
            }
        }
    }
}

int QVariant_toDouble(lua_State* const state)
{
    return 0;
}
int QVariant_toFloat(lua_State* const state)
{
    return 0;
}
int QVariant_toInt(lua_State* const state)
{
    return 0;
}
int QVariant_toLongLong(lua_State* const state)
{
    return 0;
}
int QVariant_toReal(lua_State* const state)
{
    return 0;
}
int QVariant_toUInt(lua_State* const state)
{
    return 0;
}
int QVariant_toULongLong(lua_State* const state)
{
    return 0;
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

int luaopen_Qt5Core_QVariant(lua_State* const state)
{
    lua::thread env(state);

    env["QVariant"] = lua::value::table;
    auto t = env["QVariant"];
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
