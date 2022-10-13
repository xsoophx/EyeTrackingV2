#include "BubbleView.hpp"
#include "Exceptions.hpp"
#include "Helpers.hpp"

#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

namespace
{
using namespace config;
using BubbleViewFilter = BubbleView::BubbleViewPicture::Filter;


BubbleView::BubbleViewPicture::Filter filterFromJson(QJsonValue const &value)
{
    if (!value.isObject())
        throw config::LoadingException{"Name, value or BubbleViewPicture is not an object."};

    auto const object = value.toObject();

    ObjectComponents
        components{"filter",
                   {BubbleViewFilter::SHAPE},
                   {
                       BubbleViewFilter::GRADIENT,
                       BubbleViewFilter::INTENSITY,
                       BubbleViewFilter::SIZE,
                       BubbleViewFilter::FILTER_TYPE
                   }
    };
    components.checkComponentsByParent(object);

    static QMap<QString, BubbleView::BubbleViewPicture::FilterType> const filterTypes{
        {"gaussianBlur", BubbleView::BubbleViewPicture::FilterType::GaussianBlur},
        {"pixelate", BubbleView::BubbleViewPicture::FilterType::Pixelate},
        {"linearMovement", BubbleView::BubbleViewPicture::FilterType::LinearMovement}};

    static QMap<QString, BubbleView::BubbleViewPicture::Shape> const shapeTypes{
        {"circle", BubbleView::BubbleViewPicture::Shape::Circle},
        {"square", BubbleView::BubbleViewPicture::Shape::Square}};

    checkObjectForKeys(object,
                       BubbleView::BubbleViewPicture::Filter::FILTER_TYPE,
                       BubbleView::BubbleViewPicture::Filter::SHAPE);

    auto const filterType =
        filterTypes.find(value[BubbleView::BubbleViewPicture::Filter::FILTER_TYPE].toString()).value();
    auto const
        shapeType = shapeTypes.find(value[BubbleView::BubbleViewPicture::Filter::SHAPE].toString()).value();


    return BubbleView::BubbleViewPicture::Filter{
        .gradient = static_cast<quint16>(value[BubbleView::BubbleViewPicture::Filter::GRADIENT].toInt()),
        .type = filterType,
        .intensity = static_cast<quint16>(value[BubbleView::BubbleViewPicture::Filter::INTENSITY].toInt()),
        .shape = shapeType,
        .size = static_cast<quint16>(value[BubbleView::BubbleViewPicture::Filter::SIZE].toInt()),

    };

}

std::vector<BubbleView::BubbleViewPicture> bubbleViewPicturesFromJsonArray(QJsonArray const &pictures)
{
    std::vector<BubbleView::BubbleViewPicture> result(pictures.size());

    std::transform(pictures.begin(), pictures.end(), result.begin(), [](QJsonValue const &value)
    {
        //TODO add constants
        if (!value.isObject() || !value["name"].isString() || !value["filter"].isString())
            throw config::LoadingException{"Name, value or BubbleViewPicture is not an object."};

        return BubbleView::BubbleViewPicture{
            .name = value["name"].toString(),
            .filter = filterFromJson(value["filter"])
        };
    });

    return result;
}
}

namespace config
{
BubbleView BubbleView::load(QJsonObject const &bubbleView)
{
    if (!bubbleView["pictures"].isArray())
        throw LoadingException{"pictures of Bubble View is not an array."};

    return {
        .pictures = bubbleViewPicturesFromJsonArray(bubbleView["pictures"].toArray())
    };
}
}
