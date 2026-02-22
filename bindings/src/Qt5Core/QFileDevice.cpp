#include "QFileDevice.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QFlags.hpp"
#include "QString.hpp"
#include "QByteArray.hpp"

void lua::QFileDevice_metatable(lua_State* const state, const int pos)
{
    lua::QIODevice_metatable(state, pos);

    lua::index mt(state, pos);
    mt["error"] = &QFileDevice::error;
    mt["fileName"] = &QFileDevice::fileName;
    mt["flush"] = &QFileDevice::flush;
    mt["handle"] = &QFileDevice::handle;
    mt["map"] = &QFileDevice::map;
    mt["permissions"] = &QFileDevice::permissions;
    mt["resize"] = &QFileDevice::resize;
    mt["setPermissions"] = &QFileDevice::setPermissions;
    mt["unmap"] = &QFileDevice::unmap;
    mt["unsetError"] = &QFileDevice::unsetError;
}

int luaopen_Qt5Core_QFileDevice(lua_State* const state)
{
    lua::thread env(state);

    env["QFileDevice"] = lua::value::table;
    auto t = env["QFileDevice"];

    // enum QFileDevice::FileError
    t["NoError"] = QFileDevice::NoError;
    t["ReadError"] = QFileDevice::ReadError;
    t["WriteError"] = QFileDevice::WriteError;
    t["FatalError"] = QFileDevice::FatalError;
    t["ResourceError"] = QFileDevice::ResourceError;
    t["OpenError"] = QFileDevice::OpenError;
    t["AbortError"] = QFileDevice::AbortError;
    t["TimeOutError"] = QFileDevice::TimeOutError;
    t["UnspecifiedError"] = QFileDevice::UnspecifiedError;
    t["RemoveError"] = QFileDevice::RemoveError;
    t["RenameError"] = QFileDevice::RenameError;
    t["PositionError"] = QFileDevice::PositionError;
    t["ResizeError"] = QFileDevice::ResizeError;
    t["PermissionsError"] = QFileDevice::PermissionsError;
    t["CopyError"] = QFileDevice::CopyError;

    // enum QFileDevice::FileHandleFlag
    t["AutoCloseHandle"] = QFileDevice::AutoCloseHandle;
    t["DontCloseHandle"] = QFileDevice::DontCloseHandle;

    // enum QFileDevice::MemoryMapFlags
    t["NoOptions"] = QFileDevice::NoOptions;

    // enum QFileDevice::Permission
    t["ReadOwner"] = QFileDevice::ReadOwner;
    t["WriteOwner"] = QFileDevice::WriteOwner;
    t["ExeOwner"] = QFileDevice::ExeOwner;
    t["ReadUser"] = QFileDevice::ReadUser;
    t["WriteUser"] = QFileDevice::WriteUser;
    t["ExeUser"] = QFileDevice::ExeUser;
    t["ReadGroup"] = QFileDevice::ReadGroup;
    t["WriteGroup"] = QFileDevice::WriteGroup;
    t["ExeGroup"] = QFileDevice::ExeGroup;
    t["ReadOther"] = QFileDevice::ReadOther;
    t["WriteOther"] = QFileDevice::WriteOther;
    t["ExeOther"] = QFileDevice::ExeOther;

    return 0;
}
