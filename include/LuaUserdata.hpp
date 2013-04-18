#ifndef LUAUSERDATA_HEADER
#define LUAUSERDATA_HEADER

#include <memory>
#include <string>

class Lua;
class LuaStack;

class LuaUserdata
{
    bool _isRaw;
    std::shared_ptr<void> _data;
    void* _rawData;
    std::string _dataType;
public:

    LuaUserdata(void* const rawData, const std::string& dataType) :
        _isRaw(true),
        _data(),
        _rawData(rawData),
        _dataType(dataType)
    {
    }

    LuaUserdata(const std::shared_ptr<void>& data, const std::string& dataType) :
        _isRaw(false),
        _data(data),
        _rawData(nullptr),
        _dataType(dataType)
    {
    }

    bool isShared() const
    {
        return !_isRaw;
    }

    bool isRaw() const
    {
        return _isRaw;
    }

    /**
     * For userdata that map to a native C++ object, this should return
     * a pointer to that data. For those that do not have a native mapping,
     * it should return an empty pointer.
     */
    const std::shared_ptr<void>& data() const
    {
        return _data;
    }

    void* rawData()
    {
        return isShared() ? data().get() : _rawData;
    }

    void reset()
    {
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
};

#endif // LUAUSERDATA_HEADER
