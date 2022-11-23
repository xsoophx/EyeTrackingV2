#include "MainMenuPage.hpp"
#include "ui_MainMenuPage.h"

#include <QtCore/QEvent>

namespace ui
{
struct MainMenuPagePrivate final
{
    Ui_MainMenuPage ui;

    void setupUi(MainMenuPage *self)
    {
        ui.setupUi(self);
        QObject::connect(ui.zoomMapsButton, &QPushButton::clicked, self, &MainMenuPage::zoomMapsClicked);

    }
};

MainMenuPage::MainMenuPage(QWidget *parent /* = nullptr */)
    : QWidget{parent}, d_pointer{new MainMenuPagePrivate{}}
{
    Q_D(MainMenuPage);
    d->setupUi(this);
}

void MainMenuPage::changeEvent(QEvent *event)
{
    Q_D(MainMenuPage);
    switch (event->type()) {
    default:
        QWidget::changeEvent(event);
        break;
    case QEvent::LanguageChange:
        d->ui.retranslateUi(this);
        break;
    }
}

MainMenuPage::~MainMenuPage() noexcept
= default;
}