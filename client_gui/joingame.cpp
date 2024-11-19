#include "joingame.h"

#include "ui_joingame.h"
#include <iostream>
#include <map>
#include <tuple>

JoinGame::JoinGame(QWidget* parent, QMediaPlayer* player, QString address, QString port) : 
    QDialog(parent), 
    ui(new Ui::JoinGame),
    player(player),
    localPlayers(1) { 
        ui->setupUi(this);
        QByteArray byteArrayPort = port.toUtf8();
        QByteArray byteArrayAddress = address.toUtf8();
        char* charPort = byteArrayPort.data();
        char* charAddress = byteArrayAddress.data();
    }

JoinGame::~JoinGame() { 
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
    std::cout << "refreshButton clicked" << std::endl;
    
    // ui->matchesBox->clear();
    // std::map<int, std::tuple<int,int>> matches = client.get_available_games();
    
    // for (const auto& match : matches) {
    //     int id = match.first;
    //     int currentPlayers = std::get<0>(match.second);
    //     int maxPlayers = std::get<1>(match.second);

    //     QString matchInfo = QString("ID: %1 | Players: %2/%3")
    //                             .arg(id)
    //                             .arg(currentPlayers)
    //                             .arg(maxPlayers);
        
    //     ui->matchesBox->addItem(matchInfo);
    // }
}

void JoinGame::on_startButton_clicked() {
    // iniciar partida
    std::cout << "startButton clicked" << std::endl;

    // this->hide();
    // client.setLocalPlayers(localPlayers);
    // client.select_game_mode(0);
    // this->hide();
    // client.run();
}
