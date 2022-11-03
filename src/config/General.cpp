#include "General.hpp"

#include <functional>

#include <QtCore/QCoreApplication>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>

namespace
{
using namespace config;

namespace field_name
{

static QString const HEIGHT{"height"};

static QString const WIDTH{"width"};

static QString const FULL_SCREEN{"fullScreen"};

static QString const DISPLAY_MODE{"displayMode"};

static QString const ACTIVATED_TOOL{"activatedTool"};

static char const *const MASTER_PATH{"masterPath"};

static char const *const EXPORT_PATH{"exportPath"};

static char const *const IMAGE_PATH{"imagePath"};
}

General::DisplayMode displayModeFromJson(QJsonValue const &value)
{
    using namespace field_name;

    if (value.isString() && value.toString() == FULL_SCREEN)
        return General::FullScreen{};

    if (value.isObject()) {
        auto const object = value.toObject();
        checkObjectForKeys(object, HEIGHT, WIDTH);

        return Dimensions{
            .width = static_cast<quint16>(object[WIDTH].toInt()),
            .height = static_cast<quint16>(object[HEIGHT].toInt()),
        };
    }

    throw LoadingException{
        QStringLiteral("Invalid value for display mode")};

}

std::optional<General::Tool> toolFromJson(QJsonValue const &value)
{
    using namespace tools;

    static QMap<QString, General::Tool> const mapping{
        {BUBBLE_VIEW, General::Tool::BubbleView},
        {ZOOM_MAPS, General::Tool::ZoomMaps},
        {CODE_CHARTS, General::Tool::CodeCharts},
        {EYE_TRACKING, General::Tool::EyeTracking},
        {DATA_CLIENT, General::Tool::DataClient},
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

    auto const masterPath = getValueOrDefault(general, field_name::MASTER_PATH, &QCoreApplication::applicationDirPath);
    auto const exportPath = getValueOrDefault(general, field_name::EXPORT_PATH, [&masterPath]
    {
        return masterPath + paths::EXPORT_PATH;
    });
    auto const imagePath = getValueOrDefault(general, field_name::IMAGE_PATH, [&masterPath]
    {
        return masterPath + paths::IMAGE_PATH;
    });

    return {
        .displayMode = displayModeFromJson(general[field_name::DISPLAY_MODE]),
        .activatedTool = toolFromJson(general[field_name::ACTIVATED_TOOL]),
        .masterPath = masterPath,
        .exportPath = exportPath,
        .imagePath = imagePath,
    };
}
}
