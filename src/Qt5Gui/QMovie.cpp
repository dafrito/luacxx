#include "QMovie.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QMovie>

#include "../Qt5Core/QObject.hpp"
#include "QColor.hpp"
#include "QImage.hpp"
#include "QPixmap.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QIODevice.hpp"
#include "../Qt5Core/QByteArray.hpp"

// https://qt-project.org/doc/qt-5/qmovie.html

void lua::QMovie_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);

    mt["backgroundColor"] = &QMovie::backgroundColor;
    mt["cacheMode"] = &QMovie::cacheMode;
    mt["currentFrameNumber"] = &QMovie::currentFrameNumber;
    mt["currentImage"] = &QMovie::currentImage;
    mt["currentPixmap"] = &QMovie::currentPixmap;
    mt["device"] = &QMovie::device;
    mt["fileName"] = &QMovie::fileName;
    mt["format"] = &QMovie::format;
    mt["frameCount"] = &QMovie::frameCount;
    mt["frameRect"] = &QMovie::frameRect;
    mt["isValid"] = &QMovie::isValid;
    mt["jumpToFrame"] = &QMovie::jumpToFrame;
    mt["loopCount"] = &QMovie::loopCount;
    mt["nextFrameDelay"] = &QMovie::nextFrameDelay;
    mt["scaledSize"] = &QMovie::scaledSize;
    mt["setBackgroundColor"] = &QMovie::setBackgroundColor;
    mt["setCacheMode"] = &QMovie::setCacheMode;
    mt["setDevice"] = &QMovie::setDevice;
    mt["setFileName"] = &QMovie::setFileName;
    mt["setFormat"] = &QMovie::setFormat;
    mt["setScaledSize"] = &QMovie::setScaledSize;
    mt["speed"] = &QMovie::speed;
    mt["state"] = &QMovie::state;

}

int QMovie_new(lua_State* const state)
{
    // QMovie(QObject * parent = 0)
    // QMovie(QIODevice * device, const QByteArray & format = QByteArray(), QObject * parent = 0)
    // QMovie(const QString & fileName, const QByteArray & format = QByteArray(), QObject * parent = 0)
    lua::make<QMovie>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Gui_QMovie(lua_State* const state)
{
    lua::thread env(state);

    env["QMovie"] = lua::value::table;
    env["QMovie"]["new"] = QMovie_new;
    auto t = env["QMovie"];

    // enum QMovie::CacheMode
    t["CacheNone"] = QMovie::CacheNone;
    t["CacheAll"] = QMovie::CacheAll;

    // enum QMovie::MovieState
    t["NotRunning"] = QMovie::NotRunning;
    t["Paused"] = QMovie::Paused;
    t["Running"] = QMovie::Running;

    return 0;
}
