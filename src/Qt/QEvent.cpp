#include "QEvent.hpp"
#include "../type/function.hpp"
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

void lua::QResizeEvent_metatable(const lua::index& mt)
{
    lua::QEvent_metatable(mt);

    mt["oldSize"] = &QResizeEvent::oldSize;
    mt["size"] = &QResizeEvent::size;
}

void lua::QExposeEvent_metatable(const lua::index& mt)
{
    lua::QEvent_metatable(mt);
    mt["region"] = &QExposeEvent::region;
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

int luaopen_luacxx_QEvent(lua::state* const state)
{
    lua::thread env(state);

    env["QEvent"] = lua::value::table;
    env["QEvent"]["Close"] = "QEvent.Close";
    env["QEvent"]["Enter"] = "QEvent.Enter";
    env["QEvent"]["Expose"] = "QEvent.Expose";
    env["QEvent"]["Hide"] = "QEvent.Hide";
    env["QEvent"]["MouseButtonDblClick"] = "QEvent.MouseButtonDblClick";
    env["QEvent"]["MouseButtonPress"] = "QEvent.MouseButtonPress";
    env["QEvent"]["MouseButtonRelease"] = "QEvent.MouseButtonRelease";
    env["QEvent"]["MouseMove"] = "QEvent.MouseMove";
    env["QEvent"]["Move"] = "QEvent.Move";
    env["QEvent"]["Resize"] = "QEvent.Resize";
    env["QEvent"]["Show"] = "QEvent.Show";
    env["QEvent"]["WindowStateChange"] = "QEvent.WindowStateChange";
    env["QEvent"]["Leave"] = "QEvent.Leave";

    return 0;
}
