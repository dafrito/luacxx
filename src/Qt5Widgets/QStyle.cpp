#include "QStyle.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QSizePolicy.hpp"
#include "../Qt5Core/Qt.hpp"

#include <QStyle>

#include "../Qt5Gui/QPainter.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Gui/QPixmap.hpp"
#include "../Qt5Gui/QPalette.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Gui/QFontMetrics.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QRect.hpp"

int QStyle_drawItemText(lua_State* const state)
{
    return 0;
}
int QStyle_polish(lua_State* const state)
{
    return 0;
}
int QStyle_unpolish(lua_State* const state)
{
    return 0;
}

void lua::QStyle_metatable(const lua::index& mt)
{
    mt["combinedLayoutSpacing"] = &QStyle::combinedLayoutSpacing;
    mt["drawItemPixmap"] = &QStyle::drawItemPixmap;
    mt["drawItemText"] = QStyle_drawItemText;
    mt["itemPixmapRect"] = &QStyle::itemPixmapRect;
    mt["itemTextRect"] = &QStyle::itemTextRect;
    mt["polish"] = QStyle_polish;
    mt["proxy"] = &QStyle::proxy;
    mt["standardPalette"] = &QStyle::standardPalette;
    mt["unpolish"] = QStyle_unpolish;
}

int QStyle_sliderPositionFromValue(lua_State* const state)
{
    return 0;
}
int QStyle_sliderValueFromPosition(lua_State* const state)
{
    return 0;
}

int luaopen_Qt5Widgets_QStyle(lua_State* const state)
{
    lua::thread env(state);

    env["QStyle"] = lua::value::table;
    auto t = env["QStyle"];

    t["alignedRect"] = QStyle::alignedRect;
    t["sliderPositionFromValue"] = QStyle_sliderPositionFromValue;
    t["sliderValueFromPosition"] = QStyle_sliderValueFromPosition;
    t["visualAlignment"] = QStyle::visualAlignment;
    t["visualPos"] = QStyle::visualPos;
    t["visualRect"] = QStyle::visualRect;

    // enum QStyle::ComplexControl
    t["CC_SpinBox"] = QStyle::CC_SpinBox;
    t["CC_ComboBox"] = QStyle::CC_ComboBox;
    t["CC_ScrollBar"] = QStyle::CC_ScrollBar;
    t["CC_Slider"] = QStyle::CC_Slider;
    t["CC_ToolButton"] = QStyle::CC_ToolButton;
    t["CC_TitleBar"] = QStyle::CC_TitleBar;
    t["CC_GroupBox"] = QStyle::CC_GroupBox;
    t["CC_Dial"] = QStyle::CC_Dial;
    t["CC_MdiControls"] = QStyle::CC_MdiControls;
    t["CC_CustomBase"] = QStyle::CC_CustomBase;

    // enum QStyle::ContentsType
    t["CT_CheckBox"] = QStyle::CT_CheckBox;
    t["CT_ComboBox"] = QStyle::CT_ComboBox;
    t["CT_HeaderSection"] = QStyle::CT_HeaderSection;
    t["CT_LineEdit"] = QStyle::CT_LineEdit;
    t["CT_Menu"] = QStyle::CT_Menu;
    t["CT_MenuBar"] = QStyle::CT_MenuBar;
    t["CT_MenuBarItem"] = QStyle::CT_MenuBarItem;
    t["CT_MenuItem"] = QStyle::CT_MenuItem;
    t["CT_ProgressBar"] = QStyle::CT_ProgressBar;
    t["CT_PushButton"] = QStyle::CT_PushButton;
    t["CT_RadioButton"] = QStyle::CT_RadioButton;
    t["CT_SizeGrip"] = QStyle::CT_SizeGrip;
    t["CT_Slider"] = QStyle::CT_Slider;
    t["CT_ScrollBar"] = QStyle::CT_ScrollBar;
    t["CT_SpinBox"] = QStyle::CT_SpinBox;
    t["CT_Splitter"] = QStyle::CT_Splitter;
    t["CT_TabBarTab"] = QStyle::CT_TabBarTab;
    t["CT_TabWidget"] = QStyle::CT_TabWidget;
    t["CT_ToolButton"] = QStyle::CT_ToolButton;
    t["CT_GroupBox"] = QStyle::CT_GroupBox;
    t["CT_ItemViewItem"] = QStyle::CT_ItemViewItem;
    t["CT_CustomBase"] = QStyle::CT_CustomBase;
    t["CT_MdiControls"] = QStyle::CT_MdiControls;

    // enum QStyle::ControlElement
    t["CE_PushButton"] = QStyle::CE_PushButton;
    t["CE_PushButtonBevel"] = QStyle::CE_PushButtonBevel;
    t["CE_PushButtonLabel"] = QStyle::CE_PushButtonLabel;
    t["CE_DockWidgetTitle"] = QStyle::CE_DockWidgetTitle;
    t["CE_Splitter"] = QStyle::CE_Splitter;
    t["CE_CheckBox"] = QStyle::CE_CheckBox;
    t["CE_CheckBoxLabel"] = QStyle::CE_CheckBoxLabel;
    t["CE_RadioButton"] = QStyle::CE_RadioButton;
    t["CE_RadioButtonLabel"] = QStyle::CE_RadioButtonLabel;
    t["CE_TabBarTab"] = QStyle::CE_TabBarTab;
    t["CE_TabBarTabShape"] = QStyle::CE_TabBarTabShape;
    t["CE_TabBarTabLabel"] = QStyle::CE_TabBarTabLabel;
    t["CE_ProgressBar"] = QStyle::CE_ProgressBar;
    t["CE_ProgressBarGroove"] = QStyle::CE_ProgressBarGroove;
    t["CE_ProgressBarContents"] = QStyle::CE_ProgressBarContents;
    t["CE_ProgressBarLabel"] = QStyle::CE_ProgressBarLabel;
    t["CE_ToolButtonLabel"] = QStyle::CE_ToolButtonLabel;
    t["CE_MenuBarItem"] = QStyle::CE_MenuBarItem;
    t["CE_MenuBarEmptyArea"] = QStyle::CE_MenuBarEmptyArea;
    t["CE_MenuItem"] = QStyle::CE_MenuItem;
    t["CE_MenuScroller"] = QStyle::CE_MenuScroller;
    t["CE_MenuTearoff"] = QStyle::CE_MenuTearoff;
    t["CE_MenuEmptyArea"] = QStyle::CE_MenuEmptyArea;
    t["CE_MenuHMargin"] = QStyle::CE_MenuHMargin;
    t["CE_MenuVMargin"] = QStyle::CE_MenuVMargin;
    t["CE_ToolBoxTab"] = QStyle::CE_ToolBoxTab;
    t["CE_SizeGrip"] = QStyle::CE_SizeGrip;
    t["CE_Header"] = QStyle::CE_Header;
    t["CE_HeaderSection"] = QStyle::CE_HeaderSection;
    t["CE_HeaderLabel"] = QStyle::CE_HeaderLabel;
    t["CE_ScrollBarAddLine"] = QStyle::CE_ScrollBarAddLine;
    t["CE_ScrollBarSubLine"] = QStyle::CE_ScrollBarSubLine;
    t["CE_ScrollBarAddPage"] = QStyle::CE_ScrollBarAddPage;
    t["CE_ScrollBarSubPage"] = QStyle::CE_ScrollBarSubPage;
    t["CE_ScrollBarSlider"] = QStyle::CE_ScrollBarSlider;
    t["CE_ScrollBarFirst"] = QStyle::CE_ScrollBarFirst;
    t["CE_ScrollBarLast"] = QStyle::CE_ScrollBarLast;
    t["CE_RubberBand"] = QStyle::CE_RubberBand;
    t["CE_FocusFrame"] = QStyle::CE_FocusFrame;
    t["CE_ItemViewItem"] = QStyle::CE_ItemViewItem;
    t["CE_CustomBase"] = QStyle::CE_CustomBase;
    t["CE_ComboBoxLabel"] = QStyle::CE_ComboBoxLabel;
    t["CE_ToolBar"] = QStyle::CE_ToolBar;
    t["CE_ToolBoxTabShape"] = QStyle::CE_ToolBoxTabShape;
    t["CE_ToolBoxTabLabel"] = QStyle::CE_ToolBoxTabLabel;
    t["CE_HeaderEmptyArea"] = QStyle::CE_HeaderEmptyArea;
    t["CE_ShapedFrame"] = QStyle::CE_ShapedFrame;

    // enum QStyle::PixelMetric
    t["PM_ButtonMargin"] = QStyle::PM_ButtonMargin;
    t["PM_DockWidgetTitleBarButtonMargin"] = QStyle::PM_DockWidgetTitleBarButtonMargin;
    t["PM_ButtonDefaultIndicator"] = QStyle::PM_ButtonDefaultIndicator;
    t["PM_MenuButtonIndicator"] = QStyle::PM_MenuButtonIndicator;
    t["PM_ButtonShiftHorizontal"] = QStyle::PM_ButtonShiftHorizontal;
    t["PM_ButtonShiftVertical"] = QStyle::PM_ButtonShiftVertical;
    t["PM_DefaultFrameWidth"] = QStyle::PM_DefaultFrameWidth;
    t["PM_SpinBoxFrameWidth"] = QStyle::PM_SpinBoxFrameWidth;
    t["PM_ComboBoxFrameWidth"] = QStyle::PM_ComboBoxFrameWidth;
    t["PM_MDIFrameWidth"] = QStyle::PM_MDIFrameWidth;
    t["PM_MdiSubWindowFrameWidth"] = QStyle::PM_MdiSubWindowFrameWidth;
    t["PM_MDIMinimizedWidth"] = QStyle::PM_MDIMinimizedWidth;
    t["PM_MdiSubWindowMinimizedWidth"] = QStyle::PM_MdiSubWindowMinimizedWidth;
    t["PM_LayoutLeftMargin"] = QStyle::PM_LayoutLeftMargin;
    t["PM_LayoutTopMargin"] = QStyle::PM_LayoutTopMargin;
    t["PM_LayoutRightMargin"] = QStyle::PM_LayoutRightMargin;
    t["PM_LayoutBottomMargin"] = QStyle::PM_LayoutBottomMargin;
    t["PM_LayoutHorizontalSpacing"] = QStyle::PM_LayoutHorizontalSpacing;
    t["PM_LayoutVerticalSpacing"] = QStyle::PM_LayoutVerticalSpacing;
    t["PM_MaximumDragDistance"] = QStyle::PM_MaximumDragDistance;
    t["PM_ScrollBarExtent"] = QStyle::PM_ScrollBarExtent;
    t["PM_ScrollBarSliderMin"] = QStyle::PM_ScrollBarSliderMin;
    t["PM_SliderThickness"] = QStyle::PM_SliderThickness;
    t["PM_SliderControlThickness"] = QStyle::PM_SliderControlThickness;
    t["PM_SliderLength"] = QStyle::PM_SliderLength;
    t["PM_SliderTickmarkOffset"] = QStyle::PM_SliderTickmarkOffset;
    t["PM_SliderSpaceAvailable"] = QStyle::PM_SliderSpaceAvailable;
    t["PM_DockWidgetSeparatorExtent"] = QStyle::PM_DockWidgetSeparatorExtent;
    t["PM_DockWidgetHandleExtent"] = QStyle::PM_DockWidgetHandleExtent;
    t["PM_DockWidgetFrameWidth"] = QStyle::PM_DockWidgetFrameWidth;
    t["PM_DockWidgetTitleMargin"] = QStyle::PM_DockWidgetTitleMargin;
    t["PM_MenuBarPanelWidth"] = QStyle::PM_MenuBarPanelWidth;
    t["PM_MenuBarItemSpacing"] = QStyle::PM_MenuBarItemSpacing;
    t["PM_MenuBarHMargin"] = QStyle::PM_MenuBarHMargin;
    t["PM_MenuBarVMargin"] = QStyle::PM_MenuBarVMargin;
    t["PM_ToolBarFrameWidth"] = QStyle::PM_ToolBarFrameWidth;
    t["PM_ToolBarHandleExtent"] = QStyle::PM_ToolBarHandleExtent;
    t["PM_ToolBarItemMargin"] = QStyle::PM_ToolBarItemMargin;
    t["PM_ToolBarItemSpacing"] = QStyle::PM_ToolBarItemSpacing;
    t["PM_ToolBarSeparatorExtent"] = QStyle::PM_ToolBarSeparatorExtent;
    t["PM_ToolBarExtensionExtent"] = QStyle::PM_ToolBarExtensionExtent;
    t["PM_TabBarTabOverlap"] = QStyle::PM_TabBarTabOverlap;
    t["PM_TabBarTabHSpace"] = QStyle::PM_TabBarTabHSpace;
    t["PM_TabBarTabVSpace"] = QStyle::PM_TabBarTabVSpace;
    t["PM_TabBarBaseHeight"] = QStyle::PM_TabBarBaseHeight;
    t["PM_TabBarBaseOverlap"] = QStyle::PM_TabBarBaseOverlap;
    t["PM_TabBarScrollButtonWidth"] = QStyle::PM_TabBarScrollButtonWidth;
    t["PM_TabBarTabShiftHorizontal"] = QStyle::PM_TabBarTabShiftHorizontal;
    t["PM_TabBarTabShiftVertical"] = QStyle::PM_TabBarTabShiftVertical;
    t["PM_ProgressBarChunkWidth"] = QStyle::PM_ProgressBarChunkWidth;
    t["PM_SplitterWidth"] = QStyle::PM_SplitterWidth;
    t["PM_TitleBarHeight"] = QStyle::PM_TitleBarHeight;
    t["PM_IndicatorWidth"] = QStyle::PM_IndicatorWidth;
    t["PM_IndicatorHeight"] = QStyle::PM_IndicatorHeight;
    t["PM_ExclusiveIndicatorWidth"] = QStyle::PM_ExclusiveIndicatorWidth;
    t["PM_ExclusiveIndicatorHeight"] = QStyle::PM_ExclusiveIndicatorHeight;
    t["PM_MenuPanelWidth"] = QStyle::PM_MenuPanelWidth;
    t["PM_MenuHMargin"] = QStyle::PM_MenuHMargin;
    t["PM_MenuVMargin"] = QStyle::PM_MenuVMargin;
    t["PM_MenuScrollerHeight"] = QStyle::PM_MenuScrollerHeight;
    t["PM_MenuTearoffHeight"] = QStyle::PM_MenuTearoffHeight;
    t["PM_MenuDesktopFrameWidth"] = QStyle::PM_MenuDesktopFrameWidth;
    t["PM_HeaderMarkSize"] = QStyle::PM_HeaderMarkSize;
    t["PM_HeaderGripMargin"] = QStyle::PM_HeaderGripMargin;
    t["PM_HeaderMargin"] = QStyle::PM_HeaderMargin;
    t["PM_SpinBoxSliderHeight"] = QStyle::PM_SpinBoxSliderHeight;
    t["PM_ToolBarIconSize"] = QStyle::PM_ToolBarIconSize;
    t["PM_SmallIconSize"] = QStyle::PM_SmallIconSize;
    t["PM_LargeIconSize"] = QStyle::PM_LargeIconSize;
    t["PM_FocusFrameHMargin"] = QStyle::PM_FocusFrameHMargin;
    t["PM_FocusFrameVMargin"] = QStyle::PM_FocusFrameVMargin;
    t["PM_IconViewIconSize"] = QStyle::PM_IconViewIconSize;
    t["PM_ListViewIconSize"] = QStyle::PM_ListViewIconSize;
    t["PM_ToolTipLabelFrameWidth"] = QStyle::PM_ToolTipLabelFrameWidth;
    t["PM_CheckBoxLabelSpacing"] = QStyle::PM_CheckBoxLabelSpacing;
    t["PM_RadioButtonLabelSpacing"] = QStyle::PM_RadioButtonLabelSpacing;
    t["PM_TabBarIconSize"] = QStyle::PM_TabBarIconSize;
    t["PM_SizeGripSize"] = QStyle::PM_SizeGripSize;
    t["PM_MessageBoxIconSize"] = QStyle::PM_MessageBoxIconSize;
    t["PM_ButtonIconSize"] = QStyle::PM_ButtonIconSize;
    t["PM_TextCursorWidth"] = QStyle::PM_TextCursorWidth;
    t["PM_TabBar_ScrollButtonOverlap"] = QStyle::PM_TabBar_ScrollButtonOverlap;
    t["PM_TabCloseIndicatorWidth"] = QStyle::PM_TabCloseIndicatorWidth;
    t["PM_TabCloseIndicatorHeight"] = QStyle::PM_TabCloseIndicatorHeight;
    t["PM_CustomBase"] = QStyle::PM_CustomBase;
    t["PM_DefaultTopLevelMargin"] = QStyle::PM_DefaultTopLevelMargin;
    t["PM_DefaultChildMargin"] = QStyle::PM_DefaultChildMargin;
    t["PM_DefaultLayoutSpacing"] = QStyle::PM_DefaultLayoutSpacing;
    t["PM_ScrollView_ScrollBarSpacing"] = QStyle::PM_ScrollView_ScrollBarSpacing;
    t["PM_ScrollView_ScrollBarOverlap"] = QStyle::PM_ScrollView_ScrollBarOverlap;
    t["PM_SubMenuOverlap"] = QStyle::PM_SubMenuOverlap;

    // enum QStyle::PrimitiveElement
    t["PE_FrameStatusBar"] = QStyle::PE_FrameStatusBar;
    t["PE_PanelButtonCommand"] = QStyle::PE_PanelButtonCommand;
    t["PE_FrameDefaultButton"] = QStyle::PE_FrameDefaultButton;
    t["PE_PanelButtonBevel"] = QStyle::PE_PanelButtonBevel;
    t["PE_PanelButtonTool"] = QStyle::PE_PanelButtonTool;
    t["PE_PanelLineEdit"] = QStyle::PE_PanelLineEdit;
    t["PE_IndicatorButtonDropDown"] = QStyle::PE_IndicatorButtonDropDown;
    t["PE_FrameFocusRect"] = QStyle::PE_FrameFocusRect;
    t["PE_IndicatorArrowUp"] = QStyle::PE_IndicatorArrowUp;
    t["PE_IndicatorArrowDown"] = QStyle::PE_IndicatorArrowDown;
    t["PE_IndicatorArrowRight"] = QStyle::PE_IndicatorArrowRight;
    t["PE_IndicatorArrowLeft"] = QStyle::PE_IndicatorArrowLeft;
    t["PE_IndicatorSpinUp"] = QStyle::PE_IndicatorSpinUp;
    t["PE_IndicatorSpinDown"] = QStyle::PE_IndicatorSpinDown;
    t["PE_IndicatorSpinPlus"] = QStyle::PE_IndicatorSpinPlus;
    t["PE_IndicatorSpinMinus"] = QStyle::PE_IndicatorSpinMinus;
    t["PE_IndicatorItemViewItemCheck"] = QStyle::PE_IndicatorItemViewItemCheck;
    t["PE_IndicatorCheckBox"] = QStyle::PE_IndicatorCheckBox;
    t["PE_IndicatorRadioButton"] = QStyle::PE_IndicatorRadioButton;
    t["PE_IndicatorDockWidgetResizeHandle"] = QStyle::PE_IndicatorDockWidgetResizeHandle;
    t["PE_Frame"] = QStyle::PE_Frame;
    t["PE_FrameMenu"] = QStyle::PE_FrameMenu;
    t["PE_PanelMenuBar"] = QStyle::PE_PanelMenuBar;
    t["PE_PanelScrollAreaCorner"] = QStyle::PE_PanelScrollAreaCorner;
    t["PE_FrameDockWidget"] = QStyle::PE_FrameDockWidget;
    t["PE_FrameTabWidget"] = QStyle::PE_FrameTabWidget;
    t["PE_FrameLineEdit"] = QStyle::PE_FrameLineEdit;
    t["PE_FrameGroupBox"] = QStyle::PE_FrameGroupBox;
    t["PE_FrameButtonBevel"] = QStyle::PE_FrameButtonBevel;
    t["PE_FrameButtonTool"] = QStyle::PE_FrameButtonTool;
    t["PE_IndicatorHeaderArrow"] = QStyle::PE_IndicatorHeaderArrow;
    t["PE_FrameStatusBarItem"] = QStyle::PE_FrameStatusBarItem;
    t["PE_FrameWindow"] = QStyle::PE_FrameWindow;
    t["PE_IndicatorMenuCheckMark"] = QStyle::PE_IndicatorMenuCheckMark;
    t["PE_IndicatorProgressChunk"] = QStyle::PE_IndicatorProgressChunk;
    t["PE_IndicatorBranch"] = QStyle::PE_IndicatorBranch;
    t["PE_IndicatorToolBarHandle"] = QStyle::PE_IndicatorToolBarHandle;
    t["PE_IndicatorToolBarSeparator"] = QStyle::PE_IndicatorToolBarSeparator;
    t["PE_PanelToolBar"] = QStyle::PE_PanelToolBar;
    t["PE_PanelTipLabel"] = QStyle::PE_PanelTipLabel;
    t["PE_FrameTabBarBase"] = QStyle::PE_FrameTabBarBase;
    t["PE_IndicatorTabTear"] = QStyle::PE_IndicatorTabTear;
    t["PE_IndicatorColumnViewArrow"] = QStyle::PE_IndicatorColumnViewArrow;
    t["PE_Widget"] = QStyle::PE_Widget;
    t["PE_CustomBase"] = QStyle::PE_CustomBase;
    t["PE_IndicatorItemViewItemDrop"] = QStyle::PE_IndicatorItemViewItemDrop;
    t["PE_PanelItemViewItem"] = QStyle::PE_PanelItemViewItem;
    t["PE_PanelItemViewRow"] = QStyle::PE_PanelItemViewRow;
    t["PE_PanelStatusBar"] = QStyle::PE_PanelStatusBar;
    t["PE_IndicatorTabClose"] = QStyle::PE_IndicatorTabClose;
    t["PE_PanelMenu"] = QStyle::PE_PanelMenu;

    // enum QStyle::RequestSoftwareInputPanel
    t["RSIP_OnMouseClickAndAlreadyFocused"] = QStyle::RSIP_OnMouseClickAndAlreadyFocused;
    t["RSIP_OnMouseClick"] = QStyle::RSIP_OnMouseClick;

    // enum QStyle::StandardPixmap
    t["SP_TitleBarMinButton"] = QStyle::SP_TitleBarMinButton;
    t["SP_TitleBarMenuButton"] = QStyle::SP_TitleBarMenuButton;
    t["SP_TitleBarMaxButton"] = QStyle::SP_TitleBarMaxButton;
    t["SP_TitleBarCloseButton"] = QStyle::SP_TitleBarCloseButton;
    t["SP_TitleBarNormalButton"] = QStyle::SP_TitleBarNormalButton;
    t["SP_TitleBarShadeButton"] = QStyle::SP_TitleBarShadeButton;
    t["SP_TitleBarUnshadeButton"] = QStyle::SP_TitleBarUnshadeButton;
    t["SP_TitleBarContextHelpButton"] = QStyle::SP_TitleBarContextHelpButton;
    t["SP_MessageBoxInformation"] = QStyle::SP_MessageBoxInformation;
    t["SP_MessageBoxWarning"] = QStyle::SP_MessageBoxWarning;
    t["SP_MessageBoxCritical"] = QStyle::SP_MessageBoxCritical;
    t["SP_MessageBoxQuestion"] = QStyle::SP_MessageBoxQuestion;
    t["SP_DesktopIcon"] = QStyle::SP_DesktopIcon;
    t["SP_TrashIcon"] = QStyle::SP_TrashIcon;
    t["SP_ComputerIcon"] = QStyle::SP_ComputerIcon;
    t["SP_DriveFDIcon"] = QStyle::SP_DriveFDIcon;
    t["SP_DriveHDIcon"] = QStyle::SP_DriveHDIcon;
    t["SP_DriveCDIcon"] = QStyle::SP_DriveCDIcon;
    t["SP_DriveDVDIcon"] = QStyle::SP_DriveDVDIcon;
    t["SP_DriveNetIcon"] = QStyle::SP_DriveNetIcon;
    t["SP_DirHomeIcon"] = QStyle::SP_DirHomeIcon;
    t["SP_DirOpenIcon"] = QStyle::SP_DirOpenIcon;
    t["SP_DirClosedIcon"] = QStyle::SP_DirClosedIcon;
    t["SP_DirIcon"] = QStyle::SP_DirIcon;
    t["SP_DirLinkIcon"] = QStyle::SP_DirLinkIcon;
    t["SP_DirLinkOpenIcon"] = QStyle::SP_DirLinkOpenIcon;
    t["SP_FileIcon"] = QStyle::SP_FileIcon;
    t["SP_FileLinkIcon"] = QStyle::SP_FileLinkIcon;
    t["SP_FileDialogStart"] = QStyle::SP_FileDialogStart;
    t["SP_FileDialogEnd"] = QStyle::SP_FileDialogEnd;
    t["SP_FileDialogToParent"] = QStyle::SP_FileDialogToParent;
    t["SP_FileDialogNewFolder"] = QStyle::SP_FileDialogNewFolder;
    t["SP_FileDialogDetailedView"] = QStyle::SP_FileDialogDetailedView;
    t["SP_FileDialogInfoView"] = QStyle::SP_FileDialogInfoView;
    t["SP_FileDialogContentsView"] = QStyle::SP_FileDialogContentsView;
    t["SP_FileDialogListView"] = QStyle::SP_FileDialogListView;
    t["SP_FileDialogBack"] = QStyle::SP_FileDialogBack;
    t["SP_DockWidgetCloseButton"] = QStyle::SP_DockWidgetCloseButton;
    t["SP_ToolBarHorizontalExtensionButton"] = QStyle::SP_ToolBarHorizontalExtensionButton;
    t["SP_ToolBarVerticalExtensionButton"] = QStyle::SP_ToolBarVerticalExtensionButton;
    t["SP_DialogOkButton"] = QStyle::SP_DialogOkButton;
    t["SP_DialogCancelButton"] = QStyle::SP_DialogCancelButton;
    t["SP_DialogHelpButton"] = QStyle::SP_DialogHelpButton;
    t["SP_DialogOpenButton"] = QStyle::SP_DialogOpenButton;
    t["SP_DialogSaveButton"] = QStyle::SP_DialogSaveButton;
    t["SP_DialogCloseButton"] = QStyle::SP_DialogCloseButton;
    t["SP_DialogApplyButton"] = QStyle::SP_DialogApplyButton;
    t["SP_DialogResetButton"] = QStyle::SP_DialogResetButton;
    t["SP_DialogDiscardButton"] = QStyle::SP_DialogDiscardButton;
    t["SP_DialogYesButton"] = QStyle::SP_DialogYesButton;
    t["SP_DialogNoButton"] = QStyle::SP_DialogNoButton;
    t["SP_ArrowUp"] = QStyle::SP_ArrowUp;
    t["SP_ArrowDown"] = QStyle::SP_ArrowDown;
    t["SP_ArrowLeft"] = QStyle::SP_ArrowLeft;
    t["SP_ArrowRight"] = QStyle::SP_ArrowRight;
    t["SP_ArrowBack"] = QStyle::SP_ArrowBack;
    t["SP_ArrowForward"] = QStyle::SP_ArrowForward;
    t["SP_CommandLink"] = QStyle::SP_CommandLink;
    t["SP_VistaShield"] = QStyle::SP_VistaShield;
    t["SP_BrowserReload"] = QStyle::SP_BrowserReload;
    t["SP_BrowserStop"] = QStyle::SP_BrowserStop;
    t["SP_MediaPlay"] = QStyle::SP_MediaPlay;
    t["SP_MediaStop"] = QStyle::SP_MediaStop;
    t["SP_MediaPause"] = QStyle::SP_MediaPause;
    t["SP_MediaSkipForward"] = QStyle::SP_MediaSkipForward;
    t["SP_MediaSkipBackward"] = QStyle::SP_MediaSkipBackward;
    t["SP_MediaSeekForward"] = QStyle::SP_MediaSeekForward;
    t["SP_MediaSeekBackward"] = QStyle::SP_MediaSeekBackward;
    t["SP_MediaVolume"] = QStyle::SP_MediaVolume;
    t["SP_MediaVolumeMuted"] = QStyle::SP_MediaVolumeMuted;
    t["SP_LineEditClearButton"] = QStyle::SP_LineEditClearButton;
    t["SP_CustomBase"] = QStyle::SP_CustomBase;

    // enum QStyle::StateFlag
    t["State_None"] = QStyle::State_None;
    t["State_Active"] = QStyle::State_Active;
    t["State_AutoRaise"] = QStyle::State_AutoRaise;
    t["State_Children"] = QStyle::State_Children;
    t["State_DownArrow"] = QStyle::State_DownArrow;
    t["State_Editing"] = QStyle::State_Editing;
    t["State_Enabled"] = QStyle::State_Enabled;
    // t["State_HasEditFocus"] = QStyle::State_HasEditFocus;
    t["State_HasFocus"] = QStyle::State_HasFocus;
    t["State_Horizontal"] = QStyle::State_Horizontal;
    t["State_KeyboardFocusChange"] = QStyle::State_KeyboardFocusChange;
    t["State_MouseOver"] = QStyle::State_MouseOver;
    t["State_NoChange"] = QStyle::State_NoChange;
    t["State_Off"] = QStyle::State_Off;
    t["State_On"] = QStyle::State_On;
    t["State_Raised"] = QStyle::State_Raised;
    t["State_ReadOnly"] = QStyle::State_ReadOnly;
    t["State_Selected"] = QStyle::State_Selected;
    t["State_Item"] = QStyle::State_Item;
    t["State_Open"] = QStyle::State_Open;
    t["State_Sibling"] = QStyle::State_Sibling;
    t["State_Sunken"] = QStyle::State_Sunken;
    t["State_UpArrow"] = QStyle::State_UpArrow;
    t["State_Mini"] = QStyle::State_Mini;
    t["State_Small"] = QStyle::State_Small;

    // enum QStyle::StyleHint
    t["SH_EtchDisabledText"] = QStyle::SH_EtchDisabledText;
    t["SH_DitherDisabledText"] = QStyle::SH_DitherDisabledText;
    t["SH_ScrollBar_ContextMenu"] = QStyle::SH_ScrollBar_ContextMenu;
    t["SH_ScrollBar_MiddleClickAbsolutePosition"] = QStyle::SH_ScrollBar_MiddleClickAbsolutePosition;
    t["SH_ScrollBar_LeftClickAbsolutePosition"] = QStyle::SH_ScrollBar_LeftClickAbsolutePosition;
    t["SH_ScrollBar_ScrollWhenPointerLeavesControl"] = QStyle::SH_ScrollBar_ScrollWhenPointerLeavesControl;
    t["SH_ScrollBar_RollBetweenButtons"] = QStyle::SH_ScrollBar_RollBetweenButtons;
    t["SH_TabBar_Alignment"] = QStyle::SH_TabBar_Alignment;
    t["SH_Header_ArrowAlignment"] = QStyle::SH_Header_ArrowAlignment;
    t["SH_Slider_SnapToValue"] = QStyle::SH_Slider_SnapToValue;
    t["SH_Slider_SloppyKeyEvents"] = QStyle::SH_Slider_SloppyKeyEvents;
    t["SH_ProgressDialog_CenterCancelButton"] = QStyle::SH_ProgressDialog_CenterCancelButton;
    t["SH_ProgressDialog_TextLabelAlignment"] = QStyle::SH_ProgressDialog_TextLabelAlignment;
    t["SH_PrintDialog_RightAlignButtons"] = QStyle::SH_PrintDialog_RightAlignButtons;
    t["SH_MainWindow_SpaceBelowMenuBar"] = QStyle::SH_MainWindow_SpaceBelowMenuBar;
    t["SH_FontDialog_SelectAssociatedText"] = QStyle::SH_FontDialog_SelectAssociatedText;
    t["SH_Menu_KeyboardSearch"] = QStyle::SH_Menu_KeyboardSearch;
    t["SH_Menu_AllowActiveAndDisabled"] = QStyle::SH_Menu_AllowActiveAndDisabled;
    t["SH_Menu_SpaceActivatesItem"] = QStyle::SH_Menu_SpaceActivatesItem;
    t["SH_Menu_SubMenuPopupDelay"] = QStyle::SH_Menu_SubMenuPopupDelay;
    t["SH_Menu_Scrollable"] = QStyle::SH_Menu_Scrollable;
    t["SH_Menu_SloppySubMenus"] = QStyle::SH_Menu_SloppySubMenus;
    t["SH_ScrollView_FrameOnlyAroundContents"] = QStyle::SH_ScrollView_FrameOnlyAroundContents;
    t["SH_MenuBar_AltKeyNavigation"] = QStyle::SH_MenuBar_AltKeyNavigation;
    t["SH_ComboBox_ListMouseTracking"] = QStyle::SH_ComboBox_ListMouseTracking;
    t["SH_Menu_MouseTracking"] = QStyle::SH_Menu_MouseTracking;
    t["SH_MenuBar_MouseTracking"] = QStyle::SH_MenuBar_MouseTracking;
    t["SH_Menu_FillScreenWithScroll"] = QStyle::SH_Menu_FillScreenWithScroll;
    t["SH_Menu_SelectionWrap"] = QStyle::SH_Menu_SelectionWrap;
    t["SH_ItemView_ChangeHighlightOnFocus"] = QStyle::SH_ItemView_ChangeHighlightOnFocus;
    t["SH_Widget_ShareActivation"] = QStyle::SH_Widget_ShareActivation;
    t["SH_TabBar_SelectMouseType"] = QStyle::SH_TabBar_SelectMouseType;
    t["SH_ListViewExpand_SelectMouseType"] = QStyle::SH_ListViewExpand_SelectMouseType;
    t["SH_TabBar_PreferNoArrows"] = QStyle::SH_TabBar_PreferNoArrows;
    t["SH_ComboBox_Popup"] = QStyle::SH_ComboBox_Popup;
    t["SH_Workspace_FillSpaceOnMaximize"] = QStyle::SH_Workspace_FillSpaceOnMaximize;
    t["SH_TitleBar_NoBorder"] = QStyle::SH_TitleBar_NoBorder;
    t["SH_ScrollBar_StopMouseOverSlider"] = QStyle::SH_ScrollBar_StopMouseOverSlider;
    t["SH_Slider_StopMouseOverSlider"] = QStyle::SH_Slider_StopMouseOverSlider;
    t["SH_BlinkCursorWhenTextSelected"] = QStyle::SH_BlinkCursorWhenTextSelected;
    t["SH_RichText_FullWidthSelection"] = QStyle::SH_RichText_FullWidthSelection;
    t["SH_GroupBox_TextLabelVerticalAlignment"] = QStyle::SH_GroupBox_TextLabelVerticalAlignment;
    t["SH_GroupBox_TextLabelColor"] = QStyle::SH_GroupBox_TextLabelColor;
    t["SH_DialogButtons_DefaultButton"] = QStyle::SH_DialogButtons_DefaultButton;
    t["SH_ToolBox_SelectedPageTitleBold"] = QStyle::SH_ToolBox_SelectedPageTitleBold;
    t["SH_LineEdit_PasswordCharacter"] = QStyle::SH_LineEdit_PasswordCharacter;
    t["SH_Table_GridLineColor"] = QStyle::SH_Table_GridLineColor;
    t["SH_UnderlineShortcut"] = QStyle::SH_UnderlineShortcut;
    t["SH_SpellCheckUnderlineStyle"] = QStyle::SH_SpellCheckUnderlineStyle;
    t["SH_SpinBox_AnimateButton"] = QStyle::SH_SpinBox_AnimateButton;
    t["SH_SpinBox_KeyPressAutoRepeatRate"] = QStyle::SH_SpinBox_KeyPressAutoRepeatRate;
    t["SH_SpinBox_ClickAutoRepeatRate"] = QStyle::SH_SpinBox_ClickAutoRepeatRate;
    t["SH_SpinBox_ClickAutoRepeatThreshold"] = QStyle::SH_SpinBox_ClickAutoRepeatThreshold;
    t["SH_ToolTipLabel_Opacity"] = QStyle::SH_ToolTipLabel_Opacity;
    t["SH_DrawMenuBarSeparator"] = QStyle::SH_DrawMenuBarSeparator;
    t["SH_TitleBar_ModifyNotification"] = QStyle::SH_TitleBar_ModifyNotification;
    t["SH_Button_FocusPolicy"] = QStyle::SH_Button_FocusPolicy;
    t["SH_CustomBase"] = QStyle::SH_CustomBase;
    t["SH_MessageBox_UseBorderForButtonSpacing"] = QStyle::SH_MessageBox_UseBorderForButtonSpacing;
    t["SH_MessageBox_CenterButtons"] = QStyle::SH_MessageBox_CenterButtons;
    t["SH_MessageBox_TextInteractionFlags"] = QStyle::SH_MessageBox_TextInteractionFlags;
    t["SH_TitleBar_AutoRaise"] = QStyle::SH_TitleBar_AutoRaise;
    t["SH_ToolButton_PopupDelay"] = QStyle::SH_ToolButton_PopupDelay;
    t["SH_FocusFrame_Mask"] = QStyle::SH_FocusFrame_Mask;
    t["SH_RubberBand_Mask"] = QStyle::SH_RubberBand_Mask;
    t["SH_WindowFrame_Mask"] = QStyle::SH_WindowFrame_Mask;
    t["SH_SpinControls_DisableOnBounds"] = QStyle::SH_SpinControls_DisableOnBounds;
    t["SH_Dial_BackgroundRole"] = QStyle::SH_Dial_BackgroundRole;
    t["SH_ComboBox_LayoutDirection"] = QStyle::SH_ComboBox_LayoutDirection;
    t["SH_ItemView_EllipsisLocation"] = QStyle::SH_ItemView_EllipsisLocation;
    t["SH_ItemView_ShowDecorationSelected"] = QStyle::SH_ItemView_ShowDecorationSelected;
    t["SH_ItemView_ActivateItemOnSingleClick"] = QStyle::SH_ItemView_ActivateItemOnSingleClick;
    t["SH_Slider_AbsoluteSetButtons"] = QStyle::SH_Slider_AbsoluteSetButtons;
    t["SH_Slider_PageSetButtons"] = QStyle::SH_Slider_PageSetButtons;
    t["SH_TabBar_ElideMode"] = QStyle::SH_TabBar_ElideMode;
    t["SH_DialogButtonLayout"] = QStyle::SH_DialogButtonLayout;
    t["SH_WizardStyle"] = QStyle::SH_WizardStyle;
    t["SH_FormLayoutWrapPolicy"] = QStyle::SH_FormLayoutWrapPolicy;
    t["SH_FormLayoutFieldGrowthPolicy"] = QStyle::SH_FormLayoutFieldGrowthPolicy;
    t["SH_FormLayoutFormAlignment"] = QStyle::SH_FormLayoutFormAlignment;
    t["SH_FormLayoutLabelAlignment"] = QStyle::SH_FormLayoutLabelAlignment;
    t["SH_ItemView_ArrowKeysNavigateIntoChildren"] = QStyle::SH_ItemView_ArrowKeysNavigateIntoChildren;
    t["SH_ComboBox_PopupFrameStyle"] = QStyle::SH_ComboBox_PopupFrameStyle;
    t["SH_DialogButtonBox_ButtonsHaveIcons"] = QStyle::SH_DialogButtonBox_ButtonsHaveIcons;
    t["SH_ItemView_MovementWithoutUpdatingSelection"] = QStyle::SH_ItemView_MovementWithoutUpdatingSelection;
    t["SH_ToolTip_Mask"] = QStyle::SH_ToolTip_Mask;
    t["SH_FocusFrame_AboveWidget"] = QStyle::SH_FocusFrame_AboveWidget;
    t["SH_TextControl_FocusIndicatorTextCharFormat"] = QStyle::SH_TextControl_FocusIndicatorTextCharFormat;
    t["SH_Menu_FlashTriggeredItem"] = QStyle::SH_Menu_FlashTriggeredItem;
    t["SH_Menu_FadeOutOnHide"] = QStyle::SH_Menu_FadeOutOnHide;
    t["SH_TabWidget_DefaultTabPosition"] = QStyle::SH_TabWidget_DefaultTabPosition;
    t["SH_ToolBar_Movable"] = QStyle::SH_ToolBar_Movable;
    t["SH_ItemView_PaintAlternatingRowColorsForEmptyArea"] = QStyle::SH_ItemView_PaintAlternatingRowColorsForEmptyArea;
    t["SH_Menu_Mask"] = QStyle::SH_Menu_Mask;
    t["SH_ItemView_DrawDelegateFrame"] = QStyle::SH_ItemView_DrawDelegateFrame;
    t["SH_TabBar_CloseButtonPosition"] = QStyle::SH_TabBar_CloseButtonPosition;
    t["SH_DockWidget_ButtonsHaveFrame"] = QStyle::SH_DockWidget_ButtonsHaveFrame;
    t["SH_ToolButtonStyle"] = QStyle::SH_ToolButtonStyle;
    t["SH_RequestSoftwareInputPanel"] = QStyle::SH_RequestSoftwareInputPanel;
    t["SH_ScrollBar_Transient"] = QStyle::SH_ScrollBar_Transient;
    t["SH_Menu_SupportsSections"] = QStyle::SH_Menu_SupportsSections;
    t["SH_ToolTip_WakeUpDelay"] = QStyle::SH_ToolTip_WakeUpDelay;
    t["SH_ToolTip_FallAsleepDelay"] = QStyle::SH_ToolTip_FallAsleepDelay;
    t["SH_Widget_Animate"] = QStyle::SH_Widget_Animate;
    t["SH_Splitter_OpaqueResize"] = QStyle::SH_Splitter_OpaqueResize;

    // enum QStyle::SubControl
    t["SC_None"] = QStyle::SC_None;
    t["SC_ScrollBarAddLine"] = QStyle::SC_ScrollBarAddLine;
    t["SC_ScrollBarSubLine"] = QStyle::SC_ScrollBarSubLine;
    t["SC_ScrollBarAddPage"] = QStyle::SC_ScrollBarAddPage;
    t["SC_ScrollBarSubPage"] = QStyle::SC_ScrollBarSubPage;
    t["SC_ScrollBarFirst"] = QStyle::SC_ScrollBarFirst;
    t["SC_ScrollBarLast"] = QStyle::SC_ScrollBarLast;
    t["SC_ScrollBarSlider"] = QStyle::SC_ScrollBarSlider;
    t["SC_ScrollBarGroove"] = QStyle::SC_ScrollBarGroove;
    t["SC_SpinBoxUp"] = QStyle::SC_SpinBoxUp;
    t["SC_SpinBoxDown"] = QStyle::SC_SpinBoxDown;
    t["SC_SpinBoxFrame"] = QStyle::SC_SpinBoxFrame;
    t["SC_SpinBoxEditField"] = QStyle::SC_SpinBoxEditField;
    t["SC_ComboBoxEditField"] = QStyle::SC_ComboBoxEditField;
    t["SC_ComboBoxArrow"] = QStyle::SC_ComboBoxArrow;
    t["SC_ComboBoxFrame"] = QStyle::SC_ComboBoxFrame;
    t["SC_ComboBoxListBoxPopup"] = QStyle::SC_ComboBoxListBoxPopup;
    t["SC_SliderGroove"] = QStyle::SC_SliderGroove;
    t["SC_SliderHandle"] = QStyle::SC_SliderHandle;
    t["SC_SliderTickmarks"] = QStyle::SC_SliderTickmarks;
    t["SC_ToolButton"] = QStyle::SC_ToolButton;
    t["SC_ToolButtonMenu"] = QStyle::SC_ToolButtonMenu;
    t["SC_TitleBarSysMenu"] = QStyle::SC_TitleBarSysMenu;
    t["SC_TitleBarMinButton"] = QStyle::SC_TitleBarMinButton;
    t["SC_TitleBarMaxButton"] = QStyle::SC_TitleBarMaxButton;
    t["SC_TitleBarCloseButton"] = QStyle::SC_TitleBarCloseButton;
    t["SC_TitleBarLabel"] = QStyle::SC_TitleBarLabel;
    t["SC_TitleBarNormalButton"] = QStyle::SC_TitleBarNormalButton;
    t["SC_TitleBarShadeButton"] = QStyle::SC_TitleBarShadeButton;
    t["SC_TitleBarUnshadeButton"] = QStyle::SC_TitleBarUnshadeButton;
    t["SC_TitleBarContextHelpButton"] = QStyle::SC_TitleBarContextHelpButton;
    t["SC_DialHandle"] = QStyle::SC_DialHandle;
    t["SC_DialGroove"] = QStyle::SC_DialGroove;
    t["SC_DialTickmarks"] = QStyle::SC_DialTickmarks;
    t["SC_GroupBoxFrame"] = QStyle::SC_GroupBoxFrame;
    t["SC_GroupBoxLabel"] = QStyle::SC_GroupBoxLabel;
    t["SC_GroupBoxCheckBox"] = QStyle::SC_GroupBoxCheckBox;
    t["SC_GroupBoxContents"] = QStyle::SC_GroupBoxContents;
    t["SC_MdiNormalButton"] = QStyle::SC_MdiNormalButton;
    t["SC_MdiMinButton"] = QStyle::SC_MdiMinButton;
    t["SC_MdiCloseButton"] = QStyle::SC_MdiCloseButton;
    t["SC_All"] = QStyle::SC_All;

    // enum QStyle::SubElement
    t["SE_PushButtonContents"] = QStyle::SE_PushButtonContents;
    t["SE_PushButtonFocusRect"] = QStyle::SE_PushButtonFocusRect;
    t["SE_PushButtonLayoutItem"] = QStyle::SE_PushButtonLayoutItem;
    t["SE_CheckBoxIndicator"] = QStyle::SE_CheckBoxIndicator;
    t["SE_CheckBoxContents"] = QStyle::SE_CheckBoxContents;
    t["SE_CheckBoxFocusRect"] = QStyle::SE_CheckBoxFocusRect;
    t["SE_CheckBoxClickRect"] = QStyle::SE_CheckBoxClickRect;
    t["SE_CheckBoxLayoutItem"] = QStyle::SE_CheckBoxLayoutItem;
    t["SE_DateTimeEditLayoutItem"] = QStyle::SE_DateTimeEditLayoutItem;
    t["SE_RadioButtonIndicator"] = QStyle::SE_RadioButtonIndicator;
    t["SE_RadioButtonContents"] = QStyle::SE_RadioButtonContents;
    t["SE_RadioButtonFocusRect"] = QStyle::SE_RadioButtonFocusRect;
    t["SE_RadioButtonClickRect"] = QStyle::SE_RadioButtonClickRect;
    t["SE_RadioButtonLayoutItem"] = QStyle::SE_RadioButtonLayoutItem;
    t["SE_ComboBoxFocusRect"] = QStyle::SE_ComboBoxFocusRect;
    t["SE_SliderFocusRect"] = QStyle::SE_SliderFocusRect;
    t["SE_SliderLayoutItem"] = QStyle::SE_SliderLayoutItem;
    t["SE_SpinBoxLayoutItem"] = QStyle::SE_SpinBoxLayoutItem;
    t["SE_ProgressBarGroove"] = QStyle::SE_ProgressBarGroove;
    t["SE_ProgressBarContents"] = QStyle::SE_ProgressBarContents;
    t["SE_ProgressBarLabel"] = QStyle::SE_ProgressBarLabel;
    t["SE_ProgressBarLayoutItem"] = QStyle::SE_ProgressBarLayoutItem;
    t["SE_FrameContents"] = QStyle::SE_FrameContents;
    t["SE_ShapedFrameContents"] = QStyle::SE_ShapedFrameContents;
    t["SE_FrameLayoutItem"] = QStyle::SE_FrameLayoutItem;
    t["SE_HeaderArrow"] = QStyle::SE_HeaderArrow;
    t["SE_HeaderLabel"] = QStyle::SE_HeaderLabel;
    t["SE_LabelLayoutItem"] = QStyle::SE_LabelLayoutItem;
    t["SE_LineEditContents"] = QStyle::SE_LineEditContents;
    t["SE_TabWidgetLeftCorner"] = QStyle::SE_TabWidgetLeftCorner;
    t["SE_TabWidgetRightCorner"] = QStyle::SE_TabWidgetRightCorner;
    t["SE_TabWidgetTabBar"] = QStyle::SE_TabWidgetTabBar;
    t["SE_TabWidgetTabContents"] = QStyle::SE_TabWidgetTabContents;
    t["SE_TabWidgetTabPane"] = QStyle::SE_TabWidgetTabPane;
    t["SE_TabWidgetLayoutItem"] = QStyle::SE_TabWidgetLayoutItem;
    t["SE_ToolBoxTabContents"] = QStyle::SE_ToolBoxTabContents;
    t["SE_ToolButtonLayoutItem"] = QStyle::SE_ToolButtonLayoutItem;
    t["SE_ItemViewItemCheckIndicator"] = QStyle::SE_ItemViewItemCheckIndicator;
    t["SE_TabBarTearIndicator"] = QStyle::SE_TabBarTearIndicator;
    t["SE_TreeViewDisclosureItem"] = QStyle::SE_TreeViewDisclosureItem;
    t["SE_DialogButtonBoxLayoutItem"] = QStyle::SE_DialogButtonBoxLayoutItem;
    t["SE_GroupBoxLayoutItem"] = QStyle::SE_GroupBoxLayoutItem;
    t["SE_CustomBase"] = QStyle::SE_CustomBase;
    t["SE_DockWidgetFloatButton"] = QStyle::SE_DockWidgetFloatButton;
    t["SE_DockWidgetTitleBarText"] = QStyle::SE_DockWidgetTitleBarText;
    t["SE_DockWidgetCloseButton"] = QStyle::SE_DockWidgetCloseButton;
    t["SE_DockWidgetIcon"] = QStyle::SE_DockWidgetIcon;
    t["SE_ComboBoxLayoutItem"] = QStyle::SE_ComboBoxLayoutItem;
    t["SE_ItemViewItemDecoration"] = QStyle::SE_ItemViewItemDecoration;
    t["SE_ItemViewItemText"] = QStyle::SE_ItemViewItemText;
    t["SE_ItemViewItemFocusRect"] = QStyle::SE_ItemViewItemFocusRect;
    t["SE_TabBarTabLeftButton"] = QStyle::SE_TabBarTabLeftButton;
    t["SE_TabBarTabRightButton"] = QStyle::SE_TabBarTabRightButton;
    t["SE_TabBarTabText"] = QStyle::SE_TabBarTabText;
    t["SE_ToolBarHandle"] = QStyle::SE_ToolBarHandle;

    return 0;
}
