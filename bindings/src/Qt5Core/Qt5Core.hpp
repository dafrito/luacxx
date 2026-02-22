#ifndef luacxx_Qt5Core_INCLUDED
#define luacxx_Qt5Core_INCLUDED

#include "../stack.hpp"

#include "../convert/numeric.hpp"
#include "../convert/const_char_p.hpp"
#include "../convert/string.hpp"
#include "../convert/char.hpp"
#include "../convert/callable.hpp"

#include "QString.hpp"

#include "../algorithm.hpp"

lua::index load_file(lua_State* const state, QFile& file);
lua::index load_file(lua_State* const state, const QString& filename);

/*
=head2 lua::index run_dir(state, const QDir&, bool recurse)

Runs every file in the specified directory, optionally recursing into
subdirectories.

By default, QDir will include every file, so if you want to filter the files,
specify a filter list on the directory itself:

    QDir dir = QDir::current();
    dir.setFilters(QDir::Files);

    QStringList filters;
    filters << "*.lua";
    dir.setNameFilters(filters);

    lua::run_dir(state, dir, true);

*/
void run_dir(lua_State* const state, const QDir& dir, const bool recurse);

#endif // luacxx_Qt5Core_INCLUDED
