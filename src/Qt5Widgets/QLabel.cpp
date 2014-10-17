#include "QLabel.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QLabel>

#include "QFrame.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Gui/QMovie.hpp"
#include "../Qt5Gui/QPicture.hpp"
#include "../Qt5Gui/QPixmap.hpp"
#include "QWidget.hpp"

void lua::QLabel_metatable(lua_State* const state, const int pos)
{
    lua::QFrame_metatable(state, pos);

    lua::index mt(state, pos);
    mt["alignment"] = &QLabel::alignment;
    mt["buddy"] = &QLabel::buddy;
    mt["hasScaledContents"] = &QLabel::hasScaledContents;
    mt["hasSelectedText"] = &QLabel::hasSelectedText;
    mt["indent"] = &QLabel::indent;
    mt["margin"] = &QLabel::margin;
    mt["movie"] = &QLabel::movie;
    mt["openExternalLinks"] = &QLabel::openExternalLinks;
    mt["picture"] = &QLabel::picture;
    mt["pixmap"] = &QLabel::pixmap;
    mt["selectedText"] = &QLabel::selectedText;
    mt["selectionStart"] = &QLabel::selectionStart;
    mt["setAlignment"] = &QLabel::setAlignment;
    mt["setBuddy"] = &QLabel::setBuddy;
    mt["setIndent"] = &QLabel::setIndent;
    mt["setMargin"] = &QLabel::setMargin;
    mt["setOpenExternalLinks"] = &QLabel::setOpenExternalLinks;
    mt["setScaledContents"] = &QLabel::setScaledContents;
    mt["setSelection"] = &QLabel::setSelection;
    mt["setTextFormat"] = &QLabel::setTextFormat;
    mt["setTextInteractionFlags"] = &QLabel::setTextInteractionFlags;
    mt["setWordWrap"] = &QLabel::setWordWrap;
    mt["text"] = &QLabel::text;
    mt["textFormat"] = &QLabel::textFormat;
    mt["textInteractionFlags"] = &QLabel::textInteractionFlags;
    mt["wordWrap"] = &QLabel::wordWrap;
}

int QLabel_new(lua_State* const state)
{
    // QLabel(QWidget * parent = 0, Qt::WindowFlags f = 0)
    // QLabel(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0)
    lua::make<QLabel>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Widgets_QLabel(lua_State* const state)
{
    lua::thread env(state);

    env["QLabel"] = lua::value::table;
    env["QLabel"]["new"] = QLabel_new;

    return 0;
}
