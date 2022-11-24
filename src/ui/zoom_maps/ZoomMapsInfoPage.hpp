#ifndef ZOOMMAPSINFOPAGE_HPP
#define ZOOMMAPSINFOPAGE_HPP

#include <QWidget>

namespace ui::zoom_maps
{
class ZoomMapsInfoPage final: public QWidget
{
Q_OBJECT

public:
    explicit ZoomMapsInfoPage(QWidget *parent = nullptr);

signals:
    void startButtonClicked();

};
}


#endif //ZOOMMAPSINFOPAGE_HPP
