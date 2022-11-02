#ifndef UI_MAIN_WINDOW_HPP
#define UI_MAIN_WINDOW_HPP

#include <QtWidgets/QStackedWidget>

namespace ui
{
class UserInfoPage;

class MainWindow final: public QStackedWidget
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    UserInfoPage *userInfoPage;
};
}

#endif // UI_MAIN_WINDOW_HPP
