#ifndef NEWGAMEWINDOW_H
#define NEWGAMEWINDOW_H
#include <QDialog>
#include <QMediaPlayer>

#include "../client_src/client.h"

namespace Ui {
class NewGameWindow;
}

class NewGameWindow: public QDialog {
    Q_OBJECT

public:
    NewGameWindow(QWidget* parent, QMediaPlayer* player, QString host, QString port);
    void on_open_new_game();
    ~NewGameWindow();

private slots:
    void on_backButton_clicked();

    void on_musicButton_clicked();

    void on_mapaUnoButton_clicked();

    void on_playgroundButton_clicked();

    void on_maps_activated();

    void on_startButton_clicked();

private:
    Ui::NewGameWindow* ui;
    Client* client;
    QMediaPlayer* player;
    int map;
    int gamePlayers;
    QString address;
    QString port;
};

#endif  // NEWGAMEWINDOW_H