#include "QEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/string.hpp"
#include "../thread.hpp"
#include "QSize.hpp"

#ifdef HAVE_Qt5Gui
#include <QResizeEvent>
#include <QExposeEvent>
#endif

std::string QEvent_type(QEvent* event);
std::string QEvent_tostring(QEvent* event);

void lua::QEvent_metatable(const lua::index& mt, QEvent* const event)
{
    mt["accept"] = &QEvent::accept;
    mt["ignore"] = &QEvent::ignore;
    mt["setAccepted"] = &QEvent::setAccepted;
    mt["isAccepted"] = &QEvent::isAccepted;
    mt["spontaneous"] = &QEvent::spontaneous;
    mt["type"] = &QEvent::type;

    mt["__tostring"] = QEvent_tostring;

#ifdef HAVE_Qt5Gui
    if (event) {
        switch (event->type()) {
        case QEvent::Resize:
            mt["oldSize"] = &QResizeEvent::oldSize;
            mt["size"] = &QResizeEvent::size;
            break;
        case QEvent::Expose:
            mt["region"] = &QExposeEvent::region;
            break;
        default:
            break;
        }
    }
#endif
}

std::string QEvent_typename(QEvent* event)
{
    switch (event->type()) {
    case QEvent::None: return "QEvent.None";
    case QEvent::ActionAdded: return "QEvent::ActionAdded";
    case QEvent::ActionChanged: return "QEvent::ActionChanged";
    case QEvent::ActionRemoved: return "QEvent::ActionRemoved";
    case QEvent::ActivationChange: return "QEvent::ActivationChange";
    case QEvent::ApplicationDeactivate: return "QEvent::ApplicationDeactivate";
    case QEvent::ApplicationFontChange: return "QEvent::ApplicationFontChange";
    case QEvent::ApplicationLayoutDirectionChange: return "QEvent::ApplicationLayoutDirectionChange";
    case QEvent::ApplicationPaletteChange: return "QEvent::ApplicationPaletteChange";
    case QEvent::ApplicationStateChange: return "QEvent::ApplicationStateChange";
    case QEvent::ApplicationWindowIconChange: return "QEvent::ApplicationWindowIconChange";
    case QEvent::ChildAdded: return "QEvent::ChildAdded";
    case QEvent::ChildPolished: return "QEvent::ChildPolished";
    case QEvent::ChildRemoved: return "QEvent::ChildRemoved";
    case QEvent::Clipboard: return "QEvent::Clipboard";
    case QEvent::Close: return "QEvent::Close";
    case QEvent::CloseSoftwareInputPanel: return "QEvent::CloseSoftwareInputPanel";
    case QEvent::ContentsRectChange: return "QEvent::ContentsRectChange";
    case QEvent::ContextMenu: return "QEvent::ContextMenu";
    case QEvent::CursorChange: return "QEvent::CursorChange";
    case QEvent::DeferredDelete: return "QEvent::DeferredDelete";
    case QEvent::DragEnter: return "QEvent::DragEnter";
    case QEvent::DragLeave: return "QEvent::DragLeave";
    case QEvent::DragMove: return "QEvent::DragMove";
    case QEvent::Drop: return "QEvent::Drop";
    case QEvent::DynamicPropertyChange: return "QEvent::DynamicPropertyChange";
    case QEvent::EnabledChange: return "QEvent::EnabledChange";
    case QEvent::Enter: return "QEvent::Enter";
    #ifdef QT_KEYPAD_NAVIGATION
    case QEvent::EnterEditFocus: return "QEvent::EnterEditFocus";
    #endif
    case QEvent::EnterWhatsThisMode: return "QEvent::EnterWhatsThisMode";
    case QEvent::Expose: return "QEvent::Expose";
    case QEvent::FileOpen: return "QEvent::FileOpen";
    case QEvent::FocusIn: return "QEvent::FocusIn";
    case QEvent::FocusOut: return "QEvent::FocusOut";
    case QEvent::FocusAboutToChange: return "QEvent::FocusAboutToChange";
    case QEvent::FontChange: return "QEvent::FontChange";
    case QEvent::Gesture: return "QEvent::Gesture";
    case QEvent::GestureOverride: return "QEvent::GestureOverride";
    case QEvent::GrabKeyboard: return "QEvent::GrabKeyboard";
    case QEvent::GrabMouse: return "QEvent::GrabMouse";
    case QEvent::GraphicsSceneContextMenu: return "QEvent::GraphicsSceneContextMenu";
    case QEvent::GraphicsSceneDragEnter: return "QEvent::GraphicsSceneDragEnter";
    case QEvent::GraphicsSceneDragLeave: return "QEvent::GraphicsSceneDragLeave";
    case QEvent::GraphicsSceneDragMove: return "QEvent::GraphicsSceneDragMove";
    case QEvent::GraphicsSceneDrop: return "QEvent::GraphicsSceneDrop";
    case QEvent::GraphicsSceneHelp: return "QEvent::GraphicsSceneHelp";
    case QEvent::GraphicsSceneHoverEnter: return "QEvent::GraphicsSceneHoverEnter";
    case QEvent::GraphicsSceneHoverLeave: return "QEvent::GraphicsSceneHoverLeave";
    case QEvent::GraphicsSceneHoverMove: return "QEvent::GraphicsSceneHoverMove";
    case QEvent::GraphicsSceneMouseDoubleClick: return "QEvent::GraphicsSceneMouseDoubleClick";
    case QEvent::GraphicsSceneMouseMove: return "QEvent::GraphicsSceneMouseMove";
    case QEvent::GraphicsSceneMousePress: return "QEvent::GraphicsSceneMousePress";
    case QEvent::GraphicsSceneMouseRelease: return "QEvent::GraphicsSceneMouseRelease";
    case QEvent::GraphicsSceneMove: return "QEvent::GraphicsSceneMove";
    case QEvent::GraphicsSceneResize: return "QEvent::GraphicsSceneResize";
    case QEvent::GraphicsSceneWheel: return "QEvent::GraphicsSceneWheel";
    case QEvent::Hide: return "QEvent::Hide";
    case QEvent::HideToParent: return "QEvent::HideToParent";
    case QEvent::HoverEnter: return "QEvent::HoverEnter";
    case QEvent::HoverLeave: return "QEvent::HoverLeave";
    case QEvent::HoverMove: return "QEvent::HoverMove";
    case QEvent::IconDrag: return "QEvent::IconDrag";
    case QEvent::IconTextChange: return "QEvent::IconTextChange";
    case QEvent::InputMethod: return "QEvent::InputMethod";
    case QEvent::InputMethodQuery: return "QEvent::InputMethodQuery";
    case QEvent::KeyboardLayoutChange: return "QEvent::KeyboardLayoutChange";
    case QEvent::KeyPress: return "QEvent::KeyPress";
    case QEvent::KeyRelease: return "QEvent::KeyRelease";
    case QEvent::LanguageChange: return "QEvent::LanguageChange";
    case QEvent::LayoutDirectionChange: return "QEvent::LayoutDirectionChange";
    case QEvent::LayoutRequest: return "QEvent::LayoutRequest";
    case QEvent::Leave: return "QEvent::Leave";
    #ifdef QT_KEYPAD_NAVIGATION
    case QEvent::LeaveEditFocus: return "QEvent::LeaveEditFocus";
    #endif
    case QEvent::LeaveWhatsThisMode: return "QEvent::LeaveWhatsThisMode";
    case QEvent::LocaleChange: return "QEvent::LocaleChange";
    case QEvent::NonClientAreaMouseButtonDblClick: return "QEvent::NonClientAreaMouseButtonDblClick";
    case QEvent::NonClientAreaMouseButtonPress: return "QEvent::NonClientAreaMouseButtonPress";
    case QEvent::NonClientAreaMouseButtonRelease: return "QEvent::NonClientAreaMouseButtonRelease";
    case QEvent::NonClientAreaMouseMove: return "QEvent::NonClientAreaMouseMove";
    case QEvent::MacSizeChange: return "QEvent::MacSizeChange";
    case QEvent::MetaCall: return "QEvent::MetaCall";
    case QEvent::ModifiedChange: return "QEvent::ModifiedChange";
    case QEvent::MouseButtonDblClick: return "QEvent::MouseButtonDblClick";
    case QEvent::MouseButtonPress: return "QEvent::MouseButtonPress";
    case QEvent::MouseButtonRelease: return "QEvent::MouseButtonRelease";
    case QEvent::MouseMove: return "QEvent::MouseMove";
    case QEvent::MouseTrackingChange: return "QEvent::MouseTrackingChange";
    case QEvent::Move: return "QEvent::Move";
    case QEvent::OrientationChange: return "QEvent::OrientationChange";
    case QEvent::Paint: return "QEvent::Paint";
    case QEvent::PaletteChange: return "QEvent::PaletteChange";
    case QEvent::ParentAboutToChange: return "QEvent::ParentAboutToChange";
    case QEvent::ParentChange: return "QEvent::ParentChange";
    case QEvent::PlatformPanel: return "QEvent::PlatformPanel";
    case QEvent::Polish: return "QEvent::Polish";
    case QEvent::PolishRequest: return "QEvent::PolishRequest";
    case QEvent::QueryWhatsThis: return "QEvent::QueryWhatsThis";
    case QEvent::RequestSoftwareInputPanel: return "QEvent::RequestSoftwareInputPanel";
    case QEvent::Resize: return "QEvent::Resize";
    case QEvent::ScrollPrepare: return "QEvent::ScrollPrepare";
    case QEvent::Scroll: return "QEvent::Scroll";
    case QEvent::Shortcut: return "QEvent::Shortcut";
    case QEvent::ShortcutOverride: return "QEvent::ShortcutOverride";
    case QEvent::Show: return "QEvent::Show";
    case QEvent::ShowToParent: return "QEvent::ShowToParent";
    case QEvent::SockAct: return "QEvent::SockAct";
    case QEvent::StateMachineSignal: return "QEvent::StateMachineSignal";
    case QEvent::StateMachineWrapped: return "QEvent::StateMachineWrapped";
    case QEvent::StatusTip: return "QEvent::StatusTip";
    case QEvent::StyleChange: return "QEvent::StyleChange";
    case QEvent::TabletMove: return "QEvent::TabletMove";
    case QEvent::TabletPress: return "QEvent::TabletPress";
    case QEvent::TabletRelease: return "QEvent::TabletRelease";
    case QEvent::OkRequest: return "QEvent::OkRequest";
    case QEvent::TabletEnterProximity: return "QEvent::TabletEnterProximity";
    case QEvent::TabletLeaveProximity: return "QEvent::TabletLeaveProximity";
    case QEvent::ThreadChange: return "QEvent::ThreadChange";
    case QEvent::Timer: return "QEvent::Timer";
    case QEvent::ToolBarChange: return "QEvent::ToolBarChange";
    case QEvent::ToolTip: return "QEvent::ToolTip";
    case QEvent::ToolTipChange: return "QEvent::ToolTipChange";
    case QEvent::TouchBegin: return "QEvent::TouchBegin";
    case QEvent::TouchCancel: return "QEvent::TouchCancel";
    case QEvent::TouchEnd: return "QEvent::TouchEnd";
    case QEvent::TouchUpdate: return "QEvent::TouchUpdate";
    case QEvent::UngrabKeyboard: return "QEvent::UngrabKeyboard";
    case QEvent::UngrabMouse: return "QEvent::UngrabMouse";
    case QEvent::UpdateLater: return "QEvent::UpdateLater";
    case QEvent::UpdateRequest: return "QEvent::UpdateRequest";
    case QEvent::WhatsThis: return "QEvent::WhatsThis";
    case QEvent::WhatsThisClicked: return "QEvent::WhatsThisClicked";
    case QEvent::Wheel: return "QEvent::Wheel";
    case QEvent::WinEventAct: return "QEvent::WinEventAct";
    case QEvent::WindowActivate: return "QEvent::WindowActivate";
    case QEvent::WindowBlocked: return "QEvent::WindowBlocked";
    case QEvent::WindowDeactivate: return "QEvent::WindowDeactivate";
    case QEvent::WindowIconChange: return "QEvent::WindowIconChange";
    case QEvent::WindowStateChange: return "QEvent::WindowStateChange";
    case QEvent::WindowTitleChange: return "QEvent::WindowTitleChange";
    case QEvent::WindowUnblocked: return "QEvent::WindowUnblocked";
    case QEvent::WinIdChange: return "QEvent::WinIdChange";
    case QEvent::ZOrderChange: return "QEvent::ZOrderChange";
    default:
    {
        std::stringstream str;
        str << "QEvent." << (int)event->type();
        return str.str();
    }
    }
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
