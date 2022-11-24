#ifndef ZOOMMAPSPAGE_HPP
#define ZOOMMAPSPAGE_HPP

#include <QtWidgets/QGraphicsView>

namespace ui::zoom_maps
{
class ZoomMapsPage final: public QGraphicsView
{
Q_OBJECT

public:
    explicit ZoomMapsPage(QWidget *parent = nullptr);

};
}


#endif //ZOOMMAPSPAGE_HPP
