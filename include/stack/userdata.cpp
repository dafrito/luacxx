namespace lua {

    template <typename T>
    struct UserdataType
    {
        constexpr static const char* name = 0;
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

    // Handle primitive types
    template <typename Sink>
    typename std::enable_if<
        !std::is_reference<Sink>::value && !isUserdataType<Sink>::value,
        Sink
    >::type
    as(const LuaIndex& index)
    {
        typename std::remove_const<Sink>::type sink;
        index.stack().to(sink, index.pos());
        return sink;
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
            LuaUserdata* const userdata(index.stack().as<LuaUserdata*>(index.pos()));
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

        template <typename Sink>
        static typename std::enable_if<
                std::is_pointer<Sink>::value,
                Target*>::type
        as(const LuaIndex& index)
        {
            return static_cast<Target*>(getUserdataObject(index)->rawData());
        }

        template <typename Sink>
        static typename std::enable_if<
                std::is_same<Sink, Target>::value,
                Target>::type
        as(const LuaIndex& index)
        {
            return Sink(as<Target&>(index));
        }

        template <typename Sink>
        static typename std::enable_if<
                !std::is_pointer<Sink>::value && std::is_constructible<Sink, std::shared_ptr<Target>>::value,
                std::shared_ptr<Target>
        >::type
        as(const LuaIndex& index)
        {
            LuaUserdata* userdata = getUserdataObject(index);
            return std::shared_ptr<Target>(
                userdata->data(),
                static_cast<Target*>(userdata->rawData())
            );
        }

        template <typename Sink>
        static typename std::enable_if<
            std::is_reference<Sink>::value,
            Target&>::type
        as(const LuaIndex& index)
        {
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
    as(const LuaIndex& index)
    {
        return UserdataConverter<typename isUserdataType<Sink>::type>::template as<Sink>(index);
    }

    // Handle userdata shared_ptr's
    template <typename Sink>
    typename std::enable_if<
        isUserdataType<Sink>::value
            && std::is_constructible<typename std::remove_reference<Sink>::type, std::shared_ptr<typename isUserdataType<Sink>::type>>::value,
        std::shared_ptr<typename isUserdataType<Sink>::type>
    >::type
    as(const LuaIndex& index)
    {
        return UserdataConverter<typename isUserdataType<Sink>::type>::template as<Sink>(index);
    }

    // Handle const references by returning a value
    template <typename Sink>
    typename std::enable_if<
        std::is_reference<Sink>::value && !isUserdataType<Sink>::value && std::is_const<typename std::remove_reference<Sink>::type>::value,
        typename remove_qualifiers<Sink>::type
    >::type
    as(const LuaIndex& index)
    {
        return as<typename remove_qualifiers<Sink>::type>(index);
    }

} // namespace lua
