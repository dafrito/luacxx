#include "Qt5Core.hpp"

#include <boost/test/unit_test.hpp>

#include "luacxx/thread.hpp"
#include "luacxx/stack.hpp"
#include "luacxx/algorithm.hpp"
#include "luacxx/load.hpp"
#include "luacxx/reference.hpp"

#include "luacxx/convert/string.hpp"
#include "luacxx/convert/char.hpp"
#include "luacxx/convert/callable.hpp"
#include "luacxx/convert/numeric.hpp"

#include "Qt5Core/QString.hpp"
#include "Qt5Core/QChar.hpp"
#include "Qt5Core/QVariant.hpp"
#include "Qt5Core/QObject.hpp"

#include "luacxx/module/DirectoryModuleLoader.hpp"
#include <QDir>
#include <QPoint>

#include <QCoreApplication>

struct QCoreApplicationFixture
{
    int argc;
    char name[100];
    char* argv[1];

    QCoreApplication* app;
public:
    QCoreApplicationFixture() :
        argc(1)
    {
        strcpy(name, "luacxx");
        argv[0] = name;
        app = new QCoreApplication(argc, argv);
    }

    ~QCoreApplicationFixture()
    {
        delete app;
    }
};

BOOST_GLOBAL_FIXTURE(QCoreApplicationFixture);

BOOST_AUTO_TEST_CASE(run_file)
{
    auto env = lua::create();

    QFile file(TEST_DIR "command/assert_No_is_Time.lua");
    env["No"] = "Time";
    lua::run_file(env, file);

    // run_file throws on a missing file
    BOOST_CHECK_THROW(
        lua::run_file(env, "somemissingfile.lua"),
        std::runtime_error
    );

    // Does the parameterized version return the first argument?
    QFile falseFile(TEST_DIR "command/return_false.lua");
    BOOST_CHECK_EQUAL(lua::run_file<bool>(env, falseFile), false);

    QFile trueFile(TEST_DIR "command/return_true.lua");
    BOOST_CHECK_EQUAL(lua::run_file<bool>(env, trueFile), true);

    lua::run_dir(env, QDir(TEST_DIR "command"), true);
    BOOST_CHECK_EQUAL(lua::get<int>(env["a"]), 42);
    BOOST_CHECK_EQUAL(lua::get<const char*>(env["b"]), "foo");
}

BOOST_AUTO_TEST_CASE(qstring)
{
    auto env = lua::create();

    env << QString("c");
    BOOST_CHECK(lua::get<QString>(env, 1) == QString("c"));
}

BOOST_AUTO_TEST_CASE(qchar)
{
    auto env = lua::create();

    env << QChar('c');
    BOOST_CHECK(lua::get<QChar>(env, 1) == QChar('c'));
}

BOOST_AUTO_TEST_CASE(qvariant)
{
    auto env = lua::create();

    // Can QVariants be passed to Lua?
    env["foo"] = QVariant(42);

    // Are QVariants automatically converted to numbers?
    BOOST_CHECK_EQUAL(env["foo"].get<int>(), 42);

    lua::set_qvariant_push_handler(QVariant::Point, [](lua_State* const state, const QVariant& source) {
        auto point = source.toPoint();
        auto table = lua::push(state, lua::value::table);

        lua::table::set(table, "x", point.x());
        lua::table::set(table, "y", point.y());
    });

    lua::set_qvariant_store_handler(QVariant::Point, [](QVariant& destination, const lua::index& source) {
        destination.setValue(QPoint(
            lua::table::get<int>(source, "x"),
            lua::table::get<int>(source, "y")
        ));
    });

    env["point"] = QVariant(QPoint(2, 3));
    BOOST_CHECK_EQUAL(2, lua::table::get<int>(env["point"], "x"));
    BOOST_CHECK_EQUAL(3, lua::table::get<int>(env["point"], "y"));

    lua::run_string(env, "point.x = 4; point.y = 6");

    QVariant pointVariant(QVariant::Point);
    env["point"] >> pointVariant;
    BOOST_CHECK_EQUAL(4, pointVariant.toPoint().x());
    BOOST_CHECK_EQUAL(6, pointVariant.toPoint().y());
}

BOOST_AUTO_TEST_CASE(qobject_properties)
{
    auto env = lua::create();

    auto point = std::make_shared<QtPoint>(2, 2);
    env["point"] = point;

    // Can QObject properties be accessed from lua?
    lua::run_string(env, "bar = point.x");
    BOOST_CHECK_EQUAL(env["bar"].get<int>(), 2);

    // Can QObject properties be modified from lua?
    lua::run_string(env, "point.x = 24");
    BOOST_CHECK_EQUAL(point->getX(), 24);

    // Do invalid QObject property names throw errors?
    env["point"] = point;
    BOOST_CHECK_THROW(lua::run_string(env, "point.a_missing_value = 24"), lua::error);

    // Can simple algorithms be run on points?
    point->setX(2);
    point->setY(2);
    lua::run_string(env,
    "function work(point, delta)"
    "    delta = delta or 1;"
    "    point.x = point.x + delta;"
    "    point.y = point.y + delta;"
    "end;");
    lua::call(env["work"], point, 3);
    BOOST_CHECK_EQUAL(point->getX(), 5);
    BOOST_CHECK_EQUAL(point->getY(), 5);
}

BOOST_AUTO_TEST_CASE(qobject_signals)
{
    auto env = lua::create();

    QtPoint point;
    env["point"] = &point;
    lua::run_string(env,
    "remover = point:connect('xChanged', function()"
    "    flag = point.x;"
    "end)");

    // Are slots actually invoked?
    BOOST_CHECK_NO_THROW(point.setX(3));
    BOOST_CHECK_EQUAL(env["flag"].get<int>(), 3);

    // Is the remover idempotent?
    lua::run_string(env, "remover()");
    lua::run_string(env, "remover()");

    // Does the remover actually work?
    BOOST_CHECK_NO_THROW(point.setX(6));
    BOOST_CHECK_EQUAL(env["flag"].get<int>(), 3);
}

BOOST_AUTO_TEST_CASE(qobject_methods)
{
    auto env = lua::create();

    QtPoint point(2, 3);
    env["point"] = &point;
    BOOST_CHECK_EQUAL(env["point"].type().name(), "userdata");

    BOOST_CHECK_EQUAL(lua::run_string<int>(env, "return point:getX()"), 2);

    lua::run_string(env, "point:setX(point:getX() * 2)");
    BOOST_CHECK_EQUAL(point.getX(), 4);

    lua::run_string(env, "point:setY(point:getY() + 3)");
    BOOST_CHECK_EQUAL(point.getY(), 6);
}

BOOST_AUTO_TEST_CASE(directory_module_loader)
{
    auto env = lua::create();

    DirectoryModuleLoader loader;
    loader.setRoot(QDir(TEST_DIR "testlib"));
    loader.setPrefix("testlib/");

    const char* searchersName = "searchers";
    #if LUA_VERSION_NUM < 502
        searchersName = "loaders";
    #endif

    std::string module;
    lua::table::insert(env["package"][searchersName],
        std::function<std::function<void()>(const std::string&) >(
            [&](const std::string& arg) {
                module = arg;
                return [&]() {
                    loader.load(env, module);
                };
            }
        )
    );

    env["foo"] = lua::push_function<int(int, int)>(env, [](int a, int b) {
        return a + b;
    });

    lua::run_string(env, "require 'testlib/Partial';"
        ""
        "bar = Partial(foo, 40);"
    );

    BOOST_CHECK_EQUAL(lua::call<int>(env["bar"], 2), 42);
}

BOOST_AUTO_TEST_CASE(qt)
{
    auto env = lua::create();
    env["package"]["cpath"] = ".libs/libluacxx-?.so";

    lua::run_string(env, "require 'Qt5Core.QElapsedTimer'");
    lua::run_string(env, "foo = QElapsedTimer:new()");
    lua::run_string(env, "foo:start()");
    lua::run_string(env, "elapsed = foo:nsecsElapsed()");
    BOOST_CHECK(env["elapsed"].type().number());
}
