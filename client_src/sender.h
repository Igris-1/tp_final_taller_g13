#ifndef SENDER_H
#define SENDER_H

#include <iostream>
#include <map>

#include <unistd.h>

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "protocol_client.h"

class Sender: public Thread {
private:
    ProtocolClient& protocol;
    Queue<action_t>& queue;
    
    int localPlayers = 2;

    void run() override;


public:
    Sender(ProtocolClient& protocol, int localPlayers, Queue<action_t>& queue);

    void send_game_to_join(int game_id);

    void send_max_players(int max_players_for_game);

    void send_map_name(std::string& map_name);

    void send_players();

    ~Sender() override;
};

#endif  // SENDER_H
