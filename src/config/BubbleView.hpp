#ifndef CONFIG_BUBBLEVIEW_HPP
#define CONFIG_BUBBLEVIEW_HPP

#include <QtCore/QString>
#include <vector>

class QJsonObject;

namespace config
{
struct BubbleView
{
    static BubbleView load(QJsonObject const &bubbleView);

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
};
}


#endif // CONFIG_BUBBLEVIEW_HPP
