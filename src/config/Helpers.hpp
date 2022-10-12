#ifndef CONFIG_HELPERS_HPP
#define CONFIG_HELPERS_HPP

#include "Exceptions.hpp"

#include <type_traits>

#include <QtCore/QJsonObject>
#include <QtCore/QString>

namespace config
{
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
