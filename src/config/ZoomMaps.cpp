#include "ZoomMaps.hpp"
#include "Helpers.hpp"

#include <QtCore/QJsonArray>

namespace
{
using namespace config;

namespace field_name
{
static QString const KEY_BINDINGS{"keyBindings"};

static QString const PICTURES{"pictures"};

static QString const UP{"up"};

static QString const DOWN{"down"};

static QString const LEFT{"left"};

static QString const RIGHT{"right"};

static QString const IN{"in"};

static QString const OUT{"out"};

static QString const ZOOM_SPEED{"zoomSpeed"};
}

ZoomMaps::KeyBindings loadKeyBindingsFromJson(QJsonObject const &keyBindings)
{
    using namespace field_name;

    static std::vector<QString> keyCharacters
        {UP, DOWN, LEFT, RIGHT, IN, OUT};

    for (auto const &character: keyCharacters) {
        if (!keyBindings[character].isString() || keyBindings[character].toString().size() != 1)
            throw config::LoadingException{
                QStringLiteral("%1 of ZoomMaps Keybindings is not a char").arg(character)};
    }


    return ZoomMaps::KeyBindings{
        .up = keyBindings[UP].toString()[0],
        .down = keyBindings[DOWN].toString()[0],
        .left = keyBindings[LEFT].toString()[0],
        .right = keyBindings[RIGHT].toString()[0],
        .in = keyBindings[IN].toString()[0],
        .out = keyBindings[OUT].toString()[0],
    };
}

std::vector<ZoomMaps::ZoomMapsPicture> zoomMapsPicturesFromJsonArray(QJsonArray const &pictures)
{
    using namespace field_name;

    std::vector<ZoomMaps::ZoomMapsPicture> result(pictures.size());

    std::transform(pictures.begin(),
                   pictures.end(),
                   result.begin(),
                   [index = size_t{0}](QJsonValue const &value) mutable
                   {
                       if (!value.isObject()
                           || !value[config::NAME].isString()
                           || !value[ZOOM_SPEED].isDouble())
                           throw config::LoadingException{
                               QStringLiteral(
                                   "%1 of Zoom Maps Picture is not an object or has invalid name or zoomSpeed")
                                   .arg(index++)};

                       return ZoomMaps::ZoomMapsPicture{
                           .name = value[config::NAME].toString(),
                           .zoomSpeed = value[ZOOM_SPEED].toDouble()
                       };
                   });

    return result;
}
}

namespace config
{

ZoomMaps ZoomMaps::load(QJsonObject const &zoomMaps)
{
    using namespace field_name;

    checkObjectForKeys(zoomMaps, KEY_BINDINGS, PICTURES);

    return ZoomMaps{
        .keyBindings = loadKeyBindingsFromJson(zoomMaps[KEY_BINDINGS].toObject()),
        .pictures = zoomMapsPicturesFromJsonArray(zoomMaps[PICTURES].toArray())
    };
}
}