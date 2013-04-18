namespace
{
    struct ArgStop {};

    template <typename Callee, typename RV, typename Arg, typename... Remaining>
    struct Invocator
    {
        template <typename... Rest>
        static void apply(LuaIndex& index, const Callee& func, Rest... rest)
        {
            static_assert(
                        // Non-references are fine
                        !std::is_reference<Arg>::value ||
                        // References to references are fine
                        std::is_reference<decltype(lua::as<Arg>(index++))>::value ||
                        // References to const are fine
                        std::is_const<typename std::remove_reference<Arg>::type>::value,
                "Provided function must not use non-const lvalue references to refer to temporary objects");
            Invocator<Callee, RV, Remaining...>::template apply<Rest..., Arg>(
                index, func, rest..., lua::as<Arg>(index++)
            );
        }
    };

    template <typename Callee, typename RV>
    struct Invocator<Callee, RV, ArgStop>
    {
        template <typename... FullArgs>
        static void apply(LuaIndex& index, const Callee& func, FullArgs... args)
        {
            index.stack().clear();
            index.stack() << func(args...);
        }
    };

    template <typename Callee>
    struct Invocator<Callee, void, ArgStop>
    {
        template <typename... FullArgs>
        static void apply(LuaIndex& index, const Callee& func, FullArgs... args)
        {
            index.stack().clear();
            func(args...);
        }
    };

    /**
     * LuaWrapper enables C++ functions of arbitrary complexity to be called
     * from Lua. Conceptually, the template behaves similarly to a varargs
     * function from C. However, types are preserved using variadic templates.
     * This allows us to automatically generate correct code for each
     * argument.
     *
     * This implementation was based off of:
     * http://dvandyk.wordpress.com/2010/08/15/apply-functions-to-stdtuple/
     */
    template <typename RV, typename... Args>
    class LuaWrapper
    {
        /**
         * The C++ function that will eventually be invoked.
         */
        std::function<RV(Args...)> func;

    public:
        LuaWrapper(std::function<RV(Args...)> func) : func(func)
        {}

        void operator()(LuaStack& stack)
        {
            LuaIndex index(stack.begin());

            // We could ensure the stack.size() matches the Arg size exactly, but most
            // native Lua methods don't check for that condition, so for us to fit in,
            // we won't either.

            if (stack.size() < sizeof...(Args)) {
                std::stringstream msg;
                msg << "Function expects at least "
                    << sizeof...(Args)
                    << " argument" << (sizeof...(Args) == 1 ? "" : "s");
                if (stack.size() > 1) {
                    msg << " but only" << stack.size() << " were given";
                } else if (stack.size() > 0) {
                    msg << " but only" << stack.size() << " was given";
                } else {
                    msg << " but none were given";
                }
                throw LuaException(msg.str());
            }
            Invocator<decltype(func), RV, Args..., ArgStop>::template apply<>(index, func);
        }
    };
}

