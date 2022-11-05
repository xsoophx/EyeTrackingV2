#include "MainWindow.hpp"
#include "MainMenuPage.hpp"
#include "UserInfoPage.hpp"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>

namespace ui
{
MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle(QStringLiteral("EyeTrackingV2"));

    auto const layout = new QVBoxLayout{this};
    stackedWidget = new QStackedWidget{this};

    layout->addWidget(stackedWidget);

    userInfoPage = new UserInfoPage{stackedWidget};
    stackedWidget->addWidget(userInfoPage);

    mainMenuPage = new MainMenuPage{stackedWidget};
    stackedWidget->addWidget(mainMenuPage);

    stackedWidget->setCurrentWidget(userInfoPage);

    mainMenuButton = new QPushButton{tr("Main Menu"), this};
    quitButton = new QPushButton{tr("Quit"), this};

    auto const buttonLayout = new QHBoxLayout{};
    layout->addLayout(buttonLayout);
    buttonLayout->addWidget(mainMenuButton);
    buttonLayout->addWidget(quitButton);

    connect(userInfoPage, &UserInfoPage::accepted, this, &MainWindow::showMainMenu);
    connect(quitButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(mainMenuButton, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(stackedWidget, &QStackedWidget::currentChanged, this, &MainWindow::adjustButtonBar);

    adjustButtonBar();
}

void MainWindow::showMainMenu()
{
    stackedWidget->setCurrentWidget(mainMenuPage);
}

void MainWindow::adjustButtonBar()
{
    auto const currentWidget = stackedWidget->currentWidget();
    mainMenuButton->setDisabled(currentWidget == userInfoPage || currentWidget == mainMenuPage);
}
}
