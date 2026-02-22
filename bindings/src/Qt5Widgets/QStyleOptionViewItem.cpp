#include "QStyleOptionViewItem.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QFlags.hpp"

namespace lua {

void QStyleOptionViewItem_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QStyleOptionViewItem_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::make<QStyleOptionViewItem>(state);
    } else {
        lua::make<QStyleOptionViewItem>(state,
            lua::get<const QStyleOptionViewItem&>(state, 1)
        );
    }

    return 1;
}

int luaopen_Qt5Widgets_QStyleOptionViewItem(lua_State* const state)
{
    lua::thread env(state);

    env["QStyleOptionViewItem"] = lua::value::table;
    env["QStyleOptionViewItem"]["new"] = QStyleOptionViewItem_new;
    auto t = env["QStyleOptionViewItem"];

    // enum QStyleOptionViewItem::Position
    t["Left"] = QStyleOptionViewItem::Left;
    t["Right"] = QStyleOptionViewItem::Right;
    t["Top"] = QStyleOptionViewItem::Top;
    t["Bottom"] = QStyleOptionViewItem::Bottom;

    // enum QStyleOptionViewItem::StyleOptionType
    t["Type"] = QStyleOptionViewItem::Type;

    // enum QStyleOptionViewItem::StyleOptionVersion
    t["Version"] = QStyleOptionViewItem::Version;

    // enum QStyleOptionViewItem::ViewItemFeature
    t["ViewItemFeatures"] = lua::QFlags_new<QStyleOptionViewItem::ViewItemFeatures>;
    t["None"] = QStyleOptionViewItem::None;
    t["WrapText"] = QStyleOptionViewItem::WrapText;
    t["Alternate"] = QStyleOptionViewItem::Alternate;
    t["HasCheckIndicator"] = QStyleOptionViewItem::HasCheckIndicator;
    t["HasDisplay"] = QStyleOptionViewItem::HasDisplay;
    t["HasDecoration"] = QStyleOptionViewItem::HasDecoration;

    // enum QStyleOptionViewItem::ViewItemPosition
    t["Invalid"] = QStyleOptionViewItem::Invalid;
    t["Beginning"] = QStyleOptionViewItem::Beginning;
    t["Middle"] = QStyleOptionViewItem::Middle;
    t["End"] = QStyleOptionViewItem::End;
    t["OnlyOne"] = QStyleOptionViewItem::OnlyOne;

    return 0;
}
