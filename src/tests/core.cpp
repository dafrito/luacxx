#include "core.hpp"

#include "thread.hpp"
#include "stack.hpp"
#include "algorithm.hpp"
#include "load.hpp"
#include "reference.hpp"

#include "type/standard.hpp"
#include "type/function.hpp"
#include "type/numeric.hpp"

#include "module/DirectoryModuleLoader.hpp"

#include <QDir>

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
    return a+b+c+d+e;
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
    lua::thread env;

    lua::push(env, 42);
    BOOST_CHECK_EQUAL(lua::get<int>(env[1]), 42);

    int foo = 1;
    lua::store(foo, env[1]);
    BOOST_CHECK_EQUAL(foo, 42);

    bool flag = true;
    lua::push(env, flag);
    BOOST_CHECK_EQUAL(lua::get<bool>(env[2]), true);

    env[1] = 44;
    BOOST_CHECK_EQUAL(lua::get<int>(env[1]), 44);

    lua::clear(env);
    lua::push(env, true, 42, "No time");
    BOOST_CHECK_EQUAL(env[1].type().boolean(), true);
    BOOST_CHECK_EQUAL(env[2].type().number(), true);
    BOOST_CHECK_EQUAL(env[3].type().string(), true);
}

BOOST_AUTO_TEST_CASE(run_string)
{
    lua::thread env;
    luaL_openlibs(env);

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

BOOST_AUTO_TEST_CASE(run_file)
{
    lua::thread env;
    luaL_openlibs(env);

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
    lua::thread env;

    lua::run_dir(env, QDir(LUA_DIR "bin"), true);
    BOOST_CHECK_EQUAL(lua::get<int>(env["a"]), 42);
    BOOST_CHECK_EQUAL(lua::get<const char*>(env["b"]), "foo");
}

BOOST_AUTO_TEST_CASE(reference)
{
    lua::thread env;

    lua::reference ref(lua::push(env, "No Time"));
    BOOST_CHECK_EQUAL(lua::size(env), 1);

    lua::push(env, ref);
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
    lua::thread env;

    auto point = new Point<int>(2, 3);
    lua::push(env, point);

    auto copy = lua::get<Point<int>*>(env, -1);
    BOOST_CHECK_EQUAL(copy->x, 2);
    BOOST_CHECK_EQUAL(copy->y, 3);

    copy->x = 8;
    BOOST_CHECK_EQUAL(point->x, 8);

    lua::clear(env);
    lua::push(env, point);

    auto value = lua::get<Point<int>>(env, -1);
    BOOST_CHECK_EQUAL(value.x, 8);
    BOOST_CHECK_EQUAL(value.y, 3);
}

BOOST_AUTO_TEST_CASE(value_userdata)
{
    lua::thread env;

    lua::push<Point<int>>(env, Point<int>(2, 3));

    auto point = lua::get<Point<int>*>(env, -1);
    BOOST_CHECK_EQUAL(point->x, 2);
    BOOST_CHECK_EQUAL(point->y, 3);

    point->x = 8;
    BOOST_CHECK_EQUAL(lua::get<Point<int>*>(env, -1)->x, 8);
}

BOOST_AUTO_TEST_CASE(call_cpp_from_lua)
{
    lua::thread env;
    luaL_openlibs(env);

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
}

BOOST_AUTO_TEST_CASE(call_lua_from_cpp)
{
    lua::thread env;
    luaL_openlibs(env);

    lua::run_string(env, "function foo(a, b)\n"
    "    return a + b\n"
    "end");

    BOOST_CHECK_EQUAL(env["foo"].type().name(), "function");

    auto result = lua::call<int>(env["foo"], 42, "24");
    BOOST_CHECK_EQUAL(result, 66);
}

BOOST_AUTO_TEST_CASE(index_and_global)
{
    lua::thread env;
    luaL_openlibs(env);

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
    lua::thread env;
    luaL_openlibs(env);

    auto first = lua::push(env, 2);
    auto second = lua::push(env, 3);
    lua::swap(first, second);
    BOOST_CHECK_EQUAL(lua::get<int>(first), 3);
    BOOST_CHECK_EQUAL(lua::get<int>(second), 2);

    second = 5;
    BOOST_CHECK_EQUAL(lua::get<int>(second), 5);

    auto nil_value = lua::push(env, lua::value::nil);
    BOOST_CHECK_EQUAL(nil_value.type().name(), "nil");

    lua::run_string(env, "foo = {42, 42, 42}");
    BOOST_CHECK_EQUAL(lua::size(env["foo"]), 3);
}

/*

BOOST_AUTO_TEST_CASE(nestedInvocations)
{
    LuaEnvironment lua;

    lua["bar"] = std::function<const char*()>([&]() {
        return "bar";
    });

    lua["foo"] = std::function<QString(const QString&)>([&](const QString& internal) {
        return internal + QString("foo") + lua["bar"]().get<QString>();
    });

    BOOST_REQUIRE_EQUAL(lua("return foo('lua')").get<const char*>(), "luafoobar");
}

BOOST_AUTO_TEST_CASE(throwAnError)
{
    LuaEnvironment lua;

    bool errored = false;

    try {
        lua("function foo()"
        "   someUnknownFunction();"
        "end");

        lua["foo"]();
    } catch(LuaException& ex) {
        errored = true;
    }

    BOOST_REQUIRE(errored);
}

void immediatelyThrow()
{
    throw LuaException("Intentional");
}

BOOST_AUTO_TEST_CASE(luaExceptionIsCatchableWithinLua)
{
    LuaEnvironment lua;

    lua["thrower"] = immediatelyThrow;

    lua("result = not pcall(thrower);");

    BOOST_CHECK_EQUAL(lua["result"].get<bool>(), true);
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

BOOST_AUTO_TEST_CASE(luaIsBuiltWithExceptionSupport)
{
    LuaEnvironment lua;

    int value = 0;
    lua["call"] = std::function<void(bool)>([&](bool shouldErr) {
        Wrapper wrapper(value);

        if (shouldErr) {
            LuaStack(lua).error("Intentional");
        }
    });

    lua["call"](false);
    BOOST_CHECK_EQUAL(value, 2);

    try {
        lua["call"](true);
    } catch (LuaException& ex) {
        // pass through
    }
    BOOST_CHECK_EQUAL(value, 4);
}

BOOST_AUTO_TEST_CASE(luaValuesCanBePassedIntoLua)
{
    LuaEnvironment lua;

    lua("foo = {}");
    auto bar = lua("return function(a) end;");
    bar(lua["foo"]);
}

BOOST_AUTO_TEST_CASE(stackSavedTheRightReturnedValue)
{
    lua::thread env;

    lua::push(env, "An extra argument to ensure the stack doesn't just return the 'second' argument");

    auto worker = lua(""
    "return function(value)"
    "    foo = value;"
    "end;"
    "");
    lua::call(worker, 42);

    auto foo = env["foo"];
    BOOST_CHECK_EQUAL(foo.type().number(), true);
    BOOST_CHECK_EQUAL(lua::get<int>(foo), 42);
}

BOOST_AUTO_TEST_CASE(stackCanRetrieveMultipleArgumentsAtOnce)
{
    LuaEnvironment lua;
    LuaStack stack(lua);

    lua::push(stack, 1);
    lua::push(stack, 2);
    lua::push(stack, 3);
    lua::push(stack, 4);

    auto results = lua::getAll<int>(stack);
    BOOST_REQUIRE_EQUAL(4, results.size());
    BOOST_CHECK_EQUAL(1, results[0]);
    BOOST_CHECK_EQUAL(2, results[1]);
    BOOST_CHECK_EQUAL(3, results[2]);
    BOOST_CHECK_EQUAL(4, results[3]);
}

// Extraction/Insertion operators

BOOST_AUTO_TEST_CASE(testLuaStackSupportsExtractionOperators)
{
    LuaEnvironment lua;
    LuaStack s(lua);
    s << 42 << 34;
    int a, b;
    s >> a;
    BOOST_REQUIRE(a == 34);
    s >> b;
    BOOST_REQUIRE(b == 34);
}

BOOST_AUTO_TEST_CASE(testStackSupportsIndexing)
{
    LuaEnvironment lua;
    LuaStack s(lua);
    s << 5 << 6 << 7;

    int a;
    int b;
    int c;
    s.begin() >> a >> b >> c;
    BOOST_REQUIRE_EQUAL(a, 5);
    BOOST_REQUIRE_EQUAL(b, 6);
    BOOST_REQUIRE_EQUAL(c, 7);
}

// Table manipulation

static void receive(LuaStack& stack)
{
    BOOST_REQUIRE_EQUAL(stack.get<const char*>(1), "getValue");
    BOOST_REQUIRE_EQUAL(stack.get<int>(2), 2);
}

BOOST_AUTO_TEST_CASE(stackSetsATableValue)
{
    LuaEnvironment lua;
    lua("c = {}");
    LuaStack stack(lua);
    stack.global("c").set("a", 42);
    stack.global("c").set("b", true);

    // We don't repush global because that table should
    // already be at the top of the stack; only the key
    // and value were removed
    BOOST_REQUIRE_EQUAL(42, stack.get("a").get<int>());
    stack.pop();
    BOOST_REQUIRE_EQUAL(true, stack.get("b").get<bool>());
}

BOOST_AUTO_TEST_CASE(cRetrievesBasicProperties)
{
    LuaEnvironment lua;
    lua::runString(lua, "c = {f = 42};");
    LuaStack stack(lua);
    BOOST_REQUIRE_EQUAL(stack.global("c").get("f").get<int>(), 42);
}

BOOST_AUTO_TEST_CASE(cRetrievesNestedPropertiesWithLuaStack)
{
    LuaEnvironment lua;
    lua("d = {e = {f = 42} };");
    LuaStack stack(lua);
    BOOST_REQUIRE_EQUAL(stack.global("d").get("e").get("f").get<int>(), 42);
}

BOOST_AUTO_TEST_CASE(cRetrievesDeeplyNestedPropertiesWithLuaStack)
{
    LuaEnvironment lua;
    lua("c = {d = {e = {f = 42} } };");
    LuaStack stack(lua);
    BOOST_REQUIRE_EQUAL(stack.global("c").get("d").get("e").get("f").get<int>(), 42);
}

BOOST_AUTO_TEST_CASE(testPushWithInteger)
{
    LuaEnvironment lua;
    LuaStack stack(lua);

    lua("foo = {}");

    table::push(lua["foo"], 42);

    BOOST_REQUIRE_EQUAL((int)lua["foo"][1], 42);
}

BOOST_AUTO_TEST_CASE(testPushWithFunction)
{
    LuaEnvironment lua;
    LuaStack stack(lua);

    lua("foo = {}");

    table::push(lua["foo"], addNumbers);

    BOOST_REQUIRE_EQUAL((int)lua("return foo[1](2, 2)"), 4);
}

BOOST_AUTO_TEST_CASE(tablesCanBeSetWhileNested)
{
    LuaEnvironment lua;

    lua["Rainback"] = lua::value::table;
    lua["Rainback"]["Font"] = returnMagic;

    lua("assert(Rainback.Font)");
}

BOOST_AUTO_TEST_CASE(tableReferences)
{
    LuaEnvironment lua;

    lua("foo = {bar = 42}");

    BOOST_REQUIRE_EQUAL(lua["foo"]["bar"].typestring(), std::string("number"));
}

// Module loading

BOOST_AUTO_TEST_CASE(testDirectoryModuleLoader)
{
    LuaEnvironment lua;

    DirectoryModuleLoader loader;
    loader.setRoot(QDir(LUA_DIR "testlib"));
    loader.setPrefix("testlib/");

    const char* searchersName = "searchers";
    #if LUA_VERSION_NUM < 502
        searchersName = "loaders";
    #endif

    std::string module;
    table::push(lua["package"][searchersName],
        std::function< std::function<void()>(const std::string&) >(
            [&](const std::string& arg) {
                module = arg;
                return [&]() {
                    loader.load(lua, module);
                };
            }
        )
    );

    lua["foo"] = std::function<int(int, int)>( [](int a, int b) {
        return a + b;
    });

    lua("require 'testlib/Library';"
        ""
        "bar = Curry(foo, 40);"
    );

    BOOST_REQUIRE_EQUAL((int)lua["bar"](2), 42);
}

BOOST_AUTO_TEST_CASE(testModuleLoaderUtility)
{
    LuaEnvironment lua;

    DirectoryModuleLoader loader;
    loader.setRoot(QDir(LUA_DIR "testlib"));
    loader.setPrefix("testlib/");

    lua.addModuleLoader(&loader);

    lua["foo"] = std::function<int(int, int)>( [](int a, int b) {
        return a + b;
    });

    lua("require 'testlib/Library';"
        ""
        "bar = Curry(foo, 40);"
    );

    BOOST_REQUIRE_EQUAL((int)lua["bar"](2), 42);
}
*/
