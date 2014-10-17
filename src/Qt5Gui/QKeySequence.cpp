#include "QKeySequence.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QKeySequence>

#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QList.hpp"

int QKeySequence_toString(lua_State* const state)
{
    return 0;
}

void lua::QKeySequence_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["count"] = &QKeySequence::count;
    mt["isEmpty"] = &QKeySequence::isEmpty;
    mt["matches"] = &QKeySequence::matches;
    mt["swap"] = &QKeySequence::swap;
    mt["toString"] = QKeySequence_toString;
}

int QKeySequence_new(lua_State* const state)
{
    // QKeySequence()
    // QKeySequence(const QString & key, SequenceFormat format = NativeText)
    // QKeySequence(int k1, int k2 = 0, int k3 = 0, int k4 = 0)
    // QKeySequence(const QKeySequence & keysequence)
    // QKeySequence(StandardKey key)
    lua::make<QKeySequence>(state);
    // TODO Set up object-specific methods

    return 1;
}

int QKeySequence_fromString(lua_State* const state)
{
    return 0;
}

int QKeySequence_listFromString(lua_State* const state)
{
    return 0;
}
int QKeySequence_listToString(lua_State* const state)
{
    return 0;
}

int luaopen_Qt5Gui_QKeySequence(lua_State* const state)
{
    lua::thread env(state);

    env["QKeySequence"] = lua::value::table;
    env["QKeySequence"]["new"] = QKeySequence_new;
    auto t = env["QKeySequence"];

    t["mnemonic"] = QKeySequence_fromString;
    t["keyBindings"] = &QKeySequence::keyBindings;
    t["listFromString"] = QKeySequence_listFromString;
    t["listToString"] = QKeySequence_listToString;
    t["mnemonic"] = &QKeySequence::mnemonic;

    // enum QKeySequence::SequenceFormat
    t["NativeText"] = QKeySequence::NativeText;
    t["PortableText"] = QKeySequence::PortableText;

    // enum QKeySequence::SequenceMatch
    t["NoMatch"] = QKeySequence::NoMatch;
    t["PartialMatch"] = QKeySequence::PartialMatch;
    t["ExactMatch"] = QKeySequence::ExactMatch;

    // enum QKeySequence::StandardKey
    t["AddTab"] = QKeySequence::AddTab;
    t["Back"] = QKeySequence::Back;
    t["Bold"] = QKeySequence::Bold;
    t["Close"] = QKeySequence::Close;
    t["Copy"] = QKeySequence::Copy;
    t["Cut"] = QKeySequence::Cut;
    t["Delete"] = QKeySequence::Delete;
    t["DeleteEndOfLine"] = QKeySequence::DeleteEndOfLine;
    t["DeleteEndOfWord"] = QKeySequence::DeleteEndOfWord;
    t["DeleteStartOfWord"] = QKeySequence::DeleteStartOfWord;
    t["DeleteCompleteLine"] = QKeySequence::DeleteCompleteLine;
    t["Find"] = QKeySequence::Find;
    t["FindNext"] = QKeySequence::FindNext;
    t["FindPrevious"] = QKeySequence::FindPrevious;
    t["Forward"] = QKeySequence::Forward;
    t["HelpContents"] = QKeySequence::HelpContents;
    t["InsertLineSeparator"] = QKeySequence::InsertLineSeparator;
    t["InsertParagraphSeparator"] = QKeySequence::InsertParagraphSeparator;
    t["Italic"] = QKeySequence::Italic;
    t["MoveToEndOfBlock"] = QKeySequence::MoveToEndOfBlock;
    t["MoveToEndOfDocument"] = QKeySequence::MoveToEndOfDocument;
    t["MoveToEndOfLine"] = QKeySequence::MoveToEndOfLine;
    t["MoveToNextChar"] = QKeySequence::MoveToNextChar;
    t["MoveToNextLine"] = QKeySequence::MoveToNextLine;
    t["MoveToNextPage"] = QKeySequence::MoveToNextPage;
    t["MoveToNextWord"] = QKeySequence::MoveToNextWord;
    t["MoveToPreviousChar"] = QKeySequence::MoveToPreviousChar;
    t["MoveToPreviousLine"] = QKeySequence::MoveToPreviousLine;
    t["MoveToPreviousPage"] = QKeySequence::MoveToPreviousPage;
    t["MoveToPreviousWord"] = QKeySequence::MoveToPreviousWord;
    t["MoveToStartOfBlock"] = QKeySequence::MoveToStartOfBlock;
    t["MoveToStartOfDocument"] = QKeySequence::MoveToStartOfDocument;
    t["MoveToStartOfLine"] = QKeySequence::MoveToStartOfLine;
    t["New"] = QKeySequence::New;
    t["NextChild"] = QKeySequence::NextChild;
    t["Open"] = QKeySequence::Open;
    t["Paste"] = QKeySequence::Paste;
    t["Preferences"] = QKeySequence::Preferences;
    t["PreviousChild"] = QKeySequence::PreviousChild;
    t["Print"] = QKeySequence::Print;
    t["Quit"] = QKeySequence::Quit;
    t["Redo"] = QKeySequence::Redo;
    t["Refresh"] = QKeySequence::Refresh;
    t["Replace"] = QKeySequence::Replace;
    t["SaveAs"] = QKeySequence::SaveAs;
    t["Save"] = QKeySequence::Save;
    t["SelectAll"] = QKeySequence::SelectAll;
    t["Deselect"] = QKeySequence::Deselect;
    t["SelectEndOfBlock"] = QKeySequence::SelectEndOfBlock;
    t["SelectEndOfDocument"] = QKeySequence::SelectEndOfDocument;
    t["SelectEndOfLine"] = QKeySequence::SelectEndOfLine;
    t["SelectNextChar"] = QKeySequence::SelectNextChar;
    t["SelectNextLine"] = QKeySequence::SelectNextLine;
    t["SelectNextPage"] = QKeySequence::SelectNextPage;
    t["SelectNextWord"] = QKeySequence::SelectNextWord;
    t["SelectPreviousChar"] = QKeySequence::SelectPreviousChar;
    t["SelectPreviousLine"] = QKeySequence::SelectPreviousLine;
    t["SelectPreviousPage"] = QKeySequence::SelectPreviousPage;
    t["SelectPreviousWord"] = QKeySequence::SelectPreviousWord;
    t["SelectStartOfBlock"] = QKeySequence::SelectStartOfBlock;
    t["SelectStartOfDocument"] = QKeySequence::SelectStartOfDocument;
    t["SelectStartOfLine"] = QKeySequence::SelectStartOfLine;
    t["Underline"] = QKeySequence::Underline;
    t["Undo"] = QKeySequence::Undo;
    t["UnknownKey"] = QKeySequence::UnknownKey;
    t["WhatsThis"] = QKeySequence::WhatsThis;
    t["ZoomIn"] = QKeySequence::ZoomIn;
    t["ZoomOut"] = QKeySequence::ZoomOut;
    t["FullScreen"] = QKeySequence::FullScreen;

    return 0;
}
