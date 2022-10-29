#include <QtWidgets/QApplication>

#include "ui/UserInfoPage.hpp"

int main(int argc, char ** argv)
{
    QApplication app{argc, argv};
    ui::UserInfoPage userInfoWidget;
    userInfoWidget.show();

    return QApplication::exec();
}
