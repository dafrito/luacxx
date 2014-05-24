#include "Qt/QObject.hpp"
#include "Qt/QObjectSlot.hpp"
#include "Qt/QVariant.hpp"

#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>

#include "../algorithm.hpp"
#include "../reference.hpp"
#include "../type/function.hpp"

#include <cassert>
#include <functional>

namespace {
    int QObject_connect(lua::state* const state);
    QString getSignature(const QMetaMethod& method);
}

void lua::QObject_metatable(const lua::index& mt)
{
    mt["__index"] = lua::function([](lua::state* const state) {
        auto obj = lua::get<QObject*>(state, 1);
        auto name = lua::get<const char*>(state, 2);

        // Do we have a cached value?
        lua_getmetatable(state, 1);
        lua::push(state, name);
        lua_rawget(state, -2);
        if (lua_type(state, -1) != LUA_TNIL) {
            // We do. Return it directly.
            lua_replace(state, 1);
            lua_settop(state, 1);
            return 1;
        } else {
            // Nope, so clean up and move on.
            lua_pop(state, 2);
        }

        // Properties
        QVariant propValue = obj->property(name);
        if (propValue.isValid()) {
            lua::push(state, propValue);
            return 1;
        }

        // Slot connections
        if (QString(name).compare("connect", Qt::CaseInsensitive) == 0) {
            lua::push(state, QObject_connect);
            return 1;
        }

        // Invokables
        const QMetaObject* metaObject = obj->metaObject();
        for (int i = 0; i < metaObject->methodCount(); ++i) {
            auto method = metaObject->method(i);
            QString sig = getSignature(method);

            if (sig.startsWith(QString(name) + "(", Qt::CaseInsensitive)) {
                lua::push(state, method);
                return 1;
            }
        }

        return 0;
    });

    mt["__newindex"] = lua::function([](lua::state* const state) {
        auto obj = lua::get<QObject*>(state, 1);
        auto name = lua::get<const char*>(state, 2);

        // Properties
        QVariant propValue = obj->property(name);
        if (!propValue.isValid()) {
            throw lua::error("New properties must not be added to this userdata");
        }

        lua::store(propValue, lua::index(state, 3));
        obj->setProperty(name, propValue);

        return 0;
    });
}

void lua::qmetamethod_metatable(const lua::index& mt)
{
    mt["Signature"] = lua::function([](lua::state* const state) {
        auto method = lua::get<QMetaMethod*>(state, 1);
        lua::clear(state);
        lua::push(state, getSignature(*method));
        return 1;
    });

    mt["__call"] = lua::function([](lua::state* const state) {
        auto method = lua::get<QMetaMethod&>(state, 1);
        auto obj = lua::get<QObject*>(state, 2);

        QVariant returnValue;
        auto returnType = QMetaType::type(method.typeName());
        if (returnType != QMetaType::Void) {
            returnValue = QVariant(returnType, nullptr);
        }
        QList<QVariant> variants;
        variants << returnType;

        void* argdata[11];
        argdata[0] = const_cast<void*>(variants.at(0).data());

        QList<QByteArray> params = method.parameterTypes();
        if (params.size() == 1 && QString(params.at(0)).startsWith("lua::state*")) {
            argdata[1] = state;
        } else {
            for (int i = 0; i < params.count(); ++i) {
                int type = QMetaType::type(params.at(i));
                if (!type) {
                    std::stringstream str;
                    str << "lua::QMetaMethod::_call: The parameter type, "
                        << params.at(i).constData()
                        << ", does not have a registered strategy to convert into a QVariant, so "
                        << getSignature(method).toStdString()
                        << " cannot be invoked.";
                    throw std::logic_error(str.str());
                }

                QVariant arg(type, nullptr);
                lua::store(arg, lua::index(state, i + 3));
                arg.convert(static_cast<QVariant::Type>(type));
                variants << arg;
            }
            for (int i = 0; i < variants.size(); ++i) {
                argdata[i] = const_cast<void*>(variants.at(i).data());
            }
        }

        QMetaObject::metacall(
            obj,
            QMetaObject::InvokeMetaMethod,
            method.methodIndex(),
            argdata
        );

        if (variants.at(0).isValid()) {
            lua::push(state, variants.at(0));
            lua_replace(state, 1);
            lua_settop(state, 1);
            return 1;
        } else {
            return 0;
        }
    });
}

namespace {

QString getSignature(const QMetaMethod& method)
{
    #if QT_VERSION >= 0x050000
    return QString::fromLatin1(method.methodSignature());
    #else
    return QString::fromLatin1(method.signature());
    #endif
}

int QObject_connect(lua::state* const state)
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
            if (getSignature(metaObject->method(i)).startsWith(name.c_str())) {
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

} // namespace anonymous
