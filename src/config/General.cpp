#include "General.hpp"
#include "Helpers.hpp"

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

        return General::Dimensions{
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

namespace config
{
General General::load(QJsonObject const &general)
{
    checkObjectForKeys(general,
                       QStringLiteral("masterPath"),
                       QStringLiteral("exportPath"),
                       QStringLiteral("imagePath"));

    return {
        .displayMode = displayModeFromJson(general["displayMode"]),
        .activatedTool = toolFromJson(general["activatedTool"]),
        .masterPath = general["masterPath"].toString(),
        .exportPath = general["exportPath"].toString(),
        .imagePath = general["imagePath"].toString(),
    };

}
}
