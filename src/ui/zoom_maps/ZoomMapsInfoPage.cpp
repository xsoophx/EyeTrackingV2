#include "ZoomMapsInfoPage.hpp"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

namespace ui::zoom_maps
{

ZoomMapsInfoPage::ZoomMapsInfoPage(QWidget *parent /* = nullptr */)
    : QWidget{parent}
{
    auto const layout = new QVBoxLayout{this};

    // TODO: add some nicer texts and info to keys
    auto const label = new QLabel{"Zoom into the most interesting points in the image.\n", this};
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);

    auto const startButton = new QPushButton{"Start", this};
    startButton->setDefault(true);
    layout->addWidget(startButton);

    connect(startButton, &QPushButton::clicked, this, &ZoomMapsInfoPage::startButtonClicked);

}
}