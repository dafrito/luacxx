namespace lua {

    template <typename T>
    struct UserdataType
    {
        constexpr static const char* name = 0;

        /**
         * Initialize the userdata at the top of this stack. This is
         * typically used to set up a metatable.
         */
        static void initialize(LuaStack& stack, T& object)
        {
        }
    };

    template <typename T>
    struct isUserdataType
    {
        typedef typename std::remove_const<
                typename remove_shared_ptr<
                typename std::remove_pointer<
                typename std::remove_reference<T
                >::type
                >::type
                >::type
                >::type type;

        constexpr static const bool value = UserdataType<isUserdataType::type>::name != 0;
    };

    template<>
    struct UserdataType<lua::LuaCallable>
    {
        constexpr static const char* name = "lua::LuaCallable";

        static void initialize(LuaStack& stack, lua::LuaCallable& object)
        {
        }
    };

    // Handle non-userdata types
    template <typename Sink>
    typename std::enable_if<
        !std::is_reference<Sink>::value && !isUserdataType<Sink>::value,
        Sink
    >::type
    get(const LuaIndex& index)
    {
        return Getter<Sink>::get(index);
    }

    template <typename Sink, typename std::enable_if<
        std::is_same<typename std::remove_reference<Sink>::type, LuaStack>::value, int>::type = 0>
    LuaStack& get(const LuaIndex& index)
    {
        // This bug typically crops up when we mistakenly try to treat a void(LuaStack&) function as an
        // arbitrary function.
        static_assert(!std::is_same<Sink, LuaStack&>::value,
            "Refusing to try to retrieve a LuaStack value from a stack, as this is almost certainly a bug."
        );
        throw "Unreachable";
    }

    template <typename Target>
    struct UserdataConverter
    {
        static const char* expectedName()
        {
            static_assert(UserdataType<Target>::name != 0, "Userdata name must be non-zero");
            return UserdataType<Target>::name;
        }

        static LuaUserdata* getUserdataObject(const LuaIndex& index)
        {
            LuaUserdata* const userdata(index.stack().get<LuaUserdata*>(index.pos()));
            if (!userdata) {
                std::stringstream msg;
                msg << "Userdata of type '" << expectedName() << "' must be provided at position "
                    << index.pos() << ", but provided Lua type was '" << index.stack().typestring(index.pos())
                    << "'";
                throw LuaException(msg.str());
             }
            if (userdata->dataType() != UserdataType<Target>::name) {
                std::stringstream msg;
                msg << "Userdata at position " << index.pos()
                    << " must be of type '" << expectedName() << "', but provided userdata type was '"
                    << userdata->dataType() << "'";
                throw LuaException(msg.str());
            }
            return userdata;
        }

        // Handle raw pointers
        template <typename Sink>
        static typename std::enable_if<
                std::is_pointer<Sink>::value,
                Target*>::type
        get(const LuaIndex& index)
        {
            //std::cout << "Converting to raw pointer" << std::endl;
            return static_cast<Target*>(getUserdataObject(index)->rawData());
        }

        // Handle values
        template <typename Sink>
        static typename std::enable_if<
                std::is_same<Sink, Target>::value,
                Target>::type
        get(const LuaIndex& index)
        {
            //std::cout << "Converting to value" << std::endl;
            return Sink(get<Target&>(index));
        }

        // Handle shared_ptrs
        template <typename Sink>
        static typename std::enable_if<
                !std::is_pointer<Sink>::value && std::is_constructible<Sink, std::shared_ptr<Target>>::value,
                std::shared_ptr<Target>
        >::type
        get(const LuaIndex& index)
        {
            //std::cout << "Converting to shared_ptr" << std::endl;
            LuaUserdata* userdata = getUserdataObject(index);
            return std::shared_ptr<Target>(
                userdata->data(),
                static_cast<Target*>(userdata->rawData())
            );
        }

        // Handle references
        template <typename Sink>
        static typename std::enable_if<
            std::is_reference<Sink>::value,
            Target&>::type
        get(const LuaIndex& index)
        {
            //std::cout << "Converting to reference" << std::endl;
            LuaUserdata* userdata = getUserdataObject(index);
            if (!userdata->rawData()) {
                std::stringstream msg;
                msg << "Userdata of type '" << expectedName() << "' at position "
                    << index.pos() << " must have valid data";
                throw LuaException(msg.str());
            }
            return *static_cast<Target*>(userdata->rawData());
        }
    };

    // Handle userdata references, values, and pointers
    template <typename Sink>
    typename std::enable_if<
        isUserdataType<Sink>::value
            && !std::is_constructible<typename std::remove_reference<Sink>::type, std::shared_ptr<typename isUserdataType<Sink>::type>>::value,
        Sink
    >::type
    get(const LuaIndex& index)
    {
        return UserdataConverter<typename isUserdataType<Sink>::type>::template get<Sink>(index);
    }

    // Handle userdata shared_ptr's
    template <typename Sink>
    typename std::enable_if<
        isUserdataType<Sink>::value
            && std::is_constructible<typename std::remove_reference<Sink>::type, std::shared_ptr<typename isUserdataType<Sink>::type>>::value,
        std::shared_ptr<typename isUserdataType<Sink>::type>
    >::type
    get(const LuaIndex& index)
    {
        return UserdataConverter<typename isUserdataType<Sink>::type>::template get<Sink>(index);
    }

    // Handle const references by returning a value
    template <typename Sink>
    typename std::enable_if<
        std::is_reference<Sink>::value && !isUserdataType<Sink>::value && std::is_const<typename std::remove_reference<Sink>::type>::value,
        typename remove_qualifiers<Sink>::type
    >::type
    get(const LuaIndex& index)
    {
        return get<typename remove_qualifiers<Sink>::type>(index);
    }

} // namespace lua
