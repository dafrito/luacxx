#include "QMetaMethod.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QString.hpp"
#include "QByteArray.hpp"
#include "QList.hpp"
#include "QVariant.hpp"
#include "QObject.hpp"

QString lua::QMetaMethod_signature(const QMetaMethod& method)
{
    #if QT_VERSION >= 0x050000
    return QString::fromLatin1(method.methodSignature());
    #else
    return QString::fromLatin1(method.signature());
    #endif
}

void lua::QMetaMethod_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

    mt["isValid"] = &QMetaMethod::isValid;
    mt["methodIndex"] = &QMetaMethod::methodIndex;
    mt["methodSignature"] = &QMetaMethod::methodSignature;
    mt["methodType"] = &QMetaMethod::methodType;
    mt["name"] = &QMetaMethod::name;
    mt["parameterCount"] = &QMetaMethod::parameterCount;
    mt["parameterNames"] = &QMetaMethod::parameterNames;
    mt["parameterType"] = &QMetaMethod::parameterType;
    mt["parameterTypes"] = &QMetaMethod::parameterTypes;
    mt["returnType"] = &QMetaMethod::returnType;
    mt["revision"] = &QMetaMethod::revision;
    mt["tag"] = &QMetaMethod::tag;
    mt["typeName"] = &QMetaMethod::typeName;

    mt["signature"] = lua_CFunction([](lua_State* const state) {
        auto method = lua::get<QMetaMethod*>(state, 1);
        lua::clear(state);
        lua::push(state, lua::QMetaMethod_signature(*method));
        return 1;
    });

    mt["__tostring"] = lua_CFunction([](lua_State* const state) {
        auto method = lua::get<QMetaMethod*>(state, 1);
        lua_settop(state, 0);
        lua::push(state, lua::QMetaMethod_signature(*method));
        return 1;
    });

    mt["__call"] = lua_CFunction([](lua_State* const state) {
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
        bool method_is_lua_CFunction = false;
        if (params.size() == 1 && QString(params.at(0)).startsWith("lua_State*")) {
            // Remove the leading QMetaMethod and QObject, as these are not expected when
            // passed into a C++ method.
            lua_remove(state, 1);
            lua_remove(state, 1);

            argdata[1] = (void*)&state;
            method_is_lua_CFunction = true;
        } else {
            for (int i = 0; i < params.count(); ++i) {
                int type = QMetaType::type(params.at(i));
                if (!type) {
                    std::stringstream str;
                    str << "lua::QMetaMethod::_call: The parameter type, "
                        << params.at(i).constData()
                        << ", does not have a registered strategy to convert into a QVariant, so "
                        << lua::QMetaMethod_signature(method).toStdString()
                        << " cannot be invoked.";
                    throw std::logic_error(str.str());
                }

                QVariant arg(type, nullptr);
                lua::store(arg, state, i + 3);
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
            if (method_is_lua_CFunction) {
                return variants.at(0).toInt();
            }
            lua::push(state, variants.at(0));
            return 1;
        }

        return 0;
    });
}

int luaopen_Qt5Core_QMetaMethod(lua_State* const state)
{
    lua::thread env(state);

    env["QMetaMethod"] = lua::value::table;
    auto t = env["QMetaMethod"];

    // enum QMetaMethod::Access
    t["Private"] = QMetaMethod::Private;
    t["Protected"] = QMetaMethod::Protected;
    t["Public"] = QMetaMethod::Public;

    // enum QMetaMethod::MethodType
    t["Method"] = QMetaMethod::Method;
    t["Signal"] = QMetaMethod::Signal;
    t["Slot"] = QMetaMethod::Slot;
    t["Constructor"] = QMetaMethod::Constructor;

    return 0;
}
