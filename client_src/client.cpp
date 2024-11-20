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

Client::Client(const char* host, const char* port):
        localPlayers(LOCAL_PLAYERS),
        protocol(Socket(host, port)),
        receiver_queue(),
        game_view() {
            std::cout << "game size " << games.size() << std::endl;
}

void Client::setLocalPlayers(int players) { localPlayers = players; }

Client::~Client() {}

void Client::select_game_mode(int game_mode){
    protocol.send_number(game_mode);
}


// std::vector<int> Client::get_available_games() {
    
// }

void Client::select_game(int game_id){
    protocol.send_number(game_id);
}


std::vector<games_DTO> Client::get_games_info(){
    
    return this->games;
}


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
                    std::cout << "Score received: " << std::endl;
                    std::cout << "1st place: " << static_cast<int>(score.first_place_score) << std::endl;
                    std::cout << "2nd place: " << static_cast<int>(score.second_place_score) << std::endl;
                    std::cout << "3rd place: " << static_cast<int>(score.third_place_score) << std::endl;
                    std::cout << "4th place: " << static_cast<int>(score.fourth_place_score) << std::endl;
                    game_view.load_score(score);
                } else if (m.get_code() == END_SCORE_CODE) {
                    score_DTO score = m.get_score();
                    std::cout << "Score received: " << std::endl;
                    std::cout << "1st place: " << static_cast<int>(score.first_place_score) << std::endl;
                    std::cout << "2nd place: " << static_cast<int>(score.second_place_score) << std::endl;
                    std::cout << "3rd place: " << static_cast<int>(score.third_place_score) << std::endl;
                    std::cout << "4th place: " << static_cast<int>(score.fourth_place_score) << std::endl;
                    game_view.load_endgame_score(score);
                    break;
                }
                else if (m.get_code() == GAMES_INFO_CODE) {
                    std::cout << "choose game to join" << std::endl;
                    // std::string input;
                    // std::getline(std::cin, input);
                    // sender.send_game_to_join(input);
                    
                    int size = m.get_size();
                    this->games.resize(size);                    
                    std::vector <games_DTO> available_games = m.get_games();
                    std::cout << "choose game to join2" << std::endl;
                    for (int i = 0; i < size; i++){
                        this->games[i].game_id = available_games[i].game_id;
                        this->games[i].current_players = available_games[i].current_players;
                        this->games[i].max_players = available_games[i].max_players;
                    }
                }
                else if(m.get_code() == PLAYERS_CODE){
                    std::cout << "players sending" << std::endl;
                    sender.send_players();
                    std::cout << "players sent" << std::endl;

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