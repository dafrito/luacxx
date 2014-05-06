#include "qt/type/QString.hpp"
#include "qt/type/QChar.hpp"
//#include "qt/type/QVariant.hpp"

#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>
using namespace boost::math;

#include <memory>

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

BOOST_AUTO_TEST_CASE(shared_ptr)
{
    lua::thread env;
    env["c"] = std::shared_ptr<QObject>(new Counter(42));

    env["acceptShared"] = acceptShared;
    env["acceptSharedRef"] = acceptSharedRef;

    auto orig = std::shared_ptr<QObject>(new QObject);
    lua::push(env, orig);

    auto other = lua::get<std::shared_ptr<QObject>>(env, 1);
    BOOST_CHECK_EQUAL(other.get(), orig.get());
}

BOOST_AUTO_TEST_CASE(callables_with_userdata)
{
    lua::thread env;

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
    BOOST_CHECK_THROW(lua::run_string(env, "foo.y.z = 42"), lua::exception);

    // Underflow
    BOOST_CHECK_THROW(lua::run_string(env, "receiveRef()"), lua::exception);

    // Allow extra args
    BOOST_CHECK_NO_THROW(lua::run_string(env, "receiveRef(counter, 3)"));
}

BOOST_AUTO_TEST_CASE(userdata_by_value)
{
    lua::thread env;

    Blank blank(42);
    env["blank"] = blank;

    env["receiveValue"] = receiveValue;
    env["receiveConstValue"] = receiveConstValue;

    lua::run_string(env, "receiveValue(blank)");
    lua::run_string(env, "receiveConstValue(blank)");
}

BOOST_AUTO_TEST_CASE(qstring)
{
    lua::thread env;
    lua::push(env, QString("c"));
    BOOST_CHECK(lua::get<QString>(env, 1) == QString("c"));
}

BOOST_AUTO_TEST_CASE(qchar)
{
    lua::thread env;
    lua::push(env, QChar('c'));
    BOOST_CHECK(lua::get<QChar>(env, 1) == QChar('c'));
}

BOOST_AUTO_TEST_CASE(raw_char)
{
    lua::thread env;

    char c = 'c';
    lua::push(env, c);
    BOOST_CHECK_EQUAL(lua::get<std::string>(env, 1), "c");
}

/*

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
    lua::thread env;

    env["Rainback"] = lua::value::table;
    env["Rainback"]["MakeCounter"] = makeCounter;

    lua::run_string(env, "font = Rainback.MakeCounter(42)");

    BOOST_CHECK_EQUAL(lua::evaluate<int>(env, "return font.value"), 42);
}

BOOST_AUTO_TEST_CASE(stack_userdata)
{
    lua::thread env;

    Counter counter(42);
    auto s = lua::push(env, &counter);
    BOOST_CHECK_EQUAL(s.type().name(), "userdata");

    env["c"] = &counter;
    BOOST_CHECK_EQUAL(lua::evaluate<int>(env, "return c:getValue()"), 42);

    lua::run_string(env, "c:addAll(1, 2, 3)");
    BOOST_REQUIRE_EQUAL(counter->getValue(), 48);

    lua::run_string(env, "c:setValue(24)");
    BOOST_CHECK_EQUAL(c.getValue(), 24);

    lua::run_string(env, "c:setAddedValue(2, 4)");
    BOOST_CHECK_EQUAL(c.getValue(), 30);

    BOOST_CHECK_EQUAL(lua::evaluate<int>(env, "return c:summed(1, 2, 3)"), 6);
}

BOOST_AUTO_TEST_CASE(qobject_properties)
{
    lua::thread env;
    QFile file(LUA_DIR "anim.lua");
    lua::runFile(lua, file);

    auto square = new Square;

    int old = square->getX();
    lua["Tick"](std::shared_ptr<QObject>(square), constants::pi<double>());
    BOOST_REQUIRE(square->getX() != old);

    Counter counter(42);
    lua["counter"] = counter;
    lua("bar = counter.value");

    BOOST_REQUIRE_EQUAL(lua["bar"].get<int>(), 42);

    Counter counter(42);
    lua["counter"] = counter;
    lua("counter.value = 24");

    BOOST_REQUIRE_EQUAL(counter.getValue(), 24);

    auto obj = std::shared_ptr<QObject>(new Counter(42));
    lua["c"] = obj;

    BOOST_CHECK_THROW(lua("c.someValue = 24"), LuaException);
}

BOOST_AUTO_TEST_CASE(qobject_signals)
{
    lua::thread env;

    Counter counter(42);
    Counter flag(10);

    lua(
    "function work(counter, flag)"
    "    remover = counter:connect('valueChanged', function(newNum)"
    "        flag.value = newNum;"
    "    end);"
    "end;");

    lua["work"](counter, flag);

    counter.setValue(50);
    BOOST_CHECK_EQUAL(flag.getValue(), 50);

    // Invoke twice to ensure the removal process is idempotent
    lua("remover()");
    lua("remover()");

    flag.setValue(30);

    counter.setValue(60);

    BOOST_CHECK_EQUAL(flag.getValue(), 30);
}

BOOST_AUTO_TEST_CASE(qvariant)
{
    lua::thread env;

    env["foo"] = QVariant(42);
    BOOST_CHECK_EQUAL(lua::get<int>(env["foo"]), 42);

    lua::run_string(env,
    "function work(a, b)"
    "   a:set(b);"
    "end;");

    Counter a(42);
    BOOST_CHECK_THROW(lua["work"](a, Counter(53)), std::logic_error);

    lua::qvariantPusher(QVariant::Point, [](LuaStack& stack, const QVariant& source)
    {
        auto point = source.toPoint();
        lua::push(stack, lua::value::table);

        stack.set("x", point.x());
        stack.set("y", point.y());
    });

    lua::qvariantStorer(QVariant::Point, [](const LuaIndex& index, QVariant& sink)
    {
        auto table = lua::get<LuaReference>(index);
        sink.setValue(QPoint(
            table["x"].get<int>(),
            table["y"].get<int>()
        ));
    });

    lua(
    "function work(counter)"
    "    counter.point = {x = 2, y = 4};"
    "end;");

    Counter counter(42);
    counter.setPoint(QPoint(36, 54));
    lua["work"](counter);
    BOOST_CHECK_EQUAL(counter.getPoint().x(), 2);

    counter.setPoint(QPoint(85, 34));

    lua(
    "function work(counter)"
    "    remover = counter:connect('pointEmitted', function(point)"
    "        foo = point;"
    "    end);"
    "end;");
    lua["work"](counter);

    counter.setValue(23);

    BOOST_CHECK_EQUAL(lua["foo"]["x"].get<int>(), 85);
    BOOST_CHECK_EQUAL(lua["foo"]["y"].get<int>(), 34);
}

*/
