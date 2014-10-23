#include "QCoreApplication.hpp"
#include "QObject.hpp"
#include "QEventLoop.hpp"
#include "QAbstractNativeEventFilter.hpp"
#include "QStringList.hpp"
#include "QEvent.hpp"
#include "QTranslator.hpp"
#include "QAbstractEventDispatcher.hpp"
#include "Qt.hpp"
#include "QFlags.hpp"

#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"
#include "../thread.hpp"

#include <QCoreApplication>

lua::QCoreApplicationArgs* lua::save_arguments(lua::index arg)
{
    auto state = arg.state();

    // Get an arguments struct, to persist the passed arguments. The size is all the arguments from
    // the given position to the end.
    auto arguments = lua::make<lua::QCoreApplicationArgs>(state, lua_gettop(state) - arg.pos() + 1);

    while (arg.pos() < lua_gettop(state)) {
        // Get the string at the given arg position
        auto value = lua::get<const char*>(arg);
        if (!value || strlen(value) == 0) {
            value = "";
        }

        // Assign it within the arguments struct, adjusting for differences in position.
        arguments->set(arg.pos() - 2, value);
        ++arg;
    }

    return arguments;
}

void lua::QCoreApplication_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["installNativeEventFilter"] = &QCoreApplication::installNativeEventFilter;
    mt["notify"] = &QCoreApplication::notify;
    mt["removeNativeEventFilter"] = &QCoreApplication::removeNativeEventFilter;
}

int QCoreApplication_processEvents(lua_State* const state)
{
    switch (lua_gettop(state)) {
        case 0:
            QCoreApplication::processEvents();
            break;
        case 1:
            QCoreApplication::processEvents(
                lua::get<QEventLoop::ProcessEventsFlags>(state, 1)
            );
            break;
        default:
            QCoreApplication::processEvents(
                lua::get<QEventLoop::ProcessEventsFlags>(state, 1),
                lua::get<int>(state, 2)
            );
            break;
    }
    return 0;
}

int luaopen_Qt5Core_QCoreApplication(lua_State* const state)
{
    luaL_requiref(state, "luacxx.QEventLoop", luaopen_Qt5Core_QEventLoop, false);

    lua::thread env(state);

    env["QCoreApplication"] = lua::value::table;
    env["QCoreApplication"]["new"] = lua::QCoreApplication_new<QCoreApplication>;
    auto t = env["QCoreApplication"];

    t["addLibraryPath"] = &QCoreApplication::addLibraryPath;
    t["applicationDirPath"] = &QCoreApplication::applicationDirPath;
    t["applicationFilePath"] = &QCoreApplication::applicationFilePath;
    t["applicationName"] = &QCoreApplication::applicationName;
    t["applicationPid"] = &QCoreApplication::applicationPid;
    t["applicationVersion"] = &QCoreApplication::applicationVersion;
    t["arguments"] = &QCoreApplication::arguments;
    t["closingDown"] = &QCoreApplication::closingDown;
    t["eventDispatcher"] = &QCoreApplication::eventDispatcher;
    t["exec"] = &QCoreApplication::exec;
    t["exit"] = &QCoreApplication::exit;
    t["flush"] = &QCoreApplication::flush;
    t["installTranslator"] = &QCoreApplication::installTranslator;
    t["instance"] = &QCoreApplication::instance;
    t["isQuitLockEnabled"] = &QCoreApplication::isQuitLockEnabled;
    t["libraryPaths"] = &QCoreApplication::libraryPaths;
    t["organizationDomain"] = &QCoreApplication::organizationDomain;
    t["organizationName"] = &QCoreApplication::organizationName;
    t["postEvent"] = &QCoreApplication::postEvent;
    t["processEvents"] = QCoreApplication_processEvents;
    t["removeLibraryPath"] = &QCoreApplication::removeLibraryPath;
    t["removePostedEvents"] = &QCoreApplication::removePostedEvents;
    t["removeTranslator"] = &QCoreApplication::removeTranslator;
    t["sendEvent"] = &QCoreApplication::sendEvent;
    t["sendPostedEvents"] = &QCoreApplication::sendPostedEvents;
    t["setApplicationName"] = &QCoreApplication::setApplicationName;
    t["setApplicationVersion"] = &QCoreApplication::setApplicationVersion;
    t["setAttribute"] = &QCoreApplication::setAttribute;
    t["setEventDispatcher"] = &QCoreApplication::setEventDispatcher;
    t["setLibraryPaths"] = &QCoreApplication::setLibraryPaths;
    t["setOrganizationDomain"] = &QCoreApplication::setOrganizationDomain;
    t["setOrganizationName"] = &QCoreApplication::setOrganizationName;
    t["setQuitLockEnabled"] = &QCoreApplication::setQuitLockEnabled;
    t["startingUp"] = &QCoreApplication::startingUp;
    t["testAttribute"] = &QCoreApplication::testAttribute;
    t["translate"] = &QCoreApplication::translate;

    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    t["setSetuidAllowed"] = &QCoreApplication::setSetuidAllowed;
    t["isSetuidAllowed"] = &QCoreApplication::isSetuidAllowed;
    #endif

    return 0;
}
