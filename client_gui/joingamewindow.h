#ifndef JOINWINDOW_H
#define JOINWINDOW_H

#include <QDialog>


namespace Ui {
class JoinWindow;
}

class JoinWindow : public QDialog
{
    Q_OBJECT

public:
    JoinWindow(QWidget *parent);
    ~JoinWindow();

private slots:
    void on_refreshButton_clicked();

    void on_joinButton_clicked();

private:
    // ClientLobby cl;
    Ui::JoinWindow *ui;
};

#endif // JOINWINDOW_H