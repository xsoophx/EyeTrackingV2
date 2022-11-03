#include "BubbleView.hpp"
#include "Exceptions.hpp"
#include "Helpers.hpp"

#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <utility>

namespace
{
using namespace config;
using BubbleViewFilterType = BubbleView::BubbleViewPicture::FilterType;
using BubbleViewShape = BubbleView::BubbleViewPicture::Shape;

namespace field_name
{
static QString const PICTURES{"pictures"};

static QString const FILTER_TYPE{"type"};

static QString const GRADIENT{"gradient"};

static QString const INTENSITY{"intensity"};

static QString const SHAPE{"shape"};

static QString const SIZE{"size"};

static QString const FILTER{"filter"};
}

BubbleView::BubbleViewPicture::Filter filterFromJson(QJsonValue const &value)
{
    if (!value.isObject())
        throw config::LoadingException{"Name, value or BubbleViewPicture is not an object."};

    auto const object = value.toObject();

    ObjectComponents const
        components{field_name::FILTER,
                   {field_name::SHAPE},
                   {
                       field_name::GRADIENT,
                       field_name::INTENSITY,
                       field_name::SIZE,
                       field_name::FILTER_TYPE
                   },
                   {}
    };
    components.checkComponentsByParent(object);

    static QMap<QString, BubbleViewFilterType> const filterTypes{
        {"gaussianBlur", BubbleViewFilterType::GaussianBlur},
        {"pixelate", BubbleViewFilterType::Pixelate},
        {"linearMovement", BubbleViewFilterType::LinearMovement}};

    static QMap<QString, BubbleView::BubbleViewPicture::Shape> const shapeTypes{
        {"circle", BubbleViewShape::Circle},
        {"square", BubbleViewShape::Square}};

    checkObjectForKeys(object, field_name::FILTER_TYPE, field_name::SHAPE);

    auto const filterType =
        filterTypes.find(value[field_name::FILTER_TYPE].toString()).value();
    auto const
        shapeType = shapeTypes.find(value[field_name::SHAPE].toString()).value();


    return BubbleView::BubbleViewPicture::Filter{
        .gradient = static_cast<quint16>(value[field_name::GRADIENT].toInt()),
        .type = filterType,
        .intensity = static_cast<quint16>(value[field_name::INTENSITY].toInt()),
        .shape = shapeType,
        .size = static_cast<quint16>(value[field_name::SIZE].toInt()),

    };

}

std::vector<BubbleView::BubbleViewPicture> bubbleViewPicturesFromJsonArray(QJsonArray const &pictures)
{
    std::vector<BubbleView::BubbleViewPicture> result(pictures.size());

    std::transform(pictures.begin(), pictures.end(), result.begin(), [](QJsonValue const &value)
    {
        if (!value.isObject() || !value[config::NAME].isString() || !value[field_name::FILTER].isString())
            throw config::LoadingException{"Name, value or BubbleViewPicture is not an object."};

        return BubbleView::BubbleViewPicture{
            .name = value[config::NAME].toString(),
            .filter = filterFromJson(value[field_name::FILTER])
        };
    });

    return result;
}
}

namespace config
{

BubbleView BubbleView::load(QJsonObject const &bubbleView)
{
    if (!bubbleView[field_name::PICTURES].isArray())
        throw LoadingException{"pictures of Bubble View is not an array."};

    return BubbleView{bubbleViewPicturesFromJsonArray(bubbleView[field_name::PICTURES].toArray())};
}
BubbleView::BubbleView(std::vector<BubbleViewPicture> pictures)
    : pictures{std::move(pictures)}
{}

BubbleView::BubbleView()
    : BubbleView({BubbleViewPicture{}})
{}
}
