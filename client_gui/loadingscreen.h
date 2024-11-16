#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>

namespace Ui {
class LoadingScreen;
}

class LoadingScreen : public QMainWindow {
    Q_OBJECT

public:
    explicit LoadingScreen(QWidget *parent = nullptr);
    ~LoadingScreen();

private:
    Ui::LoadingScreen *ui;
};

#endif // MYWINDOW_H
