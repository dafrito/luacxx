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

#include "load/DirectoryModuleLoader.hpp"
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

BOOST_AUTO_TEST_CASE(run_file)
{
    auto env = lua::create();
}
