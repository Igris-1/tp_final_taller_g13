#ifndef PROTOCOL_CLIENT_H
#define PROTOCOL_CLIENT_H

#include "../common_src/socket.h"
#include <string>
#include "../common_src/game_snapshot_t.h"
#include "../common_src/action_t.h"

class ProtocolClient {

private:
    Socket connection;
    bool socket_is_closed;

public:
    explicit ProtocolClient(Socket&& client);

     ProtocolClient(ProtocolClient&& protocol) noexcept;

    void send_action(action_t& action);

    bool socket_closed();

    uint8_t read_number();

    game_snapshot_t read_snapshot();

    void shutDown();

    ~ProtocolClient();
};

#endif
