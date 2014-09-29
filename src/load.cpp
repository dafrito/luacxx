#include "load.hpp"
#include "error.hpp"

#include <fstream>
#include <sstream>

namespace {
    struct LuaReadingData
    {
        std::istream& stream;
        char buffer[4096];
        bool atStart;
        LuaReadingData(std::istream& stream) :
            stream(stream),
            atStart(true)
        {
        }
    };

    const int CHUNKSIZE = 4096;
    const char EMPTY_LINE = '\n';

    const char* readStdStream(lua_State* const, void* data, size_t* size)
    {
        LuaReadingData* d = static_cast<LuaReadingData*>(data);
        if (d->atStart) {
            d->atStart = false;
            d->stream.read(d->buffer, 2);
            if (d->stream.eof()) {
                // This can occur if insufficient characters were read
                return NULL;
            }
            d->buffer[2] = '\0';
            if (std::string(d->buffer) == "#!") {
                // Shebang, so ignore the rest of the line
                std::string shebangLine;
                std::getline(d->stream, shebangLine);

                // Return a newline so line counts are correct
                *size = 1;
                return &EMPTY_LINE;
            } else {
                // Nothing found, so head back to the start of the file
                d->stream.seekg(0);
            }
        }
        if (d->stream.eof()) {
            return NULL;
        }
        d->stream.read(d->buffer, CHUNKSIZE);
        switch (d->stream.rdstate()) {
            case std::ifstream::failbit:
            throw std::runtime_error("std::ifstream::failbit: A logical error occurred on a I/O operation.");
            break;

            case std::ifstream::badbit:
            throw std::runtime_error("std::ifstream::badbit: A read/writing error occurred on a I/O operation.");
            break;

            default:
            break;
        }
        *size = d->stream.gcount();
        return d->buffer;
    }

    lua::index do_post_load(lua_State* const state, const int rv)
    {
        switch (rv) {
            case LUA_ERRSYNTAX:
                throw lua::error(std::string("Syntax error during compilation:\n") + lua_tostring(state, -1));
            case LUA_ERRMEM:
                throw std::runtime_error(std::string("Memory allocation error during compilation:\n") + lua_tostring(state, -1));
        }
        return lua::index(state, -1);
    }

} // namespace anonymous

lua::index lua::load_file(lua_State* const state, const std::string& file)
{
    std::ifstream stream(file, std::ios::in);
    if (!stream) {
        throw std::runtime_error(std::string("File stream could not be opened for '") + file + "'");
    }

    return lua::load_file(state, stream, file);
}

lua::index lua::load_file(lua_State* const state, std::istream& stream, const std::string& name)
{
    LuaReadingData d(stream);
    if (!stream) {
        throw std::runtime_error(std::string("Input stream is invalid for '") + name + "'");
    }

    return do_post_load(state, lua_load(state, &readStdStream, &d, name.c_str()
        #if LUA_VERSION_NUM >= 502
            // Account for the extra mode parameter introduced in 5.2
            , NULL
        #endif
    ));
}

lua::index lua::load_file(lua_State* const state, const char* filename)
{
    return lua::load_file(state, std::string(filename));
}

lua::index lua::load_string(lua_State* const state, const std::string& input)
{
    return lua::load_string(state, input.c_str());
}

lua::index lua::load_string(lua_State* const state, const char* input)
{
    do_post_load(state, luaL_loadstring(state, input));
    return lua::index(state, -1);
}

#ifdef HAVE_Qt5Core

#include <QDir>
#include <QFile>
#include <QTextStream>

namespace {

struct QtReadingData
{
    QTextStream stream;
    QByteArray chunk;
    bool atStart;
    QtReadingData(QFile& file) :
        stream(&file),
        atStart(true)
    {
    }
};

const char* readQtStream(lua_State*, void *pstream, size_t *size)
{
    QtReadingData* d = static_cast<QtReadingData*>(pstream);
    if (d->atStart) {
        d->atStart = false;
        auto firstTwo = d->stream.read(2);
        if (firstTwo == "#!") {
            // Shebang, so ignore the rest of the line
            d->stream.readLine();

            // Return a newline so line counts are correct
            *size = 1;
            return &EMPTY_LINE;
        } else {
            // Nothing found, so head back to the start of the file
            d->stream.seek(0);
        }
    }
    if (d->stream.atEnd()) {
        return NULL;
    }
    d->chunk = d->stream.read(CHUNKSIZE).toUtf8();
    *size = d->chunk.size();
    return d->chunk.constData();
}

} // namespace anonymous

lua::index lua::load_file(lua_State* const state, const QString& filename)
{
    QFile file(filename);
    return lua::load_file(state, file);
}

lua::index lua::load_file(lua_State* const state, QFile& file)
{
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error(
            (QString("Cannot open file ") + file.fileName() + ": " + file.errorString()).toStdString()
        );
    }
    QtReadingData d(file);

    return do_post_load(state, lua_load(state, &readQtStream, &d, file.fileName().toUtf8().constData()
        #if LUA_VERSION_NUM >= 502
            // Account for the extra mode parameter introduced in 5.2
            , NULL
        #endif
    ));
}

void lua::run_dir(lua_State* const state, const QDir& dir, const bool recurse)
{
    foreach(QFileInfo info, dir.entryInfoList(
        (recurse ? QDir::AllEntries : QDir::Files) | QDir::NoDotAndDotDot,
        QDir::Name
        ))
    {
        if (info.isFile()) {
            QFile file(info.filePath());
            lua::run_file(state, file);
        } else if (recurse && info.isDir()) {
            lua::run_dir(state, info.filePath(), recurse);
        }
    }
}

#endif // HAVE_Qt5Core
