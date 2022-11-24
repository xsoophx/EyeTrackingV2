#include "ZoomMapsPage.hpp"

#include <QGraphicsPixmapItem>

namespace ui::zoom_maps
{
ZoomMapsPage::ZoomMapsPage(QWidget *parent)
    : QGraphicsView{parent}
{
    QImage image{":/images/Peepo.png"};

    auto const item = new QGraphicsPixmapItem{QPixmap::fromImage(image)};
    item->setPos(0.0f, 0.0f);
    auto scene = new QGraphicsScene{this};
    scene->addItem(item);

    setScene(scene);
    centerOn(0.0f, 0.0f);

}
}
