#ifndef UI_USERINFOWIDGET_HPP
#define UI_USERINFOWIDGET_HPP

#include <QtCore/QScopedPointer>
#include <QtWidgets/QWidget>

namespace ui
{
struct UserInfoPagePrivate;

class UserInfoPage final: public QWidget
{
Q_OBJECT
    Q_DECLARE_PRIVATE_D(d_pointer, UserInfoPage)

public:
    explicit UserInfoPage(QWidget *parent = nullptr);
    ~UserInfoPage() noexcept override;

protected:
    void changeEvent(QEvent *event) override;

private:
    QScopedPointer<UserInfoPagePrivate> d_pointer;
};
}

#endif //UI_USERINFOWIDGET_HPP
