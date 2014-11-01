#include "QEasingCurve.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../convert/numeric.hpp"
#include "../thread.hpp"

#include "QVector.hpp"
#include "QPointF.hpp"

namespace lua {

void QEasingCurve_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["addCubicBezierSegment"] = &QEasingCurve::addCubicBezierSegment;
    mt["addTCBSegment"] = &QEasingCurve::addTCBSegment;
    mt["amplitude"] = &QEasingCurve::amplitude;
    //mt["customType"] = &QEasingCurve::customType;
    mt["overshoot"] = &QEasingCurve::overshoot;
    mt["period"] = &QEasingCurve::period;
    mt["setAmplitude"] = &QEasingCurve::setAmplitude;
    //mt["setCustomType"] = &QEasingCurve::setCustomType;
    mt["setOvershoot"] = &QEasingCurve::setOvershoot;
    mt["setPeriod"] = &QEasingCurve::setPeriod;
    mt["setType"] = &QEasingCurve::setType;
    mt["swap"] = &QEasingCurve::swap;
    mt["toCubicSpline"] = &QEasingCurve::toCubicSpline;
    mt["type"] = &QEasingCurve::type;
    mt["valueForProgress"] = &QEasingCurve::valueForProgress;
}

} // namespace lua

int QEasingCurve_new(lua_State* const state)
{
    if (lua::is_type<QEasingCurve>(state, 1)) {
        // QEasingCurve(const QEasingCurve & other)
        // QEasingCurve(QEasingCurve && other)
        lua::make<QEasingCurve>(state, lua::get<const QEasingCurve&>(state, 1));
    } else if (lua_gettop(state) > 0) {
        // QEasingCurve(Type type = Linear)
        lua::make<QEasingCurve>(state, lua::get<QEasingCurve::Type>(state, 1));
    } else {
        // QEasingCurve()
        lua::make<QEasingCurve>(state);

    }
    return 1;
}

int luaopen_luacxx_QEasingCurve(lua_State* const state)
{
    lua::thread env(state);

    env["QEasingCurve"] = lua::value::table;
    env["QEasingCurve"]["new"] = QEasingCurve_new;
    auto t = env["QEasingCurve"];

    // enum QEasingCurve::Type
    t["Linear"] = QEasingCurve::Linear;
    t["InQuad"] = QEasingCurve::InQuad;
    t["OutQuad"] = QEasingCurve::OutQuad;
    t["InOutQuad"] = QEasingCurve::InOutQuad;
    t["OutInQuad"] = QEasingCurve::OutInQuad;
    t["InCubic"] = QEasingCurve::InCubic;
    t["OutCubic"] = QEasingCurve::OutCubic;
    t["InOutCubic"] = QEasingCurve::InOutCubic;
    t["OutInCubic"] = QEasingCurve::OutInCubic;
    t["InQuart"] = QEasingCurve::InQuart;
    t["OutQuart"] = QEasingCurve::OutQuart;
    t["InOutQuart"] = QEasingCurve::InOutQuart;
    t["OutInQuart"] = QEasingCurve::OutInQuart;
    t["InQuint"] = QEasingCurve::InQuint;
    t["OutQuint"] = QEasingCurve::OutQuint;
    t["InOutQuint"] = QEasingCurve::InOutQuint;
    t["OutInQuint"] = QEasingCurve::OutInQuint;
    t["InSine"] = QEasingCurve::InSine;
    t["OutSine"] = QEasingCurve::OutSine;
    t["InOutSine"] = QEasingCurve::InOutSine;
    t["OutInSine"] = QEasingCurve::OutInSine;
    t["InExpo"] = QEasingCurve::InExpo;
    t["OutExpo"] = QEasingCurve::OutExpo;
    t["InOutExpo"] = QEasingCurve::InOutExpo;
    t["OutInExpo"] = QEasingCurve::OutInExpo;
    t["InCirc"] = QEasingCurve::InCirc;
    t["OutCirc"] = QEasingCurve::OutCirc;
    t["InOutCirc"] = QEasingCurve::InOutCirc;
    t["OutInCirc"] = QEasingCurve::OutInCirc;
    t["InElastic"] = QEasingCurve::InElastic;
    t["OutElastic"] = QEasingCurve::OutElastic;
    t["InOutElastic"] = QEasingCurve::InOutElastic;
    t["OutInElastic"] = QEasingCurve::OutInElastic;
    t["InBack"] = QEasingCurve::InBack;
    t["OutBack"] = QEasingCurve::OutBack;
    t["InOutBack"] = QEasingCurve::InOutBack;
    t["OutInBack"] = QEasingCurve::OutInBack;
    t["InBounce"] = QEasingCurve::InBounce;
    t["OutBounce"] = QEasingCurve::OutBounce;
    t["InOutBounce"] = QEasingCurve::InOutBounce;
    t["OutInBounce"] = QEasingCurve::OutInBounce;
    t["BezierSpline"] = QEasingCurve::BezierSpline;
    t["TCBSpline"] = QEasingCurve::TCBSpline;
    t["Custom"] = QEasingCurve::Custom;

    return 0;
}
