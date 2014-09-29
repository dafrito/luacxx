#include "QSizePolicy.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QSizePolicy>

void lua::QSizePolicy_metatable(const lua::index& mt)
{
    mt["controlType"] = &QSizePolicy::controlType;
    mt["expandingDirections"] = &QSizePolicy::expandingDirections;
    mt["hasHeightForWidth"] = &QSizePolicy::hasHeightForWidth;
    mt["hasWidthForHeight"] = &QSizePolicy::hasWidthForHeight;
    mt["horizontalPolicy"] = &QSizePolicy::horizontalPolicy;
    mt["horizontalStretch"] = &QSizePolicy::horizontalStretch;
    mt["retainSizeWhenHidden"] = &QSizePolicy::retainSizeWhenHidden;
    mt["setControlType"] = &QSizePolicy::setControlType;
    mt["setHeightForWidth"] = &QSizePolicy::setHeightForWidth;
    mt["setHorizontalPolicy"] = &QSizePolicy::setHorizontalPolicy;
    mt["setHorizontalStretch"] = &QSizePolicy::setHorizontalStretch;
    mt["setRetainSizeWhenHidden"] = &QSizePolicy::setRetainSizeWhenHidden;
    mt["setVerticalPolicy"] = &QSizePolicy::setVerticalPolicy;
    mt["setVerticalStretch"] = &QSizePolicy::setVerticalStretch;
    mt["setWidthForHeight"] = &QSizePolicy::setWidthForHeight;
    mt["transpose"] = &QSizePolicy::transpose;
    mt["verticalPolicy"] = &QSizePolicy::verticalPolicy;
    mt["verticalStretch"] = &QSizePolicy::verticalStretch;
}

int QSizePolicy_new(lua_State* const state)
{
    lua::make<QSizePolicy>(state);
    // TODO Set up object-specific methods
    // QSizePolicy()
    // QSizePolicy(Policy horizontal, Policy vertical, ControlType type = DefaultType)

    return 1;
}

int luaopen_Qt5Widgets_QSizePolicy(lua_State* const state)
{
    lua::thread env(state);

    env["QSizePolicy"] = lua::value::table;
    env["QSizePolicy"]["new"] = QSizePolicy_new;
    auto t = env["QSizePolicy"];

    // enum QSizePolicy::ControlType
    t["DefaultType"] = QSizePolicy::DefaultType;
    t["ButtonBox"] = QSizePolicy::ButtonBox;
    t["CheckBox"] = QSizePolicy::CheckBox;
    t["ComboBox"] = QSizePolicy::ComboBox;
    t["Frame"] = QSizePolicy::Frame;
    t["GroupBox"] = QSizePolicy::GroupBox;
    t["Label"] = QSizePolicy::Label;
    t["Line"] = QSizePolicy::Line;
    t["LineEdit"] = QSizePolicy::LineEdit;
    t["PushButton"] = QSizePolicy::PushButton;
    t["RadioButton"] = QSizePolicy::RadioButton;
    t["Slider"] = QSizePolicy::Slider;
    t["SpinBox"] = QSizePolicy::SpinBox;
    t["TabWidget"] = QSizePolicy::TabWidget;
    t["ToolButton"] = QSizePolicy::ToolButton;

    // enum QSizePolicy::Policy
    t["Fixed"] = QSizePolicy::Fixed;
    t["Minimum"] = QSizePolicy::Minimum;
    t["Maximum"] = QSizePolicy::Maximum;
    t["Preferred"] = QSizePolicy::Preferred;
    t["Expanding"] = QSizePolicy::Expanding;
    t["MinimumExpanding"] = QSizePolicy::MinimumExpanding;
    t["Ignored"] = QSizePolicy::Ignored;

    // enum QSizePolicy::PolicyFlag
    t["GrowFlag"] = QSizePolicy::GrowFlag;
    t["ExpandFlag"] = QSizePolicy::ExpandFlag;
    t["ShrinkFlag"] = QSizePolicy::ShrinkFlag;
    t["IgnoreFlag"] = QSizePolicy::IgnoreFlag;

    return 0;
}
