#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <functional>
#include <unistd.h>

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "message.h"
#include "protocol_client.h"

#define MAP_CODE 0x00
#define GAME_SNAPSHOT_CODE 0x01
#define SCORE_CODE 0x02
#define END_SCORE_CODE 0x03
#define GAMES_INFO_CODE 0x04
#define PLAYERS_CODE 0x05
#define SEND_GAME_PLAYERS 0x06
#define FAIL_TO_JOIN 0x07
#define SEND_MAX_PLAYERS 0x08
#define SEND_MAP_NAME 0x09

class Receiver: public Thread {
private:
    ProtocolClient& protocol;
    Queue<Message>& queue;

    void receive_map();

    void receive_game_snapshot();

    void receive_score();

    void receive_end_score();

    void receive_game_info();

    void send_players();

    void send_players_and_game_id();

    void fail_to_join();

    void send_max_players();

    void send_map_name();

    void run() override;

public:
    Receiver(ProtocolClient& protocol, Queue<Message>& queue): protocol(protocol), queue(queue) {
        start();
    }

    ~Receiver() override;
};

#endif  // RECEIVER_H
