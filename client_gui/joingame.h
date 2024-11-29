#ifndef JOINGAME_H
#define JOINGAME_H

#include <QDialog>
#include <QMediaPlayer>
#include <memory>

#include "../client_src/client.h"
#include "../client_src/joinable_games_finder.h"


namespace Ui {
class JoinGame;
}

class JoinGame: public QDialog {
    Q_OBJECT

public:
    explicit JoinGame(QWidget* parent, QMediaPlayer* player, QString address, QString port);
    void on_open_join_game();

    ~JoinGame();

private slots:

    void on_backButton_clicked();

    void on_musicButton_clicked();

    void on_player2Button_clicked();

    void on_refreshButton_clicked();

    void on_startButton_clicked();

private:
    Ui::JoinGame* ui;
    QMediaPlayer* player;
    int localPlayers;
    QString address;
    QString port;

    void refresh_matches(std::vector<games_DTO> games);
};

#endif  // JOINGAME_H
