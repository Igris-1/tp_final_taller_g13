#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

private slots:
    void on_backButton_clicked();
    void on_gameRepoButton_clicked();
    void on_fedeButton_clicked();
    void on_nicoButton_clicked();
    void on_franButton_clicked();
    void on_pedroButton_clicked();

private:
    Ui::AboutWindow *ui;
};

#endif // ABOUTWINDOW_H