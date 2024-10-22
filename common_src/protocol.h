#pragma once
#include <string>

#include "socket.h"
#include "string"
#include "game_snapshot.h"


class Protocol {
private:
    Socket socket;
    bool socket_is_closed;

public:
    explicit Protocol(Socket&& socket);
    bool socket_closed();

    void kill_socket();

    void send_game_snapshot(GameSnapshot& gs);

    ~Protocol();
};
