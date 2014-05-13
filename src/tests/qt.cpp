#include "qt/type/QString.hpp"
#include "qt/type/QChar.hpp"
#include "qt/type/QVariant.hpp"

#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>
using namespace boost::math;

#include <memory>

#include "module/DirectoryModuleLoader.hpp"
#include <QDir>

#include "mocks.hpp"
#include "thread.hpp"
#include "push.hpp"
#include "store.hpp"
#include "algorithm.hpp"
#include "load.hpp"
#include "reference.hpp"
#include "type/function.hpp"
#include "type/standard.hpp"
#include "type/numeric.hpp"

void acceptShared(std::shared_ptr<Counter> ptr)
{
}

void acceptSharedRef(const std::shared_ptr<Counter>& ptr)
{
}

std::shared_ptr<Counter> makeCounter(lua::state* const state)
{
    switch (lua::size(state)) {
        case 0: return std::make_shared<Counter>();
        case 1: return std::make_shared<Counter>(lua::get<int>(state, 1));
        default: return std::make_shared<Counter>(lua::get<int>(state, 1) + lua::get<int>(state, 2));
    }
}

BOOST_AUTO_TEST_CASE(shared_ptr)
{
    auto env = lua::create();

    env["acceptShared"] = acceptShared;
    env["acceptSharedRef"] = acceptSharedRef;

    auto orig = std::shared_ptr<QObject>(new QObject);
    lua::push(env, orig);

    auto other = lua::get<std::shared_ptr<QObject>>(env, 1);
    BOOST_CHECK_EQUAL(other.get(), orig.get());

    env["Rainback"] = lua::value::table;
    env["Rainback"]["MakeCounter"] = makeCounter;

    lua::run_string(env, "font = Rainback.MakeCounter(42)");
    BOOST_CHECK_EQUAL(lua::evaluate<int>(env, "return font.value"), 42);
}

static void receiveValue(Blank blank)
{
    BOOST_CHECK_EQUAL(blank.count(), 42);
}

static void receiveConstValue(const Blank blank)
{
    BOOST_CHECK_EQUAL(blank.count(), 42);
}

static void receivePtr(Counter* const counter)
{
    counter->setValue(24);
}

static int receiveConstPtr(const Counter* counter)
{
    return counter->getValue();
}

static void receiveRef(Counter& counter)
{
    counter.setValue(24);
}

static int receiveConstRef(const Counter& counter)
{
    return counter.getValue();
}

BOOST_AUTO_TEST_CASE(callables_with_userdata)
{
    auto env = lua::create();

    Counter counter(42);
    env["counter"] = &counter;
    env["receiveValue"] = receiveValue;
    lua::push_function<void(Counter* count)>(env, receivePtr);
    env["receivePtr"] = receivePtr;
    env["receiveRef"] = receiveRef;
    env["receiveConstRef"] = receiveConstRef;
    env["receiveConstPtr"] = receiveConstPtr;

    BOOST_CHECK_EQUAL(counter.getValue(), 42);
    lua::run_string(env, "receivePtr(counter)");
    BOOST_CHECK_EQUAL(counter.getValue(), 24);
    BOOST_CHECK_EQUAL(lua::get<int>(
        lua::run_string(env, "return receiveConstPtr(counter)")),
        24
    );

    counter.setValue(42);

    BOOST_CHECK_EQUAL(counter.getValue(), 42);
    lua::run_string(env, "receiveRef(counter)");
    BOOST_CHECK_EQUAL(counter.getValue(), 24);
    BOOST_CHECK_EQUAL(lua::evaluate<int>(env, "return receiveConstRef(counter)"), 24);

    // Runtime error
    BOOST_CHECK_THROW(lua::run_string(env, "foo.y.z = 42"), lua::error);

    // Underflow
    BOOST_CHECK_THROW(lua::run_string(env, "receiveRef()"), lua::error);

    // Allow extra args
    BOOST_CHECK_NO_THROW(lua::run_string(env, "receiveRef(counter, 3)"));
}

BOOST_AUTO_TEST_CASE(userdata_by_value)
{
    auto env = lua::create();

    Blank blank(42);
    env["blank"] = blank;

    env["receiveValue"] = receiveValue;
    env["receiveConstValue"] = receiveConstValue;

    lua::run_string(env, "receiveValue(blank)");
    lua::run_string(env, "receiveConstValue(blank)");
}

BOOST_AUTO_TEST_CASE(qstring)
{
    auto env = lua::create();

    lua::push(env, QString("c"));
    BOOST_CHECK(lua::get<QString>(env, 1) == QString("c"));
}

BOOST_AUTO_TEST_CASE(qchar)
{
    auto env = lua::create();

    lua::push(env, QChar('c'));
    BOOST_CHECK(lua::get<QChar>(env, 1) == QChar('c'));
}

BOOST_AUTO_TEST_CASE(raw_char)
{
    auto env = lua::create();

    char c = 'c';
    lua::push(env, c);
    BOOST_CHECK_EQUAL(lua::get<std::string>(env, 1), "c");
}

BOOST_AUTO_TEST_CASE(qvariant)
{
    auto env = lua::create();

    env["foo"] = QVariant(42);
    BOOST_CHECK_EQUAL(lua::get<int>(env["foo"]), 42);

    lua::qvariant_push_handler[QVariant::Point] = [](lua::state* const state, const QVariant& source) {
        auto point = source.toPoint();
        auto table = lua::push(state, lua::value::table);

        lua::table::set(table, "x", point.x());
        lua::table::set(table, "y", point.x());
    };

    lua::qvariant_store_handler[QVariant::Point] = [](QVariant& destination, const lua::index& source) {
        destination.setValue(QPoint(
            lua::table::get<int>(source, "x"),
            lua::table::get<int>(source, "y")
        ));

    };

    lua::run_string(env,
    "function work(counter)"
    "    counter.point = {x = 2, y = 4};"
    "end;");

    Counter counter(42);
    counter.setPoint(QPoint(36, 54));
    lua::call(env["work"], &counter);
    BOOST_CHECK_EQUAL(counter.getPoint().x(), 2);

    counter.setPoint(QPoint(85, 34));

    lua::run_string(env,
    "function work(counter)"
    "    remover = counter:connect('pointEmitted', function(point)"
    "        foo = point;"
    "    end);"
    "end;");
    lua::call(env["work"], &counter);

    counter.setValue(23);

    BOOST_CHECK_EQUAL(lua::get<int>(env["foo"]["x"]), 85);
    BOOST_CHECK_EQUAL(lua::get<int>(env["foo"]["y"]), 34);
}

BOOST_AUTO_TEST_CASE(stack_userdata)
{
    auto env = lua::create();

    Counter counter(42);
    BOOST_CHECK_EQUAL(lua::push(env, &counter).type().name(), "userdata");

    env["counter"] = &counter;
    BOOST_CHECK_EQUAL(lua::evaluate<int>(env, "return counter:getValue()"), 42);

    lua::run_string(env, "counter:addAll(1, 2, 3)");
    BOOST_CHECK_EQUAL(counter.getValue(), 48);

    lua::run_string(env, "counter:setValue(24)");
    BOOST_CHECK_EQUAL(counter.getValue(), 24);

    lua::run_string(env, "counter:setAddedValue(2, 4)");
    BOOST_CHECK_EQUAL(counter.getValue(), 30);

    BOOST_CHECK_EQUAL(lua::evaluate<int>(env, "return counter:summed(1, 2, 3)"), 6);
}

BOOST_AUTO_TEST_CASE(qobject_properties)
{
    auto env = lua::create();

    QFile file(LUA_DIR "anim.lua");
    lua::run_file(env, file);

    auto square = new Square;
    int old = square->getX();
    lua::call(env["Tick"], std::shared_ptr<QObject>(square), constants::pi<double>());
    BOOST_CHECK(square->getX() != old);

    Counter counter(42);
    env["counter"] = &counter;

    lua::run_string(env, "bar = counter.value");
    BOOST_CHECK_EQUAL(lua::get<int>(env["bar"]), 42);

    lua::run_string(env, "counter.value = 24");
    BOOST_CHECK_EQUAL(counter.getValue(), 24);

    auto obj = std::shared_ptr<QObject>(new Counter(42));
    env["c"] = obj;

    BOOST_CHECK_THROW(lua::run_string(env, "c.someValue = 24"), lua::error);
}

BOOST_AUTO_TEST_CASE(qobject_signals)
{
    auto env = lua::create();

    Counter counter(42);
    Counter flag(10);

    lua::run_string(env,
    "function work(counter, flag)"
    "    remover = counter:connect('valueChanged', function(newNum)"
    "        flag.value = newNum;"
    "    end);"
    "end;");
    lua::call(env["work"], &counter, &flag);

    counter.setValue(50);
    BOOST_CHECK_EQUAL(flag.getValue(), 50);

    // Invoke twice to ensure the removal process is idempotent
    lua::run_string(env, "remover()");
    lua::run_string(env, "remover()");
}

BOOST_AUTO_TEST_CASE(run_file)
{
    auto env = lua::create();

    QFile file(LUA_DIR "simple.lua");
    lua::run_string(env, "No = 'Time'");
    lua::run_file(env, file);

    // run_file throws on a missing file
    BOOST_CHECK_THROW(
        lua::run_file(env, "somemissingfile.lua"),
        std::runtime_error
    );

    QFile falseFile(LUA_DIR "returnfalse.lua");
    BOOST_CHECK_EQUAL(lua::get<bool>(lua::run_file(env, falseFile)), false);

    QFile trueFile(LUA_DIR "returntrue.lua");
    BOOST_CHECK_EQUAL(lua::get<bool>(lua::run_file(env, trueFile)), true);
}

BOOST_AUTO_TEST_CASE(run_dir)
{
    auto env = lua::create();

    lua::run_dir(env, QDir(LUA_DIR "bin"), true);
    BOOST_CHECK_EQUAL(lua::get<int>(env["a"]), 42);
    BOOST_CHECK_EQUAL(lua::get<const char*>(env["b"]), "foo");
}

BOOST_AUTO_TEST_CASE(directory_module_loader)
{
    auto env = lua::create();

    DirectoryModuleLoader loader;
    loader.setRoot(QDir(LUA_DIR "testlib"));
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

    lua::run_string(env, "require 'testlib/Library';"
        ""
        "bar = Curry(foo, 40);"
    );

    BOOST_CHECK_EQUAL(lua::call<int>(env["bar"], 2), 42);
}
