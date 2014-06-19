#include "QPalette.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "QColor.hpp"
#include "QBrush.hpp"

// http://qt-project.org/doc/qt-5/qpalette.html

int QPalette_brush(lua_State* const state)
{
    auto self = lua::get<QPalette*>(state, 1);
    if (lua_gettop(state) > 2) {
        lua::push(state, self->brush(
            lua::get<QPalette::ColorGroup>(state, 2),
            lua::get<QPalette::ColorRole>(state, 3)
        ));
    } else {
        lua::push(state, self->brush(
            lua::get<QPalette::ColorRole>(state, 2)
        ));
    }
    return 1;
}

int QPalette_color(lua_State* const state)
{
    auto self = lua::get<QPalette*>(state, 1);
    if (lua_gettop(state) > 2) {
        lua::push(state, self->color(
            lua::get<QPalette::ColorGroup>(state, 2),
            lua::get<QPalette::ColorRole>(state, 3)
        ));
    } else {
        lua::push(state, self->color(
            lua::get<QPalette::ColorRole>(state, 2)
        ));
    }
    return 1;
}

int QPalette_resolve(lua_State* const state)
{
    auto self = lua::get<QPalette*>(state, 1);
    lua::push(state, self->resolve(lua::get<const QPalette&>(state, 2)));
    return 0;
}

int QPalette_setBrush(lua_State* const state)
{
    auto self = lua::get<QPalette*>(state, 1);
    if (lua_gettop(state) > 3) {
        self->setBrush(
            lua::get<QPalette::ColorGroup>(state, 2),
            lua::get<QPalette::ColorRole>(state, 3),
            lua::get<const QBrush&>(state, 4)
        );
    } else {
        self->setBrush(
            lua::get<QPalette::ColorRole>(state, 2),
            lua::get<const QBrush&>(state, 3)
        );
    }
    return 1;
}

int QPalette_setColor(lua_State* const state)
{
    auto self = lua::get<QPalette*>(state, 1);
    if (lua_gettop(state) > 3) {
        self->setColor(
            lua::get<QPalette::ColorGroup>(state, 2),
            lua::get<QPalette::ColorRole>(state, 3),
            lua::get<const QColor&>(state, 4)
        );
    } else {
        self->setColor(
            lua::get<QPalette::ColorRole>(state, 2),
            lua::get<const QColor&>(state, 3)
        );
    }
    return 0;
}

int QPalette_setColorGroup(lua_State* const state)
{
    auto self = lua::get<QPalette*>(state, 1);
    self->setColorGroup(
            lua::get<QPalette::ColorGroup>(state, 2),
            lua::get<const QBrush&>(state, 3),
            lua::get<const QBrush&>(state, 4),
            lua::get<const QBrush&>(state, 5),
            lua::get<const QBrush&>(state, 6),
            lua::get<const QBrush&>(state, 7),
            lua::get<const QBrush&>(state, 8),
            lua::get<const QBrush&>(state, 9),
            lua::get<const QBrush&>(state, 10),
            lua::get<const QBrush&>(state, 11)
    );
    return 0;
}

void lua::QPalette_metatable(const lua::index& mt)
{
    mt["alternateBase"] = &QPalette::alternateBase;
    mt["base"] = &QPalette::base;
    mt["brightText"] = &QPalette::brightText;
    mt["brush"] = QPalette_brush;
    mt["button"] = &QPalette::button;
    mt["buttonText"] = &QPalette::buttonText;
    mt["cacheKey"] = &QPalette::cacheKey;
    mt["color"] = QPalette_color;
    mt["currentColorGroup"] = &QPalette::currentColorGroup;
    mt["dark"] = &QPalette::dark;
    mt["highlight"] = &QPalette::highlight;
    mt["highlightedText"] = &QPalette::highlightedText;
    mt["isBrushSet"] = &QPalette::isBrushSet;
    mt["isCopyOf"] = &QPalette::isCopyOf;
    mt["isEqual"] = &QPalette::isEqual;
    mt["light"] = &QPalette::light;
    mt["link"] = &QPalette::link;
    mt["linkVisited"] = &QPalette::linkVisited;
    mt["mid"] = &QPalette::mid;
    mt["midlight"] = &QPalette::midlight;
    mt["resolve"] = QPalette_resolve;
    mt["setBrush"] = QPalette_setBrush;
    mt["setColor"] = QPalette_setColor;
    mt["setColorGroup"] = QPalette_setColorGroup;
    mt["setCurrentColorGroup"] = &QPalette::setCurrentColorGroup;
    mt["shadow"] = &QPalette::shadow;
    mt["swap"] = &QPalette::swap;
    mt["text"] = &QPalette::text;
    mt["toolTipBase"] = &QPalette::toolTipBase;
    mt["toolTipText"] = &QPalette::toolTipText;
    mt["window"] = &QPalette::window;
    mt["windowText"] = &QPalette::windowText;
}

int QPalette_new(lua_State* const state)
{
    if (lua_gettop(state) < 1) {
        // QPalette()
        lua::make<QPalette>(state);
        return 1;
    }

    if (lua_gettop(state) == 3) {
        // QPalette(const QColor & button, const QColor & window)
        lua::make<QPalette>(state,
            lua::get<const QColor&>(state, 2),
            lua::get<const QColor&>(state, 3)
        );
        return 1;
    }

    if (lua_gettop(state) > 3) {
        // QPalette(const QBrush & windowText, const QBrush & button, const QBrush & light, const QBrush & dark, const QBrush & mid, const QBrush & text, const QBrush & bright_text, const QBrush & base, const QBrush & window)
        lua::make<QPalette>(state,
            lua::get<const QBrush&>(state, 2),
            lua::get<const QBrush&>(state, 3),
            lua::get<const QBrush&>(state, 4),
            lua::get<const QBrush&>(state, 5),
            lua::get<const QBrush&>(state, 6),
            lua::get<const QBrush&>(state, 7),
            lua::get<const QBrush&>(state, 8),
            lua::get<const QBrush&>(state, 9),
            lua::get<const QBrush&>(state, 10)
        );
        return 1;
    }

    auto name = lua::class_name(state, 2);
    if (name == lua::Metatable<QPalette>::name) {
        // QPalette(const QPalette & p)
        lua::make<QPalette>(state,
            lua::get<const QPalette&>(state, 2)
        );
        return 1;
    }

    // QPalette(const QColor& p)
    lua::make<QPalette>(state,
        lua::get<const QColor&>(state, 2)
    );
    return 1;
}

int luaopen_luacxx_QPalette(lua_State* const state)
{
    lua::thread env(state);

    env["QPalette"] = lua::value::table;
    auto t = env["QPalette"];

    t["new"] = QPalette_new;

    // enum QPalette::ColorGroup
    t["Disabled"] = QPalette::Disabled;
    t["Active"] = QPalette::Active;
    t["Inactive"] = QPalette::Inactive;
    t["Normal"] = QPalette::Normal;

    // enum QPalette::ColorRole
    t["Window"] = QPalette::Window;
    t["Background"] = QPalette::Background;
    t["WindowText"] = QPalette::WindowText;
    t["Foreground"] = QPalette::Foreground;
    t["Base"] = QPalette::Base;
    t["AlternateBase"] = QPalette::AlternateBase;
    t["ToolTipBase"] = QPalette::ToolTipBase;
    t["ToolTipText"] = QPalette::ToolTipText;
    t["Text"] = QPalette::Text;
    t["Button"] = QPalette::Button;
    t["ButtonText"] = QPalette::ButtonText;
    t["BrightText"] = QPalette::BrightText;

    t["Light"] = QPalette::Light;
    t["Midlight"] = QPalette::Midlight;
    t["Dark"] = QPalette::Dark;
    t["Mid"] = QPalette::Mid;
    t["Shadow"] = QPalette::Shadow;

    t["Highlight"] = QPalette::Highlight;
    t["HighlightedText"] = QPalette::HighlightedText;

    t["Link"] = QPalette::Link;
    t["LinkVisited"] = QPalette::LinkVisited;

    t["NoRole"] = QPalette::NoRole;

    return 1;
}
