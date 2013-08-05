#include "LuaStack.hpp"

LuaUserdata::LuaUserdata(void* const rawData, const std::string& dataType, const bool manuallyManaged) :
        _isRaw(true),
        _isManaged(manuallyManaged),
        _manager(),
        _data(),
        _rawData(rawData),
        _dataType(dataType)
{
}

LuaUserdata::LuaUserdata(const std::shared_ptr<void>& data, const std::string& dataType, const bool manuallyManaged) :
    _isRaw(false),
    _isManaged(manuallyManaged),
    _manager(),
    _data(data),
    _rawData(nullptr),
    _dataType(dataType)
{
    if (_isManaged) {
        throw std::logic_error("shared_ptr userdata must not be manually managed");
    }
}

void LuaUserdata::addMethod(const std::string& name, const lua::LuaCallable& method)
{
    _methods[name] = method;
}

bool LuaUserdata::hasMethod(const std::string& name) const
{
    return _methods.find(name) != _methods.end();
}

void LuaUserdata::invoke(const std::string& name, LuaStack& stack)
{
    _methods[name](stack);
}
