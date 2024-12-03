#include "newgamewindow.h"

#include <QMediaPlayer>
#include <QMessageBox>
#include <iostream>

#include "../client_src/client.h"
#include "../client_src/usableMapsFinder.h"
#include "../client_src/joinable_games_finder.h"

#include "ui_newgamewindow.h"

#define PLAYER1 1
#define PLAYER2 2
#define PLAYERS 2
#define NEW_GAME 0
#define JOIN_GAME 1
#define RANDOM_GAME 3
#define PLAYGROUND 4
#define NEW_GAME_CUSTOM_MAP 6


NewGameWindow::NewGameWindow(QWidget* parent, QMediaPlayer* player, QString address, QString port):
        QDialog(parent),
        ui(new Ui::NewGameWindow),
        player(player),
        gamePlayers(PLAYERS),
        address(address),
        port(port) {
    ui->setupUi(this);
}

NewGameWindow::~NewGameWindow() { delete ui; }

void NewGameWindow::on_open_new_game() {
    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    UsableMapsFinder dummy2(charAddress, charPort);
    std::vector<std::string> maps = dummy2.ask_for_maps();

    this->ui->maps->clear();

    for (auto& map : maps) {
        QString qstr = QString::fromStdString(map);
        ui->maps->addItem(qstr);
    }
}

void NewGameWindow::on_backButton_clicked() { this->close();}

void NewGameWindow::on_musicButton_clicked() {
    if (this->player->playbackState() == QMediaPlayer::PlayingState) {
        this->player->pause();
    } else {
        this->player->play();
    }
}

void NewGameWindow::on_mapaUnoButton_clicked() {
    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    int localPlayers;
    if (ui->player2Button->isChecked()) {
        localPlayers = PLAYER2;
    } else {
        localPlayers = PLAYER1;
    }

    int players = this->ui->selectPlayers->currentIndex() + PLAYERS;

    this->player->stop();
    Client client(charAddress, charPort, NEW_GAME);
    client.setLocalPlayers(localPlayers);
    client.setMaxPlayers(players);
    client.select_game_mode(NEW_GAME);
    this->hide();
    client.run();
    this->player->play();
}

void NewGameWindow::on_playgroundButton_clicked() {
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
    this->player->play();
}

void NewGameWindow::on_startButton_clicked() {
    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    int localPlayers;
    if (ui->player2Button->isChecked()) {
        localPlayers = PLAYER2;
    } else {
        localPlayers = PLAYER1;
    }

    int players = this->ui->selectPlayers->currentIndex() + PLAYERS;
    this->player->stop();
    Client client(charAddress, charPort, 0);
    client.setLocalPlayers(localPlayers);
    client.setMaxPlayers(players);
    client.setMapName(this->ui->maps->currentText().toStdString());
    client.select_game_mode(NEW_GAME_CUSTOM_MAP);
    this->hide();
    client.run();
    this->player->play();
}
