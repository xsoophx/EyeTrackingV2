#ifndef CONFIG_DATABASE_HPP
#define CONFIG_DATABASE_HPP

#include <QtCore/QString>

class QJsonObject;

namespace config
{
struct Database
{
    static Database load(QJsonObject const &database);

    static QString const DATABASE_PATH;

    QString databasePath;
};
}


#endif //CONFIG_DATABASE_HPP
