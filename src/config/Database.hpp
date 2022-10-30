#ifndef CONFIG_DATABASE_HPP
#define CONFIG_DATABASE_HPP

#include "../Constants.hpp"

#include <QtCore/QString>

class QJsonObject;

namespace config
{
struct Database final
{
    static Database load(QJsonObject const &database);

    // TODO: refactor text constants
    static QString const DATABASE_TEXT;

    QString databasePath{config::DATABASE_PATH};

    explicit Database(QString databasePath);
};
}


#endif //CONFIG_DATABASE_HPP
