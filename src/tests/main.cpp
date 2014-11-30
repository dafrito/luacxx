#define BOOST_TEST_MODULE luacxx
#include "main.hpp"
#include "log.hpp"
#include "enum.hpp"

#include <boost/test/unit_test.hpp>

#include <memory>

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

BOOST_AUTO_TEST_CASE(run_string)
{
    auto env = lua::create();

    lua::load_string(env, "return 2 + 2");

    BOOST_CHECK_EQUAL(lua::size(env), 1);
    BOOST_CHECK_EQUAL(lua::index(env, 1).type().name(), "function");
    BOOST_CHECK_EQUAL(lua::index(env, -1).type().name(), "function");
    lua::clear(env);

    lua::run_string(env, "No = 'Time'");
    BOOST_CHECK_EQUAL(env["No"].get<const char*>(), "Time");
    lua::clear(env);

    lua::run_string(env, "return function() end");
    lua::index worker(env, -1);
    BOOST_CHECK_EQUAL(lua::size(env), 1);

    lua::call(worker, 2);
    BOOST_CHECK_EQUAL(lua::size(env), 1);

    // Does run_string throw on syntax errors?
    BOOST_CHECK_THROW(lua::run_string(env, "foo.y.z = 42"), lua::error);
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

    lua::run_string(env, "return 42");
    BOOST_CHECK_EQUAL(lua::get<int>(env, -1), 42);
}

BOOST_AUTO_TEST_CASE(reference)
{
    auto env = lua::create();

    lua::reference ref(env);
    ref = lua::push(env, "No Time");
    lua_pop(env, 1);

    BOOST_CHECK_EQUAL(lua_gettop(env), 0);
    BOOST_CHECK_EQUAL(ref.get<const char*>(), "No Time");
    BOOST_CHECK_EQUAL(lua_gettop(env), 0);

    env["Foo"] = lua::value::table;

    // Can references be constructed from lua locations?
    lua::reference Foo(env["Foo"]);

    // Does lua::reference support operator[]?
    Foo["Bar"] = 42;

    // Do changes to references refer back to the original environment or just a copy?
    BOOST_CHECK_EQUAL(env["Foo"]["Bar"].get<int>(), 42);
}

BOOST_AUTO_TEST_CASE(link_and_conversions)
{
    auto env = lua::create();

    lua::run_string(env, "foo = {a=42}");
    BOOST_CHECK_EQUAL(env["foo"]["a"].get<int>(), 42);
}

int sum(lua_State* const state)
{
    int sum = 0;
    for (auto value : lua::range<int>(state)) {
        sum += value;
    }
    lua::push(state, sum);
    return 1;
}

BOOST_AUTO_TEST_CASE(table_algorithms)
{
    auto env = lua::create();

    env["foo"] = lua::value::table;
    lua::table::insert(env["foo"], 42);

    auto inserted = lua::table::get(env["foo"], 1);
    BOOST_CHECK_EQUAL(inserted.type().name(), "number");

    BOOST_CHECK_EQUAL(lua::table::get<int>(env["foo"], 1), 42);

    lua::table::insert(env["foo"], sum);
    BOOST_CHECK_EQUAL(2, lua::size(env["foo"]));
    lua::assert_type("table", lua::type::function, lua::push(env["foo"][2]));

    lua::run_string(env, "return foo[2](2, 2)");
    BOOST_CHECK_EQUAL(4, lua::get<int>(env, -1));

    lua::run_string(env, "foo = {bar = 42}");
    BOOST_CHECK_EQUAL(env["foo"]["bar"].type().name(), "number");

    lua::run_string(env, "c = {f = 42};");
    BOOST_CHECK_EQUAL(lua::get<int>(env["c"]["f"]), 42);

    lua::run_string(env, "d = {e = {f = 68} }");
    BOOST_CHECK_EQUAL(lua::get<int>(env["d"]["e"]["f"]), 68);

    lua::run_string(env, "c = {d = {e = {f = 96} } };");
    BOOST_CHECK_EQUAL(lua::get<int>(env["c"]["d"]["e"]["f"]), 96);
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

static int receiveConstValue(const Counter counter)
{
    BOOST_CHECK_EQUAL(counter.get(), 42);
    return counter.get();
}

static int receiveValue(Counter counter)
{
    BOOST_CHECK_EQUAL(counter.get(), 42);
    counter.set(24);
    return counter.get();
}

BOOST_AUTO_TEST_CASE(value_userdata)
{
    auto env = lua::create();

    // Can userdata be pushed onto the stack?
    env << Point<int>(2, 3);

    // Can userdata be retrieve from the stack?
    auto point = lua::get<Point<int>*>(env, -1);
    BOOST_CHECK_EQUAL(point->x(), 2);
    BOOST_CHECK_EQUAL(point->y(), 3);

    env["counter"] = Counter(42);

    // Can userdata be passed to C++?
    env["receiveValue"] = receiveValue;
    BOOST_CHECK_EQUAL(24, lua::run_string<int>(env, "return receiveValue(counter)"));

    // Can const userdata be passed to C++?
    env["receiveConstValue"] = receiveConstValue;
    BOOST_CHECK_EQUAL(42, lua::run_string<int>(env, "return receiveConstValue(counter)"));

    // Can counters be created from Lua?
    Counter* foo = env["counter"];
    BOOST_CHECK_EQUAL(42, foo->get());
}

BOOST_AUTO_TEST_CASE(push_metatable)
{
    auto env = lua::create();

    // Does push_metatable add trash to the environment?
    lua::push(env, Counter(42));
    BOOST_CHECK_EQUAL(lua_gettop(env), 1);
}

BOOST_AUTO_TEST_CASE(lambda_with_wrap)
{
    auto env = lua::create();

    env["multiply"] = std::function<int(int, int)>([](int a, int b) {
        return a * b;
    });

    auto result = lua::run_string<int>(env, "return multiply(2, 3)");
    BOOST_CHECK_EQUAL(6, result);
}

static int receiveConstPtr(const Counter* counter)
{
    BOOST_CHECK_EQUAL(counter->get(), 42);
    return counter->get();
}

static int receivePtr(Counter* const counter)
{
    BOOST_CHECK_EQUAL(counter->get(), 42);
    counter->set(24);
    return counter->get();
}

BOOST_AUTO_TEST_CASE(pointer_userdata)
{
    auto env = lua::create();

    // Can pointers to userdata be pushed onto the stack?
    auto point = new Point<int>(2, 3);
    env << point;

    // Can pointers to userdata be retrieved from the stack?
    auto copy = lua::get<Point<int>*>(env, -1);
    BOOST_CHECK_EQUAL(copy->x(), 2);
    BOOST_CHECK_EQUAL(copy->y(), 3);

    // Are pointers to equal objects identical?
    BOOST_CHECK_EQUAL(copy, point);

    Counter counter(42);
    env["counter"] = &counter;
    BOOST_CHECK_EQUAL(&counter, env["counter"].get<Counter*>());

    // Can pointers to userdata be passed to C++?
    env["receivePtr"] = receivePtr;
    BOOST_CHECK_EQUAL(24, lua::run_string<int>(env, "return receivePtr(counter)"));
    counter.check<std::runtime_error>(24);
    counter.set(42);

    // Can pointers to const userdata be passed to C++?
    env["receiveConstPtr"] = receiveConstPtr;
    BOOST_CHECK_EQUAL(42, lua::run_string<int>(env, "return receiveConstPtr(counter)"));
    counter.check<std::runtime_error>(42);

    delete point;
}

template <class T>
void acceptShared(std::shared_ptr<T> ptr)
{
}

template <class T>
void acceptSharedRef(const std::shared_ptr<T>& ptr)
{
}

BOOST_AUTO_TEST_CASE(shared_ptr_userdata)
{
    auto env = lua::create();

    // Can shared_ptr's be passed into Lua by value and reference?
    env["acceptShared"] = acceptShared<Point<int>>;
    env["acceptSharedRef"] = acceptSharedRef<Point<int>>;

    // Can shared_ptr's be pushed onto the stack?
    auto point = std::make_shared<Point<int>>(2, 2);
    env << point;

    // Does the returned pointer refer to the same object?
    auto other = lua::get<std::shared_ptr<Point<int>>>(env, -1);
    BOOST_CHECK_EQUAL(point.get(), other.get());
}

static int receiveRef(Counter& counter)
{
    BOOST_CHECK_EQUAL(counter.get(), 42);
    counter.set(24);
    return counter.get();
}

static int receiveConstRef(const Counter& counter)
{
    BOOST_CHECK_EQUAL(counter.get(), 24);
    return counter.get();
}

BOOST_AUTO_TEST_CASE(reference_userdata)
{
    auto env = lua::create();

    Counter counter(42);
    env["counter"] = counter;

    // Are references treated as values or as pointers?
    env["receiveRef"] = receiveRef;
    BOOST_CHECK_EQUAL(24, lua::run_string<int>(env, "return receiveRef(counter)"));
    counter.check<std::runtime_error>(42);

    // Are const references treated differently than references?
    env["receiveConstRef"] = receiveConstRef;
    BOOST_CHECK_EQUAL(24, lua::run_string<int>(env, "return receiveConstRef(counter)"));
    counter.check<std::runtime_error>(42);
}

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

int luaAdd(lua_State* const state)
{
    auto a = lua::get<int>(state, 1);
    auto b = lua::get<int>(state, 2);
    lua_settop(state, 0);
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

BOOST_AUTO_TEST_CASE(call_cpp_from_lua)
{
    auto env = lua::create();

    env["luaAdd"] = luaAdd;
    BOOST_CHECK_EQUAL(env["luaAdd"].type().name(), "function");

    lua::run_string(env, "Bar = luaAdd(2, 2)");
    BOOST_CHECK_EQUAL(env["Bar"].get<int>(), 4);

    env["getMagicNumber"] = getMagicNumber;
    BOOST_CHECK_EQUAL(env["getMagicNumber"].type().name(), "function");

    lua::run_string(env, "Bar = getMagicNumber()");
    BOOST_CHECK_EQUAL(env["Bar"].get<int>(), 42);

    env["addToMagicNumber"] = addToMagicNumber;
    BOOST_CHECK_EQUAL(env["addToMagicNumber"].type().name(), "function");

    lua::run_string(env, "Bar = addToMagicNumber(2)");
    BOOST_CHECK_EQUAL(env["Bar"].get<int>(), 44);

    env["addNumbers"] = addNumbers;
    BOOST_CHECK_EQUAL(env["addNumbers"].type().name(), "function");

    lua::run_string(env, "Bar = addNumbers(2, 3)");
    BOOST_CHECK_EQUAL(env["Bar"].get<int>(), 5);

    env["addBonanza"] = addBonanza;
    BOOST_CHECK_EQUAL(env["addBonanza"].type().name(), "function");

    lua::run_string(env, "Bar = addBonanza(2, 3, 4, 5, 6)");
    BOOST_CHECK_EQUAL(env["Bar"].get<int>(), 2+3+4+5+6);

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
    BOOST_CHECK_EQUAL(lua::run_string<const char*>(env, "return foo('lua')"), "luafoobar");
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
    lua::run_string(env,
        "return function(a) table.insert(a, 42); end;"
    );
    lua::index bar(env, -1);

    BOOST_CHECK_EQUAL(0, lua::size(env["foo"]));
    lua::call(bar, env["foo"]);
    BOOST_CHECK_EQUAL(1, lua::size(env["foo"]));
}

struct MethodSum {
    int sum(int a, int b)
    {
        return a + b;
    }
};

LUA_METATABLE_NAMED(MethodSum);

BOOST_AUTO_TEST_CASE(call_cpp_methods)
{
    auto env = lua::create();

    env["sum"] = &MethodSum::sum;

    auto result = lua::run_string<int>(env, "return sum(nil, 2, 3)");
    BOOST_CHECK_EQUAL(result, 5);
}

BOOST_AUTO_TEST_CASE(call_lua_from_cpp_with_extra_arguments)
{
    auto env = lua::create();

    env << "An extra argument to ensure the stack doesn't just return the 'second' argument";

    lua::run_string(env, ""
    "return function(value)"
    "    foo = value;"
    "end;"
    "");
    lua::call(lua::index(env, -1), 42);

    auto foo = env["foo"];
    BOOST_CHECK_EQUAL(foo.type().number(), true);
    BOOST_CHECK_EQUAL(foo.get<int>(), 42);
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

BOOST_AUTO_TEST_CASE(error_support)
{
    auto env = lua::create();

    int value = 0;
    env["call"] = lua::push_function<void(bool)>(env, [&](bool shouldErr) {
        Wrapper wrapper(value);

        if (shouldErr) {
            throw lua::error("Intentional");
        }
    });

    // Can "call" normally return?
    lua::call<void>(env["call"], false);
    BOOST_CHECK_EQUAL(value, 2);

    // Do callables throw lua::error on insufficient arguments?
    BOOST_CHECK_THROW(lua::call<void>(env["call"]), lua::error);

    // Is lua::error thrown safely from Lua?
    try {
        lua::call<void>(env["call"], true);
    } catch (lua::error& ex) {
        // pass through
    }
    BOOST_CHECK_EQUAL(value, 4);


    // Are exceptions thrown when errors occur in Lua?
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

    // Does pcall handle lua::error gracefully?
    env["thrower"] = lua::callable([](lua_State* const state) -> int {
        throw lua::error("Intentional");
    });
    lua::run_string(env, "return not pcall(thrower);");
    BOOST_CHECK_EQUAL(lua::get<bool>(env, -1), true);

    // Do callables allow superfluous arguments?
    BOOST_CHECK_NO_THROW(lua::run_string(env, "call(false, 1, 2, 3)"));
}

BOOST_AUTO_TEST_CASE(callable_with_automatic_conversions)
{
    auto env = lua::create();

    env["get_number"] = lua::callable([](lua_State* const state) {
        lua::push(state, 42);
        return 1;
    });

    BOOST_CHECK_EQUAL(42, lua::run_string<int>(env, "return get_number()"));
}

BOOST_AUTO_TEST_CASE(raw_char)
{
    auto env = lua::create();

    char c = 'c';
    env << c;
    BOOST_CHECK_EQUAL(lua::get<std::string>(env, 1), "c");
}

struct Named {
    const char* name;

    Named(const char* name) :
        name(name)
    {
    }
};

struct Numbered {
    int num;

    Numbered(int num) :
        num(num)
    {
    }
};

struct Value {
    int version;
    const char* value;

    Value(const char* value, int version) :
        version(version),
        value(value)
    {
    }
};

struct Child : public Named, public Value {
Child() :
    Named("Child"), Value("Boog", 42)
    {
    }
};

struct Grandchild : public Numbered, public Child {
Grandchild() :
    Numbered(24), Child()
    {
    }
};

namespace lua {

template<>
struct Metatable<Named>
{
    static const userdata_type& info()
    {
        static userdata_type _info("Named");
        if (!_info.has_casts()) {
            _info.add_cast<Named>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int pos, const void* const value)
    {
        return true;
    }
};

template<>
struct Metatable<Value>
{
    static const userdata_type& info()
    {
        static userdata_type _info("Value");
        if (!_info.has_casts()) {
            _info.add_cast<Value>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int pos, const void* const value)
    {
        return true;
    }
};

template<>
struct Metatable<Child>
{
    static const userdata_type& info()
    {
        static userdata_type _info("Child");
        if (!_info.has_casts()) {
            _info.add_cast<Named, Child>();
            _info.add_cast<Value, Child>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int pos, const void* const value)
    {
        auto userdata = lua::get<lua::userdata_block*>(state, pos - 1);

        return true;
    }
};

template<>
struct Metatable<Numbered>
{
    static const userdata_type& info()
    {
        static userdata_type _info("Numbered");
        if (!_info.has_casts()) {
            _info.add_cast<Numbered>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int pos, const void* const value)
    {
        return true;
    }
};

template<>
struct Metatable<Grandchild>
{
    static const userdata_type& info()
    {
        static userdata_type _info("Grandchild");
        if (!_info.has_casts()) {
            _info.add_cast<Grandchild>();
            _info.add_cast<Numbered, Grandchild>();
            _info.add_cast<Child, Grandchild>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int pos, const void* const value)
    {
        return true;
    }
};


} // namespace lua

BOOST_AUTO_TEST_CASE(multiple_inheritance)
{
    auto env = lua::create();

    auto child = lua::make<Child>(env);
    auto child_as_value = static_cast<Value*>(child);
    auto child_as_named = static_cast<Named*>(child);

    // Does multiple inheritance require that the two superclasses have
    // distinct, rather than identical, pointer addresses?
    BOOST_REQUIRE(static_cast<void*>(child_as_value) != static_cast<void*>(child_as_named));

    BOOST_CHECK(lua::is_type<Value*>(env, -1));
    BOOST_CHECK_EQUAL(child_as_value, lua::get<Value*>(env, -1));

    BOOST_CHECK(lua::is_type<Named*>(env, -1));
    BOOST_CHECK_EQUAL(child_as_named, lua::get<Named*>(env, -1));

    // Does is_type return false for classes outside an object hierarchy?
    BOOST_CHECK(!lua::is_type<Counter*>(env, -1));

    auto grandchild = lua::make<Grandchild>(env);
    auto grandchild_as_Child = static_cast<Child*>(grandchild);
    auto grandchild_as_Numbered = static_cast<Numbered*>(grandchild);
    auto grandchild_as_Named = static_cast<Named*>(grandchild);
    auto grandchild_as_Value = static_cast<Value*>(grandchild);

    BOOST_CHECK(lua::is_type<Numbered*>(env, -1));
    BOOST_CHECK_EQUAL(grandchild_as_Numbered, lua::get<Numbered*>(env, -1));

    BOOST_CHECK(lua::is_type<Named*>(env, -1));
    BOOST_CHECK_EQUAL(grandchild_as_Named, lua::get<Named*>(env, -1));

    BOOST_CHECK(lua::is_type<Child*>(env, -1));
    BOOST_CHECK_EQUAL(grandchild_as_Child, lua::get<Child*>(env, -1));

    BOOST_CHECK(lua::is_type<Value*>(env, -1));
    BOOST_CHECK_EQUAL(grandchild_as_Value, lua::get<Value*>(env, -1));
}

enum class Color {
    Red = 1,
    Blue,
    Green
};

LUA_METATABLE_ENUM(Color);

BOOST_AUTO_TEST_CASE(enums)
{
    auto env = lua::create();
    env["Red"] = Color::Red;
    env["Green"] = Color::Green;
    env["Blue"] = Color::Blue;
    env["Test"] = Color::Red;

    BOOST_CHECK_EQUAL(true, lua::run_string<bool>(env, "return Test == Red"));
}

BOOST_AUTO_TEST_CASE(enums_and_each)
{
    auto env = lua::create();
    env["Red"] = Color::Red;
    env["Green"] = Color::Green;
    env["Blue"] = Color::Blue;
    env["Test"] = Color::Red;

    lua::run_string(env, "Colors = {Red, Green, Red, Blue}");

    std::vector<Color> colors;
    lua::table::each<Color>(env["Colors"], [&colors](const Color& c) {
        colors.push_back(c);
    });

    BOOST_CHECK(colors[0] == Color::Red);
    BOOST_CHECK(colors[1] == Color::Green);
    BOOST_CHECK(colors[2] == Color::Red);
    BOOST_CHECK(colors[3] == Color::Blue);

    BOOST_CHECK_EQUAL(true, lua::run_string<bool>(env, "return Test == Red"));
}

BOOST_AUTO_TEST_CASE(logging)
{
    auto env = lua::create();

    lua::addLogger(env, lua::logger([](lua_State* const state, const lua::LogMessageType mtype, const lua::LogMessage& message) {
    }));

    lua::logEnterm(env, "No time");
    lua::logLeave(env);
}

BOOST_AUTO_TEST_CASE(algorithm_call_with_int)
{
    auto env = lua::create();

    lua::run_string(env, ""
    "function return_1_2()\n"
    "    return 1, 2;\n"
    "end;\n"
    );

    lua::call<1>(env["return_1_2"]);
    BOOST_CHECK_EQUAL(1, lua::get<int>(env, 1));

    lua_settop(env, 0);
    lua::call<2>(env["return_1_2"]);
    BOOST_CHECK_EQUAL(1, lua::get<int>(env, 1));
    BOOST_CHECK_EQUAL(2, lua::get<int>(env, 2));
}

#ifdef HAVE_gobject_introspection

#include "search/GIRepository.hpp"

BOOST_AUTO_TEST_CASE(gobject_introspection)
{
    auto env = lua::create();
    env["package"]["cpath"] = ".libs/libluacxx-?.so";

    lua::run_string(env, "require 'luacxx.search.GIRepository'");
    lua::run_string(env, "require 'Gtk'");
    lua::run_string(env, "app = gtk_application_new()");
}

#endif // HAVE_gobject_introspection
