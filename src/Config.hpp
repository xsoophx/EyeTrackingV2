#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "config/BubbleView.hpp"
#include "config/CodeCharts.hpp"
#include "config/General.hpp"
#include "config/ZoomMaps.hpp"

#include <optional>
#include <variant>
#include <vector>

#include <QtCore/QString>
#include <QtGlobal>
#include <QtGui/QColor>


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
    using CodeCharts = config::CodeCharts;

    using Tool = General::Tool;

    General general;
    BubbleView bubbleView;
    ZoomMaps zoomMaps;
    CodeCharts codeCharts;

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
