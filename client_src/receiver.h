#ifndef RECEIVER_H
#define RECEIVER_H

#include <unistd.h>
#include <iostream>

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

class Receiver: public Thread {
private:
    ProtocolClient& protocol;
    Queue<Message>& queue;

    void receive_map() {
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
        std::cout << "encolo soliciutd d players en la queue" << std::endl;
        queue.push(message);
    }

    void send_players_and_game_id(){
        Message message(0x06);
        queue.push(message);
    }

    void run() override {
        while (!protocol.socket_closed() && _keep_running) {
            try {
                
                uint8_t code = protocol.read_number();
                if(code == MAP_CODE){
                    receive_map();
                }
                else if (code == GAME_SNAPSHOT_CODE) {
                    receive_game_snapshot();
                }
                else if(code == SCORE_CODE){
                    receive_score();
                }
                else if(code == END_SCORE_CODE){
                    receive_end_score();
                }
                else if(code == GAMES_INFO_CODE){
                    receive_game_info();
                }
                else if(code == PLAYERS_CODE){
                    send_players();
                }
                else if(code == 0x06){
                    send_players_and_game_id();
                }
    
                usleep(SLEEP_TIME);
            } catch (const std::exception& e) {
                std::cerr << "Exception while in client receiver thread: " << e.what() << std::endl;
            }
        }
    }

public:
    Receiver(ProtocolClient& protocol, Queue<Message>& queue):
            protocol(protocol), queue(queue) {
        start();
    }

    ~Receiver() override { _is_alive = false; }
};

#endif  // RECEIVER_H
