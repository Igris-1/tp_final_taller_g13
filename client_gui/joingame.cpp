#include "joingame.h"

#include "ui_joingame.h"
#include <iostream>
#include <memory>
#include "../common_src/duck_DTO.h"

JoinGame::JoinGame(QWidget* parent, QMediaPlayer* player, QString address, QString port) : 
    QDialog(parent), 
    ui(new Ui::JoinGame),
    player(player),
    localPlayers(1),
    address(address),
    port(port), 
    client(nullptr) { 
        ui->setupUi(this);
    }

JoinGame::~JoinGame() { 
        delete ui; 
    }

void JoinGame::on_open_join_game() {
    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    this->client = std::make_shared<Client>(charPort, charAddress);
    client->select_game_mode(1);


    std::vector<games_DTO> games = client->get_games_info();
    std::cout << "Games size: " << games.size() << std::endl;

    if (!games.empty()) {
        ui->matchesBox->clear();
        for (const games_DTO& game : games) {
            QString gameInfo = QString("Game ID: %1 | Max Players: %2 | Current Players: %3")
                            .arg(game.game_id)
                            .arg(game.max_players)
                            .arg(game.current_players);
            ui->matchesBox->addItem(gameInfo);
        }
    }
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

void JoinGame::on_refreshButton_clicked() {
    // refrescar partidas del combo box
    std::cout << "refreshButton clicked" << std::endl;
}

void JoinGame::on_startButton_clicked() {
    // iniciar partida
    std::cout << "startButton clicked" << std::endl;

    int index = ui->matchesBox->currentIndex();

    //levantar un error si index es -1

    if (index != -1) {
        client->setLocalPlayers(localPlayers);

        std::cout << "Selected game: " << ui->matchesBox->currentIndex() << std::endl;

        client->select_game(ui->matchesBox->currentIndex());
        this->hide();
        client->run();
    }
}
