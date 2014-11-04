#include "QObject.hpp"
#include "QObjectSlot.hpp"
#include "QVariant.hpp"
#include "QString.hpp"
#include "QEventFilter.hpp"

#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>

#include "../algorithm.hpp"
#include "../reference.hpp"
#include "../link.hpp"
#include "../convert/callable.hpp"

#include "QList.hpp"
#include "QByteArray.hpp"
#include "QEvent.hpp"
#include "QMetaObject.hpp"
#include "QMetaMethod.hpp"
#include "QThread.hpp"
#include "QString.hpp"
#include "QVariant.hpp"

#include <cassert>
#include <functional>
#include <iostream>

int QObject_connect(lua_State* const state)
{
    auto obj = lua::get<QObject*>(state, 1);
    auto name = lua::get<std::string>(state, 2);
    lua::index callable(state, 3);
    lua::assert_type("lua::QObject_connect", lua::type::function, lua::index(state, 3));

    const QMetaObject* const metaObject = obj->metaObject();

    // Find the signal
    int signalId = -1;
    if (name.find("(") != std::string::npos) {
        QByteArray signalSig = QMetaObject::normalizedSignature(name.c_str());
        signalId = metaObject->indexOfSignal(signalSig);
    } else {
        for (int i = 0; i < metaObject->methodCount(); ++i) {
            if (lua::QMetaMethod_signature(metaObject->method(i)).startsWith(name.c_str())) {
                if (signalId != -1) {
                    throw lua::error(std::string("Ambiguous signal name: ") + name);
                }
                signalId = i;
            }
        }
    }
    if (signalId == -1) {
        throw lua::error(std::string("No signal for name: ") + name);
    }

    auto slotWrapper = new lua::QObjectSlot(
        obj,
        metaObject->method(signalId),
        callable
    );
    lua::QObjectSlot::connect(slotWrapper);

    QMetaObject::connect(obj, signalId, slotWrapper, 0);

    // Return a method to disconnect this slot
    lua_settop(state, 0);
    lua::push(state, std::function<void()>([=]() {
        lua::QObjectSlot::disconnect(slotWrapper);
    }));
    return 1;
}

int QObject_disconnect(lua_State* const state)
{
    return 0;
}
int QObject_findChild(lua_State* const state)
{
    return 0;
}
int QObject_findChildren(lua_State* const state)
{
    return 0;
}
int QObject_startTimer(lua_State* const state)
{
    return 0;
}

void lua::QObject_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

    mt["blockSignals"] = &QObject::blockSignals;
    //mt["children"] = &QObject::children;
    mt["disconnect"] = QObject_disconnect;
    mt["dumpObjectInfo"] = &QObject::dumpObjectInfo;
    mt["dumpObjectTree"] = &QObject::dumpObjectTree;
    mt["dynamicPropertyNames"] = &QObject::dynamicPropertyNames;
    mt["event"] = &QObject::event;
    mt["eventFilter"] = &QObject::eventFilter;
    mt["findChild"] = QObject_findChild;
    mt["findChildren"] = QObject_findChildren;
    mt["inherits"] = &QObject::inherits;
    //mt["installEventFilter"] = &QObject::installEventFilter;
    mt["isWidgetType"] = &QObject::isWidgetType;
    mt["isWindowType"] = &QObject::isWindowType;
    mt["killTimer"] = &QObject::killTimer;
    mt["metaObject"] = &QObject::metaObject;
    mt["moveToThread"] = &QObject::moveToThread;
    mt["objectName"] = &QObject::objectName;
    mt["parent"] = &QObject::parent;
    mt["property"] = &QObject::property;
    //mt["removeEventFilter"] = &QObject::removeEventFilter;
    mt["setObjectName"] = &QObject::setObjectName;
    mt["setParent"] = &QObject::setParent;
    mt["setProperty"] = &QObject::setProperty;
    mt["signalsBlocked"] = &QObject::signalsBlocked;
    mt["startTimer"] = QObject_startTimer;
    mt["thread"] = &QObject::thread;

    mt["installEventFilter"] = lua_CFunction([](lua_State* const state) {
        auto obj = lua::get<QObject*>(state, 1);
        lua::index filter_arg(state, 2);
        lua_settop(state, 2);

        // Allow functions to be converted to a QEventFilter
        if (filter_arg.type().function()) {
            auto filter = lua::make<QEventFilter>(state, state);
            filter->setDelegate(filter_arg);
            obj->installEventFilter(filter);
        } else {
            auto filter = filter_arg.get<QObject*>();
            obj->installEventFilter(filter);

            // Just use the filter as its own key
            lua_pushvalue(state, 2);
        }

        // [obj, filter delegate, QEventFilter]
        lua_getmetatable(state, 1);
        lua_insert(state, 2);
        // [obj, mt, filter delegate, QEventFilter]
        lua_settable(state, 2);

        return 0;
    });

    mt["removeEventFilter"] = lua_CFunction([](lua_State* const state) {
        auto obj = lua::get<QObject*>(state, 1);
        lua::index filter_arg(state, 2);
        lua_settop(state, 2);

        // Check the metatable for a cached value
        lua_getmetatable(state, 1);
        lua::table::get(lua::index(state, -1), filter_arg);
        if (lua::index(state, -1)) {
            // We have one, so use it to clear our filter
            obj->removeEventFilter(lua::index(state, -1).get<QObject*>());
        }
        lua_pop(state, 1);

        // Clear the cached entry
        lua::table::set(lua::index(state, -1), filter_arg, lua::value::nil);

        return 0;
    });

    mt["__index"] = lua_CFunction([](lua_State* const state) {
        auto obj = lua::get<QObject*>(state, 1);
        auto name = lua::get<const char*>(state, 2);

        // Properties
        QVariant propValue = obj->property(name);
        if (propValue.isValid()) {
            lua::push(state, propValue);
            return 1;
        }

        // Do we have a cached value?
        lua_getmetatable(state, 1);
        lua::push(state, name);
        lua_rawget(state, -2);
        if (lua_type(state, -1) != LUA_TNIL) {
            // We do. Return it directly.
            return 1;
        } else {
            // Nope, so clean up and move on. Keep the metatable around.
            lua_pop(state, 1);
        }

        // Invokables
        const QMetaObject* metaObject = obj->metaObject();
        for (int i = 0; i < metaObject->methodCount(); ++i) {
            auto method = metaObject->method(i);
            QString sig = lua::QMetaMethod_signature(method);

            if (sig.startsWith(QString(name) + "(", Qt::CaseInsensitive)) {
                lua::push(state, method);
                goto cache_and_return;
            }
        }

        // Slot connections
        if (QString(name).compare("connect", Qt::CaseInsensitive) == 0) {
            lua::push(state, QObject_connect);
            goto cache_and_return;
        }

        // Nothing found, so just return nothing.
        return 0;
    cache_and_return:
        // Cache the value for future use.

        // [..., metatable, method]
        lua::push(state, name);
        lua_pushvalue(state, -2);
        // [..., metatable, method, name, method]
        lua_rawset(state, -4);
        return 1;
    });

    mt["__newindex"] = lua_CFunction([](lua_State* const state) {
        auto obj = lua::get<QObject*>(state, 1);
        auto name = lua::get<const char*>(state, 2);

        // Properties
        QVariant propValue = obj->property(name);
        if (!propValue.isValid()) {
            throw lua::error("New properties must not be added to this userdata");
        }

        lua::store(propValue, state, 3);
        obj->setProperty(name, propValue);

        return 0;
    });

    mt["__tostring"] = lua_CFunction([](lua_State* const state) {
        // Print something like QObject@0xd3adb33f
        auto obj = lua::get<QObject*>(state, 1);
        lua_settop(state, 0);

        std::stringstream str;
        str << obj->metaObject()->className();
        str << "@" << obj;
        lua::push(state, str.str());

        return 1;
    });

    mt["on_retain_userdata"] = lua_CFunction([](lua_State* const state) {
        auto obj = lua::get<QObject*>(state, 1);
        auto userdata_block = lua::get_userdata_block(state, 1);
        QObject::connect(obj, &QObject::destroyed, [state, userdata_block](QObject* obj) {
            if (!userdata_block->retained()) {
                return;
            }
            if (!userdata_block->destroyed()) {
                userdata_block->release(state);
                userdata_block->~userdata_block();
            }
            return;
        });
        return 0;
    });
}
