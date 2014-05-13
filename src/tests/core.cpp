#include "core.hpp"

#include "thread.hpp"
#include "push.hpp"
#include "store.hpp"
#include "algorithm.hpp"
#include "load.hpp"
#include "reference.hpp"

#include "type/standard.hpp"
#include "type/function.hpp"
#include "type/numeric.hpp"

namespace {

int addToMagicNumber(int v)
{
    return 42 + v;
}

double addNumbers(int a, int b)
{
    return a + b;
}

double addBonanza(int a, long b, float c, double d, short e)
{
    return a + b + c + d + e;
}

int luaAdd(lua::state* const state)
{
    auto a = lua::get<int>(state, 1);
    auto b = lua::get<int>(state, 2);
    lua::clear(state);

    lua::push(state, a + b);
    return 1;
}

int getMagicNumber()
{
    return 42;
}

void noop(int)
{
}

} // namespace anonymous

BOOST_AUTO_TEST_CASE(push_and_store)
{
    auto env = lua::create();

    env << 42;
    BOOST_CHECK_EQUAL(lua::get<int>(env, 1), 42);

    int foo = 1;
    lua::index(env, 1) >> foo;
    BOOST_CHECK_EQUAL(foo, 42);

    bool flag = true;
    env << flag;
    BOOST_CHECK_EQUAL(lua::get<bool>(env, 2), true);

    auto pushed = lua::push(env, 44);
    pushed >> foo;
    BOOST_CHECK_EQUAL(lua::get<int>(env, -1), 44);

    lua::clear(env);
    env << true << 42 << "No time";
    BOOST_CHECK_EQUAL(lua::index(env, 1).type().boolean(), true);
    BOOST_CHECK_EQUAL(lua::index(env, 2).type().number(), true);
    BOOST_CHECK_EQUAL(lua::index(env, 3).type().string(), true);
}

BOOST_AUTO_TEST_CASE(table)
{
    auto env = lua::create();

    env["foo"] = lua::value::table;
    lua::table::insert(env["foo"], 42);

    auto inserted = lua::table::get(env["foo"], 1);
    BOOST_CHECK_EQUAL(inserted.type().name(), "number");

    BOOST_CHECK_EQUAL(lua::table::get<int>(env["foo"], 1), 42);

    lua::table::insert(env["foo"], addNumbers);
    BOOST_CHECK_EQUAL(4, lua::get<int>(
        lua::run_string(env, "return foo[2](2, 2)")
    ));

    env["Rainback"] = lua::value::table;
    env["Rainback"]["Font"] = getMagicNumber;

    BOOST_CHECK_EQUAL(env["Rainback"]["Font"].type().name(), "function");

    lua::run_string(env, "foo = {bar = 42}");
    BOOST_CHECK_EQUAL(env["foo"]["bar"].type().name(), "number");

    lua::run_string(env, "c = {f = 42};");
    BOOST_CHECK_EQUAL(lua::get<int>(env["c"]["f"]), 42);

    lua::run_string(env, "d = {e = {f = 68} }");
    BOOST_CHECK_EQUAL(lua::get<int>(env["d"]["e"]["f"]), 68);

    lua::run_string(env, "c = {d = {e = {f = 96} } };");
    BOOST_CHECK_EQUAL(lua::get<int>(env["c"]["d"]["e"]["f"]), 96);
}

BOOST_AUTO_TEST_CASE(run_string)
{
    auto env = lua::create();

    lua::load_string(env, "return 2 + 2");

    BOOST_CHECK_EQUAL(lua::size(env), 1);
    BOOST_CHECK_EQUAL(lua::index(env, 1).type().name(), "function");
    BOOST_CHECK_EQUAL(lua::index(env, -1).type().name(), "function");
    lua::clear(env);

    lua::run_string(env, "No = 'Time'");
    BOOST_CHECK_EQUAL(lua::get<const char*>(env["No"]), "Time");
    lua::clear(env);

    auto worker = lua::run_string(env, "return function() end");
    BOOST_CHECK_EQUAL(lua::size(env), 1);

    lua::call<void>(worker, 2);
    BOOST_CHECK_EQUAL(lua::size(env), 1);
}

BOOST_AUTO_TEST_CASE(reference)
{
    auto env = lua::create();

    lua::reference ref(lua::push(env, "No Time"));
    BOOST_CHECK_EQUAL(lua::size(env), 1);

    env << ref;
    BOOST_CHECK_EQUAL(lua::get<const char*>(env, -1), "No Time");
}

template <class T>
struct Point {
    T x;
    T y;

public:
    Point(const T& x, const T& y) :
        x(x),
        y(y)
    {
    }

    Point() :
        x(),
        y()
    {
    }

    Point(const Point& other) :
        x(other.x),
        y(other.y)
    {
    }
};

BOOST_AUTO_TEST_CASE(pointer_userdata)
{
    auto env = lua::create();

    auto point = new Point<int>(2, 3);
    env << point;

    auto copy = lua::get<Point<int>*>(env, -1);
    BOOST_CHECK_EQUAL(copy->x, 2);
    BOOST_CHECK_EQUAL(copy->y, 3);

    copy->x = 8;
    BOOST_CHECK_EQUAL(point->x, 8);

    lua::clear(env);
    env << point;

    auto value = lua::get<Point<int>>(env, -1);
    BOOST_CHECK_EQUAL(value.x, 8);
    BOOST_CHECK_EQUAL(value.y, 3);
}

BOOST_AUTO_TEST_CASE(value_userdata)
{
    auto env = lua::create();

    env << Point<int>(2, 3);

    auto point = lua::get<Point<int>*>(env, -1);
    BOOST_CHECK_EQUAL(point->x, 2);
    BOOST_CHECK_EQUAL(point->y, 3);

    point->x = 8;
    BOOST_CHECK_EQUAL(lua::get<Point<int>*>(env, -1)->x, 8);
}

BOOST_AUTO_TEST_CASE(call_cpp_from_lua)
{
    auto env = lua::create();

    env["luaAdd"] = luaAdd;
    BOOST_CHECK_EQUAL(env["luaAdd"].type().name(), "function");

    lua::run_string(env, "Bar = luaAdd(2, 2)");
    BOOST_CHECK_EQUAL(lua::get<int>(env["Bar"]), 4);

    env["getMagicNumber"] = getMagicNumber;
    BOOST_CHECK_EQUAL(env["getMagicNumber"].type().name(), "function");

    lua::run_string(env, "Bar = getMagicNumber()");
    BOOST_CHECK_EQUAL(lua::get<int>(env["Bar"]), 42);

    env["addToMagicNumber"] = addToMagicNumber;
    BOOST_CHECK_EQUAL(env["addToMagicNumber"].type().name(), "function");

    lua::run_string(env, "Bar = addToMagicNumber(2)");
    BOOST_CHECK_EQUAL(lua::get<int>(env["Bar"]), 44);

    env["addNumbers"] = addNumbers;
    BOOST_CHECK_EQUAL(env["addNumbers"].type().name(), "function");

    lua::run_string(env, "Bar = addNumbers(2, 3)");
    BOOST_CHECK_EQUAL(lua::get<int>(env["Bar"]), 5);

    env["addBonanza"] = addBonanza;
    BOOST_CHECK_EQUAL(env["addBonanza"].type().name(), "function");

    lua::run_string(env, "Bar = addBonanza(2, 3, 4, 5, 6)");
    BOOST_CHECK_EQUAL(lua::get<int>(env["Bar"]), 2+3+4+5+6);

    env["noop"] = noop;
    BOOST_CHECK_EQUAL(env["noop"].type().name(), "function");

    lua::run_string(env, "Bar = noop(2)");

    auto pushed = lua::push_function<int(int, int)>(env, [](int a, int b) {
        return a + b;
    });
    env["Adder"] = pushed;
    BOOST_CHECK_EQUAL(env["Adder"].type().name(), "function");
    lua::run_string(env, "assert(Adder(22, 44) == 66)");

    env["bar"] = std::function<const char*()>([&]() {
        return "bar";
    });

    env["foo"] = std::function<std::string(const std::string&)>([&](const std::string& internal) {
        return internal + std::string("foo") + lua::call<std::string>(env["bar"]);
    });
    BOOST_CHECK_EQUAL(lua::evaluate<const char*>(env, "return foo('lua')"), "luafoobar");
}

BOOST_AUTO_TEST_CASE(call_lua_from_cpp)
{
    auto env = lua::create();

    lua::run_string(env, "function foo(a, b)\n"
    "    return a + b\n"
    "end");

    BOOST_CHECK_EQUAL(env["foo"].type().name(), "function");

    auto result = lua::call<int>(env["foo"], 42, "24");
    BOOST_CHECK_EQUAL(result, 66);

    env["foo"] = lua::value::table;
    auto bar = lua::run_string(env,
        "return function(a) table.insert(a, 42); end;"
    );

    BOOST_CHECK_EQUAL(0, lua::size(env["foo"]));
    lua::call<void>(bar, env["foo"]);
    BOOST_CHECK_EQUAL(1, lua::size(env["foo"]));
}

BOOST_AUTO_TEST_CASE(call_lua_from_cpp_with_extra_arguments)
{
    auto env = lua::create();

    env << "An extra argument to ensure the stack doesn't just return the 'second' argument";

    auto worker = lua::run_string(env, ""
    "return function(value)"
    "    foo = value;"
    "end;"
    "");
    lua::call(worker, 42);

    auto foo = env["foo"];
    BOOST_CHECK_EQUAL(foo.type().number(), true);
    BOOST_CHECK_EQUAL(lua::get<int>(foo), 42);
}

BOOST_AUTO_TEST_CASE(index_and_global)
{
    auto env = lua::create();

    env["foo"] = 42;
    BOOST_CHECK_EQUAL(lua::size(env), 0);

    lua::run_string(env, "assert(foo == 42)");
    BOOST_CHECK_EQUAL(lua::size(env), 0);

    env["foo"] = lua::value::table;
    lua::run_string(env, "assert(type(foo) == 'table')");
    BOOST_CHECK_EQUAL(lua::size(env), 0);

    env["foo"] = lua::value::nil;
    lua::run_string(env, "assert(foo == nil)");
    BOOST_CHECK_EQUAL(lua::size(env), 0);

    auto rv = lua::run_string(env, "return 42");
    BOOST_CHECK_EQUAL(lua::get<int>(rv), 42);
}

BOOST_AUTO_TEST_CASE(index_algorithms)
{
    auto env = lua::create();

    auto first = lua::push(env, 2);
    auto second = lua::push(env, 3);
    lua::swap(first, second);
    BOOST_CHECK_EQUAL(lua::get<int>(first), 3);
    BOOST_CHECK_EQUAL(lua::get<int>(second), 2);

    auto nil_value = lua::push(env, lua::value::nil);
    BOOST_CHECK_EQUAL(nil_value.type().name(), "nil");

    lua::run_string(env, "foo = {42, 42, 42}");
    BOOST_CHECK_EQUAL(lua::size(env["foo"]), 3);
}

struct Wrapper {
    int& alive;

    Wrapper(int& alive) : alive(alive)
    {
        this->alive++;
    }

    ~Wrapper()
    {
        this->alive++;
    }
};

BOOST_AUTO_TEST_CASE(lua_error_support)
{
    auto env = lua::create();

    int value = 0;
    env["call"] = lua::push_function<void(bool)>(env, [&](bool shouldErr) {
        Wrapper wrapper(value);

        if (shouldErr) {
            throw lua::error("Intentional");
        }
    });

    lua::call<void>(env["call"], false);
    BOOST_CHECK_EQUAL(value, 2);

    try {
        lua::call<void>(env["call"], true);
    } catch (lua::error& ex) {
        // pass through
    }
    BOOST_CHECK_EQUAL(value, 4);
}

void immediatelyThrow()
{
    throw lua::error("Intentional");
}

BOOST_AUTO_TEST_CASE(errors)
{
    auto env = lua::create();

    bool errored = false;

    try {
        lua::run_string(env,
        "function foo()"
        "   someUnknownFunction();"
        "end");
        lua::call<void>(env["foo"]);
    } catch(lua::error& ex) {
        errored = true;
    }
    BOOST_CHECK(errored);

    env["thrower"] = immediatelyThrow;
    auto rv = lua::run_string(env, "return not pcall(thrower);");
    BOOST_CHECK_EQUAL(lua::get<bool>(rv), true);
}

BOOST_AUTO_TEST_CASE(get_all)
{
    auto env = lua::create();

    lua::push(env, 1, 2, 3, 4);

    std::vector<int> results;
    lua::get_all(results, lua::index(env, 1));
    BOOST_REQUIRE_EQUAL(4, results.size());
    BOOST_CHECK_EQUAL(1, results[0]);
    BOOST_CHECK_EQUAL(2, results[1]);
    BOOST_CHECK_EQUAL(3, results[2]);
    BOOST_CHECK_EQUAL(4, results[3]);
}

BOOST_AUTO_TEST_CASE(extraction_and_insertion)
{
    auto env = lua::create();

    env << 42 << 34;
    int a, b;
    env >> a >> b;
    BOOST_CHECK_EQUAL(a, 42);
    BOOST_CHECK_EQUAL(b, 34);
    lua::clear(env);

    env << 5 << 6 << 7;
    int d;
    int e;
    int f;
    env >> d >> e >> f;
    BOOST_CHECK_EQUAL(d, 5);
    BOOST_CHECK_EQUAL(e, 6);
    BOOST_CHECK_EQUAL(f, 7);
}
