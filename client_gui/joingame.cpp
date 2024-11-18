#include "joingame.h"

#include "ui_joingame.h"
#include <iostream>

JoinGame::JoinGame(QWidget* parent, QMediaPlayer* player, QString address, QString port) : 
    QDialog(parent), 
    ui(new Ui::JoinGame),
    player(player),
    address(address),
    port(port),
    localPlayers(1)
    { 
        ui->setupUi(this);
        this->loadingWindow = new LoadingWindow(this);
        this->loadingWindow->setModal(true);    
    
    }

JoinGame::~JoinGame() { 
        if (this->loadingWindow != nullptr) {
            delete this->loadingWindow;
        }
        delete ui; 
    }

void JoinGame::on_backButton_clicked() { this->close(); }

void JoinGame::on_musicButton_clicked() {
    if (this->player->playbackState() == QMediaPlayer::PlayingState) {
        this->player->pause();
    } else {
        this->player->play();
    }
}

void JoinGame::on_player2Button_clicked() {
    if (ui->player2Button->isChecked()) {
        localPlayers = 2;
    } else {
        localPlayers = 1;
    }
}

void JoinGame::on_matchesBox_activated() {
    // elegir una partida
    std::cout << "matchesBox clicked" << std::endl;
}

void JoinGame::on_refreshButton_clicked() {
    // refrescar partidas del combo box
}

void JoinGame::on_startButton_clicked() {
    // iniciar partida
    std::cout << "startButton clicked" << std::endl;

    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    // aca se instancia el cliente
    this->loadingWindow->exec();
    this->hide();
}
