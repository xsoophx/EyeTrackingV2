#include "Database.hpp"

#include <utility>
#include "Helpers.hpp"

namespace
{
// TODO: refactor text constants
static QString const DATABASE_TEXT{"databasePath"};

}

namespace config
{
Database Database::load(QJsonObject const &database)
{
    checkObjectForKeys(database, DATABASE_TEXT);

    return Database{database[DATABASE_TEXT].toString()
    };
}
Database::Database(QString databasePath)
    : databasePath{std::move(databasePath)}
{}
}
