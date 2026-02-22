#include <QDir>
#include <QFile>
#include <QTextStream>

#include "Qt5Core.hpp"

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

} // namespace anonymous
