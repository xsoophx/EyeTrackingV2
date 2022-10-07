#include "Config.hpp"
#include "Exceptions.hpp"

#include <unordered_map>

#include <QtCore/QJsonDocument>
#include <QtCore/QFile>
#include <QtCore/QJsonObject>
#include <QtCore/QMap>

QString const Config::GENERAL{"general"};

QStringList const mandatoryGeneralComponents = {"masterPath", "exportPath", "imagePath"};

namespace
{

Config::General::DisplayMode displayModeFromJson(QJsonValue const &value)
{
    static QString const height = "height";
    static QString const width = "width";

    if (!value.isString() && value.toString() == "fullScreen")
        return Config::General::FullScreen{};

    if (value.isObject()) {
        auto const object = value.toObject();
        if (!object.contains(height))
            throw ConfigLoadingException{
                QStringLiteral("Could not find required component: {}").arg(height)};
        if (!object.contains(width))
            throw ConfigLoadingException{
                QStringLiteral("Could not find required component: {}").arg(width)};

        return Config::Dimensions{
            .width = static_cast<quint16>(object[width].toInt()),
            .height = static_cast<quint16>(object[height].toInt()),
        };
    }
    throw ConfigLoadingException{
        QStringLiteral("Invalid value for display mode")};

}

std::optional<Config::Tool> toolFromJson(QJsonValue const &value)
{
    static QMap<QString, Config::Tool> const mapping{
        {"bubbleView", Config::Tool::BubbleView},
        {"zoomMaps", Config::Tool::ZoomMaps},
        {"codecharts", Config::Tool::CodeCharts},
        {"eyeTracking", Config::Tool::EyeTracking},
        {"dataClient", Config::Tool::DataClient},
    };

    if (!value.isString())
        return {};

    auto const tool = value.toString();
    auto const iterator = mapping.constFind(tool);
    if (iterator == mapping.constEnd())
        return {};

    return iterator.value();

}

Config::General loadGeneral(QJsonObject const &general)
{
    for (auto const &requiredComponent: mandatoryGeneralComponents) {
        if (!general.contains(requiredComponent))
            throw ConfigLoadingException{
                QStringLiteral("Could not find required component: {}").arg(requiredComponent)};
    }

    return {
        .displayMode = displayModeFromJson(general["displayMode"]),
        .activatedTool = toolFromJson(general["activatedTool"]),
        .masterPath = general["masterPath"].toString(),
        .exportPath = general["exportPath"].toString(),
        .imagePath = general["imagePath"].toString(),
    };

}
}
Config Config::load(QString const &path)
{
    QFile file{path};
    if (!file.open(QFile::ReadOnly))
        throw ConfigLoadingException{"File could not be loaded."};

    auto const document{QJsonDocument::fromJson(file.readAll())};
    if (!document.isObject())
        throw ConfigLoadingException{"Document is not an object."};

    auto const config{document.object()};
    config.contains(GENERAL);


    return Config();
}
