#ifndef CONFIG_BUBBLEVIEW_HPP
#define CONFIG_BUBBLEVIEW_HPP

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

        QString name;
        struct Filter final
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

    static QString const PICTURES;
    std::vector<BubbleViewPicture> pictures;
};
}


#endif // CONFIG_BUBBLEVIEW_HPP
