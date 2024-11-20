#include "joingame.h"

#include "ui_joingame.h"
#include <iostream>
#include <memory>
#include "../common_src/duck_DTO.h"
#include "../client_src/joinable_games_finder.h"

JoinGame::JoinGame(QWidget* parent, QMediaPlayer* player, QString address, QString port) : 
    QDialog(parent), 
    ui(new Ui::JoinGame),
    player(player),
    localPlayers(1),
    address(address),
    port(port) 
    // client(nullptr) 
    { 
        ui->setupUi(this);
    }

JoinGame::~JoinGame() { 
        delete ui; 
    }

void JoinGame::on_open_join_game() {
    std::cout << "open_join_game" << std::endl;

    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    JoinableGamesFinder dummy(charAddress, charPort);
    std::vector <games_DTO> games_to_join = dummy.ask_for_games();
    std::cout << "game id: " << static_cast<int>(games_to_join[0].game_id) << std::endl;
    
    
    
    // this->client = std::make_shared<Client>(charPort, charAddress);
    // client->select_game_mode(1);

    // std::vector<games_DTO> games = client->get_games_info();
    // std::cout << "Games size: " << games.size() << std::endl;

    // if (!games.empty()) {
    //     ui->matchesBox->clear();
    //     for (const games_DTO& game : games) {
    //         QString gameInfo = QString("Game ID: %1 | Max Players: %2 | Current Players: %3")
    //                         .arg(game.game_id)
    //                         .arg(game.max_players)
    //                         .arg(game.current_players);
    //         ui->matchesBox->addItem(gameInfo);
    //     }
    // }
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
    std::cout << "refreshButton clicked" << std::endl;
}

void JoinGame::on_startButton_clicked() {
    std::cout << "startButton clicked" << std::endl;

    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    Client client(charAddress, charPort, 1); //cambiar este 1 por el id de la partida que se elije para unir
    client.setLocalPlayers(localPlayers);
    client.select_game_mode(1);
    this->hide();
    client.run();
}
