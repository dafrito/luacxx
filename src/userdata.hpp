#ifndef LUA_CXX_USERDATA_HEADER
#define LUA_CXX_USERDATA_HEADER

namespace lua {

enum class userdata_storage {
    value,
    pointer,
    shared_ptr
};

struct userdata_block {
    userdata_storage storage;

public:
    userdata_block(const lua::userdata_storage& storage) :
        storage(storage)
    {
    }
};

} // namespace lua

#endif // LUA_CXX_USERDATA_HEADER
