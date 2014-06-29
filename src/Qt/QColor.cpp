#include "QColor.hpp"
#include "../lua-cxx/type/function.hpp"
#include "../lua-cxx/thread.hpp"
#include "QString.hpp"

#include <QColor>

void lua::QColor_metatable(const lua::index& mt)
{
    mt["alpha"] = &QColor::alpha;
    mt["alphaF"] = &QColor::alphaF;
    mt["black"] = &QColor::black;
    mt["blackF"] = &QColor::blackF;
    mt["blue"] = &QColor::blue;
    mt["blueF"] = &QColor::blueF;
    mt["convertTo"] = &QColor::convertTo;
    mt["cyan"] = &QColor::cyan;
    mt["cyanF"] = &QColor::cyanF;
    mt["darker"] = &QColor::darker;
//void    getCmyk ( int * c, int * m, int * y, int * k, int * a = 0 )
//void    getCmykF ( qreal * c, qreal * m, qreal * y, qreal * k, qreal * a = 0 )
//void    getHsl ( int * h, int * s, int * l, int * a = 0 ) const
//void    getHslF ( qreal * h, qreal * s, qreal * l, qreal * a = 0 ) const
//void    getHsv ( int * h, int * s, int * v, int * a = 0 ) const
//void    getHsvF ( qreal * h, qreal * s, qreal * v, qreal * a = 0 ) const
//void    getRgb ( int * r, int * g, int * b, int * a = 0 ) const
//void    getRgbF ( qreal * r, qreal * g, qreal * b, qreal * a = 0 ) const
    mt["green"] = &QColor::green;
    mt["greenF"] = &QColor::greenF;
    mt["hslHue"] = &QColor::hslHue;
    mt["hslHueF"] = &QColor::hslHueF;
    mt["hslSaturation"] = &QColor::hslSaturation;
    mt["hslSaturationF"] = &QColor::hslSaturationF;
    mt["hsvHue"] = &QColor::hsvHue;
    mt["hsvHueF"] = &QColor::hsvHueF;
    mt["hsvSaturation"] = &QColor::hsvSaturation;
    mt["hsvSaturationF"] = &QColor::hsvSaturationF;
    mt["hue"] = &QColor::hue;
    mt["hueF"] = &QColor::hueF;
    mt["isValid"] = &QColor::isValid;
    mt["lighter"] = &QColor::lighter;
    mt["lightness"] = &QColor::lightness;
    mt["lightnessF"] = &QColor::lightnessF;
    mt["magenta"] = &QColor::magenta;
    mt["magentaF"] = &QColor::magentaF;
    //mt["name"] = &QColor::name;
    mt["red"] = &QColor::red;
    mt["redF"] = &QColor::redF;
    mt["rgb"] = &QColor::rgb;
    mt["rgba"] = &QColor::rgba;
    mt["saturation"] = &QColor::saturation;
    mt["saturationF"] = &QColor::saturationF;
    mt["setAlpha"] = &QColor::setAlpha;
    mt["setAlphaF"] = &QColor::setAlphaF;
    mt["setBlue"] = &QColor::setBlue;
    mt["setBlueF"] = &QColor::setBlueF;
    mt["setCmyk"] = &QColor::setCmyk;
    mt["setCmykF"] = &QColor::setCmykF;
    mt["setGreen"] = &QColor::setGreen;
    mt["setGreenF"] = &QColor::setGreenF;
    mt["setHsl"] = &QColor::setHsl;
    mt["setHslF"] = &QColor::setHslF;
    mt["setHsv"] = &QColor::setHsv;
    mt["setHsvF"] = &QColor::setHsvF;
    mt["setNamedColor"] = &QColor::setNamedColor;
    mt["setRed"] = &QColor::setRed;
    mt["setRedF"] = &QColor::setRedF;
    //mt["setRgb"] = &QColor::setRgb;
    //mt["setRgb"] = &QColor::setRgb;
    mt["setRgbF"] = &QColor::setRgbF;
    mt["setRgba"] = &QColor::setRgba;
    mt["spec"] = &QColor::spec;
    mt["toCmyk"] = &QColor::toCmyk;
    mt["toHsl"] = &QColor::toHsl;
    mt["toHsv"] = &QColor::toHsv;
    mt["toRgb"] = &QColor::toRgb;
    mt["value"] = &QColor::value;
    mt["valueF"] = &QColor::valueF;
    mt["yellow"] = &QColor::yellow;
    mt["yellowF"] = &QColor::yellowF;
}

int QColor_new(lua_State* const state)
{
    lua::make<QColor>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QColor(lua_State* const state)
{
    lua::thread env(state);

    env["QColor"] = lua::value::table;
    env["QColor"]["new"] = QColor_new;

    return 0;
}
