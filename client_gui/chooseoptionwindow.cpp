#include "chooseoptionwindow.h"

#include <QAudioOutput>
#include <QMediaPlayer>
#include <QScreen>
#include <iostream>

#include "ui_chooseoptionwindow.h"

ChooseOptionWindow::ChooseOptionWindow(QWidget* parent, QString address, QString port):
        QDialog(parent),
        ui(new Ui::ChooseOptionWindow),
        player(new QMediaPlayer(this)),
        audioOutput(new QAudioOutput(this)) {
    ui->setupUi(this);
    this->newGameWindow = new NewGameWindow(nullptr, this->player, address, port);
    this->joinGame = new JoinGame(nullptr, this->player, address, port);
    this->aboutWindow = new AboutWindow(nullptr);

    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/assets/music/complete_menu_song.mp3"));
    this->player->setLoops(QMediaPlayer::Infinite);
    audioOutput->setVolume(0.2);
    player->play();
}

ChooseOptionWindow::~ChooseOptionWindow() {
    if (this->player != NULL)
        delete player;
    if (this->audioOutput != NULL)
        delete audioOutput;
    if (this->newGameWindow != NULL)
        delete newGameWindow;
    if (this->joinGame != NULL)
        delete joinGame;
    if (this->aboutWindow != NULL)
        delete aboutWindow;
    delete ui;
}

void ChooseOptionWindow::on_joinGameButton_clicked() {
    this->hide();
    this->joinGame->on_open_join_game();
    this->joinGame->exec();
    this->show();
}

void ChooseOptionWindow::on_newGameButton_clicked() {
    this->hide();
    this->newGameWindow->on_open_new_game();
    this->newGameWindow->exec();
    this->show();
}

void ChooseOptionWindow::on_exitGameButton_clicked() { QApplication::quit(); }


void ChooseOptionWindow::on_aboutGameButton_clicked() {
    this->hide();
    this->aboutWindow->exec();
    this->show();
}

void ChooseOptionWindow::on_musicButton_clicked() {
    if (this->player->playbackState() == QMediaPlayer::PlayingState) {
        this->player->pause();
    } else {
        this->player->play();
    }
}

void ChooseOptionWindow::playMusic() { this->player->play(); }
