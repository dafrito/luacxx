#include "metatables.hpp"

#include "LuaEnvironment.hpp"
#include "LuaStack.hpp"
#include "LuaUserdata.hpp"
#include "LuaException.hpp"

#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>
#include <functional>

namespace {
    void __index(LuaStack& stack);
    void __newindex(LuaStack& stack);

    void metaInvokeDirectMethod(LuaStack& stack, QObject* const obj, const QMetaMethod& method);
    void metaInvokeLuaCallableMethod(LuaStack& stack, QObject* const obj, const QMetaMethod& method);
    void callMethod(LuaStack& stack);
} // namespace anonymous

LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<QObject>& ptr)
{
    stack << LuaUserdata(ptr, "QObject");

    stack.pushMetatable();
    lua::metatable::qobject(stack, ptr);
    stack.setMetatable();
    return stack;
}

LuaStack& operator>>(LuaStack& stack, std::shared_ptr<QObject>& ptr)
{
    ptr.reset();
    LuaUserdata* userdata;
    stack >> userdata;
    if (!userdata) {
        return stack;
    }
    if (userdata->dataType() != "QObject") {
        return stack;
    }
    ptr = std::shared_ptr<QObject>(
        userdata->data(),
        static_cast<QObject*>(userdata->rawData())
    );
    return stack;
}

namespace lua {
namespace metatable {

void qobject(LuaStack& stack, const std::shared_ptr<QObject>& obj)
{
    stack.pushPointer(obj.get());
    stack.push(__index, 1);
    stack.pushedSet("__index", -2);

    stack.pushPointer(obj.get());
    stack.push(__newindex, 1);
    stack.pushedSet("__newindex", -2);
}

} // namespace metatable
} // namespace lua

namespace {

bool retrieveArgs(LuaStack& stack, QObject** obj, const char** name)
{
    void* validatingUserdata = stack.pointer(1);
    stack.shift();

    auto userdata = stack.as<LuaUserdata*>(1);
    if (!userdata) {
        goto fail;
    }

    if (!userdata->data()) {
        goto fail;
    }

    *obj = static_cast<QObject*>(userdata->rawData());

    if (validatingUserdata != *obj) {
        // The metamethod was not called with the expected userdata object.
        goto fail;
    }

    stack.at(2) >> *name;
    if (!name) {
        goto fail;
    }
    stack.shift(2);

    return true;

    fail:
        *obj = nullptr;
        *name = nullptr;
        stack.clear();
        stack.pushNil();
        return false;
}

void __index(LuaStack& stack)
{
    QObject* obj;
    const char* name;
    if (!retrieveArgs(stack, &obj, &name)) {
        return;
    }

    // First, check for properties
    QVariant propValue = obj->property(name);
    if (propValue.isValid()) {
        stack << propValue;
        return;
    }
    // Not a property, so look for a method for the given the name.
    const QMetaObject* const metaObject = obj->metaObject();
    for(int i = 0; i < metaObject->methodCount(); ++i) {
        QString sig = QString::fromLatin1(metaObject->method(i).signature());
        if (sig.startsWith(QString(name) + "(")) {
            stack.pushPointer(obj);
            stack << name;
            stack.push(callMethod, 2);
            return;
        }
    }
    stack.pushNil();
}

void __newindex(LuaStack& stack)
{
    QObject* obj;
    const char* name;
    if (!retrieveArgs(stack, &obj, &name)) {
        return;
    }
    QVariant v;
    stack.begin() >> v;
    obj->setProperty(name, v);
}

void callMethod(LuaStack& stack)
{
    QObject* validatingUserdata = static_cast<QObject*>(stack.pointer(1));
    stack.shift();

    auto name = stack.as<const char*>(1);
    auto userdata = stack.as<LuaUserdata*>(2);
    if (!userdata) {
        stack.error("Method must be invoked with a valid userdata");
    }
    if (userdata->rawData() != validatingUserdata) {
        if (!userdata->data()) {
            stack.error("Userdata must have an associated internal object");
        }
        if (userdata->dataType() != "QObject") {
            stack.error(
                QString("Userdata must be of type QObject, but was given: '%1'").arg(userdata->dataType())
            );
        }
        stack.error("Userdata provided with method call must match the userdata used to access that method");
    }
    QObject* const obj = validatingUserdata;
    stack.shift(2);

    const QMetaObject* const metaObject = obj->metaObject();

    // Prefer methods that handle the stack directly.
    for (int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i) {
        QMetaMethod method(metaObject->method(i));
        QString sig = QString::fromLatin1(method.signature());
        if (sig == QString(name) + "(LuaStack&)") {
            // The method is capable of handling the Lua stack directly, so invoke it
            metaInvokeLuaCallableMethod(stack, obj, method);
            return;
        }
    }

    // Look for any method that matches the requested name
    for (int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i) {
        QMetaMethod method(metaObject->method(i));
        QString sig = QString::fromLatin1(method.signature());
        if (sig.startsWith(QString(name) + "(")) {
            metaInvokeDirectMethod(stack, obj, method);
            return;
        }
    }

    stack.error(QString("No method found with name '%1'").arg(name));
}

void metaInvokeDirectMethod(LuaStack& stack, QObject* const obj, const QMetaMethod& method)
{
    QList<QVariant> variants;
    variants << QVariant(QMetaType::type(method.typeName()), (void*)0);
    QList<QByteArray> params = method.parameterTypes();
    for (int i = 0; i < params.count(); ++i) {
        int type = QMetaType::type(params.at(i));
        QVariant p(type, (void*)0);
        stack.at(i + 1) >> p;
        p.convert((QVariant::Type)type);
        variants << p;
    }
    void* vvargs[11];
    for (int i = 0; i < variants.size(); ++i) {
        vvargs[i] = const_cast<void*>(variants.at(i).data());
    }
    QMetaObject::metacall(
        obj,
        QMetaObject::InvokeMetaMethod,
        method.methodIndex(),
        vvargs);
    if (variants.at(0).isValid()) {
        stack << variants.at(0);
    }
}

void metaInvokeLuaCallableMethod(LuaStack& stack, QObject* const obj, const QMetaMethod& method)
{
    void* vvargs[2];
    vvargs[1] = &stack;
    QMetaObject::metacall(
        obj,
        QMetaObject::InvokeMetaMethod,
        method.methodIndex(),
        vvargs);
}

} // namespace anonymous
