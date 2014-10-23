#ifndef LUACXX_QT_INCLUDED
#define LUACXX_QT_INCLUDED

#include "Qt5Core.hpp"
#include "../global.hpp"
#include "../enum.hpp"
#include <Qt>

namespace lua {

void qt_constants_1(lua_State* const state);
void qt_constants_2(lua_State* const state);
void qt_constants_3(lua_State* const state);
void qt_constants_4(lua_State* const state);

}; // namespace lua

LUA_METATABLE_ENUM(Qt::AlignmentFlag);
LUA_METATABLE_ENUM(Qt::AnchorPoint);
LUA_METATABLE_ENUM(Qt::ApplicationAttribute);
LUA_METATABLE_ENUM(Qt::ApplicationState);
LUA_METATABLE_ENUM(Qt::ArrowType);
LUA_METATABLE_ENUM(Qt::AspectRatioMode);
LUA_METATABLE_ENUM(Qt::Axis);
LUA_METATABLE_ENUM(Qt::BGMode);
LUA_METATABLE_ENUM(Qt::BrushStyle);
LUA_METATABLE_ENUM(Qt::CaseSensitivity);
LUA_METATABLE_ENUM(Qt::CheckState);
LUA_METATABLE_ENUM(Qt::ClipOperation);
LUA_METATABLE_ENUM(Qt::ConnectionType);
LUA_METATABLE_ENUM(Qt::ContextMenuPolicy);
LUA_METATABLE_ENUM(Qt::CoordinateSystem);
LUA_METATABLE_ENUM(Qt::Corner);
LUA_METATABLE_ENUM(Qt::CursorMoveStyle);
LUA_METATABLE_ENUM(Qt::CursorShape);
LUA_METATABLE_ENUM(Qt::DayOfWeek);
LUA_METATABLE_ENUM(Qt::DateFormat);
LUA_METATABLE_ENUM(Qt::DockWidgetArea);
LUA_METATABLE_ENUM(Qt::DropAction);
LUA_METATABLE_ENUM(Qt::Edge);
LUA_METATABLE_ENUM(Qt::EventPriority);
LUA_METATABLE_ENUM(Qt::FillRule);
LUA_METATABLE_ENUM(Qt::FindChildOption);
LUA_METATABLE_ENUM(Qt::FocusPolicy);
LUA_METATABLE_ENUM(Qt::FocusReason);
LUA_METATABLE_ENUM(Qt::GestureFlag);
LUA_METATABLE_ENUM(Qt::GestureState);
LUA_METATABLE_ENUM(Qt::GestureType);
LUA_METATABLE_ENUM(Qt::GlobalColor);
LUA_METATABLE_ENUM(Qt::HitTestAccuracy);
LUA_METATABLE_ENUM(Qt::ImageConversionFlag);
LUA_METATABLE_ENUM(Qt::InputMethodHint);
LUA_METATABLE_ENUM(Qt::InputMethodQuery);
LUA_METATABLE_ENUM(Qt::ItemDataRole);
LUA_METATABLE_ENUM(Qt::ItemFlag);
LUA_METATABLE_ENUM(Qt::ItemSelectionMode);
LUA_METATABLE_ENUM(Qt::Key);
LUA_METATABLE_ENUM(Qt::KeyboardModifier);
LUA_METATABLE_ENUM(Qt::LayoutDirection);
LUA_METATABLE_ENUM(Qt::MaskMode);
LUA_METATABLE_ENUM(Qt::MatchFlag);
LUA_METATABLE_ENUM(Qt::Modifier);
LUA_METATABLE_ENUM(Qt::MouseButton);
LUA_METATABLE_ENUM(Qt::MouseEventFlag);
LUA_METATABLE_ENUM(Qt::MouseEventSource);
LUA_METATABLE_ENUM(Qt::NavigationMode);
LUA_METATABLE_ENUM(Qt::Orientation);
LUA_METATABLE_ENUM(Qt::PenCapStyle);
LUA_METATABLE_ENUM(Qt::PenJoinStyle);
LUA_METATABLE_ENUM(Qt::PenStyle);
LUA_METATABLE_ENUM(Qt::ScreenOrientation);
LUA_METATABLE_ENUM(Qt::ScrollBarPolicy);
LUA_METATABLE_ENUM(Qt::ScrollPhase);
LUA_METATABLE_ENUM(Qt::ShortcutContext);
LUA_METATABLE_ENUM(Qt::SizeHint);
LUA_METATABLE_ENUM(Qt::SizeMode);
LUA_METATABLE_ENUM(Qt::SortOrder);
LUA_METATABLE_ENUM(Qt::TextElideMode);
LUA_METATABLE_ENUM(Qt::TextFlag);
LUA_METATABLE_ENUM(Qt::TextFormat);
LUA_METATABLE_ENUM(Qt::TextInteractionFlag);
LUA_METATABLE_ENUM(Qt::TileRule);
LUA_METATABLE_ENUM(Qt::TimeSpec);
LUA_METATABLE_ENUM(Qt::TimerType);
LUA_METATABLE_ENUM(Qt::ToolBarArea);
LUA_METATABLE_ENUM(Qt::ToolButtonStyle);
LUA_METATABLE_ENUM(Qt::TouchPointState);
LUA_METATABLE_ENUM(Qt::TransformationMode);
LUA_METATABLE_ENUM(Qt::UIEffect);
LUA_METATABLE_ENUM(Qt::WhiteSpaceMode);
LUA_METATABLE_ENUM(Qt::WidgetAttribute);
LUA_METATABLE_ENUM(Qt::WindowFrameSection);
LUA_METATABLE_ENUM(Qt::WindowModality);
LUA_METATABLE_ENUM(Qt::WindowState);
LUA_METATABLE_ENUM(Qt::WindowType);

extern "C" int luaopen_Qt5Core_Qt(lua_State* const);

#endif // LUACXX_QT_INCLUDED
