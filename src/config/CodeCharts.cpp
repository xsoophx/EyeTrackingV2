#include "CodeCharts.hpp"

namespace
{
using namespace config;
using StringCharacters = CodeCharts::StringCharacters;

CodeCharts::StringCharacters stringCharactersFromJson(QJsonValue stringCharacters)
{
    if (!stringCharacters.isObject())
        throw config::LoadingException{"String Characters of Codecharts is not an object."};

    auto const object = stringCharacters.toObject();

    checkObjectForKeys(object,
                       StringCharacters::UPPER_CASE,
                       StringCharacters::LOWER_CASE,
                       StringCharacters::NUMBERS);

    ObjectComponents const objectComponents{ObjectComponents::createStringsOnly(CodeCharts::STRING_CHARACTERS,
                                                                                {StringCharacters::UPPER_CASE,
                                                                                 StringCharacters::LOWER_CASE,
                                                                                 StringCharacters::NUMBERS})};
    objectComponents.checkComponentsByParent(object);

    return {
        .upperCase = stringCharacters[StringCharacters::UPPER_CASE].toBool(),
        .lowerCase = stringCharacters[StringCharacters::LOWER_CASE].toBool(),
        .numbers = stringCharacters[StringCharacters::NUMBERS].toBool(),
    };
}

}

namespace config
{
QString const CodeCharts::MATRIX_VIEW_TIME{"matrixViewTime"};

QString const CodeCharts::MIN_VIEWS_TO_SUBDIVIDE{"minViewsToSubdivide"};

QString const CodeCharts::ORDERED{"ordered"};

QString const CodeCharts::STRING_CHARACTERS{"stringCharacters"};

QString const CodeCharts::PICTURES{"pictures"};

QString const CodeCharts::StringCharacters::LOWER_CASE{"lowerCase"};

QString const CodeCharts::StringCharacters::UPPER_CASE{"upperCase"};

QString const CodeCharts::StringCharacters::NUMBERS{"numbers"};

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
