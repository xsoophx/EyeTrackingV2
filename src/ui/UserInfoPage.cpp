#include "UserInfoPage.hpp"
#include "ui_UserInfoPage.h"

#include <QtCore/QEvent>

#include <QtWidgets/QPushButton>

namespace ui
{
struct UserInfoPagePrivate final
{
    Ui_UserInfoPage ui;

    void setupUi(UserInfoPage *self)
    {
        ui.setupUi(self);
        QObject::connect(ui.buttonBox, &QDialogButtonBox::accepted, self, &UserInfoPage::accepted);
        QObject::connect(ui.firstNameEdit, &QLineEdit::textChanged, self, &UserInfoPage::checkRequiredInput);
        QObject::connect(ui.lastNameEdit, &QLineEdit::textChanged, self, &UserInfoPage::checkRequiredInput);
        QObject::connect(ui.ageSpin, &QSpinBox::textChanged, self, &UserInfoPage::checkRequiredInput);
        QObject::connect(ui.visionCombo, &QComboBox::currentTextChanged, self, &UserInfoPage::checkRequiredInput);
    }
};

UserInfoPage::UserInfoPage(QWidget *parent /* = nullptr */)
    : QWidget{parent}, d_pointer{new UserInfoPagePrivate{}}
{
    Q_D(UserInfoPage);
    d->setupUi(this);

    clearInputs();
    checkRequiredInput();
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

void UserInfoPage::clearInputs()
{
    Q_D(UserInfoPage);
    d->ui.firstNameEdit->clear();
    d->ui.lastNameEdit->clear();
    d->ui.ageSpin->setValue(0);
    d->ui.genderCombo->setCurrentIndex(0);
    d->ui.visionCombo->setCurrentIndex(0);
}

void UserInfoPage::checkRequiredInput()
{
    Q_D(UserInfoPage);

    auto const firstNameValid = !d->ui.firstNameEdit->text().isEmpty();
    auto const lastNameValid = !d->ui.lastNameEdit->text().isEmpty();
    auto const visionValid = d->ui.visionCombo->currentIndex() != 0;

    d->ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(firstNameValid && lastNameValid && visionValid);

}

UserInfoPage::~UserInfoPage() noexcept
= default;
}
