#ifndef CONFIG_EYETRACKING_HPP
#define CONFIG_EYETRACKING_HPP

#include <QtCore/QString>

#include <vector>

class QJsonObject;

namespace config
{
struct EyeTracking final
{
    static EyeTracking load(QJsonObject const &eyeTracking);

    struct EyeTrackingPicture final
    {
        static QString const NAME;
        static QString const PICTURE_VIEW_TIME;

        QString name;
        quint16 pictureViewTime;
    };

    static QString const PICTURES;

    std::vector<EyeTrackingPicture> pictures;
};

}


#endif //CONFIG_EYETRACKING_HPP
