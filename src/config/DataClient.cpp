#include "DataClient.hpp"
#include "Helpers.hpp"

#include <QtCore/QJsonArray>

namespace
{
using namespace config;

std::vector<QColor> colorsFromJsonArray(QJsonArray const &colors)
{
    std::vector<QColor> result(colors.size());

    std::transform(colors.begin(),
                   colors.end(),
                   result.begin(),
                   [index = size_t{0}](QJsonValue const &value) mutable
                   {
                       if (!value.isObject()
                           || !isInt(value[DataClient::RED])
                           || !isInt(value[DataClient::GREEN])
                           || !isInt(value[DataClient::BLUE]))
                           throw config::LoadingException{
                               QStringLiteral(
                                   "%1 of Data Client colors contains invalid RGB value.")
                                   .arg(index++)};

                       return QColor{value[DataClient::RED].toInt(), value[DataClient::GREEN].toInt(),
                                     value[DataClient::BLUE].toInt()};
                   });

    return result;
}
}

namespace config
{
QString const DataClient::COLOR_SAMPLE_BOARD{"colorSampleBoard"};

QString const DataClient::RED{"r"};

QString const DataClient::GREEN{"g"};

QString const DataClient::BLUE{"b"};

DataClient DataClient::load(QJsonObject const &dataClient)
{
    checkObjectForKeys(dataClient, DataClient::COLOR_SAMPLE_BOARD);

    return DataClient{
        .colorSampleBoard = colorsFromJsonArray(dataClient[DataClient::COLOR_SAMPLE_BOARD].toArray())
    };
}
}
