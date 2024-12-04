#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <functional>
#include <unistd.h>

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include"../common_src/socket.h"

#include "message.h"
#include "protocol_client.h"

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
