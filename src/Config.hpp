#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "config/BubbleView.hpp"
#include "config/CodeCharts.hpp"
#include "config/EyeTracking.hpp"
#include "config/General.hpp"
#include "config/ZoomMaps.hpp"
#include "config/DataClient.hpp"
#include "config/Database.hpp"

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
    static QString const EYE_TRACKING;
    static QString const DATA_CLIENT;
    static QString const DATABASE;

    using General = config::General;
    using BubbleView = config::BubbleView;
    using ZoomMaps = config::ZoomMaps;
    using CodeCharts = config::CodeCharts;
    using EyeTracking = config::EyeTracking;
    using DataClient = config::DataClient;
    using Database = config::Database;

    using Tool = General::Tool;

    General general;
    BubbleView bubbleView;
    ZoomMaps zoomMaps;
    CodeCharts codeCharts;
    EyeTracking eyeTracking;
    DataClient dataClient;
    Database database;

    static Config load(QString const &path);

};

#endif //CONFIG_HPP
