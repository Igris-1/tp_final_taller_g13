#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>

#include <unistd.h>

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "message.h"
#include "protocol_client.h"

#define SLEEP_TIME 2000
#define MAP_CODE 0x00
#define GAME_SNAPSHOT_CODE 0x01
#define SCORE_CODE 0x02
#define END_SCORE_CODE 0x03
#define GAMES_INFO_CODE 0x04
#define PLAYERS_CODE 0x05
#define SEND_GAME_PLAYERS 0x06
#define FAIL_TO_JOIN 0x07
#define SEND_MAX_PLAYERS 0x08

class Receiver: public Thread {
private:
    ProtocolClient& protocol;
    Queue<Message>& queue;

    void receive_map() {
        std::cout << "Recibiendo mapa?" << std::endl;
        map_structure_t map = protocol.receive_map();
        Message message(MAP_CODE);
        message.set_map(map);
        queue.push(message);
    }

    void receive_game_snapshot() {
        game_snapshot_t gs = protocol.read_snapshot();
        Message message(GAME_SNAPSHOT_CODE);
        message.set_gs(gs);
        queue.push(message);
    }

    void receive_score() {
        score_DTO score = protocol.read_score();
        Message message(SCORE_CODE);
        message.set_score(score);
        queue.push(message);
    }

    void receive_end_score() {
        score_DTO score = protocol.read_score();
        Message message(END_SCORE_CODE);
        message.set_score(score);
        queue.push(message);
    }

    void receive_game_info() {
        Message message(GAMES_INFO_CODE);
        int size = protocol.read_number();
        protocol.receive_games(size, message);
        queue.push(message);
    }

    void send_players() {
        Message message(PLAYERS_CODE);
        queue.push(message);
    }

    void send_players_and_game_id() {

        std::cout << "mandame los players" << std::endl;
        Message message(SEND_GAME_PLAYERS);
        queue.push(message);
    }

    void fail_to_join() {
        std::cout << "No se pudo unir al juego" << std::endl;
        Message message(FAIL_TO_JOIN);
        queue.push(message);
    }

    void send_max_players(){
        Message message(SEND_MAX_PLAYERS);
        queue.push(message);
    }

    void run() override {
        std::map<uint8_t, std::function<void()>> functions = {
            {MAP_CODE, std::bind(&Receiver::receive_map, this)},
            {GAME_SNAPSHOT_CODE, std::bind(&Receiver::receive_game_snapshot, this)},
            {SCORE_CODE, std::bind(&Receiver::receive_score, this)},
            {END_SCORE_CODE, std::bind(&Receiver::receive_end_score, this)},
            {GAMES_INFO_CODE, std::bind(&Receiver::receive_game_info, this)},
            {PLAYERS_CODE, std::bind(&Receiver::send_players, this)},
            {SEND_GAME_PLAYERS, std::bind(&Receiver::send_players_and_game_id, this)},
            {FAIL_TO_JOIN, std::bind(&Receiver::fail_to_join, this)},
            {SEND_MAX_PLAYERS, std::bind(&Receiver::send_max_players, this)}
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

public:
    Receiver(ProtocolClient& protocol, Queue<Message>& queue): protocol(protocol), queue(queue) {
        start();
    }

    ~Receiver() override { _is_alive = false; }
};

#endif  // RECEIVER_H
