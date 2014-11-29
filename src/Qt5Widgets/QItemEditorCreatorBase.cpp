#include "QItemEditorCreatorBase.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QWidget.hpp"
#include "../Qt5Core/QByteArray.hpp"

namespace lua {

void QItemEditorCreatorBase_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["createWidget"] = &QItemEditorCreatorBase::createWidget;
    mt["valuePropertyName"] = &QItemEditorCreatorBase::valuePropertyName;
}

} // namespace lua
