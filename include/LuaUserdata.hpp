#ifndef LUAUSERDATA_HEADER
#define LUAUSERDATA_HEADER

#include <memory>
#include <functional>
#include <string>

#include "LuaException.hpp"

class Lua;
class LuaStack;

class LuaUserdata
{
    bool _isRaw;
    bool _isManaged;
    std::function<void()> _manager;
    std::shared_ptr<void> _data;
    void* _rawData;
    std::string _dataType;
public:

    LuaUserdata(void* const rawData, const std::string& dataType, const bool manuallyManaged = false) :
        _isRaw(true),
        _isManaged(manuallyManaged),
        _manager(),
        _data(),
        _rawData(rawData),
        _dataType(dataType)
    {
    }

    LuaUserdata(const std::shared_ptr<void>& data, const std::string& dataType, const bool manuallyManaged = false) :
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

    bool isShared() const
    {
        return !_isRaw;
    }

    bool isRaw() const
    {
        return _isRaw;
    }

    bool managed() const
    {
        return _isManaged;
    }

    template <class Func>
    void setManager(const Func& func)
    {
        if (!managed()) {
            throw std::logic_error("Userdata must not have a manager if it's not managed");
        }
        if (_manager) {
            throw std::logic_error("Refusing to overwrite an existing manager");
        }
        _manager = func;
    }

    void assertData() const
    {
        if (!hasData()) {
            throw LuaException("Userdata must not be accessed if it has no underlying data");
        }
    }

    /**
     * For userdata that map to a native C++ object, this should return
     * a pointer to that data. For those that do not have a native mapping,
     * it should return an empty pointer.
     */
    const std::shared_ptr<void>& data() const
    {
        assertData();
        return _data;
    }

    void* rawData() const
    {
        assertData();
        return isShared() ? data().get() : _rawData;
    }

    bool hasData() const
    {
        return _data || _rawData;
    }

    void reset()
    {
        _manager = nullptr;
        _rawData = nullptr;
        _data.reset();
    }

    /**
     * Identifies the type of raw data. Clients can use this value to ensure the
     * data provided by data is of an expected type.
     *
     * If this userdata does not have any raw data, then this should return an empty
     * string.
     */
    const std::string& dataType() const
    {
        return _dataType;
    }

    ~LuaUserdata()
    {
        if (managed() && !!_manager) {
            _manager();
        }
    }
};

#endif // LUAUSERDATA_HEADER
