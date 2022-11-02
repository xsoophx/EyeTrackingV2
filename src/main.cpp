#include <QtWidgets/QApplication>

#include "ui/MainWindow.hpp"

int main(int argc, char ** argv)
{
    QApplication app{argc, argv};
    ui::MainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}
