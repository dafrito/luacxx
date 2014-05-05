#include "type/QVariant.hpp"
#include "type/QChar.hpp"
#include "type/QString.hpp"
#include "type/LuaReference.hpp"
#include "values.hpp"

#include <unordered_map>
#include <QStringList>

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

static std::unordered_map<int, std::function<void(LuaStack&, const QVariant&)>> variantPushers;
static std::unordered_map<int, std::function<void(const LuaIndex&, QVariant&)>> variantStorers;

}

void lua::qvariantPusher(const int& type, const std::function<void(LuaStack&, const QVariant&)>& mapper)
{
    variantPushers[type] = mapper;
}

void lua::qvariantStorer(const int& type, const std::function<void(const LuaIndex&, QVariant&)>& mapper)
{
    variantStorers[type] = mapper;
}

void lua::pushVariant(LuaStack& stack, const QVariant& variant)
{
    switch (variant.userType()) {
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
    case QVariant::Hash:
        {
        auto hash = variant.toHash();

        lua::push(stack, lua::value::table);
        for (auto i = hash.begin(); i != hash.end(); ++i) {
            stack.set(i.key(), i.value());
        }

        }

        break;
    case QVariant::StringList:
        {
        auto list = variant.toStringList();

        lua::push(stack, lua::value::table);
        for (int i = 0; i < list.size(); ++i) {
            stack.set(i + 1, list[i]);
        }

        }

        break;
    default:
        auto converter = variantPushers.find(variant.userType());
        if (converter != variantPushers.end()) {
            converter->second(stack, variant);
        } else {
            throw std::logic_error(std::string("QVariant type not supported: ") + variant.typeName());
        }
    }
}

void lua::storeVariant(const LuaIndex& index, QVariant& sink)
{
    auto pos = index.pos();
    LuaStack& stack = index.stack();
    switch (sink.userType()) {
    case QVariant::Invalid:
        sink.clear();
        break;
    case QVariant::Bool:
        sink.setValue(stack.get<bool>(pos));
        break;
    case QVariant::Char:
        sink.setValue(QChar(stack.get<char>(pos)));
        break;
    case QVariant::Int:
    case QVariant::UInt:
        sink.setValue(stack.get<int>(pos));
        break;
    case QVariant::Double:
        sink.setValue(stack.get<double>(pos));
        break;
    case QVariant::String:
        sink.setValue(stack.get<QString>(pos));
        break;
    case QVariant::StringList:
        {
        auto list = lua::get<LuaReference>(index);

        QStringList items;
        for (int i = 1; i <= list.length(); ++i) {
            items << list[i].get<QString>();
        }
        sink.setValue(items);

        }
        break;
    case QVariant::Hash:
        {
        // XXX If pos is negative, then this won't work
        assert(index.pos() > 0);

        QHash<QString, QVariant> hash;

        // Push a nil to begin iteration
        lua::push(index.stack(), lua::value::nil);

        while (lua_next(index.stack().luaState(), index.pos()) != 0) {
            auto key = lua::get<QString>(index.stack(), -2);
            auto value = lua::get<QVariant>(index.stack(), -1);

            hash[key] = value;

            stack.pop();
        }
        sink.setValue(hash);
        }
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
