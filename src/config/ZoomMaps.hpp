#ifndef CONFIG_ZOOMMAPS_HPP
#define CONFIG_ZOOMMAPS_HPP

#include <QtCore/QString>

#include <vector>

class QJsonObject;

namespace config
{
struct ZoomMaps
{
    static ZoomMaps load(QJsonObject const &zoomMaps);

    struct KeyBindings
    {
        static QString const UP;
        static QString const DOWN;
        static QString const LEFT;
        static QString const RIGHT;
        static QString const IN;
        static QString const OUT;

        QChar up;
        QChar down;
        QChar left;
        QChar right;
        QChar in;
        QChar out;
    };

    struct ZoomMapsPicture
    {
        static QString const NAME;
        static QString const ZOOM_SPEED;

        QString name;
        double zoomSpeed;
    };

    static QString const KEY_BINDINGS;
    static QString const PICTURES;

    KeyBindings keyBindings;
    std::vector<ZoomMapsPicture> pictures;
};
}


#endif //CONFIG_ZOOMMAPS_HPP
