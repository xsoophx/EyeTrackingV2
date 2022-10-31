#include "CodeCharts.hpp"

namespace
{
using namespace config;

QString const MATRIX_VIEW_TIME{"matrixViewTime"};

QString const MIN_VIEWS_TO_SUBDIVIDE{"minViewsToSubdivide"};

QString const ORDERED{"ordered"};

QString const STRING_CHARACTERS{"stringCharacters"};

QString const PICTURES{"pictures"};

QString const LOWER_CASE{"lowerCase"};

QString const UPPER_CASE{"upperCase"};

QString const NUMBERS{"numbers"};

CodeCharts::StringCharacters stringCharactersFromJson(QJsonValue stringCharacters)
{
    if (!stringCharacters.isObject())
        throw config::LoadingException{"String Characters of Codecharts is not an object."};

    auto const object = stringCharacters.toObject();

    checkObjectForKeys(object, UPPER_CASE, LOWER_CASE, NUMBERS);

    ObjectComponents const objectComponents{ObjectComponents::createStringsOnly(STRING_CHARACTERS,
                                                                                {UPPER_CASE, LOWER_CASE, NUMBERS})};
    objectComponents.checkComponentsByParent(object);

    return {
        .upperCase = stringCharacters[UPPER_CASE].toBool(),
        .lowerCase = stringCharacters[LOWER_CASE].toBool(),
        .numbers = stringCharacters[NUMBERS].toBool(),
    };
}

}

namespace config
{

Dimensions const CodeCharts::CodeChartsPicture::DEFAULT_GRID{Dimensions{.width = 100, .height = 100}};

CodeCharts CodeCharts::load(QJsonObject const &bubbleView)
{
    checkObjectForKeys(bubbleView,
                       MATRIX_VIEW_TIME,
                       MIN_VIEWS_TO_SUBDIVIDE,
                       ORDERED,
                       STRING_CHARACTERS,
                       PICTURES);

    ObjectComponents const components{
        "CodeCharts",
        {},
        {MATRIX_VIEW_TIME, MIN_VIEWS_TO_SUBDIVIDE},
        {ORDERED}
    };
    components.checkComponentsByParent(bubbleView);

    return CodeCharts{
        .matrixViewTime = static_cast<quint16>(bubbleView[MATRIX_VIEW_TIME].toInt()),
        .minViewsToSubdivide = static_cast<quint16>(bubbleView[MIN_VIEWS_TO_SUBDIVIDE].toInt()),
        .ordered = bubbleView[ORDERED].toBool(),
        .stringCharacters = stringCharactersFromJson(bubbleView[STRING_CHARACTERS])
    };
}
}
