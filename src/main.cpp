#include <QtWidgets/QApplication>

#include "ui/MainWindow.hpp"

int main(int argc, char ** argv)
{
    Q_INIT_RESOURCE(resources);

    QApplication app{argc, argv};
    ui::MainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}
