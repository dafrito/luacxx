#ifndef luacxx_QList_INCLUDED
#define luacxx_QList_INCLUDED

#include "Qt5Core.hpp"
#include "../convert/callable.hpp"

#include <QList>

// http://qt-project.org/doc/qt-5/qlist.html

namespace lua {

template <class T>
void QList_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

    mt["append"] = lua::callable([](lua_State* const state) {
        auto self = lua::get<QList<T>*>(state, 1);
        if (lua::is_type<T>(state, 2)) {
            self->append(lua::get<const T&>(state, 2));
        } else {
            self->append(lua::get<const QList<T>&>(state, 2));
        }
        return 0;
    });

    mt["at"] = &QList<T>::at;

    mt["back"] = lua::callable([](lua_State* const state) {
        auto self = lua::get<QList<T>*>(state, 1);
        lua::push(state, self->back());
        return 1;
    });

    mt["clear"] = &QList<T>::clear;
    mt["count"] = lua::callable([](lua_State* const state) {
        auto self = lua::get<QList<T>*>(state, 1);
        if (lua::size(state) == 1) {
            lua::push(state, self->count());
        } else {
            lua::push(state,
                self->count(lua::Get<const T&>::get(state, 2))
            );
        }
        return 0;
    });
    mt["empty"] = &QList<T>::empty;
    mt["length"] = &QList<T>::length;
    mt["size"] = &QList<T>::size;
    mt["contains"] = &QList<T>::contains;
    mt["isEmpty"] = &QList<T>::isEmpty;
    mt["move"] = &QList<T>::move;
    mt["pop_back"] = &QList<T>::pop_back;
    mt["pop_front"] = &QList<T>::pop_front;
    mt["prepend"] = &QList<T>::prepend;
    mt["push_back"] = &QList<T>::push_back;
    mt["push_front"] = &QList<T>::push_front;
    mt["removeAll"] = &QList<T>::removeAll;
    mt["removeAt"] = &QList<T>::removeAt;
    mt["removeFirst"] = &QList<T>::removeFirst;
    mt["removeLast"] = &QList<T>::removeLast;
    mt["removeOne"] = &QList<T>::removeOne;
    mt["replace"] = &QList<T>::replace;
    mt["reserve"] = &QList<T>::reserve;
    mt["startsWith"] = &QList<T>::startsWith;
    mt["swap"] = lua::callable([](lua_State* const state) {
        auto self = lua::get<QList<T>*>(state, 1);
        if (lua::index(state, 2).type().number()) {
            self->swap(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3)
            );
        } else {
            self->swap(lua::get<QList<T>&>(state, 2));
        }
        return 0;
    });
    mt["takeAt"] = &QList<T>::takeAt;
    mt["takeFirst"] = &QList<T>::takeFirst;
    mt["takeLast"] = &QList<T>::takeLast;
    mt["value"] = lua::callable([](lua_State* const state) {
        auto self = lua::get<QList<T>*>(state, 1);
        if (lua::size(state) > 2) {
            lua::push(state, self->value(
                lua::get<int>(state, 2),
                lua::get<const T&>(state, 3)
            ));
        } else {
            lua::push(state, self->value(
                lua::get<int>(state, 2)
            ));
        }
        return 0;
    });

    /*iterator    begin()
    const_iterator  begin() const
    const_iterator  cbegin() const
    const_iterator  cend() const
    const_iterator  constBegin() const
    const_iterator  constEnd() const
    iterator    end()
    const_iterator  end() const
    bool    endsWith(const T & value) const
    iterator    erase(iterator pos)
    iterator    erase(iterator begin, iterator end)
    T &     first()
    const T &   first() const
    T &     front()
    const T &   front() const
    int     indexOf(const T & value, int from = 0) const
    void    insert(int i, const T & value)
    iterator    insert(iterator before, const T & value)
    T &     last()
    const T &   last() const
    int     lastIndexOf(const T & value, int from = -1) const
    QList<T>    mid(int pos, int length = -1) const
    QSet<T>     toSet() const
    std::list<T>    toStdList() const
    QVector<T>  toVector() const
    bool    operator!=(const QList<T> & other) const
    QList<T>    operator+(const QList<T> & other) const
    QList<T> &  operator+=(const QList<T> & other)
    QList<T> &  operator+=(const T & value)
    QList<T> &  operator<<(const QList<T> & other)
    QList<T> &  operator<<(const T & value)
    QList<T> &  operator=(const QList<T> & other)
    QList &     operator=(QList<T> && other)
    bool    operator==(const QList<T> & other) const
    T &     operator[](int i)
    const T &   operator[](int i) const*/
}

template <class T>
struct Metatable<QList<T>>
{
    static const userdata_type& info()
    {
        static userdata_type _info;
        if (!_info.has_name()) {
            std::string str("QList<");
            str += Metatable<T>::info().name();
            str += ">";
            _info.set_name(str);

            _info.add_cast<QList<T>>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, QList<T>* const)
    {
        lua::QList_metatable<T>(state, mt);
        return true;
    }
};

}; // namespace lua

#endif // luacxx_QList_INCLUDED
