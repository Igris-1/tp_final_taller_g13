#include "newgamewindow.h"

#include <QMediaPlayer>
#include <QMessageBox>
#include <iostream>
#include "../client_src/client.h"

#include "ui_newgamewindow.h"

// no te olvides de recibir al cliente tambien
NewGameWindow::NewGameWindow(QWidget* parent, QMediaPlayer* player, QString port, QString address):
        QDialog(parent),
        // cl(std::move(cl)),
        ui(new Ui::NewGameWindow),
        player(player),
        port(port),
        address(address) {
    ui->setupUi(this);
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
    this->players = 2;
}

void NewGameWindow::on_mapaUnoButton_clicked() {
    // createMatch("mapaUno");
    char* port = this->port.toUtf8().data();
    char* address = this->address.toUtf8().data();
    QString playersStr = QString::number(this->players);
    char* localPlayers = playersStr.toUtf8().data();
    Client cl(address, port, localPlayers);
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
