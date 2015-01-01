#ifndef luacxx_convert_QVariant_INCLUDED
#define luacxx_convert_QVariant_INCLUDED

#include "../stack.hpp"

#include <QVariant>
#include "../Qt5Core/QVariant.hpp"

// http://doc.qt.io/qt-5/qvariant.html

namespace lua {

template<>
struct Push<QVariant>
{
    static void push(lua_State* const state, QVariant value)
    {
        push_qvariant(state, value);
    }
};

template<>
struct Store<QVariant>
{
    static void store(QVariant& destination, lua_State* const state, const int index)
    {
        store_qvariant(destination, state, index);
    }
};

template<>
struct Get<QVariant>
{
    static QVariant get(lua_State* const state, const int pos)
    {
        return get_qvariant(state, pos);
    }
};

} // namespace lua

#endif // luacxx_convert_QVariant_INCLUDED

