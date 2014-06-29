#include "QLocale.hpp"
#include "../lua-cxx/type/function.hpp"
#include "../lua-cxx/thread.hpp"
#include "QString.hpp"
#include "QStringList.hpp"
#include "QList.hpp"
#include "QChar.hpp"

#include <QLocale>

// http://qt-project.org/doc/qt-5/qlocale.html

int QLocale_currencySymbol(lua_State* const state)
{
    return 0;
}

int QLocale_dateFormat(lua_State* const state)
{
    return 0;
}

int QLocale_dateTimeFormat(lua_State* const state)
{
    return 0;
}

int QLocale_dayName(lua_State* const state)
{
    return 0;
}

int QLocale_monthName(lua_State* const state)
{
    return 0;
}

int QLocale_quoteString(lua_State* const state)
{
    return 0;
}

int QLocale_timeFormat(lua_State* const state)
{
    return 0;
}

int QLocale_toCurrencyString(lua_State* const state)
{
    return 0;
}

int QLocale_toDate(lua_State* const state)
{
    return 0;
}

void lua::QLocale_metatable(const lua::index& mt)
{
    mt["amText"] = &QLocale::amText;
    mt["bcp47Name"] = &QLocale::bcp47Name;
    mt["country"] = &QLocale::country;
    mt["createSeparatedList"] = &QLocale::createSeparatedList;
    mt["currencySymbol"] = QLocale_currencySymbol;
    mt["dateFormat"] = QLocale_dateFormat;
    mt["dateTimeFormat"] = QLocale_dateTimeFormat;
    mt["dayName"] = QLocale_dayName;
    mt["decimalPoint"] = &QLocale::decimalPoint;
    mt["exponential"] = &QLocale::exponential;
    mt["firstDayOfWeek"] = &QLocale::firstDayOfWeek;
    mt["groupSeparator"] = &QLocale::groupSeparator;
    mt["language"] = &QLocale::language;
    mt["measurementSystem"] = &QLocale::measurementSystem;
    mt["monthName"] = QLocale_monthName;
    mt["name"] = &QLocale::name;
    mt["nativeCountryName"] = &QLocale::nativeCountryName;
    mt["nativeLanguageName"] = &QLocale::nativeLanguageName;
    mt["negativeSign"] = &QLocale::negativeSign;
    mt["numberOptions"] = &QLocale::numberOptions;
    mt["percent"] = &QLocale::percent;
    mt["pmText"] = &QLocale::pmText;
    mt["positiveSign"] = &QLocale::positiveSign;
    mt["quoteString"] = QLocale_quoteString;
    mt["script"] = &QLocale::script;
    mt["setNumberOptions"] = &QLocale::setNumberOptions;
    mt["standaloneDayName"] = &QLocale::standaloneDayName;
    mt["standaloneMonthName"] = &QLocale::standaloneMonthName;
    mt["textDirection"] = &QLocale::textDirection;
    mt["timeFormat"] = QLocale_timeFormat;
    mt["toCurrencyString"] = QLocale_toCurrencyString;
    mt["toDate"] = QLocale_toDate;
    mt["toDateTime"] = &QLocale::toDateTime;
    mt["toDouble"] = &QLocale::toDouble;
    mt["toFloat"] = &QLocale::toFloat;
    mt["toInt"] = &QLocale::toInt;
    mt["toLongLong"] = &QLocale::toLongLong;
    mt["toLower"] = &QLocale::toLower;
    mt["toShort"] = &QLocale::toShort;
    mt["toString"] = &QLocale::toString;
    mt["toTime"] = &QLocale::toTime;
    mt["toUInt"] = &QLocale::toUInt;
    mt["toULongLong"] = &QLocale::toULongLong;
    mt["toUShort"] = &QLocale::toUShort;
    mt["toUpper"] = &QLocale::toUpper;
    mt["uiLanguages"] = &QLocale::uiLanguages;
    mt["weekdays"] = &QLocale::weekdays;
    mt["zeroDigit"] = &QLocale::zeroDigit;
}

int QLocale_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
    case 1:
        // QLocale()
        lua::make<QLocale>(state);
        break;
    case 2:
        if (lua_type(state, 2) == LUA_TSTRING) {
            // QLocale(const QString & name)
            lua::make<QLocale>(state, lua::get<const char*>(state, 2));
            break;
        }
        if (lua::class_name(state, 2) == lua::Metatable<QLocale>::name) {
            // QLocale(const QLocale & other)
            lua::make<QLocale>(state, lua::get<const QLocale&>(state, 2));
            break;
        }
        // QLocale(Language language)
        lua::make<QLocale>(state, lua::get<QLocale::Language>(state, 2));
        break;
    case 3:
        // QLocale(Language language, Country country)
        lua::make<QLocale>(state,
            lua::get<QLocale::Language>(state, 2),
            lua::get<QLocale::Country>(state, 3)
        );
        break;
    case 4:
    default:
        // QLocale(Language language, Script script, Country country)
    }

    return 1;
}

int luaopen_luacxx_QLocale(lua_State* const state)
{
    lua::thread env(state);

    env["QLocale"] = lua::value::table;
    env["QLocale"]["new"] = QLocale_new;
    auto t = env["QLocale"];

    t["c"] = &QLocale::c;
    t["countryToString"] = &QLocale::countryToString;
    t["languageToString"] = &QLocale::languageToString;
    t["matchingLocales"] = &QLocale::matchingLocales;
    t["scriptToString"] = &QLocale::scriptToString;
    t["setDefault"] = &QLocale::setDefault;
    t["system"] = &QLocale::system;

    // enum QLocale::Country
    t["AnyCountry"] = QLocale::AnyCountry;
    t["Afghanistan"] = QLocale::Afghanistan;
    t["Albania"] = QLocale::Albania;
    t["Algeria"] = QLocale::Algeria;
    t["AmericanSamoa"] = QLocale::AmericanSamoa;
    t["Andorra"] = QLocale::Andorra;
    t["Angola"] = QLocale::Angola;
    t["Anguilla"] = QLocale::Anguilla;
    t["Antarctica"] = QLocale::Antarctica;
    t["AntiguaAndBarbuda"] = QLocale::AntiguaAndBarbuda;
    t["Argentina"] = QLocale::Argentina;
    t["Armenia"] = QLocale::Armenia;
    t["Aruba"] = QLocale::Aruba;
    t["Australia"] = QLocale::Australia;
    t["Austria"] = QLocale::Austria;
    t["Azerbaijan"] = QLocale::Azerbaijan;
    t["Bahamas"] = QLocale::Bahamas;
    t["Bahrain"] = QLocale::Bahrain;
    t["Bangladesh"] = QLocale::Bangladesh;
    t["Barbados"] = QLocale::Barbados;
    t["Belarus"] = QLocale::Belarus;
    t["Belgium"] = QLocale::Belgium;
    t["Belize"] = QLocale::Belize;
    t["Benin"] = QLocale::Benin;
    t["Bermuda"] = QLocale::Bermuda;
    t["Bhutan"] = QLocale::Bhutan;
    t["Bolivia"] = QLocale::Bolivia;
    t["BosniaAndHerzegowina"] = QLocale::BosniaAndHerzegowina;
    t["Botswana"] = QLocale::Botswana;
    t["BouvetIsland"] = QLocale::BouvetIsland;
    t["Brazil"] = QLocale::Brazil;
    t["BritishIndianOceanTerritory"] = QLocale::BritishIndianOceanTerritory;
    t["Brunei"] = QLocale::Brunei;
    t["Bulgaria"] = QLocale::Bulgaria;
    t["BurkinaFaso"] = QLocale::BurkinaFaso;
    t["Burundi"] = QLocale::Burundi;
    t["Cambodia"] = QLocale::Cambodia;
    t["Cameroon"] = QLocale::Cameroon;
    t["Canada"] = QLocale::Canada;
    t["CanaryIslands"] = QLocale::CanaryIslands;
    t["CapeVerde"] = QLocale::CapeVerde;
    t["CaymanIslands"] = QLocale::CaymanIslands;
    t["CentralAfricanRepublic"] = QLocale::CentralAfricanRepublic;
    t["Chad"] = QLocale::Chad;
    t["Chile"] = QLocale::Chile;
    t["China"] = QLocale::China;
    t["ChristmasIsland"] = QLocale::ChristmasIsland;
    t["ClippertonIsland"] = QLocale::ClippertonIsland;
    t["CocosIslands"] = QLocale::CocosIslands;
    t["Colombia"] = QLocale::Colombia;
    t["Comoros"] = QLocale::Comoros;
    t["CongoKinshasa"] = QLocale::CongoKinshasa;
    t["CongoBrazzaville"] = QLocale::CongoBrazzaville;
    t["DemocraticRepublicOfCongo"] = QLocale::DemocraticRepublicOfCongo;
    t["PeoplesRepublicOfCongo"] = QLocale::PeoplesRepublicOfCongo;
    t["CookIslands"] = QLocale::CookIslands;
    t["CostaRica"] = QLocale::CostaRica;
    t["IvoryCoast"] = QLocale::IvoryCoast;
    t["Croatia"] = QLocale::Croatia;
    t["Cuba"] = QLocale::Cuba;
    t["Cyprus"] = QLocale::Cyprus;
    t["CzechRepublic"] = QLocale::CzechRepublic;
    t["Denmark"] = QLocale::Denmark;
    t["Djibouti"] = QLocale::Djibouti;
    t["Dominica"] = QLocale::Dominica;
    t["DominicanRepublic"] = QLocale::DominicanRepublic;
    t["EastTimor"] = QLocale::EastTimor;
    t["Ecuador"] = QLocale::Ecuador;
    t["Egypt"] = QLocale::Egypt;
    t["ElSalvador"] = QLocale::ElSalvador;
    t["EquatorialGuinea"] = QLocale::EquatorialGuinea;
    t["Eritrea"] = QLocale::Eritrea;
    t["Estonia"] = QLocale::Estonia;
    t["Ethiopia"] = QLocale::Ethiopia;
    t["FalklandIslands"] = QLocale::FalklandIslands;
    t["FaroeIslands"] = QLocale::FaroeIslands;
    t["Fiji"] = QLocale::Fiji;
    t["Finland"] = QLocale::Finland;
    t["France"] = QLocale::France;
    t["FrenchGuiana"] = QLocale::FrenchGuiana;
    t["FrenchPolynesia"] = QLocale::FrenchPolynesia;
    t["FrenchSouthernTerritories"] = QLocale::FrenchSouthernTerritories;
    t["Gabon"] = QLocale::Gabon;
    t["Gambia"] = QLocale::Gambia;
    t["Georgia"] = QLocale::Georgia;
    t["Germany"] = QLocale::Germany;
    t["Ghana"] = QLocale::Ghana;
    t["Gibraltar"] = QLocale::Gibraltar;
    t["Greece"] = QLocale::Greece;
    t["Greenland"] = QLocale::Greenland;
    t["Grenada"] = QLocale::Grenada;
    t["Guadeloupe"] = QLocale::Guadeloupe;
    t["Guam"] = QLocale::Guam;
    t["Guatemala"] = QLocale::Guatemala;
    t["Guernsey"] = QLocale::Guernsey;
    t["Guinea"] = QLocale::Guinea;
    t["GuineaBissau"] = QLocale::GuineaBissau;
    t["Guyana"] = QLocale::Guyana;
    t["Haiti"] = QLocale::Haiti;
    t["HeardAndMcDonaldIslands"] = QLocale::HeardAndMcDonaldIslands;
    t["Honduras"] = QLocale::Honduras;
    t["HongKong"] = QLocale::HongKong;
    t["Hungary"] = QLocale::Hungary;
    t["Iceland"] = QLocale::Iceland;
    t["India"] = QLocale::India;
    t["Indonesia"] = QLocale::Indonesia;
    t["Iran"] = QLocale::Iran;
    t["Iraq"] = QLocale::Iraq;
    t["Ireland"] = QLocale::Ireland;
    t["Israel"] = QLocale::Israel;
    t["Italy"] = QLocale::Italy;
    t["Jamaica"] = QLocale::Jamaica;
    t["Japan"] = QLocale::Japan;
    t["Jordan"] = QLocale::Jordan;
    t["Kazakhstan"] = QLocale::Kazakhstan;
    t["Kenya"] = QLocale::Kenya;
    t["Kiribati"] = QLocale::Kiribati;
    t["NorthKorea"] = QLocale::NorthKorea;
    t["SouthKorea"] = QLocale::SouthKorea;
    t["DemocraticRepublicOfKorea"] = QLocale::DemocraticRepublicOfKorea;
    t["RepublicOfKorea"] = QLocale::RepublicOfKorea;
    t["Kosovo"] = QLocale::Kosovo;
    t["Kuwait"] = QLocale::Kuwait;
    t["Kyrgyzstan"] = QLocale::Kyrgyzstan;
    t["Laos"] = QLocale::Laos;
    t["Latvia"] = QLocale::Latvia;
    t["Lebanon"] = QLocale::Lebanon;
    t["Lesotho"] = QLocale::Lesotho;
    t["Liberia"] = QLocale::Liberia;
    t["Libya"] = QLocale::Libya;
    t["Liechtenstein"] = QLocale::Liechtenstein;
    t["Lithuania"] = QLocale::Lithuania;
    t["Luxembourg"] = QLocale::Luxembourg;
    t["Macau"] = QLocale::Macau;
    t["Macedonia"] = QLocale::Macedonia;
    t["Madagascar"] = QLocale::Madagascar;
    t["Malawi"] = QLocale::Malawi;
    t["Malaysia"] = QLocale::Malaysia;
    t["Maldives"] = QLocale::Maldives;
    t["Mali"] = QLocale::Mali;
    t["Malta"] = QLocale::Malta;
    t["MarshallIslands"] = QLocale::MarshallIslands;
    t["Martinique"] = QLocale::Martinique;
    t["Mauritania"] = QLocale::Mauritania;
    t["Mauritius"] = QLocale::Mauritius;
    t["Mayotte"] = QLocale::Mayotte;
    t["Mexico"] = QLocale::Mexico;
    t["Micronesia"] = QLocale::Micronesia;
    t["Moldova"] = QLocale::Moldova;
    t["Monaco"] = QLocale::Monaco;
    t["Mongolia"] = QLocale::Mongolia;
    t["Montserrat"] = QLocale::Montserrat;
    t["Morocco"] = QLocale::Morocco;
    t["Mozambique"] = QLocale::Mozambique;
    t["Myanmar"] = QLocale::Myanmar;
    t["Namibia"] = QLocale::Namibia;
    t["NauruCountry"] = QLocale::NauruCountry;
    t["Nepal"] = QLocale::Nepal;
    t["Netherlands"] = QLocale::Netherlands;
    t["NewCaledonia"] = QLocale::NewCaledonia;
    t["NewZealand"] = QLocale::NewZealand;
    t["Nicaragua"] = QLocale::Nicaragua;
    t["Niger"] = QLocale::Niger;
    t["Nigeria"] = QLocale::Nigeria;
    t["Niue"] = QLocale::Niue;
    t["NorfolkIsland"] = QLocale::NorfolkIsland;
    t["NorthernMarianaIslands"] = QLocale::NorthernMarianaIslands;
    t["Norway"] = QLocale::Norway;
    t["Oman"] = QLocale::Oman;
    t["Pakistan"] = QLocale::Pakistan;
    t["Palau"] = QLocale::Palau;
    t["PalestinianTerritories"] = QLocale::PalestinianTerritories;
    t["Panama"] = QLocale::Panama;
    t["PapuaNewGuinea"] = QLocale::PapuaNewGuinea;
    t["Paraguay"] = QLocale::Paraguay;
    t["Peru"] = QLocale::Peru;
    t["Philippines"] = QLocale::Philippines;
    t["Pitcairn"] = QLocale::Pitcairn;
    t["Poland"] = QLocale::Poland;
    t["Portugal"] = QLocale::Portugal;
    t["PuertoRico"] = QLocale::PuertoRico;
    t["Qatar"] = QLocale::Qatar;
    t["Reunion"] = QLocale::Reunion;
    t["Romania"] = QLocale::Romania;
    t["Russia"] = QLocale::Russia;
    t["RussianFederation"] = QLocale::RussianFederation;
    t["Rwanda"] = QLocale::Rwanda;
    t["SaintKittsAndNevis"] = QLocale::SaintKittsAndNevis;
    t["SaintLucia"] = QLocale::SaintLucia;
    t["SaintVincentAndTheGrenadines"] = QLocale::SaintVincentAndTheGrenadines;
    t["Samoa"] = QLocale::Samoa;
    t["SanMarino"] = QLocale::SanMarino;
    t["SaoTomeAndPrincipe"] = QLocale::SaoTomeAndPrincipe;
    t["SaudiArabia"] = QLocale::SaudiArabia;
    t["Senegal"] = QLocale::Senegal;
    t["Seychelles"] = QLocale::Seychelles;
    t["SierraLeone"] = QLocale::SierraLeone;
    t["Singapore"] = QLocale::Singapore;
    t["Slovakia"] = QLocale::Slovakia;
    t["Slovenia"] = QLocale::Slovenia;
    t["SolomonIslands"] = QLocale::SolomonIslands;
    t["Somalia"] = QLocale::Somalia;
    t["SouthAfrica"] = QLocale::SouthAfrica;
    t["SouthGeorgiaAndTheSouthSandwichIslands"] = QLocale::SouthGeorgiaAndTheSouthSandwichIslands;
    t["Spain"] = QLocale::Spain;
    t["SriLanka"] = QLocale::SriLanka;
    t["SaintHelena"] = QLocale::SaintHelena;
    t["SaintPierreAndMiquelon"] = QLocale::SaintPierreAndMiquelon;
    t["Sudan"] = QLocale::Sudan;
    t["Suriname"] = QLocale::Suriname;
    t["SvalbardAndJanMayenIslands"] = QLocale::SvalbardAndJanMayenIslands;
    t["Swaziland"] = QLocale::Swaziland;
    t["Sweden"] = QLocale::Sweden;
    t["Switzerland"] = QLocale::Switzerland;
    t["Syria"] = QLocale::Syria;
    t["SyrianArabRepublic"] = QLocale::SyrianArabRepublic;
    t["Taiwan"] = QLocale::Taiwan;
    t["Tajikistan"] = QLocale::Tajikistan;
    t["Tanzania"] = QLocale::Tanzania;
    t["Thailand"] = QLocale::Thailand;
    t["Togo"] = QLocale::Togo;
    t["Tokelau"] = QLocale::Tokelau;
    t["Tonga"] = QLocale::Tonga;
    t["TrinidadAndTobago"] = QLocale::TrinidadAndTobago;
    t["Tunisia"] = QLocale::Tunisia;
    t["Turkey"] = QLocale::Turkey;
    t["Turkmenistan"] = QLocale::Turkmenistan;
    t["TurksAndCaicosIslands"] = QLocale::TurksAndCaicosIslands;
    t["Tuvalu"] = QLocale::Tuvalu;
    t["Uganda"] = QLocale::Uganda;
    t["Ukraine"] = QLocale::Ukraine;
    t["UnitedArabEmirates"] = QLocale::UnitedArabEmirates;
    t["UnitedKingdom"] = QLocale::UnitedKingdom;
    t["UnitedStates"] = QLocale::UnitedStates;
    t["UnitedStatesMinorOutlyingIslands"] = QLocale::UnitedStatesMinorOutlyingIslands;
    t["Uruguay"] = QLocale::Uruguay;
    t["Uzbekistan"] = QLocale::Uzbekistan;
    t["Vanuatu"] = QLocale::Vanuatu;
    t["VaticanCityState"] = QLocale::VaticanCityState;
    t["Venezuela"] = QLocale::Venezuela;
    t["Vietnam"] = QLocale::Vietnam;
    t["BritishVirginIslands"] = QLocale::BritishVirginIslands;
    t["UnitedStatesVirginIslands"] = QLocale::UnitedStatesVirginIslands;
    t["WallisAndFutunaIslands"] = QLocale::WallisAndFutunaIslands;
    t["WesternSahara"] = QLocale::WesternSahara;
    t["Yemen"] = QLocale::Yemen;
    t["Zambia"] = QLocale::Zambia;
    t["Zimbabwe"] = QLocale::Zimbabwe;
    t["Montenegro"] = QLocale::Montenegro;
    t["Serbia"] = QLocale::Serbia;
    t["SaintBarthelemy"] = QLocale::SaintBarthelemy;
    t["SaintMartin"] = QLocale::SaintMartin;
    t["LatinAmericaAndTheCaribbean"] = QLocale::LatinAmericaAndTheCaribbean;
    t["AscensionIsland"] = QLocale::AscensionIsland;
    t["AlandIslands"] = QLocale::AlandIslands;
    t["DiegoGarcia"] = QLocale::DiegoGarcia;
    t["CeutaAndMelilla"] = QLocale::CeutaAndMelilla;
    t["IsleOfMan"] = QLocale::IsleOfMan;
    t["Jersey"] = QLocale::Jersey;
    t["TristanDaCunha"] = QLocale::TristanDaCunha;
    t["SouthSudan"] = QLocale::SouthSudan;
    t["CuraSao"] = QLocale::CuraSao;
    t["Bonaire"] = QLocale::Bonaire;
    t["SintMaarten"] = QLocale::SintMaarten;

    // enum QLocale::CurrencySymbolFormat
    t["CurrencyIsoCode"] = QLocale::CurrencyIsoCode;
    t["CurrencySymbol"] = QLocale::CurrencySymbol;
    t["CurrencyDisplayName"] = QLocale::CurrencyDisplayName;

    // enum QLocale::FormatType
    t["LongFormat"] = QLocale::LongFormat;
    t["ShortFormat"] = QLocale::ShortFormat;
    t["NarrowFormat"] = QLocale::NarrowFormat;

    // enum QLocale::Language
    t["AnyLanguage"] = QLocale::AnyLanguage;
    t["C  1"] = QLocale::C  1;
    t["Abkhazian"] = QLocale::Abkhazian;
    t["Oromo"] = QLocale::Oromo;
    t["Afan"] = QLocale::Afan;
    t["Afar"] = QLocale::Afar;
    t["Afrikaans"] = QLocale::Afrikaans;
    t["Akoose"] = QLocale::Akoose;
    t["Albanian"] = QLocale::Albanian;
    t["Amharic"] = QLocale::Amharic;
    t["Arabic"] = QLocale::Arabic;
    t["Armenian"] = QLocale::Armenian;
    t["Assamese"] = QLocale::Assamese;
    t["Avaric"] = QLocale::Avaric;
    t["Aymara"] = QLocale::Aymara;
    t["Azerbaijani"] = QLocale::Azerbaijani;
    t["Bashkir"] = QLocale::Bashkir;
    t["Basque"] = QLocale::Basque;
    t["Bengali"] = QLocale::Bengali;
    t["Dzongkha"] = QLocale::Dzongkha;
    t["Bhutani"] = QLocale::Bhutani;
    t["Bihari"] = QLocale::Bihari;
    t["Bislama"] = QLocale::Bislama;
    t["Bosnian"] = QLocale::Bosnian;
    t["Bodo"] = QLocale::Bodo;
    t["Breton"] = QLocale::Breton;
    t["Bulgarian"] = QLocale::Bulgarian;
    t["Burmese"] = QLocale::Burmese;
    t["Belarusian"] = QLocale::Belarusian;
    t["Byelorussian"] = QLocale::Byelorussian;
    t["Khmer"] = QLocale::Khmer;
    t["Cambodian"] = QLocale::Cambodian;
    t["Catalan"] = QLocale::Catalan;
    t["Chamorro"] = QLocale::Chamorro;
    t["Chechen"] = QLocale::Chechen;
    t["Chinese"] = QLocale::Chinese;
    t["Church"] = QLocale::Church;
    t["Chuvash"] = QLocale::Chuvash;
    t["Cornish"] = QLocale::Cornish;
    t["Corsican"] = QLocale::Corsican;
    t["Cree"] = QLocale::Cree;
    t["Croatian"] = QLocale::Croatian;
    t["Czech"] = QLocale::Czech;
    t["Danish"] = QLocale::Danish;
    t["Divehi"] = QLocale::Divehi;
    t["Dutch"] = QLocale::Dutch;
    t["English"] = QLocale::English;
    t["Esperanto"] = QLocale::Esperanto;
    t["Estonian"] = QLocale::Estonian;
    t["Faroese"] = QLocale::Faroese;
    t["Fijian"] = QLocale::Fijian;
    t["Finnish"] = QLocale::Finnish;
    t["French"] = QLocale::French;
    t["WesternFrisian"] = QLocale::WesternFrisian;
    t["Frisian"] = QLocale::Frisian;
    t["Gaelic"] = QLocale::Gaelic;
    t["Galician"] = QLocale::Galician;
    t["Georgian"] = QLocale::Georgian;
    t["German"] = QLocale::German;
    t["Greek"] = QLocale::Greek;
    t["Greenlandic"] = QLocale::Greenlandic;
    t["Guarani"] = QLocale::Guarani;
    t["Gujarati"] = QLocale::Gujarati;
    t["Haitian"] = QLocale::Haitian;
    t["Hausa"] = QLocale::Hausa;
    t["Hebrew"] = QLocale::Hebrew;
    t["Herero"] = QLocale::Herero;
    t["Hindi"] = QLocale::Hindi;
    t["HiriMotu"] = QLocale::HiriMotu;
    t["Hungarian"] = QLocale::Hungarian;
    t["Icelandic"] = QLocale::Icelandic;
    t["Indonesian"] = QLocale::Indonesian;
    t["Interlingua"] = QLocale::Interlingua;
    t["Interlingue"] = QLocale::Interlingue;
    t["Inuktitut"] = QLocale::Inuktitut;
    t["Inupiak"] = QLocale::Inupiak;
    t["Irish"] = QLocale::Irish;
    t["Italian"] = QLocale::Italian;
    t["Japanese"] = QLocale::Japanese;
    t["Javanese"] = QLocale::Javanese;
    t["Kannada"] = QLocale::Kannada;
    t["Kanuri"] = QLocale::Kanuri;
    t["Kashmiri"] = QLocale::Kashmiri;
    t["Kazakh"] = QLocale::Kazakh;
    t["Kinyarwanda"] = QLocale::Kinyarwanda;
    t["Kirghiz"] = QLocale::Kirghiz;
    t["Komi"] = QLocale::Komi;
    t["Kongo"] = QLocale::Kongo;
    t["Korean"] = QLocale::Korean;
    t["Kurdish"] = QLocale::Kurdish;
    t["Rundi"] = QLocale::Rundi;
    t["Kurundi"] = QLocale::Kurundi;
    t["Kwanyama"] = QLocale::Kwanyama;
    t["Lakota"] = QLocale::Lakota;
    t["Lao"] = QLocale::Lao;
    t["Latin"] = QLocale::Latin;
    t["Latvian"] = QLocale::Latvian;
    t["Limburgish"] = QLocale::Limburgish;
    t["Lingala"] = QLocale::Lingala;
    t["Lithuanian"] = QLocale::Lithuanian;
    t["LubaKatanga"] = QLocale::LubaKatanga;
    t["Luxembourgish"] = QLocale::Luxembourgish;
    t["Marshallese"] = QLocale::Marshallese;
    t["Macedonian"] = QLocale::Macedonian;
    t["Malagasy"] = QLocale::Malagasy;
    t["Malay"] = QLocale::Malay;
    t["Malayalam"] = QLocale::Malayalam;
    t["Maltese"] = QLocale::Maltese;
    t["Manx"] = QLocale::Manx;
    t["Maori"] = QLocale::Maori;
    t["Marathi"] = QLocale::Marathi;
    t["Moldavian"] = QLocale::Moldavian;
    t["Mongolian"] = QLocale::Mongolian;
    t["NauruLanguage"] = QLocale::NauruLanguage;
    t["Navaho"] = QLocale::Navaho;
    t["Ndonga"] = QLocale::Ndonga;
    t["Nepali"] = QLocale::Nepali;
    t["Norwegian"] = QLocale::Norwegian;
    t["NorwegianBokmal"] = QLocale::NorwegianBokmal;
    t["NorwegianNynorsk"] = QLocale::NorwegianNynorsk;
    t["Occitan"] = QLocale::Occitan;
    t["Ojibwa"] = QLocale::Ojibwa;
    t["Oriya"] = QLocale::Oriya;
    t["Ossetic"] = QLocale::Ossetic;
    t["Pali"] = QLocale::Pali;
    t["Pashto"] = QLocale::Pashto;
    t["Persian"] = QLocale::Persian;
    t["Polish"] = QLocale::Polish;
    t["Portuguese"] = QLocale::Portuguese;
    t["Punjabi"] = QLocale::Punjabi;
    t["Quechua"] = QLocale::Quechua;
    t["Romansh"] = QLocale::Romansh;
    t["RhaetoRomance"] = QLocale::RhaetoRomance;
    t["Romanian"] = QLocale::Romanian;
    t["Russian"] = QLocale::Russian;
    t["Samoan"] = QLocale::Samoan;
    t["Sango"] = QLocale::Sango;
    t["Sanskrit"] = QLocale::Sanskrit;
    t["Sardinian"] = QLocale::Sardinian;
    t["Serbian"] = QLocale::Serbian;
    t["SerboCroatian"] = QLocale::SerboCroatian;
    t["SouthernSotho"] = QLocale::SouthernSotho;
    t["Tswana"] = QLocale::Tswana;
    t["Shona"] = QLocale::Shona;
    t["Sindhi"] = QLocale::Sindhi;
    t["Sinhala"] = QLocale::Sinhala;
    t["Swati"] = QLocale::Swati;
    t["Slovak"] = QLocale::Slovak;
    t["Slovenian"] = QLocale::Slovenian;
    t["Somali"] = QLocale::Somali;
    t["Spanish"] = QLocale::Spanish;
    t["StandardMoroccanTamazight"] = QLocale::StandardMoroccanTamazight;
    t["Sundanese"] = QLocale::Sundanese;
    t["Swahili"] = QLocale::Swahili;
    t["Swedish"] = QLocale::Swedish;
    t["Tagalog"] = QLocale::Tagalog;
    t["Tahitian"] = QLocale::Tahitian;
    t["Tajik"] = QLocale::Tajik;
    t["Tamil"] = QLocale::Tamil;
    t["Tatar"] = QLocale::Tatar;
    t["Telugu"] = QLocale::Telugu;
    t["Thai"] = QLocale::Thai;
    t["Tibetan"] = QLocale::Tibetan;
    t["Tigrinya"] = QLocale::Tigrinya;
    t["Tongan"] = QLocale::Tongan;
    t["Tsonga"] = QLocale::Tsonga;
    t["Turkish"] = QLocale::Turkish;
    t["Turkmen"] = QLocale::Turkmen;
    t["Twi"] = QLocale::Twi;
    t["Uighur"] = QLocale::Uighur;
    t["Uigur"] = QLocale::Uigur;
    t["Ukrainian"] = QLocale::Ukrainian;
    t["Urdu"] = QLocale::Urdu;
    t["Uzbek"] = QLocale::Uzbek;
    t["Vietnamese"] = QLocale::Vietnamese;
    t["Volapuk"] = QLocale::Volapuk;
    t["Walloon"] = QLocale::Walloon;
    t["Welsh"] = QLocale::Welsh;
    t["Wolof"] = QLocale::Wolof;
    t["Xhosa"] = QLocale::Xhosa;
    t["Yiddish"] = QLocale::Yiddish;
    t["Yoruba"] = QLocale::Yoruba;
    t["Zhuang"] = QLocale::Zhuang;
    t["Zulu"] = QLocale::Zulu;
    t["Bosnian"] = QLocale::Bosnian;
    t["Divehi"] = QLocale::Divehi;
    t["Manx"] = QLocale::Manx;
    t["Cornish"] = QLocale::Cornish;
    t["Akan"] = QLocale::Akan;
    t["Konkani"] = QLocale::Konkani;
    t["Ga"] = QLocale::Ga;
    t["Igbo"] = QLocale::Igbo;
    t["Kamba"] = QLocale::Kamba;
    t["Syriac"] = QLocale::Syriac;
    t["Blin"] = QLocale::Blin;
    t["Geez"] = QLocale::Geez;
    t["Koro"] = QLocale::Koro;
    t["Sidamo"] = QLocale::Sidamo;
    t["Atsam"] = QLocale::Atsam;
    t["Tigre"] = QLocale::Tigre;
    t["Jju"] = QLocale::Jju;
    t["Friulian"] = QLocale::Friulian;
    t["Venda"] = QLocale::Venda;
    t["Ewe"] = QLocale::Ewe;
    t["Walamo"] = QLocale::Walamo;
    t["Hawaiian"] = QLocale::Hawaiian;
    t["Tyap"] = QLocale::Tyap;
    t["Nyanja"] = QLocale::Nyanja;
    t["Chewa"] = QLocale::Chewa;
    t["Filipino"] = QLocale::Filipino;
    t["SwissGerman"] = QLocale::SwissGerman;
    t["SichuanYi"] = QLocale::SichuanYi;
    t["Kpelle"] = QLocale::Kpelle;
    t["LowGerman"] = QLocale::LowGerman;
    t["SouthNdebele"] = QLocale::SouthNdebele;
    t["NorthernSotho"] = QLocale::NorthernSotho;
    t["NorthernSami"] = QLocale::NorthernSami;
    t["Taroko"] = QLocale::Taroko;
    t["Gusii"] = QLocale::Gusii;
    t["Taita"] = QLocale::Taita;
    t["Fulah"] = QLocale::Fulah;
    t["Kikuyu"] = QLocale::Kikuyu;
    t["Samburu"] = QLocale::Samburu;
    t["Sena"] = QLocale::Sena;
    t["NorthNdebele"] = QLocale::NorthNdebele;
    t["Rombo"] = QLocale::Rombo;
    t["Tachelhit"] = QLocale::Tachelhit;
    t["Kabyle"] = QLocale::Kabyle;
    t["Nyankole"] = QLocale::Nyankole;
    t["Bena"] = QLocale::Bena;
    t["Vunjo"] = QLocale::Vunjo;
    t["Bambara"] = QLocale::Bambara;
    t["Embu"] = QLocale::Embu;
    t["Cherokee"] = QLocale::Cherokee;
    t["Morisyen"] = QLocale::Morisyen;
    t["Makonde"] = QLocale::Makonde;
    t["Langi"] = QLocale::Langi;
    t["Ganda"] = QLocale::Ganda;
    t["Bemba"] = QLocale::Bemba;
    t["Kabuverdianu"] = QLocale::Kabuverdianu;
    t["Meru"] = QLocale::Meru;
    t["Kalenjin"] = QLocale::Kalenjin;
    t["Nama"] = QLocale::Nama;
    t["Machame"] = QLocale::Machame;
    t["Colognian"] = QLocale::Colognian;
    t["Masai"] = QLocale::Masai;
    t["Soga"] = QLocale::Soga;
    t["Luyia"] = QLocale::Luyia;
    t["Asu"] = QLocale::Asu;
    t["Teso"] = QLocale::Teso;
    t["Saho"] = QLocale::Saho;
    t["KoyraChiini"] = QLocale::KoyraChiini;
    t["Rwa"] = QLocale::Rwa;
    t["Luo"] = QLocale::Luo;
    t["Chiga"] = QLocale::Chiga;
    t["CentralMoroccoTamazight"] = QLocale::CentralMoroccoTamazight;
    t["KoyraboroSenni"] = QLocale::KoyraboroSenni;
    t["Shambala"] = QLocale::Shambala;
    t["Aghem"] = QLocale::Aghem;
    t["Basaa"] = QLocale::Basaa;
    t["Zarma"] = QLocale::Zarma;
    t["Duala"] = QLocale::Duala;
    t["JolaFonyi"] = QLocale::JolaFonyi;
    t["Ewondo"] = QLocale::Ewondo;
    t["Bafia"] = QLocale::Bafia;
    t["MakhuwaMeetto"] = QLocale::MakhuwaMeetto;
    t["Mundang"] = QLocale::Mundang;
    t["Kwasio"] = QLocale::Kwasio;
    t["Nuer"] = QLocale::Nuer;
    t["Sakha"] = QLocale::Sakha;
    t["Sangu"] = QLocale::Sangu;
    t["CongoSwahili"] = QLocale::CongoSwahili;
    t["Tasawaq"] = QLocale::Tasawaq;
    t["Vai"] = QLocale::Vai;
    t["Walser"] = QLocale::Walser;
    t["Yangben"] = QLocale::Yangben;
    t["Avestan"] = QLocale::Avestan;
    t["Asturian"] = QLocale::Asturian;
    t["Ngomba"] = QLocale::Ngomba;
    t["Kako"] = QLocale::Kako;
    t["Meta"] = QLocale::Meta;
    t["Ngiemboon"] = QLocale::Ngiemboon;
    t["Aragonese"] = QLocale::Aragonese;
    t["Akkadian"] = QLocale::Akkadian;
    t["AncientEgyptian"] = QLocale::AncientEgyptian;
    t["AncientGreek"] = QLocale::AncientGreek;
    t["Aramaic"] = QLocale::Aramaic;
    t["Balinese"] = QLocale::Balinese;
    t["Bamun"] = QLocale::Bamun;
    t["BatakToba"] = QLocale::BatakToba;
    t["Buginese"] = QLocale::Buginese;
    t["Buhid"] = QLocale::Buhid;
    t["Carian"] = QLocale::Carian;
    t["Chakma"] = QLocale::Chakma;
    t["ClassicalMandaic"] = QLocale::ClassicalMandaic;
    t["Coptic"] = QLocale::Coptic;
    t["Dogri"] = QLocale::Dogri;
    t["EasternCham"] = QLocale::EasternCham;
    t["EasternKayah"] = QLocale::EasternKayah;
    t["Etruscan"] = QLocale::Etruscan;
    t["Gothic"] = QLocale::Gothic;
    t["Hanunoo"] = QLocale::Hanunoo;
    t["Ingush"] = QLocale::Ingush;
    t["LargeFloweryMiao"] = QLocale::LargeFloweryMiao;
    t["Lepcha"] = QLocale::Lepcha;
    t["Limbu"] = QLocale::Limbu;
    t["Lisu"] = QLocale::Lisu;
    t["Lu"] = QLocale::Lu;
    t["Lycian"] = QLocale::Lycian;
    t["Lydian"] = QLocale::Lydian;
    t["Mandingo"] = QLocale::Mandingo;
    t["Manipuri"] = QLocale::Manipuri;
    t["Meroitic"] = QLocale::Meroitic;
    t["NorthernThai"] = QLocale::NorthernThai;
    t["OldIrish"] = QLocale::OldIrish;
    t["OldNorse"] = QLocale::OldNorse;
    t["OldPersian"] = QLocale::OldPersian;
    t["OldTurkish"] = QLocale::OldTurkish;
    t["Pahlavi"] = QLocale::Pahlavi;
    t["Parthian"] = QLocale::Parthian;
    t["Phoenician"] = QLocale::Phoenician;
    t["PrakritLanguage"] = QLocale::PrakritLanguage;
    t["Rejang"] = QLocale::Rejang;
    t["Sabaean"] = QLocale::Sabaean;
    t["Samaritan"] = QLocale::Samaritan;
    t["Santali"] = QLocale::Santali;
    t["Saurashtra"] = QLocale::Saurashtra;
    t["Sora"] = QLocale::Sora;
    t["Sylheti"] = QLocale::Sylheti;
    t["Tagbanwa"] = QLocale::Tagbanwa;
    t["TaiDam"] = QLocale::TaiDam;
    t["TaiNua"] = QLocale::TaiNua;
    t["Ugaritic"] = QLocale::Ugaritic;

    // enum QLocale::MeasurementSystem
    t["MetricSystem"] = QLocale::MetricSystem;
    t["ImperialUSSystem"] = QLocale::ImperialUSSystem;
    t["ImperialUKSystem"] = QLocale::ImperialUKSystem;
    t["ImperialSystem"] = QLocale::ImperialSystem;

    // enum QLocale::NumberOption
    // flags QLocale::NumberOptions
    t["OmitGroupSeparator"] = QLocale::OmitGroupSeparator;
    t["RejectGroupSeparator"] = QLocale::RejectGroupSeparator;

    // enum QLocale::QuotationStyle
    t["StandardQuotation"] = QLocale::StandardQuotation;
    t["AlternateQuotation"] = QLocale::AlternateQuotation;

    // enum QLocale::Script
    t["AnyScript"] = QLocale::AnyScript;
    t["ArabicScript"] = QLocale::ArabicScript;
    t["ArmenianScript"] = QLocale::ArmenianScript;
    t["AvestanScript"] = QLocale::AvestanScript;
    t["BalineseScript"] = QLocale::BalineseScript;
    t["BamumScript"] = QLocale::BamumScript;
    t["BatakScript"] = QLocale::BatakScript;
    t["BengaliScript"] = QLocale::BengaliScript;
    t["BopomofoScript"] = QLocale::BopomofoScript;
    t["BrahmiScript"] = QLocale::BrahmiScript;
    t["BrailleScript"] = QLocale::BrailleScript;
    t["BugineseScript"] = QLocale::BugineseScript;
    t["BuhidScript"] = QLocale::BuhidScript;
    t["CanadianAboriginalScript"] = QLocale::CanadianAboriginalScript;
    t["CarianScript"] = QLocale::CarianScript;
    t["ChakmaScript"] = QLocale::ChakmaScript;
    t["ChamScript"] = QLocale::ChamScript;
    t["CherokeeScript"] = QLocale::CherokeeScript;
    t["CopticScript"] = QLocale::CopticScript;
    t["CypriotScript"] = QLocale::CypriotScript;
    t["CyrillicScript"] = QLocale::CyrillicScript;
    t["DeseretScript"] = QLocale::DeseretScript;
    t["DevanagariScript"] = QLocale::DevanagariScript;
    t["EgyptianHieroglyphsScript"] = QLocale::EgyptianHieroglyphsScript;
    t["EthiopicScript"] = QLocale::EthiopicScript;
    t["FraserScript"] = QLocale::FraserScript;
    t["GeorgianScript"] = QLocale::GeorgianScript;
    t["GlagoliticScript"] = QLocale::GlagoliticScript;
    t["GothicScript"] = QLocale::GothicScript;
    t["GreekScript"] = QLocale::GreekScript;
    t["GujaratiScript"] = QLocale::GujaratiScript;
    t["GurmukhiScript"] = QLocale::GurmukhiScript;
    t["HanScript"] = QLocale::HanScript;
    t["HangulScript"] = QLocale::HangulScript;
    t["HanunooScript"] = QLocale::HanunooScript;
    t["HebrewScript"] = QLocale::HebrewScript;
    t["HiraganaScript"] = QLocale::HiraganaScript;
    t["ImperialAramaicScript"] = QLocale::ImperialAramaicScript;
    t["InscriptionalPahlaviScript"] = QLocale::InscriptionalPahlaviScript;
    t["InscriptionalParthianScript"] = QLocale::InscriptionalParthianScript;
    t["JapaneseScript"] = QLocale::JapaneseScript;
    t["JavaneseScript"] = QLocale::JavaneseScript;
    t["KaithiScript"] = QLocale::KaithiScript;
    t["KannadaScript"] = QLocale::KannadaScript;
    t["KatakanaScript"] = QLocale::KatakanaScript;
    t["KayahLiScript"] = QLocale::KayahLiScript;
    t["KharoshthiScript"] = QLocale::KharoshthiScript;
    t["KhmerScript"] = QLocale::KhmerScript;
    t["KoreanScript"] = QLocale::KoreanScript;
    t["LannaScript"] = QLocale::LannaScript;
    t["LaoScript"] = QLocale::LaoScript;
    t["LatinScript"] = QLocale::LatinScript;
    t["LepchaScript"] = QLocale::LepchaScript;
    t["LimbuScript"] = QLocale::LimbuScript;
    t["LinearBScript"] = QLocale::LinearBScript;
    t["LycianScript"] = QLocale::LycianScript;
    t["LydianScript"] = QLocale::LydianScript;
    t["MalayalamScript"] = QLocale::MalayalamScript;
    t["MandaeanScript"] = QLocale::MandaeanScript;
    t["MeiteiMayekScript"] = QLocale::MeiteiMayekScript;
    t["MeroiticScript"] = QLocale::MeroiticScript;
    t["MeroiticCursiveScript"] = QLocale::MeroiticCursiveScript;
    t["MongolianScript"] = QLocale::MongolianScript;
    t["MyanmarScript"] = QLocale::MyanmarScript;
    t["NkoScript"] = QLocale::NkoScript;
    t["NewTaiLueScript"] = QLocale::NewTaiLueScript;
    t["OghamScript"] = QLocale::OghamScript;
    t["OlChikiScript"] = QLocale::OlChikiScript;
    t["OldItalicScript"] = QLocale::OldItalicScript;
    t["OldPersianScript"] = QLocale::OldPersianScript;
    t["OldSouthArabianScript"] = QLocale::OldSouthArabianScript;
    t["OriyaScript"] = QLocale::OriyaScript;
    t["OrkhonScript"] = QLocale::OrkhonScript;
    t["OsmanyaScript"] = QLocale::OsmanyaScript;
    t["PhagsPaScript"] = QLocale::PhagsPaScript;
    t["PhoenicianScript"] = QLocale::PhoenicianScript;
    t["PollardPhoneticScript"] = QLocale::PollardPhoneticScript;
    t["RejangScript"] = QLocale::RejangScript;
    t["RunicScript"] = QLocale::RunicScript;
    t["SamaritanScript"] = QLocale::SamaritanScript;
    t["SaurashtraScript"] = QLocale::SaurashtraScript;
    t["SharadaScript"] = QLocale::SharadaScript;
    t["ShavianScript"] = QLocale::ShavianScript;
    t["SimplifiedHanScript"] = QLocale::SimplifiedHanScript;
    t["SimplifiedChineseScript"] = QLocale::SimplifiedChineseScript;
    t["SinhalaScript"] = QLocale::SinhalaScript;
    t["SoraSompengScript"] = QLocale::SoraSompengScript;
    t["CuneiformScript"] = QLocale::CuneiformScript;
    t["SundaneseScript"] = QLocale::SundaneseScript;
    t["SylotiNagriScript"] = QLocale::SylotiNagriScript;
    t["SyriacScript"] = QLocale::SyriacScript;
    t["TagalogScript"] = QLocale::TagalogScript;
    t["TagbanwaScript"] = QLocale::TagbanwaScript;
    t["TaiLeScript"] = QLocale::TaiLeScript;
    t["TaiVietScript"] = QLocale::TaiVietScript;
    t["TakriScript"] = QLocale::TakriScript;
    t["TamilScript"] = QLocale::TamilScript;
    t["TeluguScript"] = QLocale::TeluguScript;
    t["ThaanaScript"] = QLocale::ThaanaScript;
    t["ThaiScript"] = QLocale::ThaiScript;
    t["TibetanScript"] = QLocale::TibetanScript;
    t["TifinaghScript"] = QLocale::TifinaghScript;
    t["TraditionalHanScript"] = QLocale::TraditionalHanScript;
    t["TraditionalChineseScript"] = QLocale::TraditionalChineseScript;
    t["UgariticScript"] = QLocale::UgariticScript;
    t["VaiScript"] = QLocale::VaiScript;
    t["YiScript"] = QLocale::YiScript;

    return 0;
}
