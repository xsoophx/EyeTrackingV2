#include "Database.hpp"

#include <utility>
#include "Helpers.hpp"

namespace field_name
{
// TODO: refactor text constants
static QString const DATABASE_PATH{"databasePath"};

}

namespace config
{
Database Database::load(QJsonObject const &database)
{
    using namespace field_name;

    checkObjectForKeys(database, DATABASE_PATH);

    return Database{database[DATABASE_PATH].toString()
    };
}
Database::Database(QString databasePath)
    : databasePath{std::move(databasePath)}
{}
}
