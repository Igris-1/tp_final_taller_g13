#ifndef CHOOSEOPTIONWINDOW_H
#define CHOOSEOPTIONWINDOW_H

#include <QDialog>
// #include "joinwindow.h"
#include "newgamewindow.h"
#include "aboutwindow.h"
// #include "../client_src/client_lobby.h"
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
class ChooseOptionWindow;
}

class ChooseOptionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseOptionWindow(QWidget *parent, QString port, QString address);
    void playMusic();
    ~ChooseOptionWindow();

private slots:
    void on_newGameButton_clicked();

    void on_joinGameButton_clicked();

    void on_exitGameButton_clicked();

    void on_aboutGameButton_clicked();

    void on_musicButton_clicked();


private:
    // ClientLobby cl;
    Ui::ChooseOptionWindow *ui;
    NewGameWindow *newGameWindow;
    // JoinWindow *joinWindow;
    AboutWindow *aboutWindow;

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};

#endif // CHOOSEOPTIONWINDOW_H