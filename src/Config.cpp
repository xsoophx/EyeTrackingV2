#include "Config.hpp"
#include "config/Exceptions.hpp"
#include "config/ZoomMaps.hpp"


#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

// General
QString const Config::GENERAL{"general"};

QString const Config::BUBBLE_VIEW{"bubbleView"};

// BubbleView
QString const Config::BubbleView::BubbleViewPicture::Filter::FILTER_TYPE{"type"};

QString const Config::BubbleView::BubbleViewPicture::Filter::GRADIENT{"gradient"};

QString const Config::BubbleView::BubbleViewPicture::Filter::INTENSITY{"intensity"};

QString const Config::BubbleView::BubbleViewPicture::Filter::SHAPE{"shape"};

QString const Config::BubbleView::BubbleViewPicture::Filter::SIZE{"size"};

// ZoomMaps
QString const Config::ZoomMaps::KEY_BINDINGS{"keyBindings"};

QString const Config::ZoomMaps::PICTURES{"pictures"};

QString const Config::ZoomMaps::KeyBindings::UP{"up"};

QString const Config::ZoomMaps::KeyBindings::DOWN{"down"};

QString const Config::ZoomMaps::KeyBindings::LEFT{"left"};

QString const Config::ZoomMaps::KeyBindings::RIGHT{"right"};

QString const Config::ZoomMaps::KeyBindings::IN{"in"};

QString const Config::ZoomMaps::KeyBindings::OUT{"out"};

QString const Config::ZoomMaps::ZoomMapsPicture::NAME{"name"};

QString const Config::ZoomMaps::ZoomMapsPicture::ZOOM_SPEED{"zoomSpeed"};

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

    };
}
