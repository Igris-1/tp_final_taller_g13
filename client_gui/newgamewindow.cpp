#include "newgamewindow.h"

#include <QMediaPlayer>
#include <QMessageBox>
#include <iostream>
#include "../client_src/client.h"

#include "ui_newgamewindow.h"

NewGameWindow::NewGameWindow(QWidget* parent, QMediaPlayer* player, char* host, char* port):
        QDialog(parent),
        ui(new Ui::NewGameWindow),
        client(new Client(host, port)),
        player(player) {
    ui->setupUi(this);
    // this->loadingScreen = new LoadingScreen(nullptr);
}


NewGameWindow::~NewGameWindow() { delete ui; }

void NewGameWindow::on_backButton_clicked() { this->close(); }

void NewGameWindow::on_musicButton_clicked() {
    if (this->player->playbackState() == QMediaPlayer::PlayingState) {
        this->player->pause();
    } else {
        this->player->play();
    }
}

void NewGameWindow::on_playersButton_clicked() {
    // setear cantidad de jugadores para iniciar la partida
    std::cout << "playersButton clicked" << std::endl;
}

void NewGameWindow::on_player2Button_clicked() {
    // setea si el jugador 2 es local o no
    client->setLocalPlayers(2);
}

void NewGameWindow::on_mapaUnoButton_clicked() {
    // createMatch("mapaUno");
    std::cout << "mapaUnoButton clicked" << std::endl;
    // this->hide();
    // this->player->stop();
    // this->loadingScreen->show();
    // client->run()
    // .then([this](){
    //     this->loadingScreen->close();
    //     this->close();
    // })
    // this->player->play();
}

void NewGameWindow::on_mapaDosButton_clicked() {
    // createMatch("mapaDos");
    std::cout << "mapaDosButton clicked" << std::endl;
}

void NewGameWindow::on_mapaTresButton_clicked() {
    // createMatch("mapaTres");
    std::cout << "mapaTresButton clicked" << std::endl;
}

void NewGameWindow::on_mapaCuatroButton_clicked() {
    // createMatch("mapaCuatro");
    std::cout << "mapaCuatroButton clicked" << std::endl;
}

// void NewGameWindow::createMatch(std::string map) {
//     // dejo esta funcion por las dudas
// }
