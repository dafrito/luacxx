#ifndef luacxx_QSqlDriverCreator_INCLUDED
#define luacxx_QSqlDriverCreator_INCLUDED

#include "../stack.hpp"
#include "../index.hpp"

#include <QSqlDriverCreator>

#include "QSqlDriverCreatorBase.hpp"

// http://qt-project.org/doc/qt-5/qsqldrivercreator.html

namespace lua {

template <class T>
void QSqlDriverCreator_metatable(lua_State* const state, const int pos)
{
    lua::QSqlDriverCreatorBase_metatable(state, pos);

    lua::index mt(state, pos);

    mt["createObject"] = &QSqlDriverCreator<T>::createObject;
}

template <class T>
struct Metatable<QSqlDriverCreator<T>>
{
    static const userdata_type& info()
    {
        static userdata_type _info;
        if (!_info.has_name()) {
            std::string str("QSqlDriverCreator<");
            str += Metatable<T>::info().name();
            str += ">";
            _info.set_name(str);
        }
        _info.add_cast<QSqlDriverCreatorBase, QSqlDriverCreator<T>>();
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, QSqlDriverCreator<T>* const)
    {
        lua::QSqlDriverCreator_metatable<T>(state, mt);
        return true;
    }
};

} // namespace lua

#endif // luacxx_QSqlDriverCreator_INCLUDED
