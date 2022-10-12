#include "Config.hpp"
#include "config/Exceptions.hpp"

#include <algorithm>
#include <type_traits>
#include <unordered_map>

#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QMap>

using BubbleViewFilter = Config::BubbleView::BubbleViewPicture::Filter;


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
struct ObjectComponents
{
    QString parentName;
    std::vector<QString> strings;
    std::vector<QString> ints;

    ObjectComponents(QString parentName, std::vector<QString> strings, std::vector<QString> ints)
        : parentName{std::move(parentName)}, strings{std::move(strings)}, ints{std::move(ints)}
    {}

    void checkComponentsByParent(QJsonObject const &parent) const
    {
        for (auto const &value: strings) {
            if (!parent[value].isString())
                throw config::LoadingException{
                    QStringLiteral("%1 of parent %2 is not a string literal.").arg(value, parentName)};
        }

        for (auto const &value: ints) {
            if (auto const doubleValue = parent[value].toDouble();
                !parent[value].isDouble() || std::floor(doubleValue) != doubleValue)
                throw config::LoadingException{
                    QStringLiteral("%1 of parent %2 is not a integer.").arg(value, parentName)};
        }
    }
};

QJsonObject getSubConfig(QJsonObject const &parent, QString const &name)
{
    if (!parent.contains(name) || !parent[name].isObject())
        throw config::LoadingException{QStringLiteral("%1 is missing or not an object.").arg(name)};
    return parent[name].toObject();
}

void checkObjectForKey(QJsonObject const &object, QString const &key)
{
    if (!object.contains(key))
        throw config::LoadingException{
            QStringLiteral("Could not find required component: {}").arg(key)};
}

template<typename... KeyTypes>
auto checkObjectForKeys(QJsonObject const &object, KeyTypes const &... keys)
-> std::enable_if_t<(true && ... && std::is_same_v<QString, KeyTypes>)>
{
    for (auto const &key: {keys...})
        if (!object.contains(key))
            throw config::LoadingException{
                QStringLiteral("Could not find required component: {}").arg(key)};
}

Config::BubbleView::BubbleViewPicture::Filter filterFromJson(QJsonValue const &value)
{
    if (!value.isObject())
        throw config::LoadingException{"Name, value or BubbleViewPicture is not an object."};

    auto const object = value.toObject();

    ObjectComponents
        components{"filter",
                   {BubbleViewFilter::SHAPE},
                   {
                       BubbleViewFilter::GRADIENT,
                       BubbleViewFilter::INTENSITY,
                       BubbleViewFilter::SIZE,
                       BubbleViewFilter::FILTER_TYPE
                   }
    };
    components.checkComponentsByParent(object);

    static QMap<QString, Config::BubbleView::BubbleViewPicture::FilterType> const filterTypes{
        {"gaussianBlur", Config::BubbleView::BubbleViewPicture::FilterType::GaussianBlur},
        {"pixelate", Config::BubbleView::BubbleViewPicture::FilterType::Pixelate},
        {"linearMovement", Config::BubbleView::BubbleViewPicture::FilterType::LinearMovement}};

    static QMap<QString, Config::BubbleView::BubbleViewPicture::Shape> const shapeTypes{
        {"circle", Config::BubbleView::BubbleViewPicture::Shape::Circle},
        {"square", Config::BubbleView::BubbleViewPicture::Shape::Square}};

    checkObjectForKeys(object,
                       Config::BubbleView::BubbleViewPicture::Filter::FILTER_TYPE,
                       Config::BubbleView::BubbleViewPicture::Filter::SHAPE);

    auto const filterType =
        filterTypes.find(value[Config::BubbleView::BubbleViewPicture::Filter::FILTER_TYPE].toString()).value();
    auto const
        shapeType = shapeTypes.find(value[Config::BubbleView::BubbleViewPicture::Filter::SHAPE].toString()).value();


    return Config::BubbleView::BubbleViewPicture::Filter{
        .gradient = static_cast<quint16>(value[Config::BubbleView::BubbleViewPicture::Filter::GRADIENT].toInt()),
        .type = filterType,
        .intensity = static_cast<quint16>(value[Config::BubbleView::BubbleViewPicture::Filter::INTENSITY].toInt()),
        .shape = shapeType,
        .size = static_cast<quint16>(value[Config::BubbleView::BubbleViewPicture::Filter::SIZE].toInt()),

    };

}

std::vector<Config::BubbleView::BubbleViewPicture> bubbleViewPicturesFromJsonArray(QJsonArray const &pictures)
{
    std::vector<Config::BubbleView::BubbleViewPicture> result(pictures.size());

    std::transform(pictures.begin(), pictures.end(), result.begin(), [](QJsonValue const &value)
    {
        //TODO add constants
        if (!value.isObject() || !value["name"].isString() || !value["filter"].isString())
            throw config::LoadingException{"Name, value or BubbleViewPicture is not an object."};

        return Config::BubbleView::BubbleViewPicture{
            .name = value["name"].toString(),
            .filter = filterFromJson(value["filter"])
        };
    });

    return result;
}

Config::BubbleView loadBubbleView(QJsonObject const &bubbleView)
{
    if (!bubbleView["pictures"].isArray())
        throw config::LoadingException{"pictures of Bubble View is not an array."};

    return {
        .pictures = bubbleViewPicturesFromJsonArray(bubbleView["pictures"].toArray())
    };
}

Config::ZoomMaps::KeyBindings loadKeyBindingsFromJson(QJsonObject const &keyBindings)
{
    static std::vector<QString> keyCharacters
        {Config::ZoomMaps::KeyBindings::UP,
         Config::ZoomMaps::KeyBindings::DOWN,
         Config::ZoomMaps::KeyBindings::LEFT,
         Config::ZoomMaps::KeyBindings::RIGHT,
         Config::ZoomMaps::KeyBindings::IN,
         Config::ZoomMaps::KeyBindings::OUT};

    for (auto const &character: keyCharacters) {
        if (!keyBindings[character].isString() || keyBindings[character].toString().size() != 1)
            throw config::LoadingException{
                QStringLiteral("%1 of ZoomMaps Keybindings is not a char").arg(character)};
    }


    return Config::ZoomMaps::KeyBindings{
        .up = keyBindings[Config::ZoomMaps::KeyBindings::UP].toString()[0],
        .down = keyBindings[Config::ZoomMaps::KeyBindings::DOWN].toString()[0],
        .left = keyBindings[Config::ZoomMaps::KeyBindings::LEFT].toString()[0],
        .right = keyBindings[Config::ZoomMaps::KeyBindings::RIGHT].toString()[0],
        .in = keyBindings[Config::ZoomMaps::KeyBindings::IN].toString()[0],
        .out = keyBindings[Config::ZoomMaps::KeyBindings::OUT].toString()[0],
    };
}

std::vector<Config::ZoomMaps::ZoomMapsPicture> zoomMapsPicturesFromJsonArray(QJsonArray const &pictures)
{
    std::vector<Config::ZoomMaps::ZoomMapsPicture> result(pictures.size());

    std::transform(pictures.begin(),
                   pictures.end(),
                   result.begin(),
                   [index = size_t{0}](QJsonValue const &value) mutable
                   {
                       if (!value.isObject()
                           || !value[Config::ZoomMaps::ZoomMapsPicture::NAME].isString()
                           || !value[Config::ZoomMaps::ZoomMapsPicture::ZOOM_SPEED].isDouble())
                           throw config::LoadingException{
                               QStringLiteral(
                                   "%1 of Zoom Maps Picture is not an object or has invalid name or zoomSpeed")
                                   .arg(index++)};

                       return Config::ZoomMaps::ZoomMapsPicture{
                           .name = value["name"].toString(),
                           .zoomSpeed = value["zoomSpeed"].toDouble()
                       };
                   });

    return result;
}

Config::ZoomMaps loadZoomMaps(QJsonObject const &zoomMaps)
{
    checkObjectForKey(zoomMaps, Config::ZoomMaps::KEY_BINDINGS);
    checkObjectForKey(zoomMaps, Config::ZoomMaps::PICTURES);

    return Config::ZoomMaps{
        .keyBindings = loadKeyBindingsFromJson(zoomMaps[Config::ZoomMaps::KEY_BINDINGS].toObject()),
        .pictures = zoomMapsPicturesFromJsonArray(zoomMaps[Config::ZoomMaps::PICTURES].toArray())
    };
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
        .bubbleView = loadBubbleView(getSubConfig(config, Config::BUBBLE_VIEW)),
        .zoomMaps = loadZoomMaps(getSubConfig(config, Config::ZOOM_MAPS)),

    };
}
