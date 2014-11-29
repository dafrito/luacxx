#define BOOST_TEST_MODULE Qt5Widgets
#include "Qt5Widgets.hpp"

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

#include "load/DirectoryModuleLoader.hpp"
#include <QDir>
#include <QPoint>

#include <QApplication>

struct QApplicationFixture
{
    int argc;
    char name[100];
    char* argv[1];

    QApplication* app;
public:
    QApplicationFixture() :
        argc(1)
    {
        strcpy(name, "luacxx");
        argv[0] = name;
        app = new QApplication(argc, argv);
    }

    ~QApplicationFixture()
    {
        delete app;
    }
};

BOOST_GLOBAL_FIXTURE(QApplicationFixture);

BOOST_AUTO_TEST_CASE(Qt5Widgets_QGraphicsScene)
{
    auto env = lua::create();
    env["package"]["cpath"] = ".libs/libluacxx-?.so";

    BOOST_REQUIRE(qApp != nullptr);

    lua::run_string(env, "require 'Qt5Widgets.QGraphicsScene'");
    lua::run_string(env, "require 'Qt5Widgets.QGraphicsObject'");
    lua::run_string(env, "foo = QGraphicsScene.new()");
}
