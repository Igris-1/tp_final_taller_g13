#include "newgamewindow.h"

#include <QMediaPlayer>
#include <QMessageBox>
#include <iostream>

#include "../client_src/client.h"

#include "ui_newgamewindow.h"

#define PLAYER1 1
#define PLAYER2 2
#define PLAYERS 1
#define NEW_GAME 0
#define JOIN_GAME 1
#define RANDOM_GAME 3
#define PLAYGROUND 4


NewGameWindow::NewGameWindow(QWidget* parent, QMediaPlayer* player, QString address, QString port):
        QDialog(parent),
        ui(new Ui::NewGameWindow),
        player(player),
        localPlayers(PLAYER1),
        map(NEW_GAME),
        players(PLAYERS),
        address(address),
        port(port) {
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

void NewGameWindow::on_selectPlayers_activated() {
    // setear cantidad de jugadores para iniciar la partida
    std::cout << "selectPlayers clicked" << std::endl;
}

void NewGameWindow::on_player2Button_clicked() {
    if (ui->player2Button->isChecked()) {
        localPlayers = PLAYER2;
    } else {
        localPlayers = PLAYER1;
    }
}

void NewGameWindow::on_mapaUnoButton_clicked() {
    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    this->player->stop();
    Client client(charAddress, charPort, NEW_GAME);
    client.setLocalPlayers(localPlayers);
    client.select_game_mode(NEW_GAME);
    this->hide();
    client.run();
}

void NewGameWindow::on_playgroundButton_clicked() {
    // levantare el mapa custom
    std::cout << "playgroundButton clicked" << std::endl;

    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    this->player->stop();
    Client client(charAddress, charPort, NEW_GAME);
    client.setLocalPlayers(PLAYER2);
    client.select_game_mode(PLAYGROUND);
    this->hide();
    client.run();
}

void NewGameWindow::on_maps_activated() {
    // setear mapa para iniciar la partida
    this->map = ui->maps->currentIndex();
}

void NewGameWindow::on_startButton_clicked() {
    // levantar el mapa seleccionado
    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    // this->player->stop();
    // Client client(charAddress, charPort, 0);
    // client.setLocalPlayers(localPlayers);
    // client.select_game_mode(0);
    // this->hide();
    // client.run();
}
