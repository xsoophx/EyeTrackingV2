#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <optional>
#include <variant>
#include <vector>

#include <QtGlobal>
#include <QtGui/QColor>
#include <QtCore/QString>

#include "config/General.hpp"


struct Config
{
    static QString const GENERAL;
    static QString const BUBBLE_VIEW;
    static QString const CODE_CHARTS;
    static QString const ZOOM_MAPS;
    static QString const DATA_CLIENT;

    using General = config::General;
    using Tool = General::Tool;
    General general;

    struct Dimensions
    {
        quint16 width;
        quint16 height;
    };

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
                static QString const GRADIENT;
                static QString const FILTER_TYPE;
                static QString const INTENSITY;
                static QString const SHAPE;
                static QString const SIZE;

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
            static QString const UP;
            static QString const DOWN;
            static QString const LEFT;
            static QString const RIGHT;
            static QString const IN;
            static QString const OUT;

            QChar up;
            QChar down;
            QChar left;
            QChar right;
            QChar in;
            QChar out;
        };

        struct ZoomMapsPicture
        {
            static QString const NAME;
            static QString const ZOOM_SPEED;

            QString name;
            double zoomSpeed;
        };

        static QString const KEY_BINDINGS;
        static QString const PICTURES;

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
