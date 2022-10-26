#ifndef UI_USERINFOWIDGET_HPP
#define UI_USERINFOWIDGET_HPP

#include <QtCore/QScopedPointer>
#include <QtWidgets/QWidget>

namespace ui
{
struct UserInfoWidgetPrivate;

class UserInfoWidget: public QWidget
{
Q_OBJECT
    Q_DECLARE_PRIVATE(UserInfoWidget)

public:
    explicit UserInfoWidget(QWidget *parent = nullptr);
    ~UserInfoWidget() noexcept override;

private:
    QScopedPointer<UserInfoWidgetPrivate> d_ptr;
};
}

#endif //UI_USERINFOWIDGET_HPP
