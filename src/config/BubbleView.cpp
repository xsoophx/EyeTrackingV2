#include "BubbleView.hpp"
#include "Exceptions.hpp"
#include "Helpers.hpp"

#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <utility>

namespace
{
using namespace config;
using BubbleViewFilter = BubbleView::BubbleViewPicture::Filter;
using BubbleViewFilterType = BubbleView::BubbleViewPicture::FilterType;
using BubbleViewShape = BubbleView::BubbleViewPicture::Shape;

BubbleView::BubbleViewPicture::Filter filterFromJson(QJsonValue const &value)
{
    if (!value.isObject())
        throw config::LoadingException{"Name, value or BubbleViewPicture is not an object."};

    auto const object = value.toObject();

    ObjectComponents const
        components{"filter",
                   {BubbleViewFilter::SHAPE},
                   {
                       BubbleViewFilter::GRADIENT,
                       BubbleViewFilter::INTENSITY,
                       BubbleViewFilter::SIZE,
                       BubbleViewFilter::FILTER_TYPE
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

    checkObjectForKeys(object,
                       BubbleViewFilter::FILTER_TYPE,
                       BubbleViewFilter::SHAPE);

    auto const filterType =
        filterTypes.find(value[BubbleViewFilter::FILTER_TYPE].toString()).value();
    auto const
        shapeType = shapeTypes.find(value[BubbleViewFilter::SHAPE].toString()).value();


    return BubbleView::BubbleViewPicture::Filter{
        .gradient = static_cast<quint16>(value[BubbleViewFilter::GRADIENT].toInt()),
        .type = filterType,
        .intensity = static_cast<quint16>(value[BubbleViewFilter::INTENSITY].toInt()),
        .shape = shapeType,
        .size = static_cast<quint16>(value[BubbleViewFilter::SIZE].toInt()),

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
QString const BubbleView::PICTURES{"pictures"};

QString const BubbleViewFilter::FILTER_TYPE{"type"};

QString const BubbleViewFilter::GRADIENT{"gradient"};

QString const BubbleViewFilter::INTENSITY{"intensity"};

QString const BubbleViewFilter::SHAPE{"shape"};

QString const BubbleViewFilter::SIZE{"size"};

BubbleView BubbleView::load(QJsonObject const &bubbleView)
{
    if (!bubbleView[PICTURES].isArray())
        throw LoadingException{"pictures of Bubble View is not an array."};

    return BubbleView{bubbleViewPicturesFromJsonArray(bubbleView[PICTURES].toArray())};
}
BubbleView::BubbleView(std::vector<BubbleViewPicture> pictures)
    : pictures{std::move(pictures)}
{}

BubbleView::BubbleView()
    : BubbleView({BubbleViewPicture{}})
{}
}
