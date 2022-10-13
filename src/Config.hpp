#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <optional>
#include <variant>
#include <vector>

#include <QtGlobal>
#include <QtGui/QColor>
#include <QtCore/QString>

#include "config/General.hpp"
#include "config/BubbleView.hpp"
#include "config/ZoomMaps.hpp"


struct Config
{
    static QString const GENERAL;
    static QString const BUBBLE_VIEW;
    static QString const CODE_CHARTS;
    static QString const ZOOM_MAPS;
    static QString const DATA_CLIENT;

    using General = config::General;
    using BubbleView = config::BubbleView;
    using ZoomMaps = config::ZoomMaps;

    using Tool = General::Tool;

    General general;
    BubbleView bubbleView;
    ZoomMaps zoomMaps;

    struct Dimensions
    {
        quint16 width;
        quint16 height;
    };

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
