#include "UserInfoPage.hpp"
#include "ui_UserInfoPage.h"

#include <QtCore/QEvent>

namespace ui
{
struct UserInfoPagePrivate final
{
    Ui_UserInfoPage ui;

    void setupUi(QWidget * self) {
        ui.setupUi(self);
    }
};

UserInfoPage::UserInfoPage(QWidget *parent /* = nullptr */)
    : QWidget{parent}, d_pointer{new UserInfoPagePrivate{}}
{
    Q_D(UserInfoPage);
    d->setupUi(this);
}

void UserInfoPage::changeEvent(QEvent *event)
{
    Q_D(UserInfoPage);
    switch (event->type()) {
    default:
        QWidget::changeEvent(event);
        break;
    case QEvent::LanguageChange:
        d->ui.retranslateUi(this);
        break;
    }
}

UserInfoPage::~UserInfoPage() noexcept
= default;
}
