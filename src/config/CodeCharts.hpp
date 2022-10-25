#ifndef CONFIG_CODECHARTS_HPP
#define CONFIG_CODECHARTS_HPP

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

        bool upperCase;
        bool lowerCase;
        bool numbers;
    };

    struct CodeChartsPicture final
    {
        QString name;
        Dimensions grid;
        quint16 pictureViewTime;
        bool relative;
        quint16 maxRecursionDepth;

    };

    static QString const MATRIX_VIEW_TIME;
    static QString const MIN_VIEWS_TO_SUBDIVIDE;
    static QString const ORDERED;
    static QString const STRING_CHARACTERS;
    static QString const PICTURES;

    quint16 matrixViewTime;
    quint16 minViewsToSubdivide;
    bool ordered;
    StringCharacters stringCharacters;
    std::vector<CodeChartsPicture> pictures;

};
}


#endif //CONFIG_CODECHARTS_HPP
