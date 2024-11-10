#include "newgamewindow.h"
#include "ui_newgamewindow.h"
#include <QMessageBox>
#include <QMediaPlayer>


// no te olvides de recibir al cliente tambien
NewGameWindow::NewGameWindow(QWidget *parent, QMediaPlayer *player) :
        QDialog(parent),
        //cl(std::move(cl)),
        ui(new Ui::NewGameWindow),
        player(player)
{
    ui->setupUi(this);
}


NewGameWindow::~NewGameWindow()
{
    delete ui;
}

void NewGameWindow::on_backButton_clicked()
{
    this->close();
}

void NewGameWindow::on_musicButton_clicked()
{
    if (this->player->playbackState() == QMediaPlayer::PlayingState){
        this->player->pause();
    } else {
        this->player->play();
    }
}

void NewGameWindow::on_playersButton_clicked()
{
    // setear cantidad de jugadores para iniciar la partida
}

void NewGameWindow::on_player2Button_clicked()
{
    // setea si el jugador 2 es local o no
}

void NewGameWindow::on_mapaUnoButton_clicked()
{
    //createMatch("mapaUno");
}

void NewGameWindow::on_mapaDosButton_clicked()
{
    //createMatch("mapaDos");
}

void NewGameWindow::on_mapaTresButton_clicked()
{
    //createMatch("mapaTres");
}

void NewGameWindow::on_mapaCuatroButton_clicked()
{
    //createMatch("mapaCuatro");
}

// void NewGameWindow::createMatch(std::string map) {
//     // dejo esta funcion por las dudas
// }

