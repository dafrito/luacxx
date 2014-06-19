#include "Qt.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "QString.hpp"

#include <Qt>

void lua::qt_constants_4(lua::global& t)
{
    // enum Qt::WidgetAttribute
    t["WA_AcceptDrops"] = Qt::WA_AcceptDrops;
    t["WA_AlwaysShowToolTips"] = Qt::WA_AlwaysShowToolTips;
    t["WA_ContentsPropagated"] = Qt::WA_ContentsPropagated;
    t["WA_CustomWhatsThis"] = Qt::WA_CustomWhatsThis;
    t["WA_DeleteOnClose"] = Qt::WA_DeleteOnClose;
    t["WA_Disabled"] = Qt::WA_Disabled;
    t["WA_DontShowOnScreen"] = Qt::WA_DontShowOnScreen;
    t["WA_ForceDisabled"] = Qt::WA_ForceDisabled;
    t["WA_ForceUpdatesDisabled"] = Qt::WA_ForceUpdatesDisabled;
    t["WA_GroupLeader"] = Qt::WA_GroupLeader;
    t["WA_Hover"] = Qt::WA_Hover;
    t["WA_InputMethodEnabled"] = Qt::WA_InputMethodEnabled;
    t["WA_KeyboardFocusChange"] = Qt::WA_KeyboardFocusChange;
    t["WA_KeyCompression"] = Qt::WA_KeyCompression;
    t["WA_LayoutOnEntireRect"] = Qt::WA_LayoutOnEntireRect;
    t["WA_LayoutUsesWidgetRect"] = Qt::WA_LayoutUsesWidgetRect;
    t["WA_MacNoClickThrough"] = Qt::WA_MacNoClickThrough;
    t["WA_MacOpaqueSizeGrip"] = Qt::WA_MacOpaqueSizeGrip;
    t["WA_MacShowFocusRect"] = Qt::WA_MacShowFocusRect;
    t["WA_MacNormalSize"] = Qt::WA_MacNormalSize;
    t["WA_MacSmallSize"] = Qt::WA_MacSmallSize;
    t["WA_MacMiniSize"] = Qt::WA_MacMiniSize;
    t["WA_MacVariableSize"] = Qt::WA_MacVariableSize;
    t["WA_MacBrushedMetal"] = Qt::WA_MacBrushedMetal;
    t["WA_Mapped"] = Qt::WA_Mapped;
    t["WA_MouseNoMask"] = Qt::WA_MouseNoMask;
    t["WA_MouseTracking"] = Qt::WA_MouseTracking;
    t["WA_Moved"] = Qt::WA_Moved;
    t["WA_MSWindowsUseDirect3D"] = Qt::WA_MSWindowsUseDirect3D;
    t["WA_NoBackground"] = Qt::WA_NoBackground;
    t["WA_NoChildEventsForParent"] = Qt::WA_NoChildEventsForParent;
    t["WA_NoChildEventsFromChildren"] = Qt::WA_NoChildEventsFromChildren;
    t["WA_NoMouseReplay"] = Qt::WA_NoMouseReplay;
    t["WA_NoMousePropagation"] = Qt::WA_NoMousePropagation;
    t["WA_TransparentForMouseEvents"] = Qt::WA_TransparentForMouseEvents;
    t["WA_NoSystemBackground"] = Qt::WA_NoSystemBackground;

    t["WA_OpaquePaintEvent"] = Qt::WA_OpaquePaintEvent;

    t["WA_OutsideWSRange"] = Qt::WA_OutsideWSRange;
    t["WA_PaintOnScreen"] = Qt::WA_PaintOnScreen;

    t["WA_PaintUnclipped"] = Qt::WA_PaintUnclipped;
    t["WA_PendingMoveEvent"] = Qt::WA_PendingMoveEvent;
    t["WA_PendingResizeEvent"] = Qt::WA_PendingResizeEvent;
    t["WA_QuitOnClose"] = Qt::WA_QuitOnClose;
    t["WA_Resized"] = Qt::WA_Resized;
    t["WA_RightToLeft"] = Qt::WA_RightToLeft;
    t["WA_SetCursor"] = Qt::WA_SetCursor;
    t["WA_SetFont"] = Qt::WA_SetFont;
    t["WA_SetPalette"] = Qt::WA_SetPalette;
    t["WA_SetStyle"] = Qt::WA_SetStyle;
    t["WA_ShowModal"] = Qt::WA_ShowModal;
    t["WA_StaticContents"] = Qt::WA_StaticContents;
    t["WA_StyleSheet"] = Qt::WA_StyleSheet;
    t["WA_TranslucentBackground"] = Qt::WA_TranslucentBackground;
    t["WA_UnderMouse"] = Qt::WA_UnderMouse;
    t["WA_UpdatesDisabled"] = Qt::WA_UpdatesDisabled;

    t["WA_WindowModified"] = Qt::WA_WindowModified;
    t["WA_WindowPropagation"] = Qt::WA_WindowPropagation;
    t["WA_MacAlwaysShowToolWindow"] = Qt::WA_MacAlwaysShowToolWindow;
    t["WA_SetLocale"] = Qt::WA_SetLocale;
    t["WA_StyledBackground"] = Qt::WA_StyledBackground;
    t["WA_ShowWithoutActivating"] = Qt::WA_ShowWithoutActivating;
    t["WA_NativeWindow"] = Qt::WA_NativeWindow;
    t["WA_DontCreateNativeAncestors"] = Qt::WA_DontCreateNativeAncestors;
    t["WA_X11NetWmWindowTypeDesktop"] = Qt::WA_X11NetWmWindowTypeDesktop;
    t["WA_X11NetWmWindowTypeDock"] = Qt::WA_X11NetWmWindowTypeDock;
    t["WA_X11NetWmWindowTypeToolBar"] = Qt::WA_X11NetWmWindowTypeToolBar;
    t["WA_X11NetWmWindowTypeMenu"] = Qt::WA_X11NetWmWindowTypeMenu;
    t["WA_X11NetWmWindowTypeUtility"] = Qt::WA_X11NetWmWindowTypeUtility;
    t["WA_X11NetWmWindowTypeSplash"] = Qt::WA_X11NetWmWindowTypeSplash;
    t["WA_X11NetWmWindowTypeDialog"] = Qt::WA_X11NetWmWindowTypeDialog;
    t["WA_X11NetWmWindowTypeDropDownMenu"] = Qt::WA_X11NetWmWindowTypeDropDownMenu;
    t["WA_X11NetWmWindowTypePopupMenu"] = Qt::WA_X11NetWmWindowTypePopupMenu;
    t["WA_X11NetWmWindowTypeToolTip"] = Qt::WA_X11NetWmWindowTypeToolTip;
    t["WA_X11NetWmWindowTypeNotification"] = Qt::WA_X11NetWmWindowTypeNotification;
    t["WA_X11NetWmWindowTypeCombo"] = Qt::WA_X11NetWmWindowTypeCombo;
    t["WA_X11NetWmWindowTypeDND"] = Qt::WA_X11NetWmWindowTypeDND;
    t["WA_MacFrameworkScaled"] = Qt::WA_MacFrameworkScaled;
    t["WA_AcceptTouchEvents"] = Qt::WA_AcceptTouchEvents;
    t["WA_TouchPadAcceptSingleTouchEvents"] = Qt::WA_TouchPadAcceptSingleTouchEvents;
    t["WA_X11DoNotAcceptFocus"] = Qt::WA_X11DoNotAcceptFocus;

    // enum Qt::WindowFrameSection
    t["NoSection"] = Qt::NoSection;
    t["LeftSection"] = Qt::LeftSection;
    t["TopLeftSection"] = Qt::TopLeftSection;
    t["TopSection"] = Qt::TopSection;
    t["TopRightSection"] = Qt::TopRightSection;
    t["RightSection"] = Qt::RightSection;
    t["BottomRightSection"] = Qt::BottomRightSection;
    t["BottomSection"] = Qt::BottomSection;
    t["BottomLeftSection"] = Qt::BottomLeftSection;
    t["TitleBarArea"] = Qt::TitleBarArea;

    // enum Qt::WindowModality
    t["NonModal"] = Qt::NonModal;
    t["WindowModal"] = Qt::WindowModal;
    t["ApplicationModal"] = Qt::ApplicationModal;

    // enum Qt::WindowState
    // flags Qt::WindowStates
    t["WindowNoState"] = Qt::WindowNoState;
    t["WindowMinimized"] = Qt::WindowMinimized;
    t["WindowMaximized"] = Qt::WindowMaximized;
    t["WindowFullScreen"] = Qt::WindowFullScreen;
    t["WindowActive"] = Qt::WindowActive;

    // enum Qt::WindowType
    // flags Qt::WindowFlags

    t["Widget"] = Qt::Widget;
    t["Window"] = Qt::Window;
    t["Dialog"] = Qt::Dialog;
    t["Sheet"] = Qt::Sheet;
    t["Drawer"] = Qt::Drawer;
    t["Popup"] = Qt::Popup;
    t["Tool"] = Qt::Tool;
    t["ToolTip"] = Qt::ToolTip;
    t["SplashScreen"] = Qt::SplashScreen;
    t["Desktop"] = Qt::Desktop;
    t["SubWindow"] = Qt::SubWindow;
    t["ForeignWindow"] = Qt::ForeignWindow;
    t["CoverWindow"] = Qt::CoverWindow;

    t["MSWindowsFixedSizeDialogHint"] = Qt::MSWindowsFixedSizeDialogHint;
    t["MSWindowsOwnDC"] = Qt::MSWindowsOwnDC;
    t["BypassWindowManagerHint"] = Qt::BypassWindowManagerHint;
    t["X11BypassWindowManagerHint"] = Qt::X11BypassWindowManagerHint;
    t["FramelessWindowHint"] = Qt::FramelessWindowHint;
    t["NoDropShadowWindowHint"] = Qt::NoDropShadowWindowHint;

    t["CustomizeWindowHint"] = Qt::CustomizeWindowHint;
    t["WindowTitleHint"] = Qt::WindowTitleHint;
    t["WindowSystemMenuHint"] = Qt::WindowSystemMenuHint;
    t["WindowMinimizeButtonHint"] = Qt::WindowMinimizeButtonHint;
    t["WindowMaximizeButtonHint"] = Qt::WindowMaximizeButtonHint;
    t["WindowMinMaxButtonsHint"] = Qt::WindowMinMaxButtonsHint;
    t["WindowCloseButtonHint"] = Qt::WindowCloseButtonHint;
    t["WindowContextHelpButtonHint"] = Qt::WindowContextHelpButtonHint;
    t["MacWindowToolBarButtonHint"] = Qt::MacWindowToolBarButtonHint;
    t["WindowFullscreenButtonHint"] = Qt::WindowFullscreenButtonHint;
    t["BypassGraphicsProxyWidget"] = Qt::BypassGraphicsProxyWidget;
    t["WindowShadeButtonHint"] = Qt::WindowShadeButtonHint;
    t["WindowStaysOnTopHint"] = Qt::WindowStaysOnTopHint;
    t["WindowStaysOnBottomHint"] = Qt::WindowStaysOnBottomHint;
    t["WindowOkButtonHint"] = Qt::WindowOkButtonHint;
    t["WindowCancelButtonHint"] = Qt::WindowCancelButtonHint;
    t["WindowTransparentForInput"] = Qt::WindowTransparentForInput;
    t["WindowOverridesSystemGestures"] = Qt::WindowOverridesSystemGestures;
    t["WindowDoesNotAcceptFocus"] = Qt::WindowDoesNotAcceptFocus;
    t["WindowType_Mask"] = Qt::WindowType_Mask;

}
