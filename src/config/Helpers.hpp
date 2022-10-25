#ifndef CONFIG_HELPERS_HPP
#define CONFIG_HELPERS_HPP

#include "Exceptions.hpp"

#include <type_traits>

#include <QtCore/QJsonObject>
#include <QtCore/QString>

namespace config
{

inline bool isInt(QJsonValue const &value)
{
    auto const doubleValue = value.toDouble();
    return !value.isDouble() || std::floor(doubleValue) != doubleValue;
}

struct Dimensions final
{
    quint16 width;
    quint16 height;
};

struct ObjectComponents final
{
    QString parentName;
    std::vector<QString> strings;
    std::vector<QString> ints;
    std::vector<QString> booleans;

    ObjectComponents(QString parentName,
                     std::vector<QString> strings,
                     std::vector<QString> ints,
                     std::vector<QString> booleans)
        : parentName{std::move(parentName)},
          strings{std::move(strings)},
          ints{std::move(ints)},
          booleans(std::move(booleans))
    {}

    static ObjectComponents createStringsOnly(QString parentName, std::vector<QString> strings)
    {
        return {std::move(parentName), std::move(strings), {}, {}};
    }

    void checkComponentsByParent(QJsonObject const &parent) const
    {
        for (auto const &value: strings) {
            if (!parent[value].isString())
                throw config::LoadingException{
                    QStringLiteral("%1 of parent %2 is not a string literal.").arg(value, parentName)};
        }

        for (auto const &value: ints) {
            if (!isInt(parent[value]))
                throw config::LoadingException{
                    QStringLiteral("%1 of parent %2 is not a integer.").arg(value, parentName)};
        }

        for (auto const &value: booleans) {
            if (!parent[value].isBool())
                throw config::LoadingException{
                    QStringLiteral("%1 of parent %2 is not a boolean value.").arg(value, parentName)};
        }
    }
};

template<typename... KeyTypes>
auto checkObjectForKeys(QJsonObject const &object, KeyTypes const &... keys)
-> std::enable_if_t<(true && ... && std::is_same_v<QString, KeyTypes>)>
{
    for (auto const &key: {keys...})
        if (!object.contains(key))
            throw config::LoadingException{
                QStringLiteral("Could not find required component: %1").arg(key)};
}

}

#endif // CONFIG_HELPERS_HPP
