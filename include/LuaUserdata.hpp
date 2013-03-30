#ifndef LUAUSERDATA_HEADER
#define LUAUSERDATA_HEADER

#include <memory>
#include <QString>

class Lua;
class LuaStack;

class LuaUserdata
{
    std::shared_ptr<void> _data;
    QString _dataType;
public:

    LuaUserdata(const std::shared_ptr<void> data, const QString& dataType) :
        _data(data),
        _dataType(dataType)
    {
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
        return data().get();
    }

    /**
     * Identifies the type of raw data. Clients can use this value to ensure the
     * data provided by data is of an expected type.
     *
     * If this userdata does not have any raw data, then this should return an empty
     * string.
     */
    const QString& dataType() const
    {
        return _dataType;
    }
};

#endif // LUAUSERDATA_HEADER
