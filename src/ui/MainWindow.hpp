#ifndef UI_MAINWINDOW_HPP
#define UI_MAINWINDOW_HPP

#include <QtWidgets/QStackedWidget>

namespace ui
{
class UserInfoPage;
class MainMenuPage;

class MainWindow final: public QStackedWidget
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void showMainMenu();

private:
    UserInfoPage *userInfoPage;
    MainMenuPage *mainMenuPage;
};
}

#endif // UI_MAINWINDOW_HPP
