#include "QItemEditorFactory.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QByteArray.hpp"
#include "QWidget.hpp"
#include "QItemEditorCreatorBase.hpp"

namespace lua {

void QItemEditorFactory_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["createEditor"] = &QItemEditorFactory::createEditor;
    mt["registerEditor"] = &QItemEditorFactory::registerEditor;
    mt["valuePropertyName"] = &QItemEditorFactory::valuePropertyName;
}

} // namespace lua

int QItemEditorFactory_new(lua_State* const state)
{
    lua::make<QItemEditorFactory>(state);

    return 1;
}

int luaopen_Qt5Widgets_QItemEditorFactory(lua_State* const state)
{
    lua::thread env(state);

    env["QItemEditorFactory"] = lua::value::table;
    env["QItemEditorFactory"]["new"] = QItemEditorFactory_new;
    auto t = env["QItemEditorFactory"];

    t["defaultFactory"] = QItemEditorFactory::defaultFactory;
    t["setDefaultFactory"] = QItemEditorFactory::setDefaultFactory;

    return 0;
}
