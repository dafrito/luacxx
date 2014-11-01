#include "QPageSize.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QSizeF.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QString.hpp"

int QPageSize_definitionSize(lua_State* const state)
{
    return 0;
}
int QPageSize_definitionUnits(lua_State* const state)
{
    return 0;
}
int QPageSize_id(lua_State* const state)
{
    return 0;
}
int QPageSize_key(lua_State* const state)
{
    return 0;
}
int QPageSize_name(lua_State* const state)
{
    return 0;
}
int QPageSize_size(lua_State* const state)
{
    return 0;
}
int QPageSize_sizePixels(lua_State* const state)
{
    return 0;
}
int QPageSize_sizePoints(lua_State* const state)
{
    return 0;
}
int QPageSize_windowsId(lua_State* const state)
{
    return 0;
}

namespace lua {

void QPageSize_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["definitionSize"] = QPageSize_definitionSize;
    mt["definitionUnits"] = QPageSize_definitionUnits;
    mt["id"] = QPageSize_id;
    mt["isEquivalentTo"] = &QPageSize::isEquivalentTo;
    mt["isValid"] = &QPageSize::isValid;
    mt["key"] = QPageSize_key;
    mt["name"] = QPageSize_name;
    mt["rect"] = &QPageSize::rect;
    mt["rectPixels"] = &QPageSize::rectPixels;
    mt["rectPoints"] = &QPageSize::rectPoints;
    mt["size"] = QPageSize_size;
    mt["sizePixels"] = QPageSize_sizePixels;
    mt["sizePoints"] = QPageSize_sizePoints;
    mt["swap"] = &QPageSize::swap;
    mt["windowsId"] = QPageSize_windowsId;
}

} // namespace lua

int QPageSize_new(lua_State* const state)
{
    // QPageSize()
    // QPageSize(PageSizeId pageSize)
    // QPageSize(const QSize & pointSize, const QString & name = QString(), SizeMatchPolicy matchPolicy = FuzzyMatch)
    // QPageSize(const QSizeF & size, Unit units, const QString & name = QString(), SizeMatchPolicy matchPolicy = FuzzyMatch)
    // QPageSize(const QPageSize & other)
    lua::make<QPageSize>(state);

    return 1;
}

int static_QPageSize_definitionSize(lua_State* const state)
{
    return 0;
}
int static_QPageSize_definitionUnits(lua_State* const state)
{
    return 0;
}
int static_QPageSize_id(lua_State* const state)
{
    return 0;
}
int static_QPageSize_key(lua_State* const state)
{
    return 0;
}
int static_QPageSize_name(lua_State* const state)
{
    return 0;
}
int static_QPageSize_size(lua_State* const state)
{
    return 0;
}
int static_QPageSize_sizePixels(lua_State* const state)
{
    return 0;
}
int static_QPageSize_sizePoints(lua_State* const state)
{
    return 0;
}
int static_QPageSize_windowsId(lua_State* const state)
{
    return 0;
}

int luaopen_Qt5Gui_QPageSize(lua_State* const state)
{
    lua::thread env(state);

    env["QPageSize"] = lua::value::table;
    env["QPageSize"]["new"] = QPageSize_new;
    auto t = env["QPageSize"];

    t["definitionSize"] = static_QPageSize_definitionSize;
    t["definitionUnits"] = static_QPageSize_definitionUnits;
    t["id"] = static_QPageSize_id;
    t["key"] = static_QPageSize_key;
    t["name"] = static_QPageSize_name;
    t["size"] = static_QPageSize_size;
    t["sizePixels"] = static_QPageSize_sizePixels;
    t["sizePoints"] = static_QPageSize_sizePoints;
    t["windowsId"] = static_QPageSize_windowsId;

    // enum QPageSize::PageSizeId
    t["A0"] = QPageSize::A0;
    t["A1"] = QPageSize::A1;
    t["A2"] = QPageSize::A2;
    t["A3"] = QPageSize::A3;
    t["A4"] = QPageSize::A4;
    t["A5"] = QPageSize::A5;
    t["A6"] = QPageSize::A6;
    t["A7"] = QPageSize::A7;
    t["A8"] = QPageSize::A8;
    t["A9"] = QPageSize::A9;
    t["B0"] = QPageSize::B0;
    t["B1"] = QPageSize::B1;
    t["B2"] = QPageSize::B2;
    t["B3"] = QPageSize::B3;
    t["B4"] = QPageSize::B4;
    t["B5"] = QPageSize::B5;
    t["B6"] = QPageSize::B6;
    t["B7"] = QPageSize::B7;
    t["B8"] = QPageSize::B8;
    t["B9"] = QPageSize::B9;
    t["B10"] = QPageSize::B10;
    t["C5E"] = QPageSize::C5E;
    t["Comm10E"] = QPageSize::Comm10E;
    t["DLE"] = QPageSize::DLE;
    t["Executive"] = QPageSize::Executive;
    t["Folio"] = QPageSize::Folio;
    t["Ledger"] = QPageSize::Ledger;
    t["Legal"] = QPageSize::Legal;
    t["Letter"] = QPageSize::Letter;
    t["Tabloid"] = QPageSize::Tabloid;
    t["Custom"] = QPageSize::Custom;
    t["A10"] = QPageSize::A10;
    t["A3Extra"] = QPageSize::A3Extra;
    t["A4Extra"] = QPageSize::A4Extra;
    t["A4Plus"] = QPageSize::A4Plus;
    t["A4Small"] = QPageSize::A4Small;
    t["A5Extra"] = QPageSize::A5Extra;
    t["B5Extra"] = QPageSize::B5Extra;
    t["JisB0"] = QPageSize::JisB0;
    t["JisB1"] = QPageSize::JisB1;
    t["JisB2"] = QPageSize::JisB2;
    t["JisB3"] = QPageSize::JisB3;
    t["JisB4"] = QPageSize::JisB4;
    t["JisB5"] = QPageSize::JisB5;
    t["JisB6"] = QPageSize::JisB6;
    t["JisB7"] = QPageSize::JisB7;
    t["JisB8"] = QPageSize::JisB8;
    t["JisB9"] = QPageSize::JisB9;
    t["JisB10"] = QPageSize::JisB10;
    t["AnsiA"] = QPageSize::AnsiA;
    t["AnsiB"] = QPageSize::AnsiB;
    t["AnsiC"] = QPageSize::AnsiC;
    t["AnsiD"] = QPageSize::AnsiD;
    t["AnsiE"] = QPageSize::AnsiE;
    t["LegalExtra"] = QPageSize::LegalExtra;
    t["LetterExtra"] = QPageSize::LetterExtra;
    t["LetterPlus"] = QPageSize::LetterPlus;
    t["LetterSmall"] = QPageSize::LetterSmall;
    t["TabloidExtra"] = QPageSize::TabloidExtra;
    t["ArchA"] = QPageSize::ArchA;
    t["ArchB"] = QPageSize::ArchB;
    t["ArchC"] = QPageSize::ArchC;
    t["ArchD"] = QPageSize::ArchD;
    t["ArchE"] = QPageSize::ArchE;
    t["Imperial7x9"] = QPageSize::Imperial7x9;
    t["Imperial8x10"] = QPageSize::Imperial8x10;
    t["Imperial9x11"] = QPageSize::Imperial9x11;
    t["Imperial9x12"] = QPageSize::Imperial9x12;
    t["Imperial10x11"] = QPageSize::Imperial10x11;
    t["Imperial10x13"] = QPageSize::Imperial10x13;
    t["Imperial10x14"] = QPageSize::Imperial10x14;
    t["Imperial12x11"] = QPageSize::Imperial12x11;
    t["Imperial15x11"] = QPageSize::Imperial15x11;
    t["ExecutiveStandard"] = QPageSize::ExecutiveStandard;
    t["Note"] = QPageSize::Note;
    t["Quarto"] = QPageSize::Quarto;
    t["Statement"] = QPageSize::Statement;
    t["SuperA"] = QPageSize::SuperA;
    t["SuperB"] = QPageSize::SuperB;
    t["Postcard"] = QPageSize::Postcard;
    t["DoublePostcard"] = QPageSize::DoublePostcard;
    t["Prc16K"] = QPageSize::Prc16K;
    t["Prc32K"] = QPageSize::Prc32K;
    t["Prc32KBig"] = QPageSize::Prc32KBig;
    t["FanFoldUS"] = QPageSize::FanFoldUS;
    t["FanFoldGerman"] = QPageSize::FanFoldGerman;
    t["FanFoldGermanLegal"] = QPageSize::FanFoldGermanLegal;
    t["EnvelopeB4"] = QPageSize::EnvelopeB4;
    t["EnvelopeB5"] = QPageSize::EnvelopeB5;
    t["EnvelopeB6"] = QPageSize::EnvelopeB6;
    t["EnvelopeC0"] = QPageSize::EnvelopeC0;
    t["EnvelopeC1"] = QPageSize::EnvelopeC1;
    t["EnvelopeC2"] = QPageSize::EnvelopeC2;
    t["EnvelopeC3"] = QPageSize::EnvelopeC3;
    t["EnvelopeC4"] = QPageSize::EnvelopeC4;
    t["EnvelopeC5"] = QPageSize::EnvelopeC5;
    t["EnvelopeC6"] = QPageSize::EnvelopeC6;
    t["EnvelopeC65"] = QPageSize::EnvelopeC65;
    t["EnvelopeC7"] = QPageSize::EnvelopeC7;
    t["EnvelopeDL"] = QPageSize::EnvelopeDL;
    t["Envelope9"] = QPageSize::Envelope9;
    t["Envelope10"] = QPageSize::Envelope10;
    t["Envelope11"] = QPageSize::Envelope11;
    t["Envelope12"] = QPageSize::Envelope12;
    t["Envelope14"] = QPageSize::Envelope14;
    t["EnvelopeMonarch"] = QPageSize::EnvelopeMonarch;
    t["EnvelopePersonal"] = QPageSize::EnvelopePersonal;
    t["EnvelopeChou3"] = QPageSize::EnvelopeChou3;
    t["EnvelopeChou4"] = QPageSize::EnvelopeChou4;
    t["EnvelopeInvite"] = QPageSize::EnvelopeInvite;
    t["EnvelopeItalian"] = QPageSize::EnvelopeItalian;
    t["EnvelopeKaku2"] = QPageSize::EnvelopeKaku2;
    t["EnvelopeKaku3"] = QPageSize::EnvelopeKaku3;
    t["EnvelopePrc1"] = QPageSize::EnvelopePrc1;
    t["EnvelopePrc2"] = QPageSize::EnvelopePrc2;
    t["EnvelopePrc3"] = QPageSize::EnvelopePrc3;
    t["EnvelopePrc4"] = QPageSize::EnvelopePrc4;
    t["EnvelopePrc5"] = QPageSize::EnvelopePrc5;
    t["EnvelopePrc6"] = QPageSize::EnvelopePrc6;
    t["EnvelopePrc7"] = QPageSize::EnvelopePrc7;
    t["EnvelopePrc8"] = QPageSize::EnvelopePrc8;
    t["EnvelopePrc9"] = QPageSize::EnvelopePrc9;
    t["EnvelopePrc10"] = QPageSize::EnvelopePrc10;
    t["EnvelopeYou4"] = QPageSize::EnvelopeYou4;
    t["LastPageSize"] = QPageSize::LastPageSize;

    // enum QPageSize::SizeMatchPolicy
    t["FuzzyMatch"] = QPageSize::FuzzyMatch;
    t["FuzzyOrientationMatch"] = QPageSize::FuzzyOrientationMatch;
    t["ExactMatch"] = QPageSize::ExactMatch;

    // enum QPageSize::Unit
    t["Millimeter"] = QPageSize::Millimeter;
    t["Point"] = QPageSize::Point;
    t["Inch"] = QPageSize::Inch;
    t["Pica"] = QPageSize::Pica;
    t["Didot"] = QPageSize::Didot;
    t["Cicero"] = QPageSize::Cicero;

    return 0;
}
