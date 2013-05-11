#include "userdata.hpp"

#include "LuaEnvironment.hpp"
#include "LuaStack.hpp"
#include "LuaValue.hpp"
#include "LuaUserdata.hpp"
#include "LuaException.hpp"
#include "QObjectSlot.hpp"

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
    void connectSlot(LuaStack& stack);

} // namespace anonymous

void lua::qobject(LuaStack& stack, QObject& obj)
{
    stack.pushMetatable();
    stack.pushPointer(&obj);
    stack.push(__index, 1);
    stack.pushedSet("__index", -2);

    stack.pushPointer(&obj);
    stack.push(__newindex, 1);
    stack.pushedSet("__newindex", -2);
    stack.setMetatable();
}

namespace std {
    template<>
    class hash<QVariant::Type>
    {
    public:
        size_t operator()(const QVariant::Type& value) const
        {
            return static_cast<int>(value);
        }
    };
}

namespace {

static std::unordered_map<QVariant::Type, std::function<void(LuaStack&, const QVariant&)>> variantPushers;
static std::unordered_map<QVariant::Type, std::function<void(LuaIndex&, QVariant&)>> variantStorers;

}

void lua::qvariantPusher(const QVariant::Type& type, const std::function<void(LuaStack&, const QVariant&)>& mapper)
{
    variantPushers[type] = mapper;
}

void lua::qvariantStorer(const QVariant::Type& type, const std::function<void(LuaIndex&, QVariant&)>& mapper)
{
    variantStorers[type] = mapper;
}

void lua::pushVariant(LuaStack& stack, const QVariant& variant)
{
    switch (variant.type()) {
    case QVariant::Invalid:
        lua::push(stack, lua::value::nil);
        break;
    case QVariant::Bool:
        lua::push(stack, variant.toBool());
        break;
    case QVariant::Char:
        lua::push(stack, variant.toChar());
        break;
    case QVariant::Int:
        lua::push(stack, variant.toInt());
        break;
    case QVariant::Double:
    case QVariant::UInt:
        lua::push(stack, variant.toDouble());
        break;
    case QVariant::String:
        lua::push(stack, variant.toString());
        break;
    default:
        auto converter = variantPushers.find(variant.type());
        if (converter != variantPushers.end()) {
            converter->second(stack, variant);
        } else {
            throw std::logic_error(std::string("QVariant type not supported: ") + variant.typeName());
        }
    }
}

void lua::storeVariant(LuaIndex& index, QVariant& sink)
{
    auto pos = index.pos();
    LuaStack& stack = index.stack();
    switch (sink.type()) {
    case QVariant::Invalid:
        sink.clear();
        break;
    case QVariant::Bool:
        sink.setValue(stack.as<bool>(pos));
        break;
    case QVariant::Char:
        sink.setValue(QChar(stack.as<char>(pos)));
        break;
    case QVariant::Int:
    case QVariant::UInt:
        sink.setValue(stack.as<int>(pos));
        break;
    case QVariant::Double:
        sink.setValue(stack.as<double>(pos));
        break;
    case QVariant::String:
        sink.setValue(stack.as<QString>(pos));
        break;
    default:
        auto converter = variantStorers.find(sink.type());
        if (converter != variantStorers.end()) {
            converter->second(index, sink);
        } else {
            throw std::logic_error(std::string("QVariant type not supported: ") + sink.typeName());
        }
    }

}

namespace {

bool retrieveArgs(LuaStack& stack, QObject** obj, const char** name)
{
    void* validatingUserdata = stack.pointer(1);
    stack.shift();

    auto userdata = stack.as<LuaUserdata*>(1);
    if (!userdata) {
        goto fail;
    }

    if (!userdata->rawData()) {
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
        lua::push(stack, lua::value::nil);
        return false;
}

QString getSignature(const QMetaMethod& method)
{
    #if QT_VERSION >= 0x050000
    return QString::fromLatin1(method.methodSignature());
    #else
    return QString::fromLatin1(method.signature());
    #endif
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
        lua::push(stack, propValue);
        return;
    }

    if (QString(name) == "connect") {
        stack.pushPointer(obj);
        lua::push(stack, connectSlot, 1);
        return;
    }

    // Not a property, so look for a method for the given the name.
    const QMetaObject* const metaObject = obj->metaObject();
    for(int i = 0; i < metaObject->methodCount(); ++i) {
        QString sig = getSignature(metaObject->method(i));
        if (sig.startsWith(QString(name) + "(")) {
            stack.pushPointer(obj);
            lua::push(stack, name);
            lua::push(stack, callMethod, 2);
            return;
        }
    }
    lua::push(stack, lua::value::nil);
}

void __newindex(LuaStack& stack)
{
    QObject* obj;
    const char* name;
    if (!retrieveArgs(stack, &obj, &name)) {
        return;
    }
    QVariant prop = obj->property(name);
    if (!prop.isValid()) {
        throw LuaException("New properties must not be added to this userdata");
    }
    stack.begin() >> prop;
    obj->setProperty(name, prop);
}

void connectSlot(LuaStack& stack)
{
    QObject* validatingUserdata = static_cast<QObject*>(stack.pointer(1));
    stack.shift();

    auto userdata = stack.as<LuaUserdata*>(1);
    if (!userdata) {
        throw LuaException("Method must be invoked with a valid userdata");
    }
    if (userdata->rawData() != validatingUserdata) {
        if (!userdata->data()) {
            throw LuaException("Userdata must have an associated internal object");
        }
        if (userdata->dataType() != "QObject") {
            throw LuaException(
                QString("Userdata must be of type QObject, but was given: '%1'")
                    .arg(userdata->dataType().c_str())
                    .toStdString()
            );
        }
        throw LuaException("Userdata provided with method call must match the userdata used to access that method");
    }
    QObject* const obj = validatingUserdata;
    stack.shift();

    if (stack.size() != 2) {
        throw LuaException(
            QString("Exactly 2 arguments must be provided. Given %1").arg(stack.size()).toStdString()
        );
    }

    if (stack.typestring(1) != "string") {
        throw LuaException("signal must be a string");
    }
    auto signal = stack.as<std::string>(1);
    stack.shift();

    auto slot = stack.save();
    if (slot.typestring() != "function") {
        throw LuaException("Provided slot must be a function");
    }

    const QMetaObject* const metaObject = obj->metaObject();

    // Find the signal

    int signalId = -1;
    if (signal.find("(") != std::string::npos) {
        QByteArray signalSig = QMetaObject::normalizedSignature(signal.c_str());
        signalId = metaObject->indexOfSignal(signalSig);
    } else {
        for (int i = 0; i < metaObject->methodCount(); ++i) {
            if (getSignature(metaObject->method(i)).startsWith(signal.c_str())) {
                if (signalId != -1) {
                    throw LuaException(std::string("Ambiguous signal name: ") + signal);
                }
                signalId = i;
            }
        }
    }
    if (signalId == -1) {
        throw LuaException(std::string("No signal for name: ") + signal);
    }

    auto slotWrapper = new lua::QObjectSlot(
        obj,
        metaObject->method(signalId),
        slot
    );
    lua::QObjectSlot::connect(slotWrapper);

    QMetaObject::connect(obj, signalId, slotWrapper, 0);

    stack.clear();

    lua::push(stack, std::function<void()>([=]() {
        lua::QObjectSlot::disconnect(slotWrapper);
    }));
}

void callMethod(LuaStack& stack)
{
    QObject* validatingUserdata = static_cast<QObject*>(stack.pointer(1));
    stack.shift();

    auto name = stack.as<const char*>(1);
    auto userdata = stack.as<LuaUserdata*>(2);
    if (!userdata) {
        throw LuaException("Method must be invoked with a valid userdata");
    }
    if (userdata->rawData() != validatingUserdata) {
        if (!userdata->data()) {
            throw LuaException("Userdata must have an associated internal object");
        }
        if (userdata->dataType() != "QObject") {
            throw LuaException(
                QString("Userdata must be of type QObject, but was given: '%1'")
                    .arg(userdata->dataType().c_str())
                    .toStdString()
            );
        }
        throw LuaException("Userdata provided with method call must match the userdata used to access that method");
    }
    QObject* const obj = validatingUserdata;
    stack.shift(2);

    const QMetaObject* const metaObject = obj->metaObject();

    // Prefer methods that handle the stack directly.
    for (int i = 0; i < metaObject->methodCount(); ++i) {
        QMetaMethod method(metaObject->method(i));
        QString sig = getSignature(method);
        if (sig == QString(name) + "(LuaStack&)") {
            // The method is capable of handling the Lua stack directly, so invoke it
            metaInvokeLuaCallableMethod(stack, obj, method);
            return;
        }
    }

    // Look for any method that matches the requested name
    for (int i = 0; i < metaObject->methodCount(); ++i) {
        QMetaMethod method(metaObject->method(i));
        QString sig = getSignature(method);
        if (sig.startsWith(QString(name) + "(")) {
            metaInvokeDirectMethod(stack, obj, method);
            return;
        }
    }

    throw LuaException(QString("No method found with name '%1'").arg(name).toStdString());
}

void metaInvokeDirectMethod(LuaStack& stack, QObject* const obj, const QMetaMethod& method)
{
    QList<QVariant> variants;
    auto returnType = QMetaType::type(method.typeName());
    if (returnType != QMetaType::Void) {
        variants << QVariant(QMetaType::type(method.typeName()), nullptr);
    }
    else {
        variants << QVariant();
    }
    QList<QByteArray> params = method.parameterTypes();
    for (int i = 0; i < params.count(); ++i) {
        int type = QMetaType::type(params.at(i));
        QVariant p(type, (void*)0);
        stack.at(i + 1) >> p;
        p.convert((QVariant::Type)type);
        variants << p;
    }
    stack.clear();
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
        lua::push(stack, variants.at(0));
    }
}

void metaInvokeLuaCallableMethod(LuaStack& stack, QObject* const obj, const QMetaMethod& method)
{
    auto returnType = QMetaType::type(method.typeName());
    QVariant rv;
    if (returnType != QMetaType::Void) {
        rv = QVariant(QMetaType::type(method.typeName()), nullptr);
    }
    void* vvargs[2];
    vvargs[0] = const_cast<void*>(rv.data());
    vvargs[1] = &stack;
    QMetaObject::metacall(
        obj,
        QMetaObject::InvokeMetaMethod,
        method.methodIndex(),
        vvargs);
    if (rv.isValid()) {
        stack.clear();
        lua::push(stack, rv);
    }
}

} // namespace anonymous
