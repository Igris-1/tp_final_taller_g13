#include "joingame.h"

#include <QMessageBox>
#include <iostream>
#include <memory>

#include "../client_src/joinable_games_finder.h"
#include "../common_src/DTOs.h"

#include "ui_joingame.h"

#define PLAYER1 1
#define PLAYER2 2
#define NEW_GAME 0
#define JOIN_GAME 1
#define RANDOM_GAME 3


JoinGame::JoinGame(QWidget* parent, QMediaPlayer* player, QString address, QString port):
        QDialog(parent),
        ui(new Ui::JoinGame),
        player(player),
        localPlayers(PLAYER1),
        address(address),
        port(port){
    ui->setupUi(this);
}

JoinGame::~JoinGame() { delete ui; }

void JoinGame::on_open_join_game() {
    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    JoinableGamesFinder dummy(charAddress, charPort);
    std::vector<games_DTO> games = dummy.ask_for_games();

    if (!games.empty()) {
        refresh_matches(games);
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
        localPlayers = PLAYER2;
    } else {
        localPlayers = PLAYER1;
    }
}

void JoinGame::on_refreshButton_clicked() {
    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    JoinableGamesFinder dummy(charAddress, charPort);
    std::vector<games_DTO> games = dummy.ask_for_games();

    if (!games.empty()) {
        refresh_matches(games);
    } else {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Error");
        msgBox.setText("No games found");
        msgBox.setStyleSheet("QMessageBox QLabel {"
                                "   background-image: transparent;"
                                "   border-image: transparent;"
                                "   color: #000000;"
                                "}"
                                "QMessageBox {"
                                "   background-image: transparent;"
                                "   border-image: transparent;"
                                "   background-color: #f0f0f0;"
                                "   border: 2px solid #000000;"
                                "   color: #000000;"
                                "}"
                                "QPushButton {"
                                "   background-image: transparent;"
                                "   border-image: transparent;"
                                "   background-color: #d9d9d9;"
                                "   color: #000000;"
                                "   border: 1px solid #000000;"
                                "   border-radius: 5px;"
                                "   padding: 5px;"
                                "}"
                                "QPushButton:hover {"
                                "   background-color: #e6e6e6;"
                                "}");
    msgBox.exec();
    }
}

void JoinGame::on_startButton_clicked() {
    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    int selectedGame = this->ui->matchesBox->currentIndex();

    if (selectedGame > -1) {
        int game_id = this->games_ids[selectedGame];
        this->player->stop();
        Client client(charAddress, charPort, game_id);
        client.setLocalPlayers(localPlayers);
        client.select_game_mode(JOIN_GAME);
        this->hide();
        client.run();
        this->player->play();
    }
}

void JoinGame::on_randomGameButton_clicked() {
    QByteArray byteArrayPort = port.toUtf8();
    QByteArray byteArrayAddress = address.toUtf8();
    char* charPort = byteArrayPort.data();
    char* charAddress = byteArrayAddress.data();

    this->player->stop();
    Client client(charAddress, charPort, NEW_GAME);
    client.setLocalPlayers(localPlayers);
    client.select_game_mode(RANDOM_GAME);
    this->hide();
    client.run();
    this->player->play();
}

void JoinGame::refresh_matches(std::vector<games_DTO> games) {
    if (!games.empty()) {
        games_ids.clear();
        ui->matchesBox->clear();
        for (const games_DTO& game: games) {
            games_ids.push_back(game.game_id);
            QString gameInfo = QString("Game ID: %1 | Current Players: %2 | Max Players: %3")
                                       .arg(game.game_id)
                                       .arg(game.current_players)
                                       .arg(game.max_players);
            ui->matchesBox->addItem(gameInfo);
        }
    }
}
