#ifndef CONFIG_EYETRACKING_HPP
#define CONFIG_EYETRACKING_HPP

#include "../Constants.hpp"

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

        QString name{config::DEFAULT_IMAGE};
        quint16 pictureViewTime{5U};
    };

    static QString const PICTURES;

    std::vector<EyeTrackingPicture> pictures;

    explicit EyeTracking(std::vector<EyeTrackingPicture> pictures);
    EyeTracking();
};

}


#endif //CONFIG_EYETRACKING_HPP
