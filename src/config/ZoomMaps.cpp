#include "ZoomMaps.hpp"
#include "Helpers.hpp"

#include <QtCore/QJsonArray>

namespace
{
using namespace config;

ZoomMaps::KeyBindings loadKeyBindingsFromJson(QJsonObject const &keyBindings)
{
    static std::vector<QString> keyCharacters
        {ZoomMaps::KeyBindings::UP,
         ZoomMaps::KeyBindings::DOWN,
         ZoomMaps::KeyBindings::LEFT,
         ZoomMaps::KeyBindings::RIGHT,
         ZoomMaps::KeyBindings::IN,
         ZoomMaps::KeyBindings::OUT};

    for (auto const &character: keyCharacters) {
        if (!keyBindings[character].isString() || keyBindings[character].toString().size() != 1)
            throw config::LoadingException{
                QStringLiteral("%1 of ZoomMaps Keybindings is not a char").arg(character)};
    }


    return ZoomMaps::KeyBindings{
        .up = keyBindings[ZoomMaps::KeyBindings::UP].toString()[0],
        .down = keyBindings[ZoomMaps::KeyBindings::DOWN].toString()[0],
        .left = keyBindings[ZoomMaps::KeyBindings::LEFT].toString()[0],
        .right = keyBindings[ZoomMaps::KeyBindings::RIGHT].toString()[0],
        .in = keyBindings[ZoomMaps::KeyBindings::IN].toString()[0],
        .out = keyBindings[ZoomMaps::KeyBindings::OUT].toString()[0],
    };
}

std::vector<ZoomMaps::ZoomMapsPicture> zoomMapsPicturesFromJsonArray(QJsonArray const &pictures)
{
    std::vector<ZoomMaps::ZoomMapsPicture> result(pictures.size());

    std::transform(pictures.begin(),
                   pictures.end(),
                   result.begin(),
                   [index = size_t{0}](QJsonValue const &value) mutable
                   {
                       if (!value.isObject()
                           || !value[ZoomMaps::ZoomMapsPicture::NAME].isString()
                           || !value[ZoomMaps::ZoomMapsPicture::ZOOM_SPEED].isDouble())
                           throw config::LoadingException{
                               QStringLiteral(
                                   "%1 of Zoom Maps Picture is not an object or has invalid name or zoomSpeed")
                                   .arg(index++)};

                       return ZoomMaps::ZoomMapsPicture{
                           .name = value[ZoomMaps::ZoomMapsPicture::NAME].toString(),
                           .zoomSpeed = value[ZoomMaps::ZoomMapsPicture::ZOOM_SPEED].toDouble()
                       };
                   });

    return result;
}
}

namespace config
{
QString const ZoomMaps::KEY_BINDINGS{"keyBindings"};

QString const ZoomMaps::PICTURES{"pictures"};

QString const ZoomMaps::KeyBindings::UP{"up"};

QString const ZoomMaps::KeyBindings::DOWN{"down"};

QString const ZoomMaps::KeyBindings::LEFT{"left"};

QString const ZoomMaps::KeyBindings::RIGHT{"right"};

QString const ZoomMaps::KeyBindings::IN{"in"};

QString const ZoomMaps::KeyBindings::OUT{"out"};

QString const ZoomMaps::ZoomMapsPicture::NAME{"name"};

QString const ZoomMaps::ZoomMapsPicture::ZOOM_SPEED{"zoomSpeed"};

ZoomMaps ZoomMaps::load(QJsonObject const &zoomMaps)
{
    checkObjectForKeys(zoomMaps, ZoomMaps::KEY_BINDINGS, ZoomMaps::PICTURES);

    return ZoomMaps{
        .keyBindings = loadKeyBindingsFromJson(zoomMaps[ZoomMaps::KEY_BINDINGS].toObject()),
        .pictures = zoomMapsPicturesFromJsonArray(zoomMaps[ZoomMaps::PICTURES].toArray())
    };
}
}