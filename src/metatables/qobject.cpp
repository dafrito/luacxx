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
    void __index(Lua&, LuaStack& stack);
    void __newindex(Lua&, LuaStack& stack);

    void metaInvokeDirectMethod(Lua& lua, LuaStack& stack, QObject* const obj, const QMetaMethod& method);
    void metaInvokeLuaCallableMethod(Lua& lua, LuaStack& stack, QObject* const obj, const QMetaMethod& method);
    void callMethod(Lua& lua, LuaStack& stack);
} // namespace anonymous

namespace lua {
namespace metatable {

void qobject(LuaStack& stack, std::shared_ptr<QObject> obj)
{
    stack.set("__index", __index);
    stack.set("__newindex", __newindex);
}

} // namespace metatable
} // namespace lua

namespace {

bool retrieveArgs(LuaStack& stack, QObject** obj, const char** name)
{
    LuaUserdata* userdata = stack.object(1);
    if (!userdata) {
        stack.clear();
        stack.pushNil();
        return false;
    }
    *obj = static_cast<QObject*>(userdata->rawData());
    if (!obj) {
        // No object, so just return nil.
        stack.clear();
        stack.pushNil();
        return false;
    }
    *name = stack.cstring(2);
    if (!name) {
        stack.clear();
        stack.pushNil();
        return false;
    }
    stack.shift(2);
    return true;
}

void __index(Lua&, LuaStack& stack)
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
            stack << name;
            stack.push(callMethod, 1);
            return;
        }
    }
    stack.pushNil();
}

void __newindex(Lua&, LuaStack& stack)
{
    QObject* obj;
    const char* name;
    if (!retrieveArgs(stack, &obj, &name)) {
        return;
    }
    QVariant v;
    stack.to(&v, 1);
    obj->setProperty(name, v);
}

void metaInvokeDirectMethod(Lua& lua, LuaStack& stack, QObject* const obj, const QMetaMethod& method)
{
    QList<QVariant> variants;
    variants << QVariant(QMetaType::type(method.typeName()), (void*)0);
    QList<QByteArray> params = method.parameterTypes();
    for (int i = 0; i < params.count(); ++i) {
        int type = QMetaType::type(params.at(i));
        QVariant p(type, (void*)0);
        stack.to(p, i + 1);
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
        stack.push(variants.at(0));
    }
}

void metaInvokeLuaCallableMethod(Lua& lua, LuaStack& stack, QObject* const obj, const QMetaMethod& method)
{
    void* vvargs[3];
    vvargs[1] = &lua;
    vvargs[2] = &stack;
    QMetaObject::metacall(
        obj,
        QMetaObject::InvokeMetaMethod,
        method.methodIndex(),
        vvargs);
}

void callMethod(Lua& lua, LuaStack& stack)
{
    const char* name = stack.cstring(1);
    QObject* const obj = static_cast<QObject*>(stack.object(2)->rawData());
    stack.shift(2);

    const QMetaObject* const metaObject = obj->metaObject();

    // Prefer methods that handle the stack directly.
    for (int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i) {
        QMetaMethod method(metaObject->method(i));
        QString sig = QString::fromLatin1(method.signature());
        if (sig == QString(name) + "(Lua&,LuaStack&)") {
            // The method is capable of handling the Lua stack directly, so invoke it
            metaInvokeLuaCallableMethod(lua, stack, obj, method);
            return;
        }
    }

    // Look for any method that matches the requested name
    for (int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i) {
        QMetaMethod method(metaObject->method(i));
        QString sig = QString::fromLatin1(method.signature());
        if (sig.startsWith(QString(name) + "(")) {
            metaInvokeDirectMethod(lua, stack, obj, method);
            return;
        }
    }

    throw LuaException(string("No method found with name: ") + name);
}

} // namespace anonymous
