#include <QtWidgets/QApplication>

#include "ui/UserInfoWidget.hpp"

int main(int argc, char ** argv)
{
    QApplication app{argc, argv};
    ui::UserInfoWidget userInfoWidget;
    userInfoWidget.show();

    return QApplication::exec();
}
