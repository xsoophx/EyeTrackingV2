#ifndef CONFIG_ZOOMMAPS_HPP
#define CONFIG_ZOOMMAPS_HPP

#include "../Constants.hpp"

#include <QtCore/QString>

#include <vector>

class QJsonObject;

namespace config
{
struct ZoomMaps final
{
    static ZoomMaps load(QJsonObject const &zoomMaps);

    struct KeyBindings final
    {
        QChar up{'W'};
        QChar down{'S'};
        QChar left{'A'};
        QChar right{'D'};
        QChar in{'I'};
        QChar out{'O'};
    };

    struct ZoomMapsPicture final
    {
        QString name{config::DEFAULT_IMAGE};
        double zoomSpeed{1.0F};
    };

    KeyBindings keyBindings;
    std::vector<ZoomMapsPicture> pictures;

};
}


#endif //CONFIG_ZOOMMAPS_HPP
