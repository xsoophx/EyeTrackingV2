#ifndef CONFIG_GENERAL_HPP
#define CONFIG_GENERAL_HPP

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

    DisplayMode displayMode;
    std::optional<Tool> activatedTool;
    QString masterPath;
    QString exportPath;
    QString imagePath;
};
}

#endif // CONFIG_GENERAL_HPP