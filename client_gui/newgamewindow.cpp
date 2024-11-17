#include "newgamewindow.h"

#include <QMediaPlayer>
#include <QMessageBox>
#include <iostream>
#include "../client_src/client.h"
#include "loadingwindow.h"

#include "ui_newgamewindow.h"

NewGameWindow::NewGameWindow(QWidget* parent, QMediaPlayer* player, QString address, QString port):
        QDialog(parent),
        ui(new Ui::NewGameWindow),
        player(player),
        localPlayers(1),
        address(address),
        port(port) {
    ui->setupUi(this);
    this->loadingWindow = new LoadingWindow(nullptr);
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

void NewGameWindow::on_selectPlayers_activated() {
    // setear cantidad de jugadores para iniciar la partida
    std::cout << "selectPlayers clicked" << std::endl;
}

void NewGameWindow::on_player2Button_clicked() {
    // setea si el jugador 2 es local o no
    if (ui->player2Button->isChecked()) {
        localPlayers = 2;
    } else {
        localPlayers = 1;
    }
}

void NewGameWindow::on_mapaUnoButton_clicked() {
    // createMatch("mapaUno");
    std::cout << "mapaUnoButton clicked" << std::endl;

    QByteArray byteArrayPort = port.toUtf8();
    char* charPort = byteArrayPort.data();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charAddress = byteArrayAddress.data();

    // createMatch("mapaUno");
    Client client(charAddress, charPort);
    client.setLocalPlayers(localPlayers);

    this->hide();
    this->loadingWindow->show();

    client.receive_map();
    this->loadingWindow->hide();
    client.run();
    this->show();
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
