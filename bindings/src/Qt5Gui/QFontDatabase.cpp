#include "QFontDatabase.hpp"
#include "../convert/const_char_p.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "QFont.hpp"
#include "QFontInfo.hpp"
#include "../Qt5Core/QList.hpp"
#include "../Qt5Core/QStringList.hpp"
#include "../Qt5Core/QByteArray.hpp"

int QFontDatabase_families(lua_State* const state)
{
    return 0;
}
int QFontDatabase_isBitmapScalable(lua_State* const state)
{
    return 0;
}
int QFontDatabase_isFixedPitch(lua_State* const state)
{
    return 0;
}
int QFontDatabase_isScalable(lua_State* const state)
{
    return 0;
}
int QFontDatabase_isSmoothlyScalable(lua_State* const state)
{
    return 0;
}
int QFontDatabase_pointSizes(lua_State* const state)
{
    return 0;
}
int QFontDatabase_styleString(lua_State* const state)
{
    return 0;
}
int QFontDatabase_writingSystems(lua_State* const state)
{
    return 0;
}

namespace lua {

void QFontDatabase_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["bold"] = &QFontDatabase::bold;
    mt["families"] = QFontDatabase_families;
    mt["font"] = &QFontDatabase::font;
    mt["isBitmapScalable"] = QFontDatabase_isBitmapScalable;
    mt["isFixedPitch"] = QFontDatabase_isFixedPitch;
    mt["isScalable"] = QFontDatabase_isScalable;
    mt["isSmoothlyScalable"] = QFontDatabase_isSmoothlyScalable;
    mt["italic"] = &QFontDatabase::italic;
    mt["pointSizes"] = QFontDatabase_pointSizes;
    mt["smoothSizes"] = &QFontDatabase::smoothSizes;
    mt["styleString"] = QFontDatabase_styleString;
    mt["styles"] = &QFontDatabase::styles;
    mt["weight"] = &QFontDatabase::weight;
    mt["writingSystems"] = QFontDatabase_writingSystems;
}

} // namespace lua

int QFontDatabase_new(lua_State* const state)
{
    lua::make<QFontDatabase>(state);
    return 1;
}

int luaopen_Qt5Gui_QFontDatabase(lua_State* const state)
{
    lua::thread env(state);

    env["QFontDatabase"] = lua::value::table;
    env["QFontDatabase"]["new"] = QFontDatabase_new;
    auto t = env["QFontDatabase"];

    t["addApplicationFont"] = QFontDatabase::addApplicationFont;
    t["addApplicationFontFromData"] = QFontDatabase::addApplicationFontFromData;
    t["applicationFontFamilies"] = QFontDatabase::applicationFontFamilies;
    t["removeAllApplicationFonts"] = QFontDatabase::removeAllApplicationFonts;
    t["removeApplicationFont"] = QFontDatabase::removeApplicationFont;
    t["standardSizes"] = QFontDatabase::standardSizes;
    t["systemFont"] = QFontDatabase::systemFont;
    t["writingSystemName"] = QFontDatabase::writingSystemName;
    t["writingSystemSample"] = QFontDatabase::writingSystemSample;

    // enum QFontDatabase::SystemFont
    t["GeneralFont"] = QFontDatabase::GeneralFont;
    t["FixedFont"] = QFontDatabase::FixedFont;
    t["TitleFont"] = QFontDatabase::TitleFont;
    t["SmallestReadableFont"] = QFontDatabase::SmallestReadableFont;

    // enum QFontDatabase::WritingSystem
    t["Any"] = QFontDatabase::Any;
    t["Latin"] = QFontDatabase::Latin;
    t["Greek"] = QFontDatabase::Greek;
    t["Cyrillic"] = QFontDatabase::Cyrillic;
    t["Armenian"] = QFontDatabase::Armenian;
    t["Hebrew"] = QFontDatabase::Hebrew;
    t["Arabic"] = QFontDatabase::Arabic;
    t["Syriac"] = QFontDatabase::Syriac;
    t["Thaana"] = QFontDatabase::Thaana;
    t["Devanagari"] = QFontDatabase::Devanagari;
    t["Bengali"] = QFontDatabase::Bengali;
    t["Gurmukhi"] = QFontDatabase::Gurmukhi;
    t["Gujarati"] = QFontDatabase::Gujarati;
    t["Oriya"] = QFontDatabase::Oriya;
    t["Tamil"] = QFontDatabase::Tamil;
    t["Telugu"] = QFontDatabase::Telugu;
    t["Kannada"] = QFontDatabase::Kannada;
    t["Malayalam"] = QFontDatabase::Malayalam;
    t["Sinhala"] = QFontDatabase::Sinhala;
    t["Thai"] = QFontDatabase::Thai;
    t["Lao"] = QFontDatabase::Lao;
    t["Tibetan"] = QFontDatabase::Tibetan;
    t["Myanmar"] = QFontDatabase::Myanmar;
    t["Georgian"] = QFontDatabase::Georgian;
    t["Khmer"] = QFontDatabase::Khmer;
    t["SimplifiedChinese"] = QFontDatabase::SimplifiedChinese;
    t["TraditionalChinese"] = QFontDatabase::TraditionalChinese;
    t["Japanese"] = QFontDatabase::Japanese;
    t["Korean"] = QFontDatabase::Korean;
    t["Vietnamese"] = QFontDatabase::Vietnamese;
    t["Symbol"] = QFontDatabase::Symbol;
    t["Other"] = QFontDatabase::Other;
    t["Ogham"] = QFontDatabase::Ogham;
    t["Runic"] = QFontDatabase::Runic;
    t["Nko"] = QFontDatabase::Nko;

    return 0;
}
