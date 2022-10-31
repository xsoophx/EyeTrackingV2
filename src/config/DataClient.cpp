#include "DataClient.hpp"
#include "Helpers.hpp"

#include <QtCore/QJsonArray>
#include <utility>

namespace
{
using namespace config;

static QString const COLOR_SAMPLE_BOARD{"colorSampleBoard"};

static QString const RED{"r"};

static QString const GREEN{"g"};

static QString const BLUE{"b"};

std::vector<QColor> colorsFromJsonArray(QJsonArray const &colors)
{
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
                           throw config::LoadingException{
                               QStringLiteral(
                                   "%1 of Data Client colors contains invalid RGB value.")
                                   .arg(index++)};

                       return QColor{value[RED].toInt(), value[GREEN].toInt(), value[BLUE].toInt()};
                   });

    return result;
}
}

namespace config
{

DataClient DataClient::load(QJsonObject const &dataClient)
{
    checkObjectForKeys(dataClient, COLOR_SAMPLE_BOARD);

    return DataClient{colorsFromJsonArray(dataClient[COLOR_SAMPLE_BOARD].toArray())
    };
}
DataClient::DataClient(std::vector<QColor> colorSampleBoard)
    : colorSampleBoard{std::move(colorSampleBoard)}
{}

DataClient::DataClient()
    : DataClient({QColor{255U, 255U, 255U}})
{};
}
