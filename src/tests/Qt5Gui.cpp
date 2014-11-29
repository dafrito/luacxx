#define BOOST_TEST_MODULE Qt5Gui
#include "Qt5Gui.hpp"

#include <boost/test/unit_test.hpp>

#include "thread.hpp"
#include "stack.hpp"
#include "algorithm.hpp"
#include "load.hpp"
#include "reference.hpp"

#include "convert/string.hpp"
#include "convert/char.hpp"
#include "convert/callable.hpp"
#include "convert/numeric.hpp"

#include "Qt5Core/QString.hpp"
#include "Qt5Core/QChar.hpp"
#include "Qt5Core/QVariant.hpp"
#include "Qt5Core/QObject.hpp"

#include <QDir>
#include <QPoint>

#include <QGuiApplication>

struct QGuiApplicationFixture
{
    int argc;
    char name[100];
    char* argv[1];

    QGuiApplication* app;
public:
    QGuiApplicationFixture() :
        argc(1)
    {
        strcpy(name, "luacxx");
        argv[0] = name;
        app = new QGuiApplication(argc, argv);
    }

    ~QGuiApplicationFixture()
    {
        delete app;
    }
};

BOOST_GLOBAL_FIXTURE(QGuiApplicationFixture);

BOOST_AUTO_TEST_CASE(QObject_destruction)
{
    auto env = lua::create();
    env["package"]["cpath"] = ".libs/libluacxx-?.so";

    lua::run_string(env, ""
    "require 'Qt5Gui.QWindow';"
    "require 'Qt5Gui.QDrag';"
    "require 'Qt5Core.QMimeData';"
    "require 'Qt5Core.QCoreApplication';"
    ""
    "win = QWindow.new();\n"
    "drag = QDrag.new(win);\n"
    "md = QMimeData.new();\n"
    "drag:setMimeData(md);\n"
    );

    lua_gc(env, LUA_GCCOLLECT, 0);
}
