#include "chooseoptionwindow.h"
#include "ui_chooseoptionwindow.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QScreen>
#include <iostream>

ChooseOptionWindow::ChooseOptionWindow(QWidget *parent, QString port, QString address) :
        QDialog(parent),
        ui(new Ui::ChooseOptionWindow),
        player(new QMediaPlayer(this)),
        audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);
    // this->joinWindow = NULL;
    this->newGameWindow = new NewGameWindow(nullptr, this->player, port, address);
    this->aboutWindow = new AboutWindow(nullptr);

    // Config player
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/assets/music/menu_song.mp3"));
    this->player->setLoops(QMediaPlayer::Infinite);
    audioOutput->setVolume(0.4);
    player->play();
}

ChooseOptionWindow::~ChooseOptionWindow()
{
    if (this->newGameWindow != NULL)
        delete newGameWindow;
    // if (this->joinWindow != NULL)
    //     delete joinWindow;
    if (this->aboutWindow != NULL)
        delete aboutWindow;
    delete ui;
}

void ChooseOptionWindow::on_joinGameButton_clicked()
{
    // this->joinWindow = new JoinWindow(nullptr, std::move(this->cl));
    // hide();
    // this->joinWindow->show();
}


void ChooseOptionWindow::on_newGameButton_clicked()
{
    this->hide();
    this->newGameWindow->exec();
    this->show(); 
}


void ChooseOptionWindow::on_exitGameButton_clicked()
{
    QApplication::quit();
}


void ChooseOptionWindow::on_aboutGameButton_clicked()
{
    this->hide();
    this->aboutWindow->exec();
    this->show();
}

void ChooseOptionWindow::on_musicButton_clicked()
{
    if (this->player->playbackState() == QMediaPlayer::PlayingState){
        this->player->pause();
    } else {
        this->player->play();
    }
}

void ChooseOptionWindow::playMusic()
{
    this->player->play();
}
