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
#define GAMES_INFO_CODE 0x04
#define PLAYERS_CODE 0x05

Client::Client(const char* host, const char* port, uint8_t game_id):
        localPlayers(LOCAL_PLAYERS), protocol(Socket(host, port)), receiver_queue(), game_view() {
    game_to_join = game_id;
}

void Client::setLocalPlayers(int players) { localPlayers = players; }

void Client::setMaxPlayers(int max_players) { max_players_for_game = max_players; }

Client::~Client() {}

void Client::select_game_mode(int game_mode) { protocol.send_number(game_mode); }

// std::vector<int> Client::get_available_games() {
// for refhresh button
// }

void Client::setMapName(const std::string& map_name){
    this->map_name = map_name;
}

void Client::select_game(int game_id) { protocol.send_number(game_id); }

std::vector<games_DTO> Client::get_games_info() { return this->games; }

void Client::run() {

    try {
        Receiver receiver(protocol, receiver_queue);
        Sender sender(protocol, localPlayers);
        std::map<int, std::function<void(Message& m)>> actions = {
        {MAP_CODE, [&](Message& m) {
            map_structure_t map = m.get_map();
            game_view.add_map(map);
            
        }},
        {GAME_SNAPSHOT_CODE, [&](Message& m) {
            game_snapshot_t gs = m.get_game_snapshot();
            game_view.render_game(gs);
        }},
        {SCORE_CODE, [&](Message& m) {    
            score_DTO score = m.get_score();
            game_view.render_score(score); 
        }},
        {END_SCORE_CODE, [&](Message& m) {    
            score_DTO score = m.get_score();
            game_view.render_endgame_score(score);
        }},
        {GAMES_INFO_CODE, [&](Message& m) {   
            std::string input;
            std::getline(std::cin, input);
        }},
        {PLAYERS_CODE, [&](Message& m) {  
            sender.send_players();
        }},
        {SEND_GAME_PLAYERS, [&](Message& m) { 
            sender.send_players();
            sender.send_game_to_join(game_to_join);
        }},
        {SEND_MAX_PLAYERS, [&](Message& m) {  
            sender.send_max_players(max_players_for_game);
        }},
        {SEND_MAP_NAME, [&](Message& m) {  
            sender.send_map_name(this->map_name);
        }}
    };

        while (sender.is_alive() && receiver.is_alive()) {
            Message m(0);
            if (receiver_queue.try_pop(m)) {
                if (actions.count(m.get_code())) {
                    actions[m.get_code()](m);
                } else {
                    std::cerr << "Código desconocido: " << m.get_code() << std::endl;
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