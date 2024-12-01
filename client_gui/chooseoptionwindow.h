#ifndef CHOOSEOPTIONWINDOW_H
#define CHOOSEOPTIONWINDOW_H

#include <QAudioOutput>
#include <QDialog>
#include <QMediaPlayer>

#include "aboutwindow.h"
#include "joingame.h"
#include "newgamewindow.h"

namespace Ui {
class ChooseOptionWindow;
}

class ChooseOptionWindow: public QDialog {
    Q_OBJECT

public:
    explicit ChooseOptionWindow(QWidget* parent, QString address, QString port);
    void playMusic();
    ~ChooseOptionWindow();

private slots:
    void on_newGameButton_clicked();

    void on_joinGameButton_clicked();

    void on_exitGameButton_clicked();

    void on_aboutGameButton_clicked();

    void on_musicButton_clicked();


private:
    Ui::ChooseOptionWindow* ui;
    NewGameWindow* newGameWindow;
    JoinGame* joinGame;
    AboutWindow* aboutWindow;
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
};

#endif  // CHOOSEOPTIONWINDOW_H