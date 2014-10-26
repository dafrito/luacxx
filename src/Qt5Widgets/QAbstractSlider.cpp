#include "QAbstractSlider.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QWidget.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"

namespace lua {

void QAbstractSlider_metatable(lua_State* const state, const int pos)
{
    lua::QWidget_metatable(state, pos);

    lua::index mt(state, pos);
    mt["hasTracking"] = &QAbstractSlider::hasTracking;
    mt["invertedAppearance"] = &QAbstractSlider::invertedAppearance;
    mt["invertedControls"] = &QAbstractSlider::invertedControls;
    mt["isSliderDown"] = &QAbstractSlider::isSliderDown;
    mt["maximum"] = &QAbstractSlider::maximum;
    mt["minimum"] = &QAbstractSlider::minimum;
    mt["orientation"] = &QAbstractSlider::orientation;
    mt["pageStep"] = &QAbstractSlider::pageStep;
    mt["setInvertedAppearance"] = &QAbstractSlider::setInvertedAppearance;
    mt["setInvertedControls"] = &QAbstractSlider::setInvertedControls;
    mt["setMaximum"] = &QAbstractSlider::setMaximum;
    mt["setMinimum"] = &QAbstractSlider::setMinimum;
    mt["setPageStep"] = &QAbstractSlider::setPageStep;
    mt["setSingleStep"] = &QAbstractSlider::setSingleStep;
    mt["setSliderDown"] = &QAbstractSlider::setSliderDown;
    mt["setSliderPosition"] = &QAbstractSlider::setSliderPosition;
    mt["setTracking"] = &QAbstractSlider::setTracking;
    mt["singleStep"] = &QAbstractSlider::singleStep;
    mt["sliderPosition"] = &QAbstractSlider::sliderPosition;
    mt["triggerAction"] = &QAbstractSlider::triggerAction;
    mt["value"] = &QAbstractSlider::value;
}

} // namespace lua

int QAbstractSlider_new(lua_State* const state)
{
    lua::make<QAbstractSlider>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Widgets_QAbstractSlider(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractSlider"] = lua::value::table;
    env["QAbstractSlider"]["new"] = QAbstractSlider_new;
    auto t = env["QAbstractSlider"];

    // enum QAbstractSlider::SliderAction
    t["SliderNoAction"] = QAbstractSlider::SliderNoAction;
    t["SliderSingleStepAdd"] = QAbstractSlider::SliderSingleStepAdd;
    t["SliderSingleStepSub"] = QAbstractSlider::SliderSingleStepSub;
    t["SliderPageStepAdd"] = QAbstractSlider::SliderPageStepAdd;
    t["SliderPageStepSub"] = QAbstractSlider::SliderPageStepSub;
    t["SliderToMinimum"] = QAbstractSlider::SliderToMinimum;
    t["SliderToMaximum"] = QAbstractSlider::SliderToMaximum;
    t["SliderMove"] = QAbstractSlider::SliderMove;

    return 0;
}
