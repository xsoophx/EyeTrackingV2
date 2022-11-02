#include "MainWindow.hpp"
#include "UserInfoPage.hpp"

namespace ui
{
MainWindow::MainWindow(QWidget *parent)
    : QStackedWidget{parent}
{
    setWindowTitle(QStringLiteral("EyeTrackingV2"));

    userInfoPage = new UserInfoPage{this};
    addWidget(userInfoPage);

    setCurrentWidget(userInfoPage);
}
}
