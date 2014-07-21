#include "QEvent.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QSize.hpp"

std::string QEvent_type(QEvent* event);
std::string QEvent_tostring(QEvent* event);

void lua::QEvent_metatable(const lua::index& mt)
{
    mt["accept"] = &QEvent::accept;
    mt["ignore"] = &QEvent::ignore;
    mt["setAccepted"] = &QEvent::setAccepted;
    mt["isAccepted"] = &QEvent::isAccepted;
    mt["spontaneous"] = &QEvent::spontaneous;
    mt["type"] = QEvent_type;

    mt["__tostring"] = QEvent_tostring;
}

std::string QEvent_typename(QEvent* event)
{
    switch (event->type()) {
    case QEvent::Close: return "QEvent.Close";
    case QEvent::Enter: return "QEvent.Enter";
    case QEvent::Expose: return "QEvent.Expose";
    case QEvent::Hide: return "QEvent.Hide";
    case QEvent::Leave: return "QEvent.Leave";
    case QEvent::MouseButtonDblClick: return "QEvent.MouseButtonDblClick";
    case QEvent::MouseButtonPress: return "QEvent.MouseButtonPress";
    case QEvent::MouseButtonRelease: return "QEvent.MouseButtonRelease";
    case QEvent::MouseMove: return "QEvent.MouseMove";
    case QEvent::Move: return "QEvent.Move";
    case QEvent::Resize: return "QEvent.Resize";
    case QEvent::Show: return "QEvent.Show";
    case QEvent::WindowStateChange: return "QEvent.WindowStateChange";
    }

    std::stringstream str;
    str << "QEvent." << (int)event->type();
    return str.str();
}

std::string QEvent_type(QEvent* event)
{
    return QEvent_typename(event);
}

std::string QEvent_tostring(QEvent* event)
{
    std::stringstream str;
    str << QEvent_typename(event) << "@" << event;
    return str.str();
}

int luaopen_Qt5Core_QEvent(lua_State* const state)
{
    lua::thread env(state);

    // enum QEvent::Type
    env["QEvent"] = lua::value::table;
    env["QEvent"]["None"] = QEvent::None;
    env["QEvent"]["ActionAdded"] = QEvent::ActionAdded;
    env["QEvent"]["ActionChanged"] = QEvent::ActionChanged;
    env["QEvent"]["ActionRemoved"] = QEvent::ActionRemoved;
    env["QEvent"]["ActivationChange"] = QEvent::ActivationChange;
    env["QEvent"]["ApplicationActivate"] = QEvent::ApplicationActivate;
    env["QEvent"]["ApplicationActivated"] = QEvent::ApplicationActivated;
    env["QEvent"]["ApplicationDeactivate"] = QEvent::ApplicationDeactivate;
    env["QEvent"]["ApplicationFontChange"] = QEvent::ApplicationFontChange;
    env["QEvent"]["ApplicationLayoutDirectionChange"] = QEvent::ApplicationLayoutDirectionChange;
    env["QEvent"]["ApplicationPaletteChange"] = QEvent::ApplicationPaletteChange;
    env["QEvent"]["ApplicationStateChange"] = QEvent::ApplicationStateChange;
    env["QEvent"]["ApplicationWindowIconChange"] = QEvent::ApplicationWindowIconChange;
    env["QEvent"]["ChildAdded"] = QEvent::ChildAdded;
    env["QEvent"]["ChildPolished"] = QEvent::ChildPolished;
    env["QEvent"]["ChildRemoved"] = QEvent::ChildRemoved;
    env["QEvent"]["Clipboard"] = QEvent::Clipboard;
    env["QEvent"]["Close"] = QEvent::Close;
    env["QEvent"]["CloseSoftwareInputPanel"] = QEvent::CloseSoftwareInputPanel;
    env["QEvent"]["ContentsRectChange"] = QEvent::ContentsRectChange;
    env["QEvent"]["ContextMenu"] = QEvent::ContextMenu;
    env["QEvent"]["CursorChange"] = QEvent::CursorChange;
    env["QEvent"]["DeferredDelete"] = QEvent::DeferredDelete;
    env["QEvent"]["DragEnter"] = QEvent::DragEnter;
    env["QEvent"]["DragLeave"] = QEvent::DragLeave;
    env["QEvent"]["DragMove"] = QEvent::DragMove;
    env["QEvent"]["Drop"] = QEvent::Drop;
    env["QEvent"]["DynamicPropertyChange"] = QEvent::DynamicPropertyChange;
    env["QEvent"]["EnabledChange"] = QEvent::EnabledChange;
    env["QEvent"]["Enter"] = QEvent::Enter;
    #ifdef QT_KEYPAD_NAVIGATION
    env["QEvent"]["EnterEditFocus"] = QEvent::EnterEditFocus;
    #endif
    env["QEvent"]["EnterWhatsThisMode"] = QEvent::EnterWhatsThisMode;
    env["QEvent"]["Expose"] = QEvent::Expose;
    env["QEvent"]["FileOpen"] = QEvent::FileOpen;
    env["QEvent"]["FocusIn"] = QEvent::FocusIn;
    env["QEvent"]["FocusOut"] = QEvent::FocusOut;
    env["QEvent"]["FocusAboutToChange"] = QEvent::FocusAboutToChange;
    env["QEvent"]["FontChange"] = QEvent::FontChange;
    env["QEvent"]["Gesture"] = QEvent::Gesture;
    env["QEvent"]["GestureOverride"] = QEvent::GestureOverride;
    env["QEvent"]["GrabKeyboard"] = QEvent::GrabKeyboard;
    env["QEvent"]["GrabMouse"] = QEvent::GrabMouse;
    env["QEvent"]["GraphicsSceneContextMenu"] = QEvent::GraphicsSceneContextMenu;
    env["QEvent"]["GraphicsSceneDragEnter"] = QEvent::GraphicsSceneDragEnter;
    env["QEvent"]["GraphicsSceneDragLeave"] = QEvent::GraphicsSceneDragLeave;
    env["QEvent"]["GraphicsSceneDragMove"] = QEvent::GraphicsSceneDragMove;
    env["QEvent"]["GraphicsSceneDrop"] = QEvent::GraphicsSceneDrop;
    env["QEvent"]["GraphicsSceneHelp"] = QEvent::GraphicsSceneHelp;
    env["QEvent"]["GraphicsSceneHoverEnter"] = QEvent::GraphicsSceneHoverEnter;
    env["QEvent"]["GraphicsSceneHoverLeave"] = QEvent::GraphicsSceneHoverLeave;
    env["QEvent"]["GraphicsSceneHoverMove"] = QEvent::GraphicsSceneHoverMove;
    env["QEvent"]["GraphicsSceneMouseDoubleClick"] = QEvent::GraphicsSceneMouseDoubleClick;
    env["QEvent"]["GraphicsSceneMouseMove"] = QEvent::GraphicsSceneMouseMove;
    env["QEvent"]["GraphicsSceneMousePress"] = QEvent::GraphicsSceneMousePress;
    env["QEvent"]["GraphicsSceneMouseRelease"] = QEvent::GraphicsSceneMouseRelease;
    env["QEvent"]["GraphicsSceneMove"] = QEvent::GraphicsSceneMove;
    env["QEvent"]["GraphicsSceneResize"] = QEvent::GraphicsSceneResize;
    env["QEvent"]["GraphicsSceneWheel"] = QEvent::GraphicsSceneWheel;
    env["QEvent"]["Hide"] = QEvent::Hide;
    env["QEvent"]["HideToParent"] = QEvent::HideToParent;
    env["QEvent"]["HoverEnter"] = QEvent::HoverEnter;
    env["QEvent"]["HoverLeave"] = QEvent::HoverLeave;
    env["QEvent"]["HoverMove"] = QEvent::HoverMove;
    env["QEvent"]["IconDrag"] = QEvent::IconDrag;
    env["QEvent"]["IconTextChange"] = QEvent::IconTextChange;
    env["QEvent"]["InputMethod"] = QEvent::InputMethod;
    env["QEvent"]["InputMethodQuery"] = QEvent::InputMethodQuery;
    env["QEvent"]["KeyboardLayoutChange"] = QEvent::KeyboardLayoutChange;
    env["QEvent"]["KeyPress"] = QEvent::KeyPress;
    env["QEvent"]["KeyRelease"] = QEvent::KeyRelease;
    env["QEvent"]["LanguageChange"] = QEvent::LanguageChange;
    env["QEvent"]["LayoutDirectionChange"] = QEvent::LayoutDirectionChange;
    env["QEvent"]["LayoutRequest"] = QEvent::LayoutRequest;
    env["QEvent"]["Leave"] = QEvent::Leave;
    #ifdef QT_KEYPAD_NAVIGATION
    env["QEvent"]["LeaveEditFocus"] = QEvent::LeaveEditFocus;
    #endif
    env["QEvent"]["LeaveWhatsThisMode"] = QEvent::LeaveWhatsThisMode;
    env["QEvent"]["LocaleChange"] = QEvent::LocaleChange;
    env["QEvent"]["NonClientAreaMouseButtonDblClick"] = QEvent::NonClientAreaMouseButtonDblClick;
    env["QEvent"]["NonClientAreaMouseButtonPress"] = QEvent::NonClientAreaMouseButtonPress;
    env["QEvent"]["NonClientAreaMouseButtonRelease"] = QEvent::NonClientAreaMouseButtonRelease;
    env["QEvent"]["NonClientAreaMouseMove"] = QEvent::NonClientAreaMouseMove;
    env["QEvent"]["MacSizeChange"] = QEvent::MacSizeChange;
    env["QEvent"]["MetaCall"] = QEvent::MetaCall;
    env["QEvent"]["ModifiedChange"] = QEvent::ModifiedChange;
    env["QEvent"]["MouseButtonDblClick"] = QEvent::MouseButtonDblClick;
    env["QEvent"]["MouseButtonPress"] = QEvent::MouseButtonPress;
    env["QEvent"]["MouseButtonRelease"] = QEvent::MouseButtonRelease;
    env["QEvent"]["MouseMove"] = QEvent::MouseMove;
    env["QEvent"]["MouseTrackingChange"] = QEvent::MouseTrackingChange;
    env["QEvent"]["Move"] = QEvent::Move;
    env["QEvent"]["OrientationChange"] = QEvent::OrientationChange;
    env["QEvent"]["Paint"] = QEvent::Paint;
    env["QEvent"]["PaletteChange"] = QEvent::PaletteChange;
    env["QEvent"]["ParentAboutToChange"] = QEvent::ParentAboutToChange;
    env["QEvent"]["ParentChange"] = QEvent::ParentChange;
    env["QEvent"]["PlatformPanel"] = QEvent::PlatformPanel;
    env["QEvent"]["Polish"] = QEvent::Polish;
    env["QEvent"]["PolishRequest"] = QEvent::PolishRequest;
    env["QEvent"]["QueryWhatsThis"] = QEvent::QueryWhatsThis;
    env["QEvent"]["RequestSoftwareInputPanel"] = QEvent::RequestSoftwareInputPanel;
    env["QEvent"]["Resize"] = QEvent::Resize;
    env["QEvent"]["ScrollPrepare"] = QEvent::ScrollPrepare;
    env["QEvent"]["Scroll"] = QEvent::Scroll;
    env["QEvent"]["Shortcut"] = QEvent::Shortcut;
    env["QEvent"]["ShortcutOverride"] = QEvent::ShortcutOverride;
    env["QEvent"]["Show"] = QEvent::Show;
    env["QEvent"]["ShowToParent"] = QEvent::ShowToParent;
    env["QEvent"]["SockAct"] = QEvent::SockAct;
    env["QEvent"]["StateMachineSignal"] = QEvent::StateMachineSignal;
    env["QEvent"]["StateMachineWrapped"] = QEvent::StateMachineWrapped;
    env["QEvent"]["StatusTip"] = QEvent::StatusTip;
    env["QEvent"]["StyleChange"] = QEvent::StyleChange;
    env["QEvent"]["TabletMove"] = QEvent::TabletMove;
    env["QEvent"]["TabletPress"] = QEvent::TabletPress;
    env["QEvent"]["TabletRelease"] = QEvent::TabletRelease;
    env["QEvent"]["OkRequest"] = QEvent::OkRequest;
    env["QEvent"]["TabletEnterProximity"] = QEvent::TabletEnterProximity;
    env["QEvent"]["TabletLeaveProximity"] = QEvent::TabletLeaveProximity;
    env["QEvent"]["ThreadChange"] = QEvent::ThreadChange;
    env["QEvent"]["Timer"] = QEvent::Timer;
    env["QEvent"]["ToolBarChange"] = QEvent::ToolBarChange;
    env["QEvent"]["ToolTip"] = QEvent::ToolTip;
    env["QEvent"]["ToolTipChange"] = QEvent::ToolTipChange;
    env["QEvent"]["TouchBegin"] = QEvent::TouchBegin;
    env["QEvent"]["TouchCancel"] = QEvent::TouchCancel;
    env["QEvent"]["TouchEnd"] = QEvent::TouchEnd;
    env["QEvent"]["TouchUpdate"] = QEvent::TouchUpdate;
    env["QEvent"]["UngrabKeyboard"] = QEvent::UngrabKeyboard;
    env["QEvent"]["UngrabMouse"] = QEvent::UngrabMouse;
    env["QEvent"]["UpdateLater"] = QEvent::UpdateLater;
    env["QEvent"]["UpdateRequest"] = QEvent::UpdateRequest;
    env["QEvent"]["WhatsThis"] = QEvent::WhatsThis;
    env["QEvent"]["WhatsThisClicked"] = QEvent::WhatsThisClicked;
    env["QEvent"]["Wheel"] = QEvent::Wheel;
    env["QEvent"]["WinEventAct"] = QEvent::WinEventAct;
    env["QEvent"]["WindowActivate"] = QEvent::WindowActivate;
    env["QEvent"]["WindowBlocked"] = QEvent::WindowBlocked;
    env["QEvent"]["WindowDeactivate"] = QEvent::WindowDeactivate;
    env["QEvent"]["WindowIconChange"] = QEvent::WindowIconChange;
    env["QEvent"]["WindowStateChange"] = QEvent::WindowStateChange;
    env["QEvent"]["WindowTitleChange"] = QEvent::WindowTitleChange;
    env["QEvent"]["WindowUnblocked"] = QEvent::WindowUnblocked;
    env["QEvent"]["WinIdChange"] = QEvent::WinIdChange;
    env["QEvent"]["ZOrderChange"] = QEvent::ZOrderChange;

    env["QEvent"]["User"] = QEvent::User;
    env["QEvent"]["MaxUser"] = QEvent::MaxUser;

    return 0;
}
