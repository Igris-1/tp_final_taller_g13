#include "joingame.h"

#include "ui_joingame.h"
#include <iostream>
#include <QMessageBox>
#include <memory>
#include "../common_src/duck_DTO.h"
#include "../client_src/joinable_games_finder.h"

JoinGame::JoinGame(QWidget* parent, QMediaPlayer* player, QString address, QString port) : 
    QDialog(parent), 
    ui(new Ui::JoinGame),
    player(player),
    localPlayers(1),
    address(address),
    port(port) { 
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
    std::vector <games_DTO> games = dummy.ask_for_games();

    if (!games.empty()) {
        refresh_matches(games);
    }
}   

void JoinGame::on_backButton_clicked() { this->close(); }


void JoinGame::on_musicButton_clicked() {
    std::cout << "musicButton clicked" << std::endl;

    if (this->player->playbackState() == QMediaPlayer::PlayingState) {
        this->player->pause();
    } else {
        this->player->play();
    }
}

void JoinGame::on_player2Button_clicked() {
    std::cout << "player2Button clicked" << std::endl;

    if (ui->player2Button->isChecked()) {
        localPlayers = 2;
    } else {
        localPlayers = 1;
    }
}

void JoinGame::on_refreshButton_clicked() {
    std::cout << "refreshButton clicked" << std::endl;

    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    JoinableGamesFinder dummy(charAddress, charPort);
    std::vector <games_DTO> games = dummy.ask_for_games();

    if (!games.empty()) {
        refresh_matches(games);
    } else {
        QMessageBox::information(this, "Error", "No games found");
    }
}

void JoinGame::on_startButton_clicked() {
    std::cout << "startButton clicked" << std::endl;

    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    int selectedGame = ui->matchesBox->currentIndex();

    if (selectedGame > -1) {
        this->player->stop();
        Client client(charAddress, charPort, selectedGame + 1);
        client.setLocalPlayers(localPlayers);
        client.select_game_mode(1);
        this->hide();
        client.run();
    }
}

void JoinGame::refresh_matches(std::vector <games_DTO> games) {
    if (!games.empty()) {
        ui->matchesBox->clear();
        for (const games_DTO& game : games) {
            QString gameInfo = QString("Game ID: %1 | Current Players: %2 | Max Players: %3")
                            .arg(game.game_id)
                            .arg(game.current_players)
                            .arg(game.max_players);
            ui->matchesBox->addItem(gameInfo);
        }
    }
}
