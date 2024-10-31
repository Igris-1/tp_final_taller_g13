#ifndef CLIENT_H
#define CLIENT_H

#include <cstdint>
#include <string>
#include "../common_src/socket.h"
#include "protocol_client.h"
#include "receiver.h"
#include "sender.h"
#include "../common_src/thread.h"

class Client: public Thread {
private:
    ProtocolClient protocol;
    Queue<game_snapshot_t> receiver_queue;

    void command (char pressed_key);
    game_snapshot_t get_snapshot();
    

public:
    void run();
    Client(const char* host, const char* port);
    ~Client();
};

#endif
