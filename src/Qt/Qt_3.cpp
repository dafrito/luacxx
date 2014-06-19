#include "Qt.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "QString.hpp"

#include <Qt>

void lua::qt_constants_3(lua::global& t)
{
    // enum Qt::KeyboardModifier
    // flags Qt::KeyboardModifiers
    t["NoModifier"] = Qt::NoModifier;
    t["ShiftModifier"] = Qt::ShiftModifier;
    t["ControlModifier"] = Qt::ControlModifier;
    t["AltModifier"] = Qt::AltModifier;
    t["MetaModifier"] = Qt::MetaModifier;
    t["KeypadModifier"] = Qt::KeypadModifier;
    t["GroupSwitchModifier"] = Qt::GroupSwitchModifier;

    // enum Qt::LayoutDirection
    t["LeftToRight"] = Qt::LeftToRight;
    t["RightToLeft"] = Qt::RightToLeft;
    t["LayoutDirectionAuto"] = Qt::LayoutDirectionAuto;

    // enum Qt::MaskMode
    t["MaskInColor"] = Qt::MaskInColor;
    t["MaskOutColor"] = Qt::MaskOutColor;

    // enum Qt::MatchFlag
    // flags Qt::MatchFlags
    t["MatchExactly"] = Qt::MatchExactly;
    t["MatchFixedString"] = Qt::MatchFixedString;
    t["MatchContains"] = Qt::MatchContains;
    t["MatchStartsWith"] = Qt::MatchStartsWith;
    t["MatchEndsWith"] = Qt::MatchEndsWith;
    t["MatchCaseSensitive"] = Qt::MatchCaseSensitive;
    t["MatchRegExp"] = Qt::MatchRegExp;
    t["MatchWildcard"] = Qt::MatchWildcard;
    t["MatchWrap"] = Qt::MatchWrap;
    t["MatchRecursive"] = Qt::MatchRecursive;

    // enum Qt::Modifier
    t["SHIFT"] = Qt::SHIFT;
    t["META"] = Qt::META;
    t["CTRL"] = Qt::CTRL;
    t["ALT"] = Qt::ALT;
    t["UNICODE_ACCEL"] = Qt::UNICODE_ACCEL;

    // enum Qt::MouseButton
    // flags Qt::MouseButtons
    t["NoButton"] = Qt::NoButton;
    t["LeftButton"] = Qt::LeftButton;
    t["RightButton"] = Qt::RightButton;
    t["MidButton"] = Qt::MidButton;
    t["MiddleButton"] = Qt::MiddleButton;
    t["XButton1"] = Qt::XButton1;
    t["XButton2"] = Qt::XButton2;

    // enum Qt::MouseEventFlag
    // flags Qt::MouseEventFlags
    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    t["MouseEventCreatedDoubleClick"] = Qt::MouseEventCreatedDoubleClick;
    #endif

    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    // enum Qt::MouseEventSource
    t["MouseEventNotSynthesized"] = Qt::MouseEventNotSynthesized;
    t["MouseEventSynthesizedBySystem"] = Qt::MouseEventSynthesizedBySystem;
    t["MouseEventSynthesizedByQt"] = Qt::MouseEventSynthesizedByQt;
    #endif

    // enum Qt::NavigationMode
    t["NavigationModeNone"] = Qt::NavigationModeNone;
    t["NavigationModeKeypadTabOrder"] = Qt::NavigationModeKeypadTabOrder;
    t["NavigationModeKeypadDirectional"] = Qt::NavigationModeKeypadDirectional;
    t["NavigationModeCursorAuto"] = Qt::NavigationModeCursorAuto;
    t["NavigationModeCursorForceVisible"] = Qt::NavigationModeCursorForceVisible;

    // enum Qt::Orientation
    // flags Qt::Orientations
    t["Horizontal"] = Qt::Horizontal;
    t["Vertical"] = Qt::Vertical;

    // enum Qt::PenCapStyle
    t["FlatCap"] = Qt::FlatCap;
    t["SquareCap"] = Qt::SquareCap;
    t["RoundCap"] = Qt::RoundCap;

    // enum Qt::PenJoinStyle
    t["MiterJoin"] = Qt::MiterJoin;
    t["BevelJoin"] = Qt::BevelJoin;
    t["RoundJoin"] = Qt::RoundJoin;
    t["SvgMiterJoin"] = Qt::SvgMiterJoin;

    // enum Qt::PenStyle
    t["NoPen"] = Qt::NoPen;
    t["SolidLine"] = Qt::SolidLine;
    t["DashLine"] = Qt::DashLine;
    t["DotLine"] = Qt::DotLine;
    t["DashDotLine"] = Qt::DashDotLine;
    t["DashDotDotLine"] = Qt::DashDotDotLine;
    t["CustomDashLine"] = Qt::CustomDashLine;

    // enum Qt::ScreenOrientation
    // flags Qt::ScreenOrientations
    t["PrimaryOrientation"] = Qt::PrimaryOrientation;
    t["LandscapeOrientation"] = Qt::LandscapeOrientation;
    t["PortraitOrientation"] = Qt::PortraitOrientation;
    t["InvertedLandscapeOrientation"] = Qt::InvertedLandscapeOrientation;
    t["InvertedPortraitOrientation"] = Qt::InvertedPortraitOrientation;

    // enum Qt::ScrollBarPolicy
    t["ScrollBarAsNeeded"] = Qt::ScrollBarAsNeeded;
    t["ScrollBarAlwaysOff"] = Qt::ScrollBarAlwaysOff;
    t["ScrollBarAlwaysOn"] = Qt::ScrollBarAlwaysOn;

    // enum Qt::ScrollPhase
    t["ScrollBegin"] = Qt::ScrollBegin;
    t["ScrollUpdate"] = Qt::ScrollUpdate;
    t["ScrollEnd"] = Qt::ScrollEnd;

    // enum Qt::ShortcutContext
    t["WidgetShortcut"] = Qt::WidgetShortcut;
    t["WidgetWithChildrenShortcut"] = Qt::WidgetWithChildrenShortcut;
    t["WindowShortcut"] = Qt::WindowShortcut;
    t["ApplicationShortcut"] = Qt::ApplicationShortcut;

    // enum Qt::SizeHint
    t["MinimumSize"] = Qt::MinimumSize;
    t["PreferredSize"] = Qt::PreferredSize;
    t["MaximumSize"] = Qt::MaximumSize;
    t["MinimumDescent"] = Qt::MinimumDescent;

    // enum Qt::SizeMode
    t["AbsoluteSize"] = Qt::AbsoluteSize;
    t["RelativeSize"] = Qt::RelativeSize;

    // enum Qt::SortOrder
    t["AscendingOrder"] = Qt::AscendingOrder;
    t["DescendingOrder"] = Qt::DescendingOrder;

    // enum Qt::TextElideMode
    t["ElideLeft"] = Qt::ElideLeft;
    t["ElideRight"] = Qt::ElideRight;
    t["ElideMiddle"] = Qt::ElideMiddle;
    t["ElideNone"] = Qt::ElideNone;

    // enum Qt::TextFlag
    t["TextSingleLine"] = Qt::TextSingleLine;
    t["TextDontClip"] = Qt::TextDontClip;
    t["TextExpandTabs"] = Qt::TextExpandTabs;
    t["TextShowMnemonic"] = Qt::TextShowMnemonic;
    t["TextWordWrap"] = Qt::TextWordWrap;
    t["TextWrapAnywhere"] = Qt::TextWrapAnywhere;
    t["TextHideMnemonic"] = Qt::TextHideMnemonic;
    t["TextDontPrint"] = Qt::TextDontPrint;
    t["TextIncludeTrailingSpaces"] = Qt::TextIncludeTrailingSpaces;
    t["TextJustificationForced"] = Qt::TextJustificationForced;

    // enum Qt::TextFormat
    t["PlainText"] = Qt::PlainText;
    t["RichText"] = Qt::RichText;
    t["AutoText"] = Qt::AutoText;

    // enum Qt::TextInteractionFlag
    // flags Qt::TextInteractionFlags
    t["NoTextInteraction"] = Qt::NoTextInteraction;
    t["TextSelectableByMouse"] = Qt::TextSelectableByMouse;
    t["TextSelectableByKeyboard"] = Qt::TextSelectableByKeyboard;
    t["LinksAccessibleByMouse"] = Qt::LinksAccessibleByMouse;
    t["LinksAccessibleByKeyboard"] = Qt::LinksAccessibleByKeyboard;
    t["TextEditable"] = Qt::TextEditable;
    t["TextEditorInteraction"] = Qt::TextEditorInteraction;
    t["TextBrowserInteraction"] = Qt::TextBrowserInteraction;

    // enum Qt::TileRule
    t["StretchTile"] = Qt::StretchTile;
    t["RepeatTile"] = Qt::RepeatTile;
    t["RoundTile"] = Qt::RoundTile;

    // enum Qt::TimeSpec
    t["LocalTime"] = Qt::LocalTime;
    t["UTC"] = Qt::UTC;
    t["OffsetFromUTC"] = Qt::OffsetFromUTC;
    t["TimeZone"] = Qt::TimeZone;

    // enum Qt::TimerType
    t["PreciseTimer"] = Qt::PreciseTimer;
    t["CoarseTimer"] = Qt::CoarseTimer;
    t["VeryCoarseTimer"] = Qt::VeryCoarseTimer;

    // enum Qt::ToolBarArea
    // flags Qt::ToolBarAreas
    t["LeftToolBarArea"] = Qt::LeftToolBarArea;
    t["RightToolBarArea"] = Qt::RightToolBarArea;
    t["TopToolBarArea"] = Qt::TopToolBarArea;
    t["BottomToolBarArea"] = Qt::BottomToolBarArea;
    t["AllToolBarAreas"] = Qt::AllToolBarAreas;
    t["NoToolBarArea"] = Qt::NoToolBarArea;

    // enum Qt::ToolButtonStyle
    t["ToolButtonIconOnly"] = Qt::ToolButtonIconOnly;
    t["ToolButtonTextOnly"] = Qt::ToolButtonTextOnly;
    t["ToolButtonTextBesideIcon"] = Qt::ToolButtonTextBesideIcon;
    t["ToolButtonTextUnderIcon"] = Qt::ToolButtonTextUnderIcon;
    t["ToolButtonFollowStyle"] = Qt::ToolButtonFollowStyle;

    // enum Qt::TouchPointState
    // flags Qt::TouchPointStates
    t["TouchPointPressed"] = Qt::TouchPointPressed;
    t["TouchPointMoved"] = Qt::TouchPointMoved;
    t["TouchPointStationary"] = Qt::TouchPointStationary;
    t["TouchPointReleased"] = Qt::TouchPointReleased;

    // enum Qt::TransformationMode
    t["FastTransformation"] = Qt::FastTransformation;
    t["SmoothTransformation"] = Qt::SmoothTransformation;

    // enum Qt::UIEffect
    t["UI_AnimateMenu"] = Qt::UI_AnimateMenu;
    t["UI_FadeMenu"] = Qt::UI_FadeMenu;
    t["UI_AnimateCombo"] = Qt::UI_AnimateCombo;
    t["UI_AnimateTooltip"] = Qt::UI_AnimateTooltip;
    t["UI_FadeTooltip"] = Qt::UI_FadeTooltip;
    t["UI_AnimateToolBox"] = Qt::UI_AnimateToolBox;

    // enum Qt::WhiteSpaceMode
    t["WhiteSpaceNormal"] = Qt::WhiteSpaceNormal;
    t["WhiteSpacePre"] = Qt::WhiteSpacePre;
    t["WhiteSpaceNoWrap"] = Qt::WhiteSpaceNoWrap;
}
