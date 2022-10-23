#include "Config.hpp"

#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

QString const Config::GENERAL{"general"};

QString const Config::BUBBLE_VIEW{"bubbleView"};

QString const Config::ZOOM_MAPS{"zoomMaps"};

QString const Config::CODE_CHARTS{"codeCharts"};

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
    QFile file{path};
    if (!file.open(QFile::ReadOnly))
        throw config::LoadingException{"File could not be loaded."};

    auto const document{QJsonDocument::fromJson(file.readAll())};
    if (!document.isObject())
        throw config::LoadingException{"Document is not an object."};

    auto const config{document.object()};
    return Config{
        .general = General::load(getSubConfig(config, Config::GENERAL)),
        .bubbleView = BubbleView::load(getSubConfig(config, Config::BUBBLE_VIEW)),
        .zoomMaps = ZoomMaps::load(getSubConfig(config, Config::ZOOM_MAPS)),
        .codeCharts = CodeCharts::load(getSubConfig(config, Config::CODE_CHARTS))

    };
}
