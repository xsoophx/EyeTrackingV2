#ifndef CONFIG_GENERAL_HPP
#define CONFIG_GENERAL_HPP

#include <optional>
#include <variant>

#include <QtCore/QString>

class QJsonObject;

namespace config
{
struct General
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

    struct FullScreen
    {
    };

    struct Dimensions
    {
        quint16 width;
        quint16 height;
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