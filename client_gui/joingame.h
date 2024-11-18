#ifndef JOINGAME_H
#define JOINGAME_H

#include "loadingwindow.h"
#include <QDialog>
#include <QMediaPlayer>

namespace Ui {
class JoinGame;
}

class JoinGame: public QDialog {
    Q_OBJECT

public:
    explicit JoinGame(QWidget* parent, QMediaPlayer* player, QString address, QString port);
    ~JoinGame();

private slots:

    void on_backButton_clicked();

    void on_musicButton_clicked();

    void on_player2Button_clicked();

    void on_matchesBox_activated();
    
    void on_refreshButton_clicked();

    void on_startButton_clicked();

private:
    Ui::JoinGame* ui;
    QMediaPlayer* player;
    QString address;
    QString port;
    int localPlayers;
    LoadingWindow* loadingWindow;

};

#endif  // JOINGAME_H
