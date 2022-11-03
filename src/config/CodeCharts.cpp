#include "CodeCharts.hpp"

namespace
{
using namespace config;

namespace field_name
{
QString const MATRIX_VIEW_TIME{"matrixViewTime"};

QString const MIN_VIEWS_TO_SUBDIVIDE{"minViewsToSubdivide"};

QString const ORDERED{"ordered"};

QString const STRING_CHARACTERS{"stringCharacters"};

QString const PICTURES{"pictures"};

QString const LOWER_CASE{"lowerCase"};

QString const UPPER_CASE{"upperCase"};

QString const NUMBERS{"numbers"};
}

CodeCharts::StringCharacters stringCharactersFromJson(QJsonValue stringCharacters)
{
    if (!stringCharacters.isObject())
        throw LoadingException{"String Characters of Codecharts is not an object."};

    auto const object = stringCharacters.toObject();

    checkObjectForKeys(object, field_name::UPPER_CASE, field_name::LOWER_CASE, field_name::NUMBERS);

    ObjectComponents const objectComponents{ObjectComponents::createStringsOnly(field_name::STRING_CHARACTERS,
                                                                                {field_name::UPPER_CASE,
                                                                                 field_name::LOWER_CASE,
                                                                                 field_name::NUMBERS})};
    objectComponents.checkComponentsByParent(object);

    return {
        .upperCase = stringCharacters[field_name::UPPER_CASE].toBool(),
        .lowerCase = stringCharacters[field_name::LOWER_CASE].toBool(),
        .numbers = stringCharacters[field_name::NUMBERS].toBool(),
    };
}

}

namespace config
{

Dimensions const CodeCharts::CodeChartsPicture::DEFAULT_GRID{Dimensions{.width = 100, .height = 100}};

CodeCharts CodeCharts::load(QJsonObject const &bubbleView)
{
    checkObjectForKeys(bubbleView,
                       field_name::MATRIX_VIEW_TIME,
                       field_name::MIN_VIEWS_TO_SUBDIVIDE,
                       field_name::ORDERED,
                       field_name::STRING_CHARACTERS,
                       field_name::PICTURES);

    ObjectComponents const components{
        "CodeCharts",
        {},
        {field_name::MATRIX_VIEW_TIME, field_name::MIN_VIEWS_TO_SUBDIVIDE},
        {field_name::ORDERED}
    };
    components.checkComponentsByParent(bubbleView);

    return CodeCharts{
        .matrixViewTime = static_cast<quint16>(bubbleView[field_name::MATRIX_VIEW_TIME].toInt()),
        .minViewsToSubdivide = static_cast<quint16>(bubbleView[field_name::MIN_VIEWS_TO_SUBDIVIDE].toInt()),
        .ordered = bubbleView[field_name::ORDERED].toBool(),
        .stringCharacters = stringCharactersFromJson(bubbleView[field_name::STRING_CHARACTERS])
    };
}
}
