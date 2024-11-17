#ifndef NEWGAMEWINDOW_H
#define NEWGAMEWINDOW_H
#include "../client_src/client.h"
#include <QDialog>
#include <QMediaPlayer>

namespace Ui {
class NewGameWindow;
}

class NewGameWindow: public QDialog {
    Q_OBJECT

public:
    NewGameWindow(QWidget* parent, QMediaPlayer* player, char* host, char* port);
    ~NewGameWindow();

private slots:
    void on_backButton_clicked();

    void on_musicButton_clicked();

    void on_selectPlayers_activated();

    void on_player2Button_clicked();

    void on_mapaUnoButton_clicked();

    void on_mapaDosButton_clicked();

    void on_mapaTresButton_clicked();

    void on_mapaCuatroButton_clicked();

private:
    Ui::NewGameWindow* ui;
    Client* client;
    QMediaPlayer* player;
    int localPlayers;
    char* host;
    char* port;
    // LoadingScreen* loadingScreen;

    // void createMatch(std::string map);
};

#endif  // CREATEWINDOW_H