#include "QVector.hpp"

/*

QVector()
QVector(int size)
QVector(int size, const T & value)
QVector(const QVector<T> & other)
QVector(QVector<T> && other)
QVector(std::initializer_list<T> args)

*/
int QVector_new(lua_State* const state)
{
    // XXX Can this be done in a reasonable manner?
    return 0;
}

int luaopen_Qt5Core_QVector(lua_State* const state)
{
    lua::thread env(state);

    env["QVector"] = lua::value::table;
    env["QVector"]["new"] = QVector_new;

    //QVector<T>  fromList(const QList<T> & list)
    //QVector<T>  fromStdVector(const std::vector<T> & vector)

    return 0;
}
