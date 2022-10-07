#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <optional>
#include <variant>
#include <vector>

#include <QtGlobal>
#include <QtGui/QColor>
#include <QtCore/QString>


struct Config
{
    static QString const GENERAL;
    enum class Tool
    {
        BubbleView,
        ZoomMaps,
        CodeCharts,
        EyeTracking,
        DataClient,
    };

    struct Dimensions
    {
        quint16 width;
        quint16 height;
    };

    struct General
    {
        struct FullScreen
        {
        };

        using DisplayMode =  std::variant<FullScreen, Dimensions>;

        DisplayMode displayMode;
        std::optional<Tool> activatedTool;
        QString masterPath;
        QString exportPath;
        QString imagePath;

    } general;

    struct BubbleView
    {
        struct BubbleViewPicture
        {
            enum class FilterType
            {
                GaussianBlur,
                Pixelate,
                LinearMovement
            };

            enum class Shape
            {
                Circle,
                Square
            };

            QString name;
            struct Filter
            {
                quint16 gradient;
                FilterType type;
                quint16 intensity;
                Shape shape;
                quint16 size;

            } filter;

        };

        std::vector<BubbleViewPicture> pictures;
    } bubbleView;

    struct ZoomMaps
    {
        struct KeyBindings
        {
            QChar up;
            QChar down;
            QChar left;
            QChar right;
            QChar in;
            QChar out;
        };

        struct ZoomMapsPicture
        {
            QString name;
            double zoomSpeed;
        };

        KeyBindings keyBindings;
        std::vector<ZoomMapsPicture> pictures;
    } zoomMaps;

    struct CodeCharts
    {
        struct StringCharacters
        {
            bool upperCase;
            bool lowerCase;
            bool numbers;
        };

        struct CodeChartsPicture
        {
            QString name;
            Dimensions grid;
            quint16 pictureViewTime;
            bool relative;
            quint16 maxRecursionDepth;

        };

        quint16 matrixViewTime;
        quint16 minViewsToSubdivide;
        bool ordered;
        StringCharacters stringCharacters;
        std::vector<CodeChartsPicture> pictures;
    } codeCharts;

    struct EyeTracking
    {
        struct EyeTrackingPictures
        {
            QString name;
            quint16 pictureViewTime;
        };

        std::vector<EyeTrackingPictures> pictures;
    } eyeTracking;

    struct DataClient
    {
        std::vector<QColor> colorSampleBoard;
    } dataClient;

    struct Database
    {
        QString databasePath;
    } database;

    static Config load(QString const &path);

};

#endif //CONFIG_HPP
