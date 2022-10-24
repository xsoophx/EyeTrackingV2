#include "Database.hpp"
#include "Helpers.hpp"

namespace config
{
QString const Database::DATABASE_PATH{"databasePath"};

Database Database::load(QJsonObject const &database)
{
    checkObjectForKeys(database, Database::DATABASE_PATH);

    return Database{
        .databasePath = database[Database::DATABASE_PATH].toString()
    };
}
}
