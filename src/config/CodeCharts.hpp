#ifndef CONFIG_CODECHARTS_HPP
#define CONFIG_CODECHARTS_HPP

#include "../Constants.hpp"
#include "Helpers.hpp"

#include <QtCore/QString>
#include <vector>

class QJsonObject;

namespace config
{
struct CodeCharts final
{
    static CodeCharts load(QJsonObject const &bubbleView);

    struct StringCharacters final
    {
        static QString const UPPER_CASE;
        static QString const LOWER_CASE;
        static QString const NUMBERS;

        bool upperCase{true};
        bool lowerCase{true};
        bool numbers{true};
    };

    struct CodeChartsPicture final
    {
        static Dimensions const DEFAULT_GRID;

        QString name{config::DEFAULT_IMAGE};
        Dimensions grid{DEFAULT_GRID};
        quint16 pictureViewTime{5U};
        bool relative{false};
        quint16 maxRecursionDepth{3U};

    };

    static QString const MATRIX_VIEW_TIME;
    static QString const MIN_VIEWS_TO_SUBDIVIDE;
    static QString const ORDERED;
    static QString const STRING_CHARACTERS;
    static QString const PICTURES;

    quint16 matrixViewTime{5U};
    quint16 minViewsToSubdivide{3U};
    bool ordered{false};
    StringCharacters stringCharacters{};
    std::vector<CodeChartsPicture> pictures{};

};
}

#endif //CONFIG_CODECHARTS_HPP
