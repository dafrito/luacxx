#include "Qt.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QString.hpp"

#include <Qt>

void lua::qt_constants_2(lua_State* const state)
{
    lua::thread env(state);
    auto t = env["Qt"];

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
}
