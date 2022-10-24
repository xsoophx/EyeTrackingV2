#include "DataClient.hpp"
#include "Helpers.hpp"

#include <QtCore/QJsonArray>

namespace
{
using namespace config;

std::vector<QColor> colorsFromJsonArray(QJsonArray const &colors)
{
    std::vector<QColor> result(colors.size());
    static QString const RED{"r"};
    static QString const GREEN{"g"};
    static QString const BLUE{"b"};

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
QString const DataClient::COLOR_SAMPLE_BOARD{"colorSampleBoard"};

DataClient DataClient::load(QJsonObject const &dataClient)
{
    checkObjectForKeys(dataClient, DataClient::COLOR_SAMPLE_BOARD);

    return DataClient{
        .colorSampleBoard = colorsFromJsonArray(dataClient[DataClient::COLOR_SAMPLE_BOARD].toArray())
    };
}
}
