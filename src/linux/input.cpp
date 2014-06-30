#include "input.hpp"

#include "../luacxx/convert/callable.hpp"
#include "../luacxx/convert/numeric.hpp"
#include "../luacxx/thread.hpp"

#include <linux/input.h>

int luaopen_linux_input(lua_State* const state)
{
    lua::thread env(state);

    env["EV_VERSION"] = EV_VERSION;

    env["EVIOCGVERSION"] = EVIOCGVERSION;
    env["EVIOCGID"] = EVIOCGID;
    env["EVIOCGREP"] = EVIOCGREP;
    env["EVIOCSREP"] = EVIOCSREP;

    env["EVIOCGKEYCODE"] = EVIOCGKEYCODE;
    env["EVIOCGKEYCODE_V2"] = EVIOCGKEYCODE_V2;
    env["EVIOCSKEYCODE"] = EVIOCSKEYCODE;
    env["EVIOCSKEYCODE_V2"] = EVIOCSKEYCODE_V2;

    env["EVIOCSFF"] = EVIOCSFF;
    env["EVIOCRMFF"] = EVIOCRMFF;
    env["EVIOCGEFFECTS"] = EVIOCGEFFECTS;

    env["EVIOCGRAB"] = EVIOCGRAB;
    env["EVIOCREVOKE"] = EVIOCREVOKE;

    env["EVIOCSCLOCKID"] = EVIOCSCLOCKID;

    /*
     * Device properties and quirks
     */

    env["INPUT_PROP_POINTER"] = INPUT_PROP_POINTER;
    env["INPUT_PROP_DIRECT"] = INPUT_PROP_DIRECT;
    env["INPUT_PROP_BUTTONPAD"] = INPUT_PROP_BUTTONPAD;
    env["INPUT_PROP_SEMI_MT"] = INPUT_PROP_SEMI_MT;

    env["INPUT_PROP_MAX"] = INPUT_PROP_MAX;
    env["INPUT_PROP_CNT"] = INPUT_PROP_CNT;

    /*
     * Event types
     */

    env["EV_SYN"] = EV_SYN;
    env["EV_KEY"] = EV_KEY;
    env["EV_REL"] = EV_REL;
    env["EV_ABS"] = EV_ABS;
    env["EV_MSC"] = EV_MSC;
    env["EV_SW"] = EV_SW;
    env["EV_LED"] = EV_LED;
    env["EV_SND"] = EV_SND;
    env["EV_REP"] = EV_REP;
    env["EV_FF"] = EV_FF;
    env["EV_PWR"] = EV_PWR;
    env["EV_FF_STATUS"] = EV_FF_STATUS;
    env["EV_MAX"] = EV_MAX;
    env["EV_CNT"] = EV_CNT;

    /*
     * Synchronization events.
     */

    env["SYN_REPORT"] = SYN_REPORT;
    env["SYN_CONFIG"] = SYN_CONFIG;
    env["SYN_MT_REPORT"] = SYN_MT_REPORT;
    env["SYN_DROPPED"] = SYN_DROPPED;
    env["SYN_MAX"] = SYN_MAX;
    env["SYN_CNT"] = SYN_CNT;

    /*
     * Keys and buttons
     *
     * Most of the keys/buttons are modeled after USB HUT 1.12
     * (see http://www.usb.org/developers/hidpage).
     * Abbreviations in the comments:
     * AC - Application Control
     * AL - Application Launch Button
     * SC - System Control
     */

    env["KEY_RESERVED"] = KEY_RESERVED;
    env["KEY_ESC"] = KEY_ESC;
    env["KEY_1"] = KEY_1;
    env["KEY_2"] = KEY_2;
    env["KEY_3"] = KEY_3;
    env["KEY_4"] = KEY_4;
    env["KEY_5"] = KEY_5;
    env["KEY_6"] = KEY_6;
    env["KEY_7"] = KEY_7;
    env["KEY_8"] = KEY_8;
    env["KEY_9"] = KEY_9;
    env["KEY_0"] = KEY_0;
    env["KEY_MINUS"] = KEY_MINUS;
    env["KEY_EQUAL"] = KEY_EQUAL;
    env["KEY_BACKSPACE"] = KEY_BACKSPACE;
    env["KEY_TAB"] = KEY_TAB;
    env["KEY_Q"] = KEY_Q;
    env["KEY_W"] = KEY_W;
    env["KEY_E"] = KEY_E;
    env["KEY_R"] = KEY_R;
    env["KEY_T"] = KEY_T;
    env["KEY_Y"] = KEY_Y;
    env["KEY_U"] = KEY_U;
    env["KEY_I"] = KEY_I;
    env["KEY_O"] = KEY_O;
    env["KEY_P"] = KEY_P;
    env["KEY_LEFTBRACE"] = KEY_LEFTBRACE;
    env["KEY_RIGHTBRACE"] = KEY_RIGHTBRACE;
    env["KEY_ENTER"] = KEY_ENTER;
    env["KEY_LEFTCTRL"] = KEY_LEFTCTRL;
    env["KEY_A"] = KEY_A;
    env["KEY_S"] = KEY_S;
    env["KEY_D"] = KEY_D;
    env["KEY_F"] = KEY_F;
    env["KEY_G"] = KEY_G;
    env["KEY_H"] = KEY_H;
    env["KEY_J"] = KEY_J;
    env["KEY_K"] = KEY_K;
    env["KEY_L"] = KEY_L;
    env["KEY_SEMICOLON"] = KEY_SEMICOLON;
    env["KEY_APOSTROPHE"] = KEY_APOSTROPHE;
    env["KEY_GRAVE"] = KEY_GRAVE;
    env["KEY_LEFTSHIFT"] = KEY_LEFTSHIFT;
    env["KEY_BACKSLASH"] = KEY_BACKSLASH;
    env["KEY_Z"] = KEY_Z;
    env["KEY_X"] = KEY_X;
    env["KEY_C"] = KEY_C;
    env["KEY_V"] = KEY_V;
    env["KEY_B"] = KEY_B;
    env["KEY_N"] = KEY_N;
    env["KEY_M"] = KEY_M;
    env["KEY_COMMA"] = KEY_COMMA;
    env["KEY_DOT"] = KEY_DOT;
    env["KEY_SLASH"] = KEY_SLASH;
    env["KEY_RIGHTSHIFT"] = KEY_RIGHTSHIFT;
    env["KEY_KPASTERISK"] = KEY_KPASTERISK;
    env["KEY_LEFTALT"] = KEY_LEFTALT;
    env["KEY_SPACE"] = KEY_SPACE;
    env["KEY_CAPSLOCK"] = KEY_CAPSLOCK;
    env["KEY_F1"] = KEY_F1;
    env["KEY_F2"] = KEY_F2;
    env["KEY_F3"] = KEY_F3;
    env["KEY_F4"] = KEY_F4;
    env["KEY_F5"] = KEY_F5;
    env["KEY_F6"] = KEY_F6;
    env["KEY_F7"] = KEY_F7;
    env["KEY_F8"] = KEY_F8;
    env["KEY_F9"] = KEY_F9;
    env["KEY_F10"] = KEY_F10;
    env["KEY_NUMLOCK"] = KEY_NUMLOCK;
    env["KEY_SCROLLLOCK"] = KEY_SCROLLLOCK;
    env["KEY_KP7"] = KEY_KP7;
    env["KEY_KP8"] = KEY_KP8;
    env["KEY_KP9"] = KEY_KP9;
    env["KEY_KPMINUS"] = KEY_KPMINUS;
    env["KEY_KP4"] = KEY_KP4;
    env["KEY_KP5"] = KEY_KP5;
    env["KEY_KP6"] = KEY_KP6;
    env["KEY_KPPLUS"] = KEY_KPPLUS;
    env["KEY_KP1"] = KEY_KP1;
    env["KEY_KP2"] = KEY_KP2;
    env["KEY_KP3"] = KEY_KP3;
    env["KEY_KP0"] = KEY_KP0;
    env["KEY_KPDOT"] = KEY_KPDOT;

    env["KEY_ZENKAKUHANKAKU"] = KEY_ZENKAKUHANKAKU;
    env["KEY_102ND"] = KEY_102ND;
    env["KEY_F11"] = KEY_F11;
    env["KEY_F12"] = KEY_F12;
    env["KEY_RO"] = KEY_RO;
    env["KEY_KATAKANA"] = KEY_KATAKANA;
    env["KEY_HIRAGANA"] = KEY_HIRAGANA;
    env["KEY_HENKAN"] = KEY_HENKAN;
    env["KEY_KATAKANAHIRAGANA"] = KEY_KATAKANAHIRAGANA;
    env["KEY_MUHENKAN"] = KEY_MUHENKAN;
    env["KEY_KPJPCOMMA"] = KEY_KPJPCOMMA;
    env["KEY_KPENTER"] = KEY_KPENTER;
    env["KEY_RIGHTCTRL"] = KEY_RIGHTCTRL;
    env["KEY_KPSLASH"] = KEY_KPSLASH;
    env["KEY_SYSRQ"] = KEY_SYSRQ;
    env["KEY_RIGHTALT"] = KEY_RIGHTALT;
    env["KEY_LINEFEED"] = KEY_LINEFEED;
    env["KEY_HOME"] = KEY_HOME;
    env["KEY_UP"] = KEY_UP;
    env["KEY_PAGEUP"] = KEY_PAGEUP;
    env["KEY_LEFT"] = KEY_LEFT;
    env["KEY_RIGHT"] = KEY_RIGHT;
    env["KEY_END"] = KEY_END;
    env["KEY_DOWN"] = KEY_DOWN;
    env["KEY_PAGEDOWN"] = KEY_PAGEDOWN;
    env["KEY_INSERT"] = KEY_INSERT;
    env["KEY_DELETE"] = KEY_DELETE;
    env["KEY_MACRO"] = KEY_MACRO;
    env["KEY_MUTE"] = KEY_MUTE;
    env["KEY_VOLUMEDOWN"] = KEY_VOLUMEDOWN;
    env["KEY_VOLUMEUP"] = KEY_VOLUMEUP;
    env["KEY_POWER"] = KEY_POWER; /* SC System Power Down */
    env["KEY_KPEQUAL"] = KEY_KPEQUAL;
    env["KEY_KPPLUSMINUS"] = KEY_KPPLUSMINUS;
    env["KEY_PAUSE"] = KEY_PAUSE;
    env["KEY_SCALE"] = KEY_SCALE; /* AL Compiz Scale (Expose) */

    env["KEY_KPCOMMA"] = KEY_KPCOMMA;
    env["KEY_HANGEUL"] = KEY_HANGEUL;
    env["KEY_HANGUEL"] = KEY_HANGUEL;
    env["KEY_HANJA"] = KEY_HANJA;
    env["KEY_YEN"] = KEY_YEN;
    env["KEY_LEFTMETA"] = KEY_LEFTMETA;
    env["KEY_RIGHTMETA"] = KEY_RIGHTMETA;
    env["KEY_COMPOSE"] = KEY_COMPOSE;

    env["KEY_STOP"] = KEY_STOP; /* AC Stop */
    env["KEY_AGAIN"] = KEY_AGAIN;
    env["KEY_PROPS"] = KEY_PROPS; /* AC Properties */
    env["KEY_UNDO"] = KEY_UNDO; /* AC Undo */
    env["KEY_FRONT"] = KEY_FRONT;
    env["KEY_COPY"] = KEY_COPY; /* AC Copy */
    env["KEY_OPEN"] = KEY_OPEN; /* AC Open */
    env["KEY_PASTE"] = KEY_PASTE; /* AC Paste */
    env["KEY_FIND"] = KEY_FIND; /* AC Search */
    env["KEY_CUT"] = KEY_CUT; /* AC Cut */
    env["KEY_HELP"] = KEY_HELP; /* AL Integrated Help Center */
    env["KEY_MENU"] = KEY_MENU; /* Menu (show menu) */
    env["KEY_CALC"] = KEY_CALC; /* AL Calculator */
    env["KEY_SETUP"] = KEY_SETUP;
    env["KEY_SLEEP"] = KEY_SLEEP; /* SC System Sleep */
    env["KEY_WAKEUP"] = KEY_WAKEUP; /* System Wake Up */
    env["KEY_FILE"] = KEY_FILE; /* AL Local Machine Browser */
    env["KEY_SENDFILE"] = KEY_SENDFILE;
    env["KEY_DELETEFILE"] = KEY_DELETEFILE;
    env["KEY_XFER"] = KEY_XFER;
    env["KEY_PROG1"] = KEY_PROG1;
    env["KEY_PROG2"] = KEY_PROG2;
    env["KEY_WWW"] = KEY_WWW; /* AL Internet Browser */
    env["KEY_MSDOS"] = KEY_MSDOS;
    env["KEY_COFFEE"] = KEY_COFFEE; /* AL Terminal Lock/Screensaver */
    env["KEY_SCREENLOCK"] = KEY_SCREENLOCK;
    env["KEY_DIRECTION"] = KEY_DIRECTION;
    env["KEY_CYCLEWINDOWS"] = KEY_CYCLEWINDOWS;
    env["KEY_MAIL"] = KEY_MAIL;
    env["KEY_BOOKMARKS"] = KEY_BOOKMARKS; /* AC Bookmarks */
    env["KEY_COMPUTER"] = KEY_COMPUTER;
    env["KEY_BACK"] = KEY_BACK; /* AC Back */
    env["KEY_FORWARD"] = KEY_FORWARD; /* AC Forward */
    env["KEY_CLOSECD"] = KEY_CLOSECD;
    env["KEY_EJECTCD"] = KEY_EJECTCD;
    env["KEY_EJECTCLOSECD"] = KEY_EJECTCLOSECD;
    env["KEY_NEXTSONG"] = KEY_NEXTSONG;
    env["KEY_PLAYPAUSE"] = KEY_PLAYPAUSE;
    env["KEY_PREVIOUSSONG"] = KEY_PREVIOUSSONG;
    env["KEY_STOPCD"] = KEY_STOPCD;
    env["KEY_RECORD"] = KEY_RECORD;
    env["KEY_REWIND"] = KEY_REWIND;
    env["KEY_PHONE"] = KEY_PHONE; /* Media Select Telephone */
    env["KEY_ISO"] = KEY_ISO;
    env["KEY_CONFIG"] = KEY_CONFIG; /* AL Consumer Control Configuration */
    env["KEY_HOMEPAGE"] = KEY_HOMEPAGE; /* AC Home */
    env["KEY_REFRESH"] = KEY_REFRESH; /* AC Refresh */
    env["KEY_EXIT"] = KEY_EXIT; /* AC Exit */
    env["KEY_MOVE"] = KEY_MOVE;
    env["KEY_EDIT"] = KEY_EDIT;
    env["KEY_SCROLLUP"] = KEY_SCROLLUP;
    env["KEY_SCROLLDOWN"] = KEY_SCROLLDOWN;
    env["KEY_KPLEFTPAREN"] = KEY_KPLEFTPAREN;
    env["KEY_KPRIGHTPAREN"] = KEY_KPRIGHTPAREN;
    env["KEY_NEW"] = KEY_NEW; /* AC New */
    env["KEY_REDO"] = KEY_REDO; /* AC Redo/Repeat */

    env["KEY_F13"] = KEY_F13;
    env["KEY_F14"] = KEY_F14;
    env["KEY_F15"] = KEY_F15;
    env["KEY_F16"] = KEY_F16;
    env["KEY_F17"] = KEY_F17;
    env["KEY_F18"] = KEY_F18;
    env["KEY_F19"] = KEY_F19;
    env["KEY_F20"] = KEY_F20;
    env["KEY_F21"] = KEY_F21;
    env["KEY_F22"] = KEY_F22;
    env["KEY_F23"] = KEY_F23;
    env["KEY_F24"] = KEY_F24;

    env["KEY_PLAYCD"] = KEY_PLAYCD;
    env["KEY_PAUSECD"] = KEY_PAUSECD;
    env["KEY_PROG3"] = KEY_PROG3;
    env["KEY_PROG4"] = KEY_PROG4;
    env["KEY_DASHBOARD"] = KEY_DASHBOARD; /* AL Dashboard */
    env["KEY_SUSPEND"] = KEY_SUSPEND;
    env["KEY_CLOSE"] = KEY_CLOSE; /* AC Close */
    env["KEY_PLAY"] = KEY_PLAY;
    env["KEY_FASTFORWARD"] = KEY_FASTFORWARD;
    env["KEY_BASSBOOST"] = KEY_BASSBOOST;
    env["KEY_PRINT"] = KEY_PRINT; /* AC Print */
    env["KEY_HP"] = KEY_HP;
    env["KEY_CAMERA"] = KEY_CAMERA;
    env["KEY_SOUND"] = KEY_SOUND;
    env["KEY_QUESTION"] = KEY_QUESTION;
    env["KEY_EMAIL"] = KEY_EMAIL;
    env["KEY_CHAT"] = KEY_CHAT;
    env["KEY_SEARCH"] = KEY_SEARCH;
    env["KEY_CONNECT"] = KEY_CONNECT;
    env["KEY_FINANCE"] = KEY_FINANCE; /* AL Checkbook/Finance */
    env["KEY_SPORT"] = KEY_SPORT;
    env["KEY_SHOP"] = KEY_SHOP;
    env["KEY_ALTERASE"] = KEY_ALTERASE;
    env["KEY_CANCEL"] = KEY_CANCEL; /* AC Cancel */
    env["KEY_BRIGHTNESSDOWN"] = KEY_BRIGHTNESSDOWN;
    env["KEY_BRIGHTNESSUP"] = KEY_BRIGHTNESSUP;
    env["KEY_MEDIA"] = KEY_MEDIA;

    env["KEY_SWITCHVIDEOMODE"] = KEY_SWITCHVIDEOMODE; /* Cycle between available video
                           env["Monitor"] = Monitor; LCD/TV-out/etc) */
    env["KEY_KBDILLUMTOGGLE"] = KEY_KBDILLUMTOGGLE;
    env["KEY_KBDILLUMDOWN"] = KEY_KBDILLUMDOWN;
    env["KEY_KBDILLUMUP"] = KEY_KBDILLUMUP;

    env["KEY_SEND"] = KEY_SEND; /* AC Send */
    env["KEY_REPLY"] = KEY_REPLY; /* AC Reply */
    env["KEY_FORWARDMAIL"] = KEY_FORWARDMAIL; /* AC Forward Msg */
    env["KEY_SAVE"] = KEY_SAVE; /* AC Save */
    env["KEY_DOCUMENTS"] = KEY_DOCUMENTS;

    env["KEY_BATTERY"] = KEY_BATTERY;

    env["KEY_BLUETOOTH"] = KEY_BLUETOOTH;
    env["KEY_WLAN"] = KEY_WLAN;
    env["KEY_UWB"] = KEY_UWB;

    env["KEY_UNKNOWN"] = KEY_UNKNOWN;

    env["KEY_VIDEO_NEXT"] = KEY_VIDEO_NEXT; /* drive next video source */
    env["KEY_VIDEO_PREV"] = KEY_VIDEO_PREV; /* drive previous video source */
    env["KEY_BRIGHTNESS_CYCLE"] = KEY_BRIGHTNESS_CYCLE; /* brightness up, after max is min */
    env["KEY_BRIGHTNESS_ZERO"] = KEY_BRIGHTNESS_ZERO; /* brightness off, use ambient */
    env["KEY_DISPLAY_OFF"] = KEY_DISPLAY_OFF; /* display device to off state */

    env["KEY_WWAN"] = KEY_WWAN; /* Wireless WAN (LTE, UMTS, GSM, etc.) */
    env["KEY_WIMAX"] = KEY_WIMAX;
    env["KEY_RFKILL"] = KEY_RFKILL; /* Key that controls all radios */

    env["KEY_MICMUTE"] = KEY_MICMUTE; /* Mute / unmute the microphone */

    /* Code 255 is reserved for special needs of AT keyboard driver */

    env["BTN_MISC"] = BTN_MISC;
    env["BTN_0"] = BTN_0;
    env["BTN_1"] = BTN_1;
    env["BTN_2"] = BTN_2;
    env["BTN_3"] = BTN_3;
    env["BTN_4"] = BTN_4;
    env["BTN_5"] = BTN_5;
    env["BTN_6"] = BTN_6;
    env["BTN_7"] = BTN_7;
    env["BTN_8"] = BTN_8;
    env["BTN_9"] = BTN_9;

    env["BTN_MOUSE"] = BTN_MOUSE;
    env["BTN_LEFT"] = BTN_LEFT;
    env["BTN_RIGHT"] = BTN_RIGHT;
    env["BTN_MIDDLE"] = BTN_MIDDLE;
    env["BTN_SIDE"] = BTN_SIDE;
    env["BTN_EXTRA"] = BTN_EXTRA;
    env["BTN_FORWARD"] = BTN_FORWARD;
    env["BTN_BACK"] = BTN_BACK;
    env["BTN_TASK"] = BTN_TASK;

    env["BTN_JOYSTICK"] = BTN_JOYSTICK;
    env["BTN_TRIGGER"] = BTN_TRIGGER;
    env["BTN_THUMB"] = BTN_THUMB;
    env["BTN_THUMB2"] = BTN_THUMB2;
    env["BTN_TOP"] = BTN_TOP;
    env["BTN_TOP2"] = BTN_TOP2;
    env["BTN_PINKIE"] = BTN_PINKIE;
    env["BTN_BASE"] = BTN_BASE;
    env["BTN_BASE2"] = BTN_BASE2;
    env["BTN_BASE3"] = BTN_BASE3;
    env["BTN_BASE4"] = BTN_BASE4;
    env["BTN_BASE5"] = BTN_BASE5;
    env["BTN_BASE6"] = BTN_BASE6;
    env["BTN_DEAD"] = BTN_DEAD;

    env["BTN_GAMEPAD"] = BTN_GAMEPAD;
    env["BTN_SOUTH"] = BTN_SOUTH;
    env["BTN_A"] = BTN_A;
    env["BTN_EAST"] = BTN_EAST;
    env["BTN_B"] = BTN_B;
    env["BTN_C"] = BTN_C;
    env["BTN_NORTH"] = BTN_NORTH;
    env["BTN_X"] = BTN_X;
    env["BTN_WEST"] = BTN_WEST;
    env["BTN_Y"] = BTN_Y;
    env["BTN_Z"] = BTN_Z;
    env["BTN_TL"] = BTN_TL;
    env["BTN_TR"] = BTN_TR;
    env["BTN_TL2"] = BTN_TL2;
    env["BTN_TR2"] = BTN_TR2;
    env["BTN_SELECT"] = BTN_SELECT;
    env["BTN_START"] = BTN_START;
    env["BTN_MODE"] = BTN_MODE;
    env["BTN_THUMBL"] = BTN_THUMBL;
    env["BTN_THUMBR"] = BTN_THUMBR;

    env["BTN_DIGI"] = BTN_DIGI;
    env["BTN_TOOL_PEN"] = BTN_TOOL_PEN;
    env["BTN_TOOL_RUBBER"] = BTN_TOOL_RUBBER;
    env["BTN_TOOL_BRUSH"] = BTN_TOOL_BRUSH;
    env["BTN_TOOL_PENCIL"] = BTN_TOOL_PENCIL;
    env["BTN_TOOL_AIRBRUSH"] = BTN_TOOL_AIRBRUSH;
    env["BTN_TOOL_FINGER"] = BTN_TOOL_FINGER;
    env["BTN_TOOL_MOUSE"] = BTN_TOOL_MOUSE;
    env["BTN_TOOL_LENS"] = BTN_TOOL_LENS;
    env["BTN_TOOL_QUINTTAP"] = BTN_TOOL_QUINTTAP; /* Five fingers on trackpad */
    env["BTN_TOUCH"] = BTN_TOUCH;
    env["BTN_STYLUS"] = BTN_STYLUS;
    env["BTN_STYLUS2"] = BTN_STYLUS2;
    env["BTN_TOOL_DOUBLETAP"] = BTN_TOOL_DOUBLETAP;
    env["BTN_TOOL_TRIPLETAP"] = BTN_TOOL_TRIPLETAP;
    env["BTN_TOOL_QUADTAP"] = BTN_TOOL_QUADTAP; /* Four fingers on trackpad */

    env["BTN_WHEEL"] = BTN_WHEEL;
    env["BTN_GEAR_DOWN"] = BTN_GEAR_DOWN;
    env["BTN_GEAR_UP"] = BTN_GEAR_UP;

    env["KEY_OK"] = KEY_OK;
    env["KEY_SELECT"] = KEY_SELECT;
    env["KEY_GOTO"] = KEY_GOTO;
    env["KEY_CLEAR"] = KEY_CLEAR;
    env["KEY_POWER2"] = KEY_POWER2;
    env["KEY_OPTION"] = KEY_OPTION;
    env["KEY_INFO"] = KEY_INFO; /* AL OEM Features/Tips/Tutorial */
    env["KEY_TIME"] = KEY_TIME;
    env["KEY_VENDOR"] = KEY_VENDOR;
    env["KEY_ARCHIVE"] = KEY_ARCHIVE;
    env["KEY_PROGRAM"] = KEY_PROGRAM; /* Media Select Program Guide */
    env["KEY_CHANNEL"] = KEY_CHANNEL;
    env["KEY_FAVORITES"] = KEY_FAVORITES;
    env["KEY_EPG"] = KEY_EPG;
    env["KEY_PVR"] = KEY_PVR; /* Media Select Home */
    env["KEY_MHP"] = KEY_MHP;
    env["KEY_LANGUAGE"] = KEY_LANGUAGE;
    env["KEY_TITLE"] = KEY_TITLE;
    env["KEY_SUBTITLE"] = KEY_SUBTITLE;
    env["KEY_ANGLE"] = KEY_ANGLE;
    env["KEY_ZOOM"] = KEY_ZOOM;
    env["KEY_MODE"] = KEY_MODE;
    env["KEY_KEYBOARD"] = KEY_KEYBOARD;
    env["KEY_SCREEN"] = KEY_SCREEN;
    env["KEY_PC"] = KEY_PC; /* Media Select Computer */
    env["KEY_TV"] = KEY_TV; /* Media Select TV */
    env["KEY_TV2"] = KEY_TV2; /* Media Select Cable */
    env["KEY_VCR"] = KEY_VCR; /* Media Select VCR */
    env["KEY_VCR2"] = KEY_VCR2; /* VCR Plus */
    env["KEY_SAT"] = KEY_SAT; /* Media Select Satellite */
    env["KEY_SAT2"] = KEY_SAT2;
    env["KEY_CD"] = KEY_CD; /* Media Select CD */
    env["KEY_TAPE"] = KEY_TAPE; /* Media Select Tape */
    env["KEY_RADIO"] = KEY_RADIO;
    env["KEY_TUNER"] = KEY_TUNER; /* Media Select Tuner */
    env["KEY_PLAYER"] = KEY_PLAYER;
    env["KEY_TEXT"] = KEY_TEXT;
    env["KEY_DVD"] = KEY_DVD; /* Media Select DVD */
    env["KEY_AUX"] = KEY_AUX;
    env["KEY_MP3"] = KEY_MP3;
    env["KEY_AUDIO"] = KEY_AUDIO; /* AL Audio Browser */
    env["KEY_VIDEO"] = KEY_VIDEO; /* AL Movie Browser */
    env["KEY_DIRECTORY"] = KEY_DIRECTORY;
    env["KEY_LIST"] = KEY_LIST;
    env["KEY_MEMO"] = KEY_MEMO; /* Media Select Messages */
    env["KEY_CALENDAR"] = KEY_CALENDAR;
    env["KEY_RED"] = KEY_RED;
    env["KEY_GREEN"] = KEY_GREEN;
    env["KEY_YELLOW"] = KEY_YELLOW;
    env["KEY_BLUE"] = KEY_BLUE;
    env["KEY_CHANNELUP"] = KEY_CHANNELUP; /* Channel Increment */
    env["KEY_CHANNELDOWN"] = KEY_CHANNELDOWN; /* Channel Decrement */
    env["KEY_FIRST"] = KEY_FIRST;
    env["KEY_LAST"] = KEY_LAST; /* Recall Last */
    env["KEY_AB"] = KEY_AB;
    env["KEY_NEXT"] = KEY_NEXT;
    env["KEY_RESTART"] = KEY_RESTART;
    env["KEY_SLOW"] = KEY_SLOW;
    env["KEY_SHUFFLE"] = KEY_SHUFFLE;
    env["KEY_BREAK"] = KEY_BREAK;
    env["KEY_PREVIOUS"] = KEY_PREVIOUS;
    env["KEY_DIGITS"] = KEY_DIGITS;
    env["KEY_TEEN"] = KEY_TEEN;
    env["KEY_TWEN"] = KEY_TWEN;
    env["KEY_VIDEOPHONE"] = KEY_VIDEOPHONE; /* Media Select Video Phone */
    env["KEY_GAMES"] = KEY_GAMES; /* Media Select Games */
    env["KEY_ZOOMIN"] = KEY_ZOOMIN; /* AC Zoom In */
    env["KEY_ZOOMOUT"] = KEY_ZOOMOUT; /* AC Zoom Out */
    env["KEY_ZOOMRESET"] = KEY_ZOOMRESET; /* AC Zoom */
    env["KEY_WORDPROCESSOR"] = KEY_WORDPROCESSOR; /* AL Word Processor */
    env["KEY_EDITOR"] = KEY_EDITOR; /* AL Text Editor */
    env["KEY_SPREADSHEET"] = KEY_SPREADSHEET; /* AL Spreadsheet */
    env["KEY_GRAPHICSEDITOR"] = KEY_GRAPHICSEDITOR; /* AL Graphics Editor */
    env["KEY_PRESENTATION"] = KEY_PRESENTATION; /* AL Presentation App */
    env["KEY_DATABASE"] = KEY_DATABASE; /* AL Database App */
    env["KEY_NEWS"] = KEY_NEWS; /* AL Newsreader */
    env["KEY_VOICEMAIL"] = KEY_VOICEMAIL; /* AL Voicemail */
    env["KEY_ADDRESSBOOK"] = KEY_ADDRESSBOOK; /* AL Contacts/Address Book */
    env["KEY_MESSENGER"] = KEY_MESSENGER; /* AL Instant Messaging */
    env["KEY_DISPLAYTOGGLE"] = KEY_DISPLAYTOGGLE; /* Turn display (LCD) on and off */
    env["KEY_SPELLCHECK"] = KEY_SPELLCHECK; /* AL Spell Check */
    env["KEY_LOGOFF"] = KEY_LOGOFF; /* AL Logoff */

    env["KEY_DOLLAR"] = KEY_DOLLAR;
    env["KEY_EURO"] = KEY_EURO;

    env["KEY_FRAMEBACK"] = KEY_FRAMEBACK; /* Consumer - transport controls */
    env["KEY_FRAMEFORWARD"] = KEY_FRAMEFORWARD;
    env["KEY_CONTEXT_MENU"] = KEY_CONTEXT_MENU; /* GenDesc - system context menu */
    env["KEY_MEDIA_REPEAT"] = KEY_MEDIA_REPEAT; /* Consumer - transport control */
    env["KEY_10CHANNELSUP"] = KEY_10CHANNELSUP; /* 10 channels up (10+) */
    env["KEY_10CHANNELSDOWN"] = KEY_10CHANNELSDOWN; /* 10 channels down (10-) */
    env["KEY_IMAGES"] = KEY_IMAGES; /* AL Image Browser */

    env["KEY_DEL_EOL"] = KEY_DEL_EOL;
    env["KEY_DEL_EOS"] = KEY_DEL_EOS;
    env["KEY_INS_LINE"] = KEY_INS_LINE;
    env["KEY_DEL_LINE"] = KEY_DEL_LINE;

    env["KEY_FN"] = KEY_FN;
    env["KEY_FN_ESC"] = KEY_FN_ESC;
    env["KEY_FN_F1"] = KEY_FN_F1;
    env["KEY_FN_F2"] = KEY_FN_F2;
    env["KEY_FN_F3"] = KEY_FN_F3;
    env["KEY_FN_F4"] = KEY_FN_F4;
    env["KEY_FN_F5"] = KEY_FN_F5;
    env["KEY_FN_F6"] = KEY_FN_F6;
    env["KEY_FN_F7"] = KEY_FN_F7;
    env["KEY_FN_F8"] = KEY_FN_F8;
    env["KEY_FN_F9"] = KEY_FN_F9;
    env["KEY_FN_F10"] = KEY_FN_F10;
    env["KEY_FN_F11"] = KEY_FN_F11;
    env["KEY_FN_F12"] = KEY_FN_F12;
    env["KEY_FN_1"] = KEY_FN_1;
    env["KEY_FN_2"] = KEY_FN_2;
    env["KEY_FN_D"] = KEY_FN_D;
    env["KEY_FN_E"] = KEY_FN_E;
    env["KEY_FN_F"] = KEY_FN_F;
    env["KEY_FN_S"] = KEY_FN_S;
    env["KEY_FN_B"] = KEY_FN_B;

    env["KEY_BRL_DOT1"] = KEY_BRL_DOT1;
    env["KEY_BRL_DOT2"] = KEY_BRL_DOT2;
    env["KEY_BRL_DOT3"] = KEY_BRL_DOT3;
    env["KEY_BRL_DOT4"] = KEY_BRL_DOT4;
    env["KEY_BRL_DOT5"] = KEY_BRL_DOT5;
    env["KEY_BRL_DOT6"] = KEY_BRL_DOT6;
    env["KEY_BRL_DOT7"] = KEY_BRL_DOT7;
    env["KEY_BRL_DOT8"] = KEY_BRL_DOT8;
    env["KEY_BRL_DOT9"] = KEY_BRL_DOT9;
    env["KEY_BRL_DOT10"] = KEY_BRL_DOT10;

    env["KEY_NUMERIC_0"] = KEY_NUMERIC_0; /* used by phones, remote controls, */
    env["KEY_NUMERIC_1"] = KEY_NUMERIC_1; /* and other keypads */
    env["KEY_NUMERIC_2"] = KEY_NUMERIC_2;
    env["KEY_NUMERIC_3"] = KEY_NUMERIC_3;
    env["KEY_NUMERIC_4"] = KEY_NUMERIC_4;
    env["KEY_NUMERIC_5"] = KEY_NUMERIC_5;
    env["KEY_NUMERIC_6"] = KEY_NUMERIC_6;
    env["KEY_NUMERIC_7"] = KEY_NUMERIC_7;
    env["KEY_NUMERIC_8"] = KEY_NUMERIC_8;
    env["KEY_NUMERIC_9"] = KEY_NUMERIC_9;
    env["KEY_NUMERIC_STAR"] = KEY_NUMERIC_STAR;
    env["KEY_NUMERIC_POUND"] = KEY_NUMERIC_POUND;

    env["KEY_CAMERA_FOCUS"] = KEY_CAMERA_FOCUS;
    env["KEY_WPS_BUTTON"] = KEY_WPS_BUTTON; /* WiFi Protected Setup key */

    env["KEY_TOUCHPAD_TOGGLE"] = KEY_TOUCHPAD_TOGGLE; /* Request switch touchpad on or off */
    env["KEY_TOUCHPAD_ON"] = KEY_TOUCHPAD_ON;
    env["KEY_TOUCHPAD_OFF"] = KEY_TOUCHPAD_OFF;

    env["KEY_CAMERA_ZOOMIN"] = KEY_CAMERA_ZOOMIN;
    env["KEY_CAMERA_ZOOMOUT"] = KEY_CAMERA_ZOOMOUT;
    env["KEY_CAMERA_UP"] = KEY_CAMERA_UP;
    env["KEY_CAMERA_DOWN"] = KEY_CAMERA_DOWN;
    env["KEY_CAMERA_LEFT"] = KEY_CAMERA_LEFT;
    env["KEY_CAMERA_RIGHT"] = KEY_CAMERA_RIGHT;

    env["KEY_ATTENDANT_ON"] = KEY_ATTENDANT_ON;
    env["KEY_ATTENDANT_OFF"] = KEY_ATTENDANT_OFF;
    env["KEY_ATTENDANT_TOGGLE"] = KEY_ATTENDANT_TOGGLE; /* Attendant call on or off */
    env["KEY_LIGHTS_TOGGLE"] = KEY_LIGHTS_TOGGLE; /* Reading light on or off */

    env["BTN_DPAD_UP"] = BTN_DPAD_UP;
    env["BTN_DPAD_DOWN"] = BTN_DPAD_DOWN;
    env["BTN_DPAD_LEFT"] = BTN_DPAD_LEFT;
    env["BTN_DPAD_RIGHT"] = BTN_DPAD_RIGHT;

    env["KEY_ALS_TOGGLE"] = KEY_ALS_TOGGLE; /* Ambient light sensor */

    env["BTN_TRIGGER_HAPPY"] = BTN_TRIGGER_HAPPY;
    env["BTN_TRIGGER_HAPPY1"] = BTN_TRIGGER_HAPPY1;
    env["BTN_TRIGGER_HAPPY2"] = BTN_TRIGGER_HAPPY2;
    env["BTN_TRIGGER_HAPPY3"] = BTN_TRIGGER_HAPPY3;
    env["BTN_TRIGGER_HAPPY4"] = BTN_TRIGGER_HAPPY4;
    env["BTN_TRIGGER_HAPPY5"] = BTN_TRIGGER_HAPPY5;
    env["BTN_TRIGGER_HAPPY6"] = BTN_TRIGGER_HAPPY6;
    env["BTN_TRIGGER_HAPPY7"] = BTN_TRIGGER_HAPPY7;
    env["BTN_TRIGGER_HAPPY8"] = BTN_TRIGGER_HAPPY8;
    env["BTN_TRIGGER_HAPPY9"] = BTN_TRIGGER_HAPPY9;
    env["BTN_TRIGGER_HAPPY10"] = BTN_TRIGGER_HAPPY10;
    env["BTN_TRIGGER_HAPPY11"] = BTN_TRIGGER_HAPPY11;
    env["BTN_TRIGGER_HAPPY12"] = BTN_TRIGGER_HAPPY12;
    env["BTN_TRIGGER_HAPPY13"] = BTN_TRIGGER_HAPPY13;
    env["BTN_TRIGGER_HAPPY14"] = BTN_TRIGGER_HAPPY14;
    env["BTN_TRIGGER_HAPPY15"] = BTN_TRIGGER_HAPPY15;
    env["BTN_TRIGGER_HAPPY16"] = BTN_TRIGGER_HAPPY16;
    env["BTN_TRIGGER_HAPPY17"] = BTN_TRIGGER_HAPPY17;
    env["BTN_TRIGGER_HAPPY18"] = BTN_TRIGGER_HAPPY18;
    env["BTN_TRIGGER_HAPPY19"] = BTN_TRIGGER_HAPPY19;
    env["BTN_TRIGGER_HAPPY20"] = BTN_TRIGGER_HAPPY20;
    env["BTN_TRIGGER_HAPPY21"] = BTN_TRIGGER_HAPPY21;
    env["BTN_TRIGGER_HAPPY22"] = BTN_TRIGGER_HAPPY22;
    env["BTN_TRIGGER_HAPPY23"] = BTN_TRIGGER_HAPPY23;
    env["BTN_TRIGGER_HAPPY24"] = BTN_TRIGGER_HAPPY24;
    env["BTN_TRIGGER_HAPPY25"] = BTN_TRIGGER_HAPPY25;
    env["BTN_TRIGGER_HAPPY26"] = BTN_TRIGGER_HAPPY26;
    env["BTN_TRIGGER_HAPPY27"] = BTN_TRIGGER_HAPPY27;
    env["BTN_TRIGGER_HAPPY28"] = BTN_TRIGGER_HAPPY28;
    env["BTN_TRIGGER_HAPPY29"] = BTN_TRIGGER_HAPPY29;
    env["BTN_TRIGGER_HAPPY30"] = BTN_TRIGGER_HAPPY30;
    env["BTN_TRIGGER_HAPPY31"] = BTN_TRIGGER_HAPPY31;
    env["BTN_TRIGGER_HAPPY32"] = BTN_TRIGGER_HAPPY32;
    env["BTN_TRIGGER_HAPPY33"] = BTN_TRIGGER_HAPPY33;
    env["BTN_TRIGGER_HAPPY34"] = BTN_TRIGGER_HAPPY34;
    env["BTN_TRIGGER_HAPPY35"] = BTN_TRIGGER_HAPPY35;
    env["BTN_TRIGGER_HAPPY36"] = BTN_TRIGGER_HAPPY36;
    env["BTN_TRIGGER_HAPPY37"] = BTN_TRIGGER_HAPPY37;
    env["BTN_TRIGGER_HAPPY38"] = BTN_TRIGGER_HAPPY38;
    env["BTN_TRIGGER_HAPPY39"] = BTN_TRIGGER_HAPPY39;
    env["BTN_TRIGGER_HAPPY40"] = BTN_TRIGGER_HAPPY40;

    /* We avoid low common keys in module aliases so they don't get huge. */
    env["KEY_MIN_INTERESTING"] = KEY_MIN_INTERESTING;
    env["KEY_MAX"] = KEY_MAX;
    env["KEY_CNT"] = KEY_CNT;

    /*
     * Relative axes
     */

    env["REL_X"] = REL_X;
    env["REL_Y"] = REL_Y;
    env["REL_Z"] = REL_Z;
    env["REL_RX"] = REL_RX;
    env["REL_RY"] = REL_RY;
    env["REL_RZ"] = REL_RZ;
    env["REL_HWHEEL"] = REL_HWHEEL;
    env["REL_DIAL"] = REL_DIAL;
    env["REL_WHEEL"] = REL_WHEEL;
    env["REL_MISC"] = REL_MISC;
    env["REL_MAX"] = REL_MAX;
    env["REL_CNT"] = REL_CNT;

    /*
     * Absolute axes
     */

    env["ABS_X"] = ABS_X;
    env["ABS_Y"] = ABS_Y;
    env["ABS_Z"] = ABS_Z;
    env["ABS_RX"] = ABS_RX;
    env["ABS_RY"] = ABS_RY;
    env["ABS_RZ"] = ABS_RZ;
    env["ABS_THROTTLE"] = ABS_THROTTLE;
    env["ABS_RUDDER"] = ABS_RUDDER;
    env["ABS_WHEEL"] = ABS_WHEEL;
    env["ABS_GAS"] = ABS_GAS;
    env["ABS_BRAKE"] = ABS_BRAKE;
    env["ABS_HAT0X"] = ABS_HAT0X;
    env["ABS_HAT0Y"] = ABS_HAT0Y;
    env["ABS_HAT1X"] = ABS_HAT1X;
    env["ABS_HAT1Y"] = ABS_HAT1Y;
    env["ABS_HAT2X"] = ABS_HAT2X;
    env["ABS_HAT2Y"] = ABS_HAT2Y;
    env["ABS_HAT3X"] = ABS_HAT3X;
    env["ABS_HAT3Y"] = ABS_HAT3Y;
    env["ABS_PRESSURE"] = ABS_PRESSURE;
    env["ABS_DISTANCE"] = ABS_DISTANCE;
    env["ABS_TILT_X"] = ABS_TILT_X;
    env["ABS_TILT_Y"] = ABS_TILT_Y;
    env["ABS_TOOL_WIDTH"] = ABS_TOOL_WIDTH;

    env["ABS_VOLUME"] = ABS_VOLUME;

    env["ABS_MISC"] = ABS_MISC;

    env["ABS_MT_SLOT"] = ABS_MT_SLOT; /* MT slot being modified */
    env["ABS_MT_TOUCH_MAJOR"] = ABS_MT_TOUCH_MAJOR; /* Major axis of touching ellipse */
    env["ABS_MT_TOUCH_MINOR"] = ABS_MT_TOUCH_MINOR; /* Minor axis (omit if circular) */
    env["ABS_MT_WIDTH_MAJOR"] = ABS_MT_WIDTH_MAJOR; /* Major axis of approaching ellipse */
    env["ABS_MT_WIDTH_MINOR"] = ABS_MT_WIDTH_MINOR; /* Minor axis (omit if circular) */
    env["ABS_MT_ORIENTATION"] = ABS_MT_ORIENTATION; /* Ellipse orientation */
    env["ABS_MT_POSITION_X"] = ABS_MT_POSITION_X; /* Center X touch position */
    env["ABS_MT_POSITION_Y"] = ABS_MT_POSITION_Y; /* Center Y touch position */
    env["ABS_MT_TOOL_TYPE"] = ABS_MT_TOOL_TYPE; /* Type of touching device */
    env["ABS_MT_BLOB_ID"] = ABS_MT_BLOB_ID; /* Group a set of packets as a blob */
    env["ABS_MT_TRACKING_ID"] = ABS_MT_TRACKING_ID; /* Unique ID of initiated contact */
    env["ABS_MT_PRESSURE"] = ABS_MT_PRESSURE; /* Pressure on contact area */
    env["ABS_MT_DISTANCE"] = ABS_MT_DISTANCE; /* Contact hover distance */
    env["ABS_MT_TOOL_X"] = ABS_MT_TOOL_X; /* Center X tool position */
    env["ABS_MT_TOOL_Y"] = ABS_MT_TOOL_Y; /* Center Y tool position */


    env["ABS_MAX"] = ABS_MAX;
    env["ABS_CNT"] = ABS_CNT;

    /*
     * Switch events
     */

    env["SW_LID"] = SW_LID; /* set = lid shut */
    env["SW_TABLET_MODE"] = SW_TABLET_MODE; /* set = tablet mode */
    env["SW_HEADPHONE_INSERT"] = SW_HEADPHONE_INSERT; /* set = inserted */
    env["SW_RFKILL_ALL"] = SW_RFKILL_ALL; /* rfkill master switch, type "any"
                         env["radio"] = radio; */
    env["SW_RADIO"] = SW_RADIO; /* deprecated */
    env["SW_MICROPHONE_INSERT"] = SW_MICROPHONE_INSERT; /* set = inserted */
    env["SW_DOCK"] = SW_DOCK; /* set = plugged into dock */
    env["SW_LINEOUT_INSERT"] = SW_LINEOUT_INSERT; /* set = inserted */
    env["SW_JACK_PHYSICAL_INSERT"] = SW_JACK_PHYSICAL_INSERT; /* set = mechanical switch set */
    env["SW_VIDEOOUT_INSERT"] = SW_VIDEOOUT_INSERT; /* set = inserted */
    env["SW_CAMERA_LENS_COVER"] = SW_CAMERA_LENS_COVER; /* set = lens covered */
    env["SW_KEYPAD_SLIDE"] = SW_KEYPAD_SLIDE; /* set = keypad slide out */
    env["SW_FRONT_PROXIMITY"] = SW_FRONT_PROXIMITY; /* set = front proximity sensor active */
    env["SW_ROTATE_LOCK"] = SW_ROTATE_LOCK; /* set = rotate locked/disabled */
    env["SW_LINEIN_INSERT"] = SW_LINEIN_INSERT; /* set = inserted */
    env["SW_MUTE_DEVICE"] = SW_MUTE_DEVICE; /* set = device disabled */
    env["SW_MAX"] = SW_MAX;
    env["SW_CNT"] = SW_CNT;

    /*
     * Misc events
     */

    env["MSC_SERIAL"] = MSC_SERIAL;
    env["MSC_PULSELED"] = MSC_PULSELED;
    env["MSC_GESTURE"] = MSC_GESTURE;
    env["MSC_RAW"] = MSC_RAW;
    env["MSC_SCAN"] = MSC_SCAN;
    env["MSC_TIMESTAMP"] = MSC_TIMESTAMP;
    env["MSC_MAX"] = MSC_MAX;
    env["MSC_CNT"] = MSC_CNT;

    /*
     * LEDs
     */

    env["LED_NUML"] = LED_NUML;
    env["LED_CAPSL"] = LED_CAPSL;
    env["LED_SCROLLL"] = LED_SCROLLL;
    env["LED_COMPOSE"] = LED_COMPOSE;
    env["LED_KANA"] = LED_KANA;
    env["LED_SLEEP"] = LED_SLEEP;
    env["LED_SUSPEND"] = LED_SUSPEND;
    env["LED_MUTE"] = LED_MUTE;
    env["LED_MISC"] = LED_MISC;
    env["LED_MAIL"] = LED_MAIL;
    env["LED_CHARGING"] = LED_CHARGING;
    env["LED_MAX"] = LED_MAX;
    env["LED_CNT"] = LED_CNT;

    /*
     * Autorepeat values
     */

    env["REP_DELAY"] = REP_DELAY;
    env["REP_PERIOD"] = REP_PERIOD;
    env["REP_MAX"] = REP_MAX;
    env["REP_CNT"] = REP_CNT;

    /*
     * Sounds
     */

    env["SND_CLICK"] = SND_CLICK;
    env["SND_BELL"] = SND_BELL;
    env["SND_TONE"] = SND_TONE;
    env["SND_MAX"] = SND_MAX;
    env["SND_CNT"] = SND_CNT;

    /*
     * IDs.
     */

    env["ID_BUS"] = ID_BUS;
    env["ID_VENDOR"] = ID_VENDOR;
    env["ID_PRODUCT"] = ID_PRODUCT;
    env["ID_VERSION"] = ID_VERSION;

    env["BUS_PCI"] = BUS_PCI;
    env["BUS_ISAPNP"] = BUS_ISAPNP;
    env["BUS_USB"] = BUS_USB;
    env["BUS_HIL"] = BUS_HIL;
    env["BUS_BLUETOOTH"] = BUS_BLUETOOTH;
    env["BUS_VIRTUAL"] = BUS_VIRTUAL;

    env["BUS_ISA"] = BUS_ISA;
    env["BUS_I8042"] = BUS_I8042;
    env["BUS_XTKBD"] = BUS_XTKBD;
    env["BUS_RS232"] = BUS_RS232;
    env["BUS_GAMEPORT"] = BUS_GAMEPORT;
    env["BUS_PARPORT"] = BUS_PARPORT;
    env["BUS_AMIGA"] = BUS_AMIGA;
    env["BUS_ADB"] = BUS_ADB;
    env["BUS_I2C"] = BUS_I2C;
    env["BUS_HOST"] = BUS_HOST;
    env["BUS_GSC"] = BUS_GSC;
    env["BUS_ATARI"] = BUS_ATARI;
    env["BUS_SPI"] = BUS_SPI;

    /*
     * MT_TOOL types
     */
    env["MT_TOOL_FINGER"] = MT_TOOL_FINGER;
    env["MT_TOOL_PEN"] = MT_TOOL_PEN;
    env["MT_TOOL_MAX"] = MT_TOOL_MAX;

    /*
     * Values describing the status of a force-feedback effect
     */
    env["FF_STATUS_STOPPED"] = FF_STATUS_STOPPED;
    env["FF_STATUS_PLAYING"] = FF_STATUS_PLAYING;
    env["FF_STATUS_MAX"] = FF_STATUS_MAX;

    /*
     * Force feedback effect types
     */

    env["FF_RUMBLE"] = FF_RUMBLE;
    env["FF_PERIODIC"] = FF_PERIODIC;
    env["FF_CONSTANT"] = FF_CONSTANT;
    env["FF_SPRING"] = FF_SPRING;
    env["FF_FRICTION"] = FF_FRICTION;
    env["FF_DAMPER"] = FF_DAMPER;
    env["FF_INERTIA"] = FF_INERTIA;
    env["FF_RAMP"] = FF_RAMP;

    env["FF_EFFECT_MIN"] = FF_EFFECT_MIN;
    env["FF_EFFECT_MAX"] = FF_EFFECT_MAX;

    /*
     * Force feedback periodic effect types
     */

    env["FF_SQUARE"] = FF_SQUARE;
    env["FF_TRIANGLE"] = FF_TRIANGLE;
    env["FF_SINE"] = FF_SINE;
    env["FF_SAW_UP"] = FF_SAW_UP;
    env["FF_SAW_DOWN"] = FF_SAW_DOWN;
    env["FF_CUSTOM"] = FF_CUSTOM;

    env["FF_WAVEFORM_MIN"] = FF_WAVEFORM_MIN;
    env["FF_WAVEFORM_MAX"] = FF_WAVEFORM_MAX;

    env["FF_GAIN"] = FF_GAIN;
    env["FF_AUTOCENTER"] = FF_AUTOCENTER;

    env["FF_MAX"] = FF_MAX;
    env["FF_CNT"] = FF_CNT;

    return 0;
}
