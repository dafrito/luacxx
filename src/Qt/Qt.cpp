#include "Qt.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "QString.hpp"

#include <Qt>

// http://qt-project.org/doc/qt-5/qt.html

int luaopen_luacxx_Qt(lua_State* const state)
{
    lua::thread env(state);

    env["Qt"] = lua::value::table;
    auto t = env["Qt"];

    // Qt::AlignmentFlag
    // Qt::Alignment
    t["AlignLeft"] = Qt::AlignLeft;
    t["AlignRight"] = Qt::AlignRight;
    t["AlignHCenter"] = Qt::AlignHCenter;
    t["AlignJustify"] = Qt::AlignJustify;

    t["AlignTop"] = Qt::AlignTop;
    t["AlignBottom"] = Qt::AlignBottom;
    t["AlignVCenter"] = Qt::AlignVCenter;

    t["AlignCenter"] = Qt::AlignCenter;

    t["AlignAbsolute"] = Qt::AlignAbsolute;
    t["AlignLeading"] = Qt::AlignLeading;
    t["AlignTrailing"] = Qt::AlignTrailing;

    t["AlignHorizontal_Mask"] = Qt::AlignHorizontal_Mask;
    t["AlignVertical_Mask"] = Qt::AlignVertical_Mask;

    // Qt::AnchorPoint
    t["AnchorLeft"] = Qt::AnchorLeft;
    t["AnchorHorizontalCenter"] = Qt::AnchorHorizontalCenter;
    t["AnchorRight"] = Qt::AnchorRight;
    t["AnchorTop"] = Qt::AnchorTop;
    t["AnchorVerticalCenter"] = Qt::AnchorVerticalCenter;
    t["AnchorBottom"] = Qt::AnchorBottom;

    // Qt::ApplicationAttribute
    t["AA_DontShowIconsInMenus"] = Qt::AA_DontShowIconsInMenus;
    t["AA_NativeWindows"] = Qt::AA_NativeWindows;
    t["AA_DontCreateNativeWidgetSiblings"] = Qt::AA_DontCreateNativeWidgetSiblings;
    t["AA_MacPluginApplication"] = Qt::AA_MacPluginApplication;
    t["AA_DontUseNativeMenuBar"] = Qt::AA_DontUseNativeMenuBar;
    t["AA_MacDontSwapCtrlAndMeta"] = Qt::AA_MacDontSwapCtrlAndMeta;
    t["AA_Use96Dpi"] = Qt::AA_Use96Dpi;
    t["AA_X11InitThreads"] = Qt::AA_X11InitThreads;
    t["AA_SynthesizeTouchForUnhandledMouseEvents"] = Qt::AA_SynthesizeTouchForUnhandledMouseEvents;
    t["AA_SynthesizeMouseForUnhandledTouchEvents"] = Qt::AA_SynthesizeMouseForUnhandledTouchEvents;
    t["AA_UseHighDpiPixmaps"] = Qt::AA_UseHighDpiPixmaps;

    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    t["AA_ForceRasterWidgets"] = Qt::AA_ForceRasterWidgets;
    t["AA_UseDesktopOpenGL"] = Qt::AA_UseDesktopOpenGL;
    t["AA_UseOpenGLES"] = Qt::AA_UseOpenGLES;
    #endif

    t["AA_ImmediateWidgetCreation"] = Qt::AA_ImmediateWidgetCreation;
    t["AA_MSWindowsUseDirect3DByDefault"] = Qt::AA_MSWindowsUseDirect3DByDefault;

    // enum Qt::ApplicationState
    // flags Qt::ApplicationStates
    t["ApplicationSuspended"] = Qt::ApplicationSuspended;
    t["ApplicationHidden"] = Qt::ApplicationHidden;
    t["ApplicationInactive"] = Qt::ApplicationInactive;
    t["ApplicationActive"] = Qt::ApplicationActive;

    // enum Qt::ArrowType
    t["NoArrow"] = Qt::NoArrow;
    t["UpArrow"] = Qt::UpArrow;
    t["DownArrow"] = Qt::DownArrow;
    t["LeftArrow"] = Qt::LeftArrow;
    t["RightArrow"] = Qt::RightArrow;

    // enum Qt::AspectRatioMode
    t["IgnoreAspectRatio"] = Qt::IgnoreAspectRatio;
    t["KeepAspectRatio"] = Qt::KeepAspectRatio;
    t["KeepAspectRatioByExpanding"] = Qt::KeepAspectRatioByExpanding;

    // enum Qt::Axis
    t["XAxis"] = Qt::XAxis;
    t["YAxis"] = Qt::YAxis;
    t["ZAxis"] = Qt::ZAxis;

    // enum Qt::BGMode
    t["TransparentMode"] = Qt::TransparentMode;
    t["OpaqueMode"] = Qt::OpaqueMode;

    // enum Qt::BrushStyle
    t["NoBrush"] = Qt::NoBrush;
    t["SolidPattern"] = Qt::SolidPattern;
    t["Dense1Pattern"] = Qt::Dense1Pattern;
    t["Dense2Pattern"] = Qt::Dense2Pattern;
    t["Dense3Pattern"] = Qt::Dense3Pattern;
    t["Dense4Pattern"] = Qt::Dense4Pattern;
    t["Dense5Pattern"] = Qt::Dense5Pattern;
    t["Dense6Pattern"] = Qt::Dense6Pattern;
    t["Dense7Pattern"] = Qt::Dense7Pattern;
    t["HorPattern"] = Qt::HorPattern;
    t["VerPattern"] = Qt::VerPattern;
    t["CrossPattern"] = Qt::CrossPattern;
    t["BDiagPattern"] = Qt::BDiagPattern;
    t["FDiagPattern"] = Qt::FDiagPattern;
    t["DiagCrossPattern"] = Qt::DiagCrossPattern;
    t["LinearGradientPattern"] = Qt::LinearGradientPattern;
    t["ConicalGradientPattern"] = Qt::ConicalGradientPattern;
    t["RadialGradientPattern"] = Qt::RadialGradientPattern;
    t["TexturePattern"] = Qt::TexturePattern;

    // enum Qt::CaseSensitivity
    t["CaseInsensitive"] = Qt::CaseInsensitive;
    t["CaseSensitive"] = Qt::CaseSensitive;

    // enum Qt::CheckState
    t["Unchecked"] = Qt::Unchecked;
    t["PartiallyChecked"] = Qt::PartiallyChecked;
    t["Checked"] = Qt::Checked;

    // enum Qt::ClipOperation
    t["NoClip"] = Qt::NoClip;
    t["ReplaceClip"] = Qt::ReplaceClip;
    t["IntersectClip"] = Qt::IntersectClip;

    // enum Qt::ConnectionType
    t["AutoConnection"] = Qt::AutoConnection;
    t["DirectConnection"] = Qt::DirectConnection;
    t["QueuedConnection"] = Qt::QueuedConnection;
    t["BlockingQueuedConnection"] = Qt::BlockingQueuedConnection;
    t["UniqueConnection"] = Qt::UniqueConnection;

    // enum Qt::ContextMenuPolicy
    t["NoContextMenu"] = Qt::NoContextMenu;
    t["PreventContextMenu"] = Qt::PreventContextMenu;
    t["DefaultContextMenu"] = Qt::DefaultContextMenu;
    t["ActionsContextMenu"] = Qt::ActionsContextMenu;
    t["CustomContextMenu"] = Qt::CustomContextMenu;

    // enum Qt::CoordinateSystem
    t["DeviceCoordinates"] = Qt::DeviceCoordinates;
    t["LogicalCoordinates"] = Qt::LogicalCoordinates;

    // enum Qt::Corner
    t["TopLeftCorner"] = Qt::TopLeftCorner;
    t["TopRightCorner"] = Qt::TopRightCorner;
    t["BottomLeftCorner"] = Qt::BottomLeftCorner;
    t["BottomRightCorner"] = Qt::BottomRightCorner;

    // enum Qt::CursorMoveStyle
    t["LogicalMoveStyle"] = Qt::LogicalMoveStyle;
    t["VisualMoveStyle"] = Qt::VisualMoveStyle;

    // enum Qt::CursorShape
    t["ArrowCursor"] = Qt::ArrowCursor;
    t["UpArrowCursor"] = Qt::UpArrowCursor;
    t["CrossCursor"] = Qt::CrossCursor;
    t["WaitCursor"] = Qt::WaitCursor;
    t["IBeamCursor"] = Qt::IBeamCursor;
    t["SizeVerCursor"] = Qt::SizeVerCursor;
    t["SizeHorCursor"] = Qt::SizeHorCursor;
    t["SizeBDiagCursor"] = Qt::SizeBDiagCursor;
    t["SizeFDiagCursor"] = Qt::SizeFDiagCursor;
    t["SizeAllCursor"] = Qt::SizeAllCursor;
    t["BlankCursor"] = Qt::BlankCursor;
    t["SplitVCursor"] = Qt::SplitVCursor;
    t["SplitHCursor"] = Qt::SplitHCursor;
    t["PointingHandCursor"] = Qt::PointingHandCursor;
    t["ForbiddenCursor"] = Qt::ForbiddenCursor;
    t["OpenHandCursor"] = Qt::OpenHandCursor;
    t["ClosedHandCursor"] = Qt::ClosedHandCursor;
    t["WhatsThisCursor"] = Qt::WhatsThisCursor;
    t["BusyCursor"] = Qt::BusyCursor;
    t["DragMoveCursor"] = Qt::DragMoveCursor;
    t["DragCopyCursor"] = Qt::DragCopyCursor;
    t["DragLinkCursor"] = Qt::DragLinkCursor;
    t["BitmapCursor"] = Qt::BitmapCursor;

    // enum Qt::DateFormat
    t["TextDate"] = Qt::TextDate;
    t["ISODate"] = Qt::ISODate;
    t["SystemLocaleShortDate"] = Qt::SystemLocaleShortDate;
    t["SystemLocaleLongDate"] = Qt::SystemLocaleLongDate;
    t["DefaultLocaleShortDate"] = Qt::DefaultLocaleShortDate;
    t["DefaultLocaleLongDate"] = Qt::DefaultLocaleLongDate;
    t["SystemLocaleDate"] = Qt::SystemLocaleDate;
    t["LocaleDate"] = Qt::LocaleDate;
    t["LocalDate"] = Qt::LocalDate;
    t["RFC2822Date"] = Qt::RFC2822Date;

    // enum Qt::DayOfWeek
    t["Monday"] = Qt::Monday;
    t["Tuesday"] = Qt::Tuesday;
    t["Wednesday"] = Qt::Wednesday;
    t["Thursday"] = Qt::Thursday;
    t["Friday"] = Qt::Friday;
    t["Saturday"] = Qt::Saturday;
    t["Sunday"] = Qt::Sunday;

    // enum Qt::DockWidgetArea
    // flags Qt::DockWidgetAreas
    t["LeftDockWidgetArea"] = Qt::LeftDockWidgetArea;
    t["RightDockWidgetArea"] = Qt::RightDockWidgetArea;
    t["TopDockWidgetArea"] = Qt::TopDockWidgetArea;
    t["BottomDockWidgetArea"] = Qt::BottomDockWidgetArea;
    t["AllDockWidgetAreas"] = Qt::AllDockWidgetAreas;
    t["NoDockWidgetArea"] = Qt::NoDockWidgetArea;

    // enum Qt::DropAction
    // flags Qt::DropActions
    t["CopyAction"] = Qt::CopyAction;
    t["MoveAction"] = Qt::MoveAction;
    t["LinkAction"] = Qt::LinkAction;
    t["ActionMask"] = Qt::ActionMask;
    t["IgnoreAction"] = Qt::IgnoreAction;
    t["TargetMoveAction"] = Qt::TargetMoveAction;

    // enum Qt::Edge
    // flags Qt::Edges
    t["TopEdge"] = Qt::TopEdge;
    t["LeftEdge"] = Qt::LeftEdge;
    t["RightEdge"] = Qt::RightEdge;
    t["BottomEdge"] = Qt::BottomEdge;

    // enum Qt::EventPriority
    t["HighEventPriority"] = Qt::HighEventPriority;
    t["NormalEventPriority"] = Qt::NormalEventPriority;
    t["LowEventPriority"] = Qt::LowEventPriority;

    // enum Qt::FillRule
    t["OddEvenFill"] = Qt::OddEvenFill;
    t["WindingFill"] = Qt::WindingFill;

    // enum Qt::FindChildOption
    // flags Qt::FindChildOptions
    t["FindDirectChildrenOnly"] = Qt::FindDirectChildrenOnly;
    t["FindChildrenRecursively"] = Qt::FindChildrenRecursively;

    // enum Qt::FocusPolicy
    t["TabFocus"] = Qt::TabFocus;
    t["ClickFocus"] = Qt::ClickFocus;
    t["StrongFocus"] = Qt::StrongFocus;
    t["WheelFocus"] = Qt::WheelFocus;
    t["NoFocus"] = Qt::NoFocus;

    // enum Qt::FocusReason
    t["MouseFocusReason"] = Qt::MouseFocusReason;
    t["TabFocusReason"] = Qt::TabFocusReason;
    t["BacktabFocusReason"] = Qt::BacktabFocusReason;
    t["ActiveWindowFocusReason"] = Qt::ActiveWindowFocusReason;
    t["PopupFocusReason"] = Qt::PopupFocusReason;
    t["ShortcutFocusReason"] = Qt::ShortcutFocusReason;
    t["MenuBarFocusReason"] = Qt::MenuBarFocusReason;
    t["OtherFocusReason"] = Qt::OtherFocusReason;

    // enum Qt::GestureFlag
    // flags Qt::GestureFlags
    t["DontStartGestureOnChildren"] = Qt::DontStartGestureOnChildren;
    t["ReceivePartialGestures"] = Qt::ReceivePartialGestures;
    t["IgnoredGesturesPropagateToParent"] = Qt::IgnoredGesturesPropagateToParent;

    // enum Qt::GestureState
    t["GestureStarted"] = Qt::GestureStarted;
    t["GestureUpdated"] = Qt::GestureUpdated;
    t["GestureFinished"] = Qt::GestureFinished;
    t["GestureCanceled"] = Qt::GestureCanceled;

    // enum Qt::GestureType
    t["TapGesture"] = Qt::TapGesture;
    t["TapAndHoldGesture"] = Qt::TapAndHoldGesture;
    t["PanGesture"] = Qt::PanGesture;
    t["PinchGesture"] = Qt::PinchGesture;
    t["SwipeGesture"] = Qt::SwipeGesture;
    t["CustomGesture"] = Qt::CustomGesture;

    // enum Qt::GlobalColor
    t["white"] = Qt::white;
    t["black"] = Qt::black;
    t["red"] = Qt::red;
    t["darkRed"] = Qt::darkRed;
    t["green"] = Qt::green;
    t["darkGreen"] = Qt::darkGreen;
    t["blue"] = Qt::blue;
    t["darkBlue"] = Qt::darkBlue;
    t["cyan"] = Qt::cyan;
    t["darkCyan"] = Qt::darkCyan;
    t["magenta"] = Qt::magenta;
    t["darkMagenta"] = Qt::darkMagenta;
    t["yellow"] = Qt::yellow;
    t["darkYellow"] = Qt::darkYellow;
    t["gray"] = Qt::gray;
    t["darkGray"] = Qt::darkGray;
    t["lightGray"] = Qt::lightGray;
    t["transparent"] = Qt::transparent;
    t["color0"] = Qt::color0;
    t["color1"] = Qt::color1;

    // enum Qt::HitTestAccuracy
    t["ExactHit"] = Qt::ExactHit;
    t["FuzzyHit"] = Qt::FuzzyHit;

    // enum Qt::ImageConversionFlag
    // flags Qt::ImageConversionFlags
    t["AutoColor"] = Qt::AutoColor;
    t["ColorOnly"] = Qt::ColorOnly;
    t["MonoOnly"] = Qt::MonoOnly;

    t["DiffuseDither"] = Qt::DiffuseDither;
    t["OrderedDither"] = Qt::OrderedDither;
    t["ThresholdDither"] = Qt::ThresholdDither;

    t["ThresholdAlphaDither"] = Qt::ThresholdAlphaDither;
    t["OrderedAlphaDither"] = Qt::OrderedAlphaDither;
    t["DiffuseAlphaDither"] = Qt::DiffuseAlphaDither;

    t["PreferDither"] = Qt::PreferDither;
    t["AvoidDither"] = Qt::AvoidDither;
    t["NoOpaqueDetection"] = Qt::NoOpaqueDetection;

    // enum Qt::InputMethodHint
    // flags Qt::InputMethodHints

    t["ImhNone"] = Qt::ImhNone;

    t["ImhHiddenText"] = Qt::ImhHiddenText;
    t["ImhNoAutoUppercase"] = Qt::ImhNoAutoUppercase;
    t["ImhPreferNumbers"] = Qt::ImhPreferNumbers;
    t["ImhPreferUppercase"] = Qt::ImhPreferUppercase;
    t["ImhPreferLowercase"] = Qt::ImhPreferLowercase;
    t["ImhNoPredictiveText"] = Qt::ImhNoPredictiveText;

    t["ImhDigitsOnly"] = Qt::ImhDigitsOnly;
    t["ImhFormattedNumbersOnly"] = Qt::ImhFormattedNumbersOnly;
    t["ImhUppercaseOnly"] = Qt::ImhUppercaseOnly;
    t["ImhLowercaseOnly"] = Qt::ImhLowercaseOnly;
    t["ImhDialableCharactersOnly"] = Qt::ImhDialableCharactersOnly;
    t["ImhEmailCharactersOnly"] = Qt::ImhEmailCharactersOnly;
    t["ImhUrlCharactersOnly"] = Qt::ImhUrlCharactersOnly;

    t["ImhExclusiveInputMask"] = Qt::ImhExclusiveInputMask;

    // enum Qt::InputMethodQuery
    // flags Qt::InputMethodQueries
    t["ImEnabled"] = Qt::ImEnabled;
    t["ImMicroFocus"] = Qt::ImMicroFocus;
    t["ImCursorRectangle"] = Qt::ImCursorRectangle;
    t["ImFont"] = Qt::ImFont;
    t["ImCursorPosition"] = Qt::ImCursorPosition;
    t["ImSurroundingText"] = Qt::ImSurroundingText;
    t["ImCurrentSelection"] = Qt::ImCurrentSelection;
    t["ImMaximumTextLength"] = Qt::ImMaximumTextLength;
    t["ImAnchorPosition"] = Qt::ImAnchorPosition;
    t["ImHints"] = Qt::ImHints;
    t["ImPreferredLanguage"] = Qt::ImPreferredLanguage;
    t["ImPlatformData"] = Qt::ImPlatformData;
    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    t["ImAbsolutePosition"] = Qt::ImAbsolutePosition;
    t["ImTextBeforeCursor"] = Qt::ImTextBeforeCursor;
    t["ImTextAfterCursor"] = Qt::ImTextAfterCursor;
    #endif

    t["ImQueryInput"] = Qt::ImQueryInput;
    t["ImQueryAll"] = Qt::ImQueryAll;

    // enum Qt::ItemDataRole
    t["DisplayRole"] = Qt::DisplayRole;
    t["DecorationRole"] = Qt::DecorationRole;
    t["EditRole"] = Qt::EditRole;
    t["ToolTipRole"] = Qt::ToolTipRole;
    t["StatusTipRole"] = Qt::StatusTipRole;
    t["WhatsThisRole"] = Qt::WhatsThisRole;
    t["SizeHintRole"] = Qt::SizeHintRole;

    t["FontRole"] = Qt::FontRole;
    t["TextAlignmentRole"] = Qt::TextAlignmentRole;
    t["BackgroundRole"] = Qt::BackgroundRole;
    t["BackgroundColorRole"] = Qt::BackgroundColorRole;
    t["ForegroundRole"] = Qt::ForegroundRole;
    t["TextColorRole"] = Qt::TextColorRole;
    t["CheckStateRole"] = Qt::CheckStateRole;
    t["InitialSortOrderRole"] = Qt::InitialSortOrderRole;

    t["AccessibleTextRole"] = Qt::AccessibleTextRole;
    t["AccessibleDescriptionRole"] = Qt::AccessibleDescriptionRole;

    t["UserRole"] = Qt::UserRole;

    // enum Qt::ItemFlag
    // flags Qt::ItemFlags
    t["NoItemFlags"] = Qt::NoItemFlags;
    t["ItemIsSelectable"] = Qt::ItemIsSelectable;
    t["ItemIsEditable"] = Qt::ItemIsEditable;
    t["ItemIsDragEnabled"] = Qt::ItemIsDragEnabled;
    t["ItemIsDropEnabled"] = Qt::ItemIsDropEnabled;
    t["ItemIsUserCheckable"] = Qt::ItemIsUserCheckable;
    t["ItemIsEnabled"] = Qt::ItemIsEnabled;
    t["ItemIsTristate"] = Qt::ItemIsTristate;

    // enum Qt::ItemSelectionMode
    t["ContainsItemShape"] = Qt::ContainsItemShape;
    t["IntersectsItemShape"] = Qt::IntersectsItemShape;
    t["ContainsItemBoundingRect"] = Qt::ContainsItemBoundingRect;
    t["IntersectsItemBoundingRect"] = Qt::IntersectsItemBoundingRect;

    // enum Qt::Key
    t["Key_Escape"] = Qt::Key_Escape;
    t["Key_Tab"] = Qt::Key_Tab;
    t["Key_Backtab"] = Qt::Key_Backtab;
    t["Key_Backspace"] = Qt::Key_Backspace;
    t["Key_Return"] = Qt::Key_Return;
    t["Key_Enter"] = Qt::Key_Enter;
    t["Key_Insert"] = Qt::Key_Insert;
    t["Key_Delete"] = Qt::Key_Delete;
    t["Key_Pause"] = Qt::Key_Pause;
    t["Key_Print"] = Qt::Key_Print;
    t["Key_SysReq"] = Qt::Key_SysReq;
    t["Key_Clear"] = Qt::Key_Clear;
    t["Key_Home"] = Qt::Key_Home;
    t["Key_End"] = Qt::Key_End;
    t["Key_Left"] = Qt::Key_Left;
    t["Key_Up"] = Qt::Key_Up;
    t["Key_Right"] = Qt::Key_Right;
    t["Key_Down"] = Qt::Key_Down;
    t["Key_PageUp"] = Qt::Key_PageUp;
    t["Key_PageDown"] = Qt::Key_PageDown;
    t["Key_Shift"] = Qt::Key_Shift;
    t["Key_Control"] = Qt::Key_Control;
    t["Key_Meta"] = Qt::Key_Meta;
    t["Key_Alt"] = Qt::Key_Alt;
    t["Key_AltGr"] = Qt::Key_AltGr;
    t["Key_CapsLock"] = Qt::Key_CapsLock;
    t["Key_NumLock"] = Qt::Key_NumLock;
    t["Key_ScrollLock"] = Qt::Key_ScrollLock;
    t["Key_F1"] = Qt::Key_F1;
    t["Key_F2"] = Qt::Key_F2;
    t["Key_F3"] = Qt::Key_F3;
    t["Key_F4"] = Qt::Key_F4;
    t["Key_F5"] = Qt::Key_F5;
    t["Key_F6"] = Qt::Key_F6;
    t["Key_F7"] = Qt::Key_F7;
    t["Key_F8"] = Qt::Key_F8;
    t["Key_F9"] = Qt::Key_F9;
    t["Key_F10"] = Qt::Key_F10;
    t["Key_F11"] = Qt::Key_F11;
    t["Key_F12"] = Qt::Key_F12;
    t["Key_F13"] = Qt::Key_F13;
    t["Key_F14"] = Qt::Key_F14;
    t["Key_F15"] = Qt::Key_F15;
    t["Key_F16"] = Qt::Key_F16;
    t["Key_F17"] = Qt::Key_F17;
    t["Key_F18"] = Qt::Key_F18;
    t["Key_F19"] = Qt::Key_F19;
    t["Key_F20"] = Qt::Key_F20;
    t["Key_F21"] = Qt::Key_F21;
    t["Key_F22"] = Qt::Key_F22;
    t["Key_F23"] = Qt::Key_F23;
    t["Key_F24"] = Qt::Key_F24;
    t["Key_F25"] = Qt::Key_F25;
    t["Key_F26"] = Qt::Key_F26;
    t["Key_F27"] = Qt::Key_F27;
    t["Key_F28"] = Qt::Key_F28;
    t["Key_F29"] = Qt::Key_F29;
    t["Key_F30"] = Qt::Key_F30;
    t["Key_F31"] = Qt::Key_F31;
    t["Key_F32"] = Qt::Key_F32;
    t["Key_F33"] = Qt::Key_F33;
    t["Key_F34"] = Qt::Key_F34;
    t["Key_F35"] = Qt::Key_F35;
    t["Key_Super_L"] = Qt::Key_Super_L;
    t["Key_Super_R"] = Qt::Key_Super_R;
    t["Key_Menu"] = Qt::Key_Menu;
    t["Key_Hyper_L"] = Qt::Key_Hyper_L;
    t["Key_Hyper_R"] = Qt::Key_Hyper_R;
    t["Key_Help"] = Qt::Key_Help;
    t["Key_Direction_L"] = Qt::Key_Direction_L;
    t["Key_Direction_R"] = Qt::Key_Direction_R;
    t["Key_Space"] = Qt::Key_Space;
    t["Key_Any"] = Qt::Key_Any;
    t["Key_Exclam"] = Qt::Key_Exclam;
    t["Key_QuoteDbl"] = Qt::Key_QuoteDbl;
    t["Key_NumberSign"] = Qt::Key_NumberSign;
    t["Key_Dollar"] = Qt::Key_Dollar;
    t["Key_Percent"] = Qt::Key_Percent;
    t["Key_Ampersand"] = Qt::Key_Ampersand;
    t["Key_Apostrophe"] = Qt::Key_Apostrophe;
    t["Key_ParenLeft"] = Qt::Key_ParenLeft;
    t["Key_ParenRight"] = Qt::Key_ParenRight;
    t["Key_Asterisk"] = Qt::Key_Asterisk;
    t["Key_Plus"] = Qt::Key_Plus;
    t["Key_Comma"] = Qt::Key_Comma;
    t["Key_Minus"] = Qt::Key_Minus;
    t["Key_Period"] = Qt::Key_Period;
    t["Key_Slash"] = Qt::Key_Slash;
    t["Key_0"] = Qt::Key_0;
    t["Key_1"] = Qt::Key_1;
    t["Key_2"] = Qt::Key_2;
    t["Key_3"] = Qt::Key_3;
    t["Key_4"] = Qt::Key_4;
    t["Key_5"] = Qt::Key_5;
    t["Key_6"] = Qt::Key_6;
    t["Key_7"] = Qt::Key_7;
    t["Key_8"] = Qt::Key_8;
    t["Key_9"] = Qt::Key_9;
    t["Key_Colon"] = Qt::Key_Colon;
    t["Key_Semicolon"] = Qt::Key_Semicolon;
    t["Key_Less"] = Qt::Key_Less;
    t["Key_Equal"] = Qt::Key_Equal;
    t["Key_Greater"] = Qt::Key_Greater;
    t["Key_Question"] = Qt::Key_Question;
    t["Key_At"] = Qt::Key_At;
    t["Key_A"] = Qt::Key_A;
    t["Key_B"] = Qt::Key_B;
    t["Key_C"] = Qt::Key_C;
    t["Key_D"] = Qt::Key_D;
    t["Key_E"] = Qt::Key_E;
    t["Key_F"] = Qt::Key_F;
    t["Key_G"] = Qt::Key_G;
    t["Key_H"] = Qt::Key_H;
    t["Key_I"] = Qt::Key_I;
    t["Key_J"] = Qt::Key_J;
    t["Key_K"] = Qt::Key_K;
    t["Key_L"] = Qt::Key_L;
    t["Key_M"] = Qt::Key_M;
    t["Key_N"] = Qt::Key_N;
    t["Key_O"] = Qt::Key_O;
    t["Key_P"] = Qt::Key_P;
    t["Key_Q"] = Qt::Key_Q;
    t["Key_R"] = Qt::Key_R;
    t["Key_S"] = Qt::Key_S;
    t["Key_T"] = Qt::Key_T;
    t["Key_U"] = Qt::Key_U;
    t["Key_V"] = Qt::Key_V;
    t["Key_W"] = Qt::Key_W;
    t["Key_X"] = Qt::Key_X;
    t["Key_Y"] = Qt::Key_Y;
    t["Key_Z"] = Qt::Key_Z;
    t["Key_BracketLeft"] = Qt::Key_BracketLeft;
    t["Key_Backslash"] = Qt::Key_Backslash;
    t["Key_BracketRight"] = Qt::Key_BracketRight;
    t["Key_AsciiCircum"] = Qt::Key_AsciiCircum;
    t["Key_Underscore"] = Qt::Key_Underscore;
    t["Key_QuoteLeft"] = Qt::Key_QuoteLeft;
    t["Key_BraceLeft"] = Qt::Key_BraceLeft;
    t["Key_Bar"] = Qt::Key_Bar;
    t["Key_BraceRight"] = Qt::Key_BraceRight;
    t["Key_AsciiTilde"] = Qt::Key_AsciiTilde;
    t["Key_nobreakspace"] = Qt::Key_nobreakspace;
    t["Key_exclamdown"] = Qt::Key_exclamdown;
    t["Key_cent"] = Qt::Key_cent;
    t["Key_sterling"] = Qt::Key_sterling;
    t["Key_currency"] = Qt::Key_currency;
    t["Key_yen"] = Qt::Key_yen;
    t["Key_brokenbar"] = Qt::Key_brokenbar;
    t["Key_section"] = Qt::Key_section;
    t["Key_diaeresis"] = Qt::Key_diaeresis;
    t["Key_copyright"] = Qt::Key_copyright;
    t["Key_ordfeminine"] = Qt::Key_ordfeminine;
    t["Key_guillemotleft"] = Qt::Key_guillemotleft;
    t["Key_notsign"] = Qt::Key_notsign;
    t["Key_hyphen"] = Qt::Key_hyphen;
    t["Key_registered"] = Qt::Key_registered;
    t["Key_macron"] = Qt::Key_macron;
    t["Key_degree"] = Qt::Key_degree;
    t["Key_plusminus"] = Qt::Key_plusminus;
    t["Key_twosuperior"] = Qt::Key_twosuperior;
    t["Key_threesuperior"] = Qt::Key_threesuperior;
    t["Key_acute"] = Qt::Key_acute;
    t["Key_mu"] = Qt::Key_mu;
    t["Key_paragraph"] = Qt::Key_paragraph;
    t["Key_periodcentered"] = Qt::Key_periodcentered;
    t["Key_cedilla"] = Qt::Key_cedilla;
    t["Key_onesuperior"] = Qt::Key_onesuperior;
    t["Key_masculine"] = Qt::Key_masculine;
    t["Key_guillemotright"] = Qt::Key_guillemotright;
    t["Key_onequarter"] = Qt::Key_onequarter;
    t["Key_onehalf"] = Qt::Key_onehalf;
    t["Key_threequarters"] = Qt::Key_threequarters;
    t["Key_questiondown"] = Qt::Key_questiondown;
    t["Key_Agrave"] = Qt::Key_Agrave;
    t["Key_Aacute"] = Qt::Key_Aacute;
    t["Key_Acircumflex"] = Qt::Key_Acircumflex;
    t["Key_Atilde"] = Qt::Key_Atilde;
    t["Key_Adiaeresis"] = Qt::Key_Adiaeresis;
    t["Key_Aring"] = Qt::Key_Aring;
    t["Key_AE"] = Qt::Key_AE;
    t["Key_Ccedilla"] = Qt::Key_Ccedilla;
    t["Key_Egrave"] = Qt::Key_Egrave;
    t["Key_Eacute"] = Qt::Key_Eacute;
    t["Key_Ecircumflex"] = Qt::Key_Ecircumflex;
    t["Key_Ediaeresis"] = Qt::Key_Ediaeresis;
    t["Key_Igrave"] = Qt::Key_Igrave;
    t["Key_Iacute"] = Qt::Key_Iacute;
    t["Key_Icircumflex"] = Qt::Key_Icircumflex;
    t["Key_Idiaeresis"] = Qt::Key_Idiaeresis;
    t["Key_ETH"] = Qt::Key_ETH;
    t["Key_Ntilde"] = Qt::Key_Ntilde;
    t["Key_Ograve"] = Qt::Key_Ograve;
    t["Key_Oacute"] = Qt::Key_Oacute;
    t["Key_Ocircumflex"] = Qt::Key_Ocircumflex;
    t["Key_Otilde"] = Qt::Key_Otilde;
    t["Key_Odiaeresis"] = Qt::Key_Odiaeresis;
    t["Key_multiply"] = Qt::Key_multiply;
    t["Key_Ooblique"] = Qt::Key_Ooblique;
    t["Key_Ugrave"] = Qt::Key_Ugrave;
    t["Key_Uacute"] = Qt::Key_Uacute;
    t["Key_Ucircumflex"] = Qt::Key_Ucircumflex;
    t["Key_Udiaeresis"] = Qt::Key_Udiaeresis;
    t["Key_Yacute"] = Qt::Key_Yacute;
    t["Key_THORN"] = Qt::Key_THORN;
    t["Key_ssharp"] = Qt::Key_ssharp;
    t["Key_division"] = Qt::Key_division;
    t["Key_ydiaeresis"] = Qt::Key_ydiaeresis;
    t["Key_Multi_key"] = Qt::Key_Multi_key;
    t["Key_Codeinput"] = Qt::Key_Codeinput;
    t["Key_SingleCandidate"] = Qt::Key_SingleCandidate;
    t["Key_MultipleCandidate"] = Qt::Key_MultipleCandidate;
    t["Key_PreviousCandidate"] = Qt::Key_PreviousCandidate;
    t["Key_Mode_switch"] = Qt::Key_Mode_switch;
    t["Key_Kanji"] = Qt::Key_Kanji;
    t["Key_Muhenkan"] = Qt::Key_Muhenkan;
    t["Key_Henkan"] = Qt::Key_Henkan;
    t["Key_Romaji"] = Qt::Key_Romaji;
    t["Key_Hiragana"] = Qt::Key_Hiragana;
    t["Key_Katakana"] = Qt::Key_Katakana;
    t["Key_Hiragana_Katakana"] = Qt::Key_Hiragana_Katakana;
    t["Key_Zenkaku"] = Qt::Key_Zenkaku;
    t["Key_Hankaku"] = Qt::Key_Hankaku;
    t["Key_Zenkaku_Hankaku"] = Qt::Key_Zenkaku_Hankaku;
    t["Key_Touroku"] = Qt::Key_Touroku;
    t["Key_Massyo"] = Qt::Key_Massyo;
    t["Key_Kana_Lock"] = Qt::Key_Kana_Lock;
    t["Key_Kana_Shift"] = Qt::Key_Kana_Shift;
    t["Key_Eisu_Shift"] = Qt::Key_Eisu_Shift;
    t["Key_Eisu_toggle"] = Qt::Key_Eisu_toggle;
    t["Key_Hangul"] = Qt::Key_Hangul;
    t["Key_Hangul_Start"] = Qt::Key_Hangul_Start;
    t["Key_Hangul_End"] = Qt::Key_Hangul_End;
    t["Key_Hangul_Hanja"] = Qt::Key_Hangul_Hanja;
    t["Key_Hangul_Jamo"] = Qt::Key_Hangul_Jamo;
    t["Key_Hangul_Romaja"] = Qt::Key_Hangul_Romaja;
    t["Key_Hangul_Jeonja"] = Qt::Key_Hangul_Jeonja;
    t["Key_Hangul_Banja"] = Qt::Key_Hangul_Banja;
    t["Key_Hangul_PreHanja"] = Qt::Key_Hangul_PreHanja;
    t["Key_Hangul_PostHanja"] = Qt::Key_Hangul_PostHanja;
    t["Key_Hangul_Special"] = Qt::Key_Hangul_Special;
    t["Key_Dead_Grave"] = Qt::Key_Dead_Grave;
    t["Key_Dead_Acute"] = Qt::Key_Dead_Acute;
    t["Key_Dead_Circumflex"] = Qt::Key_Dead_Circumflex;
    t["Key_Dead_Tilde"] = Qt::Key_Dead_Tilde;
    t["Key_Dead_Macron"] = Qt::Key_Dead_Macron;
    t["Key_Dead_Breve"] = Qt::Key_Dead_Breve;
    t["Key_Dead_Abovedot"] = Qt::Key_Dead_Abovedot;
    t["Key_Dead_Diaeresis"] = Qt::Key_Dead_Diaeresis;
    t["Key_Dead_Abovering"] = Qt::Key_Dead_Abovering;
    t["Key_Dead_Doubleacute"] = Qt::Key_Dead_Doubleacute;
    t["Key_Dead_Caron"] = Qt::Key_Dead_Caron;
    t["Key_Dead_Cedilla"] = Qt::Key_Dead_Cedilla;
    t["Key_Dead_Ogonek"] = Qt::Key_Dead_Ogonek;
    t["Key_Dead_Iota"] = Qt::Key_Dead_Iota;
    t["Key_Dead_Voiced_Sound"] = Qt::Key_Dead_Voiced_Sound;
    t["Key_Dead_Semivoiced_Sound"] = Qt::Key_Dead_Semivoiced_Sound;
    t["Key_Dead_Belowdot"] = Qt::Key_Dead_Belowdot;
    t["Key_Dead_Hook"] = Qt::Key_Dead_Hook;
    t["Key_Dead_Horn"] = Qt::Key_Dead_Horn;
    t["Key_Back"] = Qt::Key_Back;
    t["Key_Forward"] = Qt::Key_Forward;
    t["Key_Stop"] = Qt::Key_Stop;
    t["Key_Refresh"] = Qt::Key_Refresh;
    t["Key_VolumeDown"] = Qt::Key_VolumeDown;
    t["Key_VolumeMute"] = Qt::Key_VolumeMute;
    t["Key_VolumeUp"] = Qt::Key_VolumeUp;
    t["Key_BassBoost"] = Qt::Key_BassBoost;
    t["Key_BassUp"] = Qt::Key_BassUp;
    t["Key_BassDown"] = Qt::Key_BassDown;
    t["Key_TrebleUp"] = Qt::Key_TrebleUp;
    t["Key_TrebleDown"] = Qt::Key_TrebleDown;
    t["Key_MediaPlay"] = Qt::Key_MediaPlay;
    t["Key_MediaStop"] = Qt::Key_MediaStop;
    t["Key_MediaPrevious"] = Qt::Key_MediaPrevious;
    t["Key_MediaNext"] = Qt::Key_MediaNext;
    t["Key_MediaRecord"] = Qt::Key_MediaRecord;
    t["Key_MediaPause"] = Qt::Key_MediaPause;
    t["Key_MediaTogglePlayPause"] = Qt::Key_MediaTogglePlayPause;
    t["Key_HomePage"] = Qt::Key_HomePage;
    t["Key_Favorites"] = Qt::Key_Favorites;
    t["Key_Search"] = Qt::Key_Search;
    t["Key_Standby"] = Qt::Key_Standby;
    t["Key_OpenUrl"] = Qt::Key_OpenUrl;
    t["Key_LaunchMail"] = Qt::Key_LaunchMail;
    t["Key_LaunchMedia"] = Qt::Key_LaunchMedia;
    t["Key_Launch0"] = Qt::Key_Launch0;
    t["Key_Launch1"] = Qt::Key_Launch1;
    t["Key_Launch2"] = Qt::Key_Launch2;
    t["Key_Launch3"] = Qt::Key_Launch3;
    t["Key_Launch4"] = Qt::Key_Launch4;
    t["Key_Launch5"] = Qt::Key_Launch5;
    t["Key_Launch6"] = Qt::Key_Launch6;
    t["Key_Launch7"] = Qt::Key_Launch7;
    t["Key_Launch8"] = Qt::Key_Launch8;
    t["Key_Launch9"] = Qt::Key_Launch9;
    t["Key_LaunchA"] = Qt::Key_LaunchA;
    t["Key_LaunchB"] = Qt::Key_LaunchB;
    t["Key_LaunchC"] = Qt::Key_LaunchC;
    t["Key_LaunchD"] = Qt::Key_LaunchD;
    t["Key_LaunchE"] = Qt::Key_LaunchE;
    t["Key_LaunchF"] = Qt::Key_LaunchF;
    t["Key_LaunchG"] = Qt::Key_LaunchG;
    t["Key_LaunchH"] = Qt::Key_LaunchH;
    t["Key_MonBrightnessUp"] = Qt::Key_MonBrightnessUp;
    t["Key_MonBrightnessDown"] = Qt::Key_MonBrightnessDown;
    t["Key_KeyboardLightOnOff"] = Qt::Key_KeyboardLightOnOff;
    t["Key_KeyboardBrightnessUp"] = Qt::Key_KeyboardBrightnessUp;
    t["Key_KeyboardBrightnessDown"] = Qt::Key_KeyboardBrightnessDown;
    t["Key_PowerOff"] = Qt::Key_PowerOff;
    t["Key_WakeUp"] = Qt::Key_WakeUp;
    t["Key_Eject"] = Qt::Key_Eject;
    t["Key_ScreenSaver"] = Qt::Key_ScreenSaver;
    t["Key_WWW"] = Qt::Key_WWW;
    t["Key_Memo"] = Qt::Key_Memo;
    t["Key_LightBulb"] = Qt::Key_LightBulb;
    t["Key_Shop"] = Qt::Key_Shop;
    t["Key_History"] = Qt::Key_History;
    t["Key_AddFavorite"] = Qt::Key_AddFavorite;
    t["Key_HotLinks"] = Qt::Key_HotLinks;
    t["Key_BrightnessAdjust"] = Qt::Key_BrightnessAdjust;
    t["Key_Finance"] = Qt::Key_Finance;
    t["Key_Community"] = Qt::Key_Community;
    t["Key_AudioRewind"] = Qt::Key_AudioRewind;
    t["Key_BackForward"] = Qt::Key_BackForward;
    t["Key_ApplicationLeft"] = Qt::Key_ApplicationLeft;
    t["Key_ApplicationRight"] = Qt::Key_ApplicationRight;
    t["Key_Book"] = Qt::Key_Book;
    t["Key_CD"] = Qt::Key_CD;
    t["Key_Calculator"] = Qt::Key_Calculator;
    t["Key_ToDoList"] = Qt::Key_ToDoList;
    t["Key_ClearGrab"] = Qt::Key_ClearGrab;
    t["Key_Close"] = Qt::Key_Close;
    t["Key_Copy"] = Qt::Key_Copy;
    t["Key_Cut"] = Qt::Key_Cut;
    t["Key_Display"] = Qt::Key_Display;
    t["Key_DOS"] = Qt::Key_DOS;
    t["Key_Documents"] = Qt::Key_Documents;
    t["Key_Excel"] = Qt::Key_Excel;
    t["Key_Explorer"] = Qt::Key_Explorer;
    t["Key_Game"] = Qt::Key_Game;
    t["Key_Go"] = Qt::Key_Go;
    t["Key_iTouch"] = Qt::Key_iTouch;
    t["Key_LogOff"] = Qt::Key_LogOff;
    t["Key_Market"] = Qt::Key_Market;
    t["Key_Meeting"] = Qt::Key_Meeting;
    t["Key_MenuKB"] = Qt::Key_MenuKB;
    t["Key_MenuPB"] = Qt::Key_MenuPB;
    t["Key_MySites"] = Qt::Key_MySites;
    t["Key_News"] = Qt::Key_News;
    t["Key_OfficeHome"] = Qt::Key_OfficeHome;
    t["Key_Option"] = Qt::Key_Option;
    t["Key_Paste"] = Qt::Key_Paste;
    t["Key_Phone"] = Qt::Key_Phone;
    t["Key_Calendar"] = Qt::Key_Calendar;
    t["Key_Reply"] = Qt::Key_Reply;
    t["Key_Reload"] = Qt::Key_Reload;
    t["Key_RotateWindows"] = Qt::Key_RotateWindows;
    t["Key_RotationPB"] = Qt::Key_RotationPB;
    t["Key_RotationKB"] = Qt::Key_RotationKB;
    t["Key_Save"] = Qt::Key_Save;
    t["Key_Send"] = Qt::Key_Send;
    t["Key_Spell"] = Qt::Key_Spell;
    t["Key_SplitScreen"] = Qt::Key_SplitScreen;
    t["Key_Support"] = Qt::Key_Support;
    t["Key_TaskPane"] = Qt::Key_TaskPane;
    t["Key_Terminal"] = Qt::Key_Terminal;
    t["Key_Tools"] = Qt::Key_Tools;
    t["Key_Travel"] = Qt::Key_Travel;
    t["Key_Video"] = Qt::Key_Video;
    t["Key_Word"] = Qt::Key_Word;
    t["Key_Xfer"] = Qt::Key_Xfer;
    t["Key_ZoomIn"] = Qt::Key_ZoomIn;
    t["Key_ZoomOut"] = Qt::Key_ZoomOut;
    t["Key_Away"] = Qt::Key_Away;
    t["Key_Messenger"] = Qt::Key_Messenger;
    t["Key_WebCam"] = Qt::Key_WebCam;
    t["Key_MailForward"] = Qt::Key_MailForward;
    t["Key_Pictures"] = Qt::Key_Pictures;
    t["Key_Music"] = Qt::Key_Music;
    t["Key_Battery"] = Qt::Key_Battery;
    t["Key_Bluetooth"] = Qt::Key_Bluetooth;
    t["Key_WLAN"] = Qt::Key_WLAN;
    t["Key_UWB"] = Qt::Key_UWB;
    t["Key_AudioForward"] = Qt::Key_AudioForward;
    t["Key_AudioRepeat"] = Qt::Key_AudioRepeat;
    t["Key_AudioRandomPlay"] = Qt::Key_AudioRandomPlay;
    t["Key_Subtitle"] = Qt::Key_Subtitle;
    t["Key_AudioCycleTrack"] = Qt::Key_AudioCycleTrack;
    t["Key_Time"] = Qt::Key_Time;
    t["Key_Hibernate"] = Qt::Key_Hibernate;
    t["Key_View"] = Qt::Key_View;
    t["Key_TopMenu"] = Qt::Key_TopMenu;
    t["Key_PowerDown"] = Qt::Key_PowerDown;
    t["Key_Suspend"] = Qt::Key_Suspend;
    t["Key_ContrastAdjust"] = Qt::Key_ContrastAdjust;
    t["Key_TouchpadToggle"] = Qt::Key_TouchpadToggle;
    t["Key_TouchpadOn"] = Qt::Key_TouchpadOn;
    t["Key_TouchpadOff"] = Qt::Key_TouchpadOff;
    t["Key_MicMute"] = Qt::Key_MicMute;
    t["Key_Red"] = Qt::Key_Red;
    t["Key_Green"] = Qt::Key_Green;
    t["Key_Yellow"] = Qt::Key_Yellow;
    t["Key_Blue"] = Qt::Key_Blue;
    t["Key_ChannelUp"] = Qt::Key_ChannelUp;
    t["Key_ChannelDown"] = Qt::Key_ChannelDown;
    t["Key_MediaLast"] = Qt::Key_MediaLast;
    t["Key_unknown"] = Qt::Key_unknown;
    t["Key_Call"] = Qt::Key_Call;
    t["Key_Camera"] = Qt::Key_Camera;
    t["Key_CameraFocus"] = Qt::Key_CameraFocus;
    t["Key_Context1"] = Qt::Key_Context1;
    t["Key_Context2"] = Qt::Key_Context2;
    t["Key_Context3"] = Qt::Key_Context3;
    t["Key_Context4"] = Qt::Key_Context4;
    t["Key_Flip"] = Qt::Key_Flip;
    t["Key_Hangup"] = Qt::Key_Hangup;
    t["Key_No"] = Qt::Key_No;
    t["Key_Select"] = Qt::Key_Select;
    t["Key_Yes"] = Qt::Key_Yes;
    t["Key_ToggleCallHangup"] = Qt::Key_ToggleCallHangup;
    t["Key_VoiceDial"] = Qt::Key_VoiceDial;
    t["Key_LastNumberRedial"] = Qt::Key_LastNumberRedial;
    t["Key_Execute"] = Qt::Key_Execute;
    t["Key_Printer"] = Qt::Key_Printer;
    t["Key_Play"] = Qt::Key_Play;
    t["Key_Sleep"] = Qt::Key_Sleep;
    t["Key_Zoom"] = Qt::Key_Zoom;
    t["Key_Cancel"] = Qt::Key_Cancel;

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

    return 0;
}
