#ifndef MAINMENUPAGE_HPP
#define MAINMENUPAGE_HPP

#include <QtCore/QScopedPointer>
#include <QtWidgets/QWidget>

namespace ui
{
struct MainMenuPagePrivate;

class MainMenuPage final: public QWidget
{
Q_OBJECT
    Q_DECLARE_PRIVATE_D(d_pointer, MainMenuPage)

public:
    explicit MainMenuPage(QWidget *parent = nullptr);
    ~MainMenuPage() noexcept override;

protected:
    void changeEvent(QEvent *event) override;

private:
    QScopedPointer<MainMenuPagePrivate> d_pointer;
};
}

#endif //MAINMENUPAGE_HPP
