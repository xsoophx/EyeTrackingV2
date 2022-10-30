#ifndef CONFIG_GENERAL_HPP
#define CONFIG_GENERAL_HPP

#include "../Constants.hpp"
#include "Helpers.hpp"

#include <optional>
#include <variant>

#include <QtCore/QString>

class QJsonObject;

namespace config
{
struct General final
{
    static General load(QJsonObject const &general);

    enum class Tool
    {
        BubbleView,
        ZoomMaps,
        CodeCharts,
        EyeTracking,
        DataClient,
    };

    struct FullScreen final
    {
    };

    using DisplayMode = std::variant<FullScreen, Dimensions>;

    DisplayMode displayMode{FullScreen{}};
    std::optional<Tool> activatedTool{};
    QString masterPath{};
    QString exportPath{masterPath + config::EXPORT_PATH};
    QString imagePath{masterPath + config::IMAGE_PATH};
};
}

#endif // CONFIG_GENERAL_HPP