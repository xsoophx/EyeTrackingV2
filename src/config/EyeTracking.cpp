#include "EyeTracking.hpp"
#include "Helpers.hpp"

#include <QtCore/QJsonArray>
#include <utility>


namespace
{
using namespace config;
using EyeTrackingPicture = EyeTracking::EyeTrackingPicture;

std::vector<EyeTrackingPicture> eyeTrackingPicturesFromJsonArray(QJsonArray const &pictures)
{
    std::vector<EyeTrackingPicture> result(pictures.size());

    std::transform(pictures.begin(),
                   pictures.end(),
                   result.begin(),
                   [index = size_t{0}](QJsonValue const &value) mutable
                   {
                       if (!value.isObject()
                           || !value[EyeTrackingPicture::NAME].isString()
                           || !isInt(value[EyeTrackingPicture::PICTURE_VIEW_TIME]))
                           throw config::LoadingException{
                               QStringLiteral(
                                   "%1 of Eye Tracking Pictures is not an object or has invalid name or picture view time.")
                                   .arg(index++)};

                       return EyeTracking::EyeTrackingPicture{
                           .name = value[EyeTrackingPicture::NAME].toString(),
                           .pictureViewTime = static_cast<quint16>(value[EyeTrackingPicture::PICTURE_VIEW_TIME]
                               .toInt()),
                       };
                   }
    );

    return result;
}
}

namespace config
{
QString const EyeTracking::PICTURES{"pictures"};

QString const EyeTracking::EyeTrackingPicture::NAME{"name"};

QString const EyeTracking::EyeTrackingPicture::PICTURE_VIEW_TIME{"pictureViewTime"};

EyeTracking EyeTracking::load(QJsonObject const &eyeTracking)
{
    checkObjectForKeys(eyeTracking, EyeTracking::PICTURES);

    return EyeTracking{eyeTrackingPicturesFromJsonArray(eyeTracking[EyeTracking::PICTURES].toArray())
    };
}
EyeTracking::EyeTracking(std::vector<EyeTrackingPicture> pictures)
    : pictures{std::move(pictures)}
{}

EyeTracking::EyeTracking()
    : EyeTracking({EyeTrackingPicture{}})
{}
}
