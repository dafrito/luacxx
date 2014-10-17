#ifndef LUACXX_QVECTOR_INCLUDED
#define LUACXX_QVECTOR_INCLUDED

#include "Qt5Core.hpp"
#include "../convert/callable.hpp"

#include <QVector>

// http://qt-project.org/doc/qt-5/qvector.html

template <class T>
int QVector_back(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_begin(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_count(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_data(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_end(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_erase(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_first(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_front(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_insert(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_last(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_pop_back(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_pop_front(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_prepend(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_push_back(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_push_front(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_remove(lua_State* const state)
{
    return 0;
}

template <class T>
int QVector_value(lua_State* const state)
{
    return 0;
}

namespace lua {

template <class T>
void QVector_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["append"] = &QVector<T>::append;
    mt["at"] = &QVector<T>::at;
    mt["back"] = &QVector_back<T>;
    mt["begin"] = &QVector_begin<T>;
    mt["capacity"] = &QVector<T>::capacity;
    mt["cbegin"] = &QVector<T>::cbegin;
    mt["cend"] = &QVector<T>::cend;
    mt["clear"] = &QVector<T>::clear;
    mt["constBegin"] = &QVector<T>::constBegin;
    mt["constData"] = &QVector<T>::constData;
    mt["constEnd"] = &QVector<T>::constEnd;
    mt["contains"] = &QVector<T>::contains;
    mt["count"] = &QVector_count<T>;
    mt["data"] = &QVector_data<T>;
    mt["empty"] = &QVector<T>::empty;
    mt["end"] = &QVector_end<T>;
    mt["endsWith"] = &QVector<T>::endsWith;
    mt["erase"] = &QVector_erase<T>;
    mt["fill"] = &QVector<T>::fill;
    mt["first"] = &QVector_first<T>;
    mt["front"] = &QVector_front<T>;
    mt["indexOf"] = &QVector<T>::indexOf;
    mt["insert"] = &QVector_insert<T>;
    mt["isEmpty"] = &QVector<T>::isEmpty;
    mt["last"] = &QVector_last<T>;
    mt["lastIndexOf"] = &QVector<T>::lastIndexOf;
    mt["length"] = &QVector<T>::length;
    mt["mid"] = &QVector<T>::mid;
    mt["pop_back"] = &QVector<T>::pop_back;
    mt["pop_front"] = &QVector<T>::pop_front;
    mt["prepend"] = &QVector<T>::prepend;
    mt["push_back"] = &QVector<T>::push_back;
    mt["push_front"] = &QVector<T>::push_front;
    mt["remove"] = &QVector_remove<T>;
    mt["removeAt"] = &QVector<T>::removeAt;
    mt["removeFirst"] = &QVector<T>::removeFirst;
    mt["removeLast"] = &QVector<T>::removeLast;
    mt["replace"] = &QVector<T>::replace;
    mt["reserve"] = &QVector<T>::reserve;
    mt["resize"] = &QVector<T>::resize;
    mt["size"] = &QVector<T>::size;
    mt["squeeze"] = &QVector<T>::squeeze;
    mt["startsWith"] = &QVector<T>::startsWith;
    mt["swap"] = &QVector<T>::swap;
    mt["takeAt"] = &QVector<T>::takeAt;
    mt["takeFirst"] = &QVector<T>::takeFirst;
    mt["takeLast"] = &QVector<T>::takeLast;
    mt["toList"] = &QVector<T>::toList;
    mt["toStdVector"] = &QVector<T>::toStdVector;
    mt["value"] = &QVector_value<T>;
}

template <class T>
struct Metatable<QVector<T>>
{
    static const userdata_type& info()
    {
        static userdata_type _info;
        std::string str("QVector<");
        str += Metatable<T>::info().name();
        str += ">";
        _info.set_name(str);
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, QVector<T>* pos)
    {
        lua::QVector_metatable<T>(state, mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QVector(lua_State* const);

#endif // LUACXX_QVECTOR_INCLUDED
