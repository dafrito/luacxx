#ifndef LUACXX_CONVERT_SHARED_PTR_INCLUDED
#define LUACXX_CONVERT_SHARED_PTR_INCLUDED

#include "../stack.hpp"

#include <memory>

namespace lua {

template <class T>
struct Metatable<std::shared_ptr<T>>
{
    static const userdata_type& info()
    {
        return Metatable<T>::info();
    }

    static bool metatable(lua_State* const state, const int pos, std::shared_ptr<T>* const source)
    {
        if (source != nullptr) {
            Metatable<T>::metatable(state, pos, source->get());
        } else {
            Metatable<T>::metatable(state, pos, nullptr);
        }
        return false;
    }
};

} // namespace lua

#endif // LUACXX_CONVERT_SHARED_PTR_INCLUDED
