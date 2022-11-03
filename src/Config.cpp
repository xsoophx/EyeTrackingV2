#include "Config.hpp"

#include "Constants.hpp"

#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

namespace
{

QJsonObject getSubConfig(QJsonObject const &parent, QString const &name)
{
    if (!parent.contains(name) || !parent[name].isObject())
        throw config::LoadingException{QStringLiteral("%1 is missing or not an object.").arg(name)};
    return parent[name].toObject();
}
}

Config Config::load(QString const &path)
{
    using namespace config::tools;

    QFile file{path};
    if (!file.open(QFile::ReadOnly))
        throw config::LoadingException{"File could not be loaded."};

    auto const document{QJsonDocument::fromJson(file.readAll())};
    if (!document.isObject())
        throw config::LoadingException{"Document is not an object."};

    auto const config{document.object()};

    return Config{
        .general = General::load(getSubConfig(config, GENERAL)),
        .bubbleView = BubbleView::load(getSubConfig(config, BUBBLE_VIEW)),
        .zoomMaps = ZoomMaps::load(getSubConfig(config, ZOOM_MAPS)),
        .codeCharts = CodeCharts::load(getSubConfig(config, CODE_CHARTS)),
        .eyeTracking = EyeTracking::load(getSubConfig(config, EYE_TRACKING)),
        .dataClient = DataClient::load(getSubConfig(config, DATA_CLIENT)),
        .database = Database::load(getSubConfig(config, DATABASE))
    };
}
