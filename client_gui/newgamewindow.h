#ifndef NEWGAMEWINDOW_H
#define NEWGAMEWINDOW_H

#include <QMediaPlayer>
#include <QDialog>

namespace Ui {
class NewGameWindow;
}

class NewGameWindow : public QDialog
{
    Q_OBJECT

public:
    // no te olvides de pasarle el puntero al cliente
    NewGameWindow(QWidget *parent, QMediaPlayer *player, QString port, QString address);
    ~NewGameWindow();

private slots:
    void on_backButton_clicked();

    void on_musicButton_clicked();

    void on_playersButton_clicked();

    void on_player2Button_clicked();

    void on_mapaUnoButton_clicked();

    void on_mapaDosButton_clicked();

    void on_mapaTresButton_clicked();

    void on_mapaCuatroButton_clicked();

private:
    //Client cl;
    Ui::NewGameWindow *ui;
    QMediaPlayer *player;
    int players;
    QString port;
    QString address;

    // void createMatch(std::string map);
};

#endif // CREATEWINDOW_H