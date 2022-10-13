#ifndef CONFIG_HELPERS_HPP
#define CONFIG_HELPERS_HPP

#include "Exceptions.hpp"

#include <type_traits>

#include <QtCore/QJsonObject>
#include <QtCore/QString>

namespace config
{
struct ObjectComponents
{
    QString parentName;
    std::vector<QString> strings;
    std::vector<QString> ints;

    ObjectComponents(QString parentName, std::vector<QString> strings, std::vector<QString> ints)
        : parentName{std::move(parentName)}, strings{std::move(strings)}, ints{std::move(ints)}
    {}

    void checkComponentsByParent(QJsonObject const &parent) const
    {
        for (auto const &value: strings) {
            if (!parent[value].isString())
                throw config::LoadingException{
                    QStringLiteral("%1 of parent %2 is not a string literal.").arg(value, parentName)};
        }

        for (auto const &value: ints) {
            if (auto const doubleValue = parent[value].toDouble();
                !parent[value].isDouble() || std::floor(doubleValue) != doubleValue)
                throw config::LoadingException{
                    QStringLiteral("%1 of parent %2 is not a integer.").arg(value, parentName)};
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
