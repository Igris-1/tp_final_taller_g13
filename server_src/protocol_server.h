#pragma once

#include "../common_src/socket.h"
#include <string>
#include <cstdint>
#include "../common_src/game_snapshot.h"
#include "game_snapshot_t.h"
#include "action_t.h"

class ProtocolServer {

private:
    Socket connection;

public:
    ProtocolServer(Socket client);

    ProtocolServer(ProtocolServer&& other) noexcept;

    // operador move
    ProtocolServer& operator=(ProtocolServer&& other) noexcept {
        if (this != &other) {
            connection = std::move(other.connection);
        }
        return *this;
    }

    //constructor por copia eliminado
    ProtocolServer(const ProtocolServer&) = delete;
    
    //operador copy assignment eliminado
    ProtocolServer& operator=(const ProtocolServer&) = delete;

    void sendStringToClient(const char* message, bool* was_closed);

    
    void sendOneByteToClient(const uint8_t* data, bool* was_closed);

    action_t receiveDataFromClient(bool* was_closed);

    //void sendGameInfo(game_snapshot_t command, bool* was_closed);

    void shutDown();

    ~ProtocolServer();
};
