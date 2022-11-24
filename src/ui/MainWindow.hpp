#ifndef UI_MAINWINDOW_HPP
#define UI_MAINWINDOW_HPP

#include <QtWidgets/QWidget>

class QStackedWidget;
class QPushButton;

namespace ui
{
class UserInfoPage;
class MainMenuPage;
namespace zoom_maps
{
class ZoomMapsInfoPage;
class ZoomMapsPage;
}

class MainWindow final: public QWidget
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void showMainMenu();
    void adjustButtonBar();
    void showZoomMapsInfo();
    void showZoomMaps();

private:
    QStackedWidget *stackedWidget;
    UserInfoPage *userInfoPage;
    MainMenuPage *mainMenuPage;
    zoom_maps::ZoomMapsInfoPage *zoomMapsInfoPage;
    zoom_maps::ZoomMapsPage *zoomMapsPage;

    QPushButton *mainMenuButton;
    QPushButton *quitButton;
};
}

#endif // UI_MAINWINDOW_HPP
