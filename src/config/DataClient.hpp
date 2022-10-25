#ifndef CONFIG_DATACLIENT_HPP
#define CONFIG_DATACLIENT_HPP

#include <QtGui/QColor>

#include <vector>

class QJsonObject;

namespace config
{
struct DataClient final
{
    static DataClient load(QJsonObject const &dataClient);

    static QString const COLOR_SAMPLE_BOARD;
    static QString const RED;
    static QString const GREEN;
    static QString const BLUE;

    std::vector<QColor> colorSampleBoard;
};
}


#endif //CONFIG_DATACLIENT_HPP
