#include "General.hpp"

#include <functional>

#include <QtCore/QCoreApplication>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>

namespace
{
using namespace config;

General::DisplayMode displayModeFromJson(QJsonValue const &value)
{
    static QString const height = "height";
    static QString const width = "width";

    if (value.isString() && value.toString() == "fullScreen")
        return General::FullScreen{};

    if (value.isObject()) {
        auto const object = value.toObject();
        checkObjectForKeys(object, height, width);

        return Dimensions{
            .width = static_cast<quint16>(object[width].toInt()),
            .height = static_cast<quint16>(object[height].toInt()),
        };
    }

    throw LoadingException{
        QStringLiteral("Invalid value for display mode")};

}

std::optional<General::Tool> toolFromJson(QJsonValue const &value)
{
    static QMap<QString, General::Tool> const mapping{
        {"bubbleView", General::Tool::BubbleView},
        {"zoomMaps", General::Tool::ZoomMaps},
        {"codecharts", General::Tool::CodeCharts},
        {"eyeTracking", General::Tool::EyeTracking},
        {"dataClient", General::Tool::DataClient},
    };

    if (!value.isString())
        return {};

    auto const tool = value.toString();
    auto const iterator = mapping.constFind(tool);
    if (iterator == mapping.constEnd())
        return {};

    return iterator.value();
}
}

namespace
{
QString
getValueOrDefault(QJsonObject const &object, char const *const key, std::function<QString()> const &defaultGenerator)
{
    auto const value = object[key].toString();
    return value.isEmpty() ? defaultGenerator() : value;
}
}

namespace config
{
General General::load(QJsonObject const &general)
{
    auto const masterPath = getValueOrDefault(general, "masterPath", &QCoreApplication::applicationDirPath);
    auto const exportPath = getValueOrDefault(general, "exportPath", [&masterPath]
    {
        return masterPath + config::EXPORT_PATH;
    });
    auto const imagePath = getValueOrDefault(general, "imagePath", [&masterPath]
    {
        return masterPath + config::IMAGE_PATH;
    });

    return {
        .displayMode = displayModeFromJson(general["displayMode"]),
        .activatedTool = toolFromJson(general["activatedTool"]),
        .masterPath = masterPath,
        .exportPath = exportPath,
        .imagePath = imagePath,
    };
}
}
