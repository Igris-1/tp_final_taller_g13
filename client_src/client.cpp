#include "client.h"

#include <iostream>
#include <vector>

#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"
#include "../common_src/queue.h"

#define LOCAL_PLAYERS 2
#define SLEEP_TIME_CLIENT 2000
#define MAP_CODE 0x00
#define GAME_SNAPSHOT_CODE 0x01
#define SCORE_CODE 0x02
#define END_SCORE_CODE 0x03
#define JOIN_GAME_CODE 0x04
#define PLAYERS_CODE 0x05

Client::Client(const char* host, const char* port):
        localPlayers(LOCAL_PLAYERS),
        protocol(Socket(host, port)),
        receiver_queue(),
        game_view() {
}

void Client::setLocalPlayers(int players) { localPlayers = players; }

Client::~Client() {}

void Client::select_game_mode(int game_mode){
    protocol.send_number_of_players(game_mode);
}

// std::map<int, std::tuple<int, int>> get_available_games(){
//     // return available games
//     // games_DTO game;


//     // std::vector<int> games;
//     // games[0] = game.game_id;
//     // games[1] = game.current_players;
//     // games[2] = game.max_players;

//     // games [3] = 2;
//     // games [4] = 4;
//     // games [5] = 4;

//     return nullptr;

// }


void Client::run() {

    try {
        Receiver receiver(protocol, receiver_queue);
        Sender sender(protocol, localPlayers);
        while (sender.is_alive() && receiver.is_alive()) {
            Message m(0);

            if (receiver_queue.try_pop(m)) {
                if(m.get_code() == MAP_CODE){
                    map_structure_t map = m.get_map();
                    game_view.add_map(map);
                } else if (m.get_code() == GAME_SNAPSHOT_CODE) {
                    game_snapshot_t gs = m.get_game_snapshot();
                    game_view.load_game(gs);
                } else if (m.get_code() == SCORE_CODE) {
                    score_DTO score = m.get_score();
                    game_view.load_score(score);
                } else if (m.get_code() == END_SCORE_CODE) {
                    score_DTO score = m.get_score();
                    game_view.load_endgame_score(score);
                    break;
                }
                else if (m.get_code() == JOIN_GAME_CODE) {
                    sender.send_game_to_join();
                }
                else if(m.get_code() == PLAYERS_CODE){
                    sender.send_players();
                }

            }
            usleep(SLEEP_TIME_CLIENT);
        }
        protocol.shutDown();

        receiver.stop();
        receiver.join();

        sender.stop();
        sender.join();

    } catch (const Exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
}