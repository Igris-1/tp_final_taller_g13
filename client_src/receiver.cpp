#include "receiver.h"
#include "../common_src/queue.h"
#include "protocol_client.h"
#include <map> 

void Receiver::receive_map() {
    std::cout << "Recibiendo mapa?" << std::endl;
    map_structure_t map = protocol.receive_map();
    Message message(MAP_CODE);
    message.set_map(map);
    queue.push(message);
}

void Receiver::receive_game_snapshot() {
    game_snapshot_t gs = protocol.read_snapshot();
    Message message(GAME_SNAPSHOT_CODE);
    message.set_gs(gs);
    queue.push(message);
}

void Receiver::receive_score() {
    score_DTO score = protocol.read_score();
    Message message(SCORE_CODE);
    message.set_score(score);
    queue.push(message);
}

void Receiver::receive_end_score() {
    score_DTO score = protocol.read_score();
    Message message(END_SCORE_CODE);
    message.set_score(score);
    queue.push(message);
}

void Receiver::receive_game_info() {
    Message message(GAMES_INFO_CODE);
    int size = protocol.read_number();
    protocol.receive_games(size, message);
    queue.push(message);
}

void Receiver::send_players() {
    Message message(PLAYERS_CODE);
    queue.push(message);
}

void Receiver::send_players_and_game_id() {

    std::cout << "mandame los players" << std::endl;
    Message message(SEND_GAME_PLAYERS);
    queue.push(message);
}

void Receiver::fail_to_join() {
    std::cout << "No se pudo unir al juego" << std::endl;
    Message message(FAIL_TO_JOIN);
    queue.push(message);
}

void Receiver::send_max_players(){
    Message message(SEND_MAX_PLAYERS);
    queue.push(message);
}
void Receiver::send_map_name(){
    Message message(SEND_MAP_NAME);
    queue.push(message);
}

void Receiver::run() {
    std::map<uint8_t, std::function<void()>> functions = {
        {MAP_CODE, std::bind(&Receiver::receive_map, this)},
        {GAME_SNAPSHOT_CODE, std::bind(&Receiver::receive_game_snapshot, this)},
        {SCORE_CODE, std::bind(&Receiver::receive_score, this)},
        {END_SCORE_CODE, std::bind(&Receiver::receive_end_score, this)},
        {GAMES_INFO_CODE, std::bind(&Receiver::receive_game_info, this)},
        {PLAYERS_CODE, std::bind(&Receiver::send_players, this)},
        {SEND_GAME_PLAYERS, std::bind(&Receiver::send_players_and_game_id, this)},
        {FAIL_TO_JOIN, std::bind(&Receiver::fail_to_join, this)},
        {SEND_MAX_PLAYERS, std::bind(&Receiver::send_max_players, this)},
        {SEND_MAP_NAME, std::bind(&Receiver::send_map_name, this)}
    };
    while (!protocol.socket_closed() && _keep_running) {
        try {
            uint8_t code = protocol.read_number();
            try {
                functions[code]();
            } catch (const std::out_of_range& e) {
                std::cerr << "funcion con codigo " << (int)code << " no existe. " << e.what() << std::endl;
            }
            usleep(SLEEP_TIME);
        } catch (const std::exception& e) {
            std::cerr << "Receiver fallo: " << e.what() << std::endl;
        }
    }
}

Receiver::~Receiver() { _is_alive = false; }