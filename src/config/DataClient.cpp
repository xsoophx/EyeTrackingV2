#include "DataClient.hpp"
#include "Helpers.hpp"

#include <QtCore/QJsonArray>
#include <utility>

namespace
{
using namespace config;

namespace field_name
{
static QString const COLOR_SAMPLE_BOARD{"colorSampleBoard"};

static QString const RED{"r"};

static QString const GREEN{"g"};

static QString const BLUE{"b"};
}

std::vector<QColor> colorsFromJsonArray(QJsonArray const &colors)
{
    using namespace field_name;

    std::vector<QColor> result(colors.size());

    std::transform(colors.begin(),
                   colors.end(),
                   result.begin(),
                   [index = size_t{0}](QJsonValue const &value) mutable
                   {
                       if (!value.isObject()
                           || !isInt(value[RED])
                           || !isInt(value[GREEN])
                           || !isInt(value[BLUE]))
                           throw LoadingException{
                               QStringLiteral(
                                   "%1 of Data Client colors contains invalid RGB value.")
                                   .arg(index++)};

                       return QColor{value[RED].toInt(),
                                     value[GREEN].toInt(),
                                     value[BLUE].toInt()};
                   });

    return result;
}
}

namespace config
{

DataClient DataClient::load(QJsonObject const &dataClient)
{
    checkObjectForKeys(dataClient, field_name::COLOR_SAMPLE_BOARD);

    return DataClient{colorsFromJsonArray(dataClient[field_name::COLOR_SAMPLE_BOARD].toArray())
    };
}
DataClient::DataClient(std::vector<QColor> colorSampleBoard)
    : colorSampleBoard{std::move(colorSampleBoard)}
{}

DataClient::DataClient()
    : DataClient({QColor{255U, 255U, 255U}})
{};
}
