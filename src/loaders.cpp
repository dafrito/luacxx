#include "loaders.hpp"
#include <fstream>
#include <sstream>
#include <QDir>
#include <QFile>
#include <QTextStream>

#include "LuaValue.hpp"

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

    const int CHUNKSIZE = 4096;

    const char* readStdStream(lua_State *, void *data, size_t *size)
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
            } else {
                // Nothing found, so head back to the start of the file
                d->stream.seekg(0);
            }
        }
        if (d->stream.eof()) {
            return NULL;
        }
        d->stream.readsome(d->buffer, CHUNKSIZE);
        if (d->stream.fail()) {
            throw std::runtime_error("Error while reading stream");
        }
        *size = d->stream.gcount();
        return d->buffer;
    }

    const char* readQtStream(lua_State*, void *pstream, size_t *size)
    {
        QtReadingData* d = static_cast<QtReadingData*>(pstream);
        if (d->atStart) {
            d->atStart = false;
            auto firstTwo = d->stream.read(2);
            if (firstTwo == "#!") {
                // Shebang, so ignore the rest of the line
                d->stream.readLine();
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

    void handleLoadValue(LuaStack& stack, const int rv)
    {
        auto state = stack.luaState();
        switch (rv) {
            case LUA_ERRSYNTAX:
                throw LuaException(std::string("Syntax error during compilation: ") + lua_tostring(state, -1));
            case LUA_ERRMEM:
                throw std::runtime_error(std::string("Memory allocation error during compilation: ") + lua_tostring(state, -1));
        }
    }

} // namespace anonymous

namespace lua
{
    void loadFile(LuaStack& stack, QFile& file)
    {
        if (!file.open(QIODevice::ReadOnly)) {
            throw std::runtime_error(
                (QString("Cannot open file ") + file.fileName() + ": " + file.errorString()).toStdString()
            );
        }
        QtReadingData d(file);

        handleLoadValue(stack, lua_load(stack.luaState(), &readQtStream, &d, file.fileName().toUtf8().constData()
            #if LUA_VERSION_NUM >= 502
                // Account for the extra mode parameter introduced in 5.2
                , NULL
            #endif
        ));
    }

    void loadFile(LuaStack& stack, const std::string& file)
    {
        std::ifstream stream(file, std::ios::in);
        if (!stream) {
            throw std::runtime_error(std::string("File stream could not be opened for '") + file + "'");
        }
        loadFile(stack, stream, file);
    }

    void loadFile(LuaStack& stack, std::istream& stream, const std::string& name)
    {
        LuaReadingData d(stream);
        if (!stream) {
            throw std::runtime_error(std::string("Input stream is invalid for '") + name + "'");
        }

        handleLoadValue(stack, lua_load(stack.luaState(), &readStdStream, &d, name.c_str()
            #if LUA_VERSION_NUM >= 502
                // Account for the extra mode parameter introduced in 5.2
                , NULL
            #endif
        ));
    }

    void loadFile(LuaStack& stack, const char* file)
    {
        loadFile(stack, std::string(file));
    }

    void loadString(LuaStack& stack, const std::string& input)
    {
        loadString(stack, input.c_str());
    }

    void loadString(LuaStack& stack, const char* input)
    {
        handleLoadValue(stack, luaL_loadstring(stack.luaState(), input));
    }

    void runDir(LuaStack& stack, const QDir& dir, const bool recurse)
    {
        foreach(QFileInfo info, dir.entryInfoList(
            (recurse ? QDir::AllEntries : QDir::Files) | QDir::NoDotAndDotDot,
            QDir::Name
            ))
        {
            if (info.isFile()) {
                QFile file(info.filePath());
                runFile(stack, file);
            } else if (recurse && info.isDir()) {
                runDir(stack, info.filePath(), recurse);
            }
        }
    }

    void runDir(LuaEnvironment& lua, const QDir& dir, const bool recurse)
    {
        LuaStack stack(lua);
        runDir(stack, dir, recurse);
    }

} // namespace lua
