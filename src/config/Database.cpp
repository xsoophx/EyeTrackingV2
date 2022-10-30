#include "Database.hpp"

#include <utility>
#include "Helpers.hpp"

namespace config
{
QString const Database::DATABASE_TEXT{"databasePath"};

Database Database::load(QJsonObject const &database)
{
    checkObjectForKeys(database, Database::DATABASE_TEXT);

    return Database{database[Database::DATABASE_TEXT].toString()
    };
}
Database::Database(QString databasePath)
    : databasePath{std::move(databasePath)}
{}
}
