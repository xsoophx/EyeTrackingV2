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
        static QString const UP;
        static QString const DOWN;
        static QString const LEFT;
        static QString const RIGHT;
        static QString const IN;
        static QString const OUT;

        QChar up{'W'};
        QChar down{'S'};
        QChar left{'A'};
        QChar right{'D'};
        QChar in{'I'};
        QChar out{'O'};
    };

    struct ZoomMapsPicture final
    {
        static QString const NAME;
        static QString const ZOOM_SPEED;

        QString name{config::DEFAULT_IMAGE};
        double zoomSpeed{1.0F};
    };

    static QString const KEY_BINDINGS;
    static QString const PICTURES;

    KeyBindings keyBindings;
    std::vector<ZoomMapsPicture> pictures;

};
}


#endif //CONFIG_ZOOMMAPS_HPP
