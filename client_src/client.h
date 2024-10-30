#ifndef CLIENT_H
#define CLIENT_H

#include <cstdint>
#include <string>
#include "../common_src/socket.h"
#include "protocol_client.h"
#include "receiver.h"
#include "sender.h"

class Client {
private:
    ProtocolClient protocol;
    Receiver receiver;
    Sender sender;
    Queue<game_snapshot_t> receiver_queue;
    Queue<action_t> sender_queue;

    void command (char pressed_key);
    game_snapshot_t get_snapshot();
    

public:
    void run();
    Client(const char* host, const char* port);
    ~Client();
};

#endif
