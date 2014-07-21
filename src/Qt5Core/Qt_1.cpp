#include "Qt.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QString.hpp"

#include <Qt>

// http://qt-project.org/doc/qt-5/qt.html

int luaopen_Qt5Core_Qt(lua_State* const state)
{
    lua::thread env(state);

    env["Qt"] = lua::value::table;
    auto t = env["Qt"];

    lua::qt_constants_1(t);
    lua::qt_constants_2(t);
    lua::qt_constants_3(t);
    lua::qt_constants_4(t);

    return 0;
}

void lua::qt_constants_1(lua::global& t)
{
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
}
