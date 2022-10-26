#include "UserInfoWidget.hpp"

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QVBoxLayout>

namespace ui
{
struct UserInfoWidgetPrivate final
{
    QWidget *parent;

    void setupChildren()
    {
    }

    void setupConnections()
    {
    }
};

UserInfoWidget::UserInfoWidget(QWidget *parent /* = nullptr */)
    : QWidget{parent}, d_ptr{new UserInfoWidgetPrivate{parent}}
{
    Q_D(UserInfoWidget);
    d->setupChildren();
    d->setupConnections();
}

UserInfoWidget::~UserInfoWidget() noexcept
= default;
}
