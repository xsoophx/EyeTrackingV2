#ifndef CONFIG_BUBBLEVIEW_HPP
#define CONFIG_BUBBLEVIEW_HPP

#include "../Constants.hpp"

#include <QtCore/QString>
#include <vector>

class QJsonObject;

namespace config
{
struct BubbleView final
{
    static BubbleView load(QJsonObject const &bubbleView);

    struct BubbleViewPicture final
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

        QString name{config::DEFAULT_IMAGE};
        struct Filter final
        {
            static QString const GRADIENT;
            static QString const FILTER_TYPE;
            static QString const INTENSITY;
            static QString const SHAPE;
            static QString const SIZE;

            quint16 gradient{1U};
            FilterType type{FilterType::GaussianBlur};
            quint16 intensity{1U};
            Shape shape{Shape::Circle};
            quint16 size{1U};

        } filter;

    };

    static QString const PICTURES;
    std::vector<BubbleViewPicture> pictures;

    explicit BubbleView(std::vector<BubbleViewPicture> pictures);
    BubbleView();
};
}


#endif // CONFIG_BUBBLEVIEW_HPP
