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

    std::vector<QColor> colorSampleBoard;

    explicit DataClient(std::vector<QColor> colorSampleBoard);
    DataClient();
};
}


#endif //CONFIG_DATACLIENT_HPP
