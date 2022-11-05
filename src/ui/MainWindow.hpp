#ifndef UI_MAINWINDOW_HPP
#define UI_MAINWINDOW_HPP

#include <QtWidgets/QWidget>

class QStackedWidget;
class QPushButton;

namespace ui
{
class UserInfoPage;
class MainMenuPage;

class MainWindow final: public QWidget
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void showMainMenu();
    void adjustButtonBar();

private:
    QStackedWidget *stackedWidget;
    UserInfoPage *userInfoPage;
    MainMenuPage *mainMenuPage;

    QPushButton *mainMenuButton;
    QPushButton *quitButton;
};
}

#endif // UI_MAINWINDOW_HPP
