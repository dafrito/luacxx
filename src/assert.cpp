#include "assert.hpp"

#include <sstream>

void lua::assert_type(const char* category, const lua::type& expected, const lua::index& given)
{
    if (given.type() != expected) {
        std::stringstream str;
        str << category;
        str << ": ";
        str << "The stack value at index " << given.pos() << " must be a ";
        str << lua::type_info(expected).name();
        str << " but a " << given.type().name() << " was given instead.";
        throw lua::exception(str.str());
    }
}
