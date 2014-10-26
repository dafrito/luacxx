#include "QPagedPaintDevice.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QPaintDevice.hpp"
#include "QPageLayout.hpp"
#include "QPageSize.hpp"
#include "../Qt5Core/QSizeF.hpp"
#include "QMarginsF.hpp"

namespace lua {

void QPagedPaintDevice_metatable(lua_State* const state, const int pos)
{
    lua::QPaintDevice_metatable(state, pos);

    lua::index mt(state, pos);
    mt["margins"] = &QPagedPaintDevice::margins;
    mt["newPage"] = &QPagedPaintDevice::newPage;
    mt["pageLayout"] = &QPagedPaintDevice::pageLayout;
    mt["pageSize"] = &QPagedPaintDevice::pageSize;
    mt["pageSizeMM"] = &QPagedPaintDevice::pageSizeMM;
    mt["setMargins"] = &QPagedPaintDevice::setMargins;
    mt["setPageLayout"] = &QPagedPaintDevice::setPageLayout;
    mt["setPageMargins"] = QPagedPaintDevice_setPageMargins;
    mt["setPageOrientation"] = &QPagedPaintDevice::setPageOrientation;
    mt["setPageSize"] = QPagedPaintDevice_setPageSize;
    mt["setPageSizeMM"] = &QPagedPaintDevice::setPageSizeMM;
}

} // namespace lua

int QPagedPaintDevice_new(lua_State* const state)
{
    lua::make<QPagedPaintDevice>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Gui_QPagedPaintDevice(lua_State* const state)
{
    lua::thread env(state);

    env["QPagedPaintDevice"] = lua::value::table;
    env["QPagedPaintDevice"]["new"] = QPagedPaintDevice_new;
    auto t = env["QPagedPaintDevice"];

    // enum QPagedPaintDevice::PageSize
    t["A0"] = QPagedPaintDevice::A0;
    t["A1"] = QPagedPaintDevice::A1;
    t["A2"] = QPagedPaintDevice::A2;
    t["A3"] = QPagedPaintDevice::A3;
    t["A4"] = QPagedPaintDevice::A4;
    t["A5"] = QPagedPaintDevice::A5;
    t["A6"] = QPagedPaintDevice::A6;
    t["A7"] = QPagedPaintDevice::A7;
    t["A8"] = QPagedPaintDevice::A8;
    t["A9"] = QPagedPaintDevice::A9;
    t["B0"] = QPagedPaintDevice::B0;
    t["B1"] = QPagedPaintDevice::B1;
    t["B2"] = QPagedPaintDevice::B2;
    t["B3"] = QPagedPaintDevice::B3;
    t["B4"] = QPagedPaintDevice::B4;
    t["B5"] = QPagedPaintDevice::B5;
    t["B6"] = QPagedPaintDevice::B6;
    t["B7"] = QPagedPaintDevice::B7;
    t["B8"] = QPagedPaintDevice::B8;
    t["B9"] = QPagedPaintDevice::B9;
    t["B10"] = QPagedPaintDevice::B10;
    t["C5E"] = QPagedPaintDevice::C5E;
    t["Comm10E"] = QPagedPaintDevice::Comm10E;
    t["DLE"] = QPagedPaintDevice::DLE;
    t["Executive"] = QPagedPaintDevice::Executive;
    t["Folio"] = QPagedPaintDevice::Folio;
    t["Ledger"] = QPagedPaintDevice::Ledger;
    t["Legal"] = QPagedPaintDevice::Legal;
    t["Letter"] = QPagedPaintDevice::Letter;
    t["Tabloid"] = QPagedPaintDevice::Tabloid;
    t["Custom"] = QPagedPaintDevice::Custom;
    t["A10"] = QPagedPaintDevice::A10;
    t["A3Extra"] = QPagedPaintDevice::A3Extra;
    t["A4Extra"] = QPagedPaintDevice::A4Extra;
    t["A4Plus"] = QPagedPaintDevice::A4Plus;
    t["A4Small"] = QPagedPaintDevice::A4Small;
    t["A5Extra"] = QPagedPaintDevice::A5Extra;
    t["B5Extra"] = QPagedPaintDevice::B5Extra;
    t["JisB0"] = QPagedPaintDevice::JisB0;
    t["JisB1"] = QPagedPaintDevice::JisB1;
    t["JisB2"] = QPagedPaintDevice::JisB2;
    t["JisB3"] = QPagedPaintDevice::JisB3;
    t["JisB4"] = QPagedPaintDevice::JisB4;
    t["JisB5"] = QPagedPaintDevice::JisB5;
    t["JisB6"] = QPagedPaintDevice::JisB6;
    t["JisB7"] = QPagedPaintDevice::JisB7;
    t["JisB8"] = QPagedPaintDevice::JisB8;
    t["JisB9"] = QPagedPaintDevice::JisB9;
    t["JisB10"] = QPagedPaintDevice::JisB10;
    t["AnsiA"] = QPagedPaintDevice::AnsiA;
    t["AnsiB"] = QPagedPaintDevice::AnsiB;
    t["AnsiC"] = QPagedPaintDevice::AnsiC;
    t["AnsiD"] = QPagedPaintDevice::AnsiD;
    t["AnsiE"] = QPagedPaintDevice::AnsiE;
    t["LegalExtra"] = QPagedPaintDevice::LegalExtra;
    t["LetterExtra"] = QPagedPaintDevice::LetterExtra;
    t["LetterPlus"] = QPagedPaintDevice::LetterPlus;
    t["LetterSmall"] = QPagedPaintDevice::LetterSmall;
    t["TabloidExtra"] = QPagedPaintDevice::TabloidExtra;
    t["ArchA"] = QPagedPaintDevice::ArchA;
    t["ArchB"] = QPagedPaintDevice::ArchB;
    t["ArchC"] = QPagedPaintDevice::ArchC;
    t["ArchD"] = QPagedPaintDevice::ArchD;
    t["ArchE"] = QPagedPaintDevice::ArchE;
    t["Imperial7x9"] = QPagedPaintDevice::Imperial7x9;
    t["Imperial8x10"] = QPagedPaintDevice::Imperial8x10;
    t["Imperial9x11"] = QPagedPaintDevice::Imperial9x11;
    t["Imperial9x12"] = QPagedPaintDevice::Imperial9x12;
    t["Imperial10x11"] = QPagedPaintDevice::Imperial10x11;
    t["Imperial10x13"] = QPagedPaintDevice::Imperial10x13;
    t["Imperial10x14"] = QPagedPaintDevice::Imperial10x14;
    t["Imperial12x11"] = QPagedPaintDevice::Imperial12x11;
    t["Imperial15x11"] = QPagedPaintDevice::Imperial15x11;
    t["ExecutiveStandard"] = QPagedPaintDevice::ExecutiveStandard;
    t["Note"] = QPagedPaintDevice::Note;
    t["Quarto"] = QPagedPaintDevice::Quarto;
    t["Statement"] = QPagedPaintDevice::Statement;
    t["SuperA"] = QPagedPaintDevice::SuperA;
    t["SuperB"] = QPagedPaintDevice::SuperB;
    t["Postcard"] = QPagedPaintDevice::Postcard;
    t["DoublePostcard"] = QPagedPaintDevice::DoublePostcard;
    t["Prc16K"] = QPagedPaintDevice::Prc16K;
    t["Prc32K"] = QPagedPaintDevice::Prc32K;
    t["Prc32KBig"] = QPagedPaintDevice::Prc32KBig;
    t["FanFoldUS"] = QPagedPaintDevice::FanFoldUS;
    t["FanFoldGerman"] = QPagedPaintDevice::FanFoldGerman;
    t["FanFoldGermanLegal"] = QPagedPaintDevice::FanFoldGermanLegal;
    t["EnvelopeB4"] = QPagedPaintDevice::EnvelopeB4;
    t["EnvelopeB5"] = QPagedPaintDevice::EnvelopeB5;
    t["EnvelopeB6"] = QPagedPaintDevice::EnvelopeB6;
    t["EnvelopeC0"] = QPagedPaintDevice::EnvelopeC0;
    t["EnvelopeC1"] = QPagedPaintDevice::EnvelopeC1;
    t["EnvelopeC2"] = QPagedPaintDevice::EnvelopeC2;
    t["EnvelopeC3"] = QPagedPaintDevice::EnvelopeC3;
    t["EnvelopeC4"] = QPagedPaintDevice::EnvelopeC4;
    t["EnvelopeC5"] = QPagedPaintDevice::EnvelopeC5;
    t["EnvelopeC6"] = QPagedPaintDevice::EnvelopeC6;
    t["EnvelopeC65"] = QPagedPaintDevice::EnvelopeC65;
    t["EnvelopeC7"] = QPagedPaintDevice::EnvelopeC7;
    t["EnvelopeDL"] = QPagedPaintDevice::EnvelopeDL;
    t["Envelope9"] = QPagedPaintDevice::Envelope9;
    t["Envelope10"] = QPagedPaintDevice::Envelope10;
    t["Envelope11"] = QPagedPaintDevice::Envelope11;
    t["Envelope12"] = QPagedPaintDevice::Envelope12;
    t["Envelope14"] = QPagedPaintDevice::Envelope14;
    t["EnvelopeMonarch"] = QPagedPaintDevice::EnvelopeMonarch;
    t["EnvelopePersonal"] = QPagedPaintDevice::EnvelopePersonal;
    t["EnvelopeChou3"] = QPagedPaintDevice::EnvelopeChou3;
    t["EnvelopeChou4"] = QPagedPaintDevice::EnvelopeChou4;
    t["EnvelopeInvite"] = QPagedPaintDevice::EnvelopeInvite;
    t["EnvelopeItalian"] = QPagedPaintDevice::EnvelopeItalian;
    t["EnvelopeKaku2"] = QPagedPaintDevice::EnvelopeKaku2;
    t["EnvelopeKaku3"] = QPagedPaintDevice::EnvelopeKaku3;
    t["EnvelopePrc1"] = QPagedPaintDevice::EnvelopePrc1;
    t["EnvelopePrc2"] = QPagedPaintDevice::EnvelopePrc2;
    t["EnvelopePrc3"] = QPagedPaintDevice::EnvelopePrc3;
    t["EnvelopePrc4"] = QPagedPaintDevice::EnvelopePrc4;
    t["EnvelopePrc5"] = QPagedPaintDevice::EnvelopePrc5;
    t["EnvelopePrc6"] = QPagedPaintDevice::EnvelopePrc6;
    t["EnvelopePrc7"] = QPagedPaintDevice::EnvelopePrc7;
    t["EnvelopePrc8"] = QPagedPaintDevice::EnvelopePrc8;
    t["EnvelopePrc9"] = QPagedPaintDevice::EnvelopePrc9;
    t["EnvelopePrc10"] = QPagedPaintDevice::EnvelopePrc10;
    t["EnvelopeYou4"] = QPagedPaintDevice::EnvelopeYou4;
    t["LastPageSize"] = QPagedPaintDevice::LastPageSize;

    return 0;
}
