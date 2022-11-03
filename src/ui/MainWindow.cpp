#include "MainWindow.hpp"
#include "MainMenuPage.hpp"
#include "UserInfoPage.hpp"

namespace ui
{
MainWindow::MainWindow(QWidget *parent)
    : QStackedWidget{parent}
{
    setWindowTitle(QStringLiteral("EyeTrackingV2"));

    userInfoPage = new UserInfoPage{this};
    addWidget(userInfoPage);

    mainMenuPage = new MainMenuPage{this};
    addWidget(mainMenuPage);

    setCurrentWidget(userInfoPage);
    connect(userInfoPage, &UserInfoPage::accepted, this, &MainWindow::showMainMenu);
    connect(mainMenuPage, &MainMenuPage::quitClicked, this, &MainWindow::close);
}

void MainWindow::showMainMenu()
{
    setCurrentWidget(mainMenuPage);
}
}
