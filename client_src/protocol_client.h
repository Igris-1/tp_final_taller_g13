#ifndef PROTOCOL_CLIENT_H
#define PROTOCOL_CLIENT_H

#include <string>

#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"
#include "../common_src/score_DTO.h"
#include "../common_src/socket.h"
#include "../common_src/translator_DTOs.h"
#include <arpa/inet.h>

#include "message.h"

class ProtocolClient {

private:
    Socket connection;
    bool socket_is_closed;
    TranslatorDTOs translator_dto;

    void send_long_number(uint16_t& number);

public:
    explicit ProtocolClient(Socket&& client);

    ProtocolClient(ProtocolClient&& protocol) noexcept;

    void send_action(action_t& action); 

    bool socket_closed(); 
    void send_number(int number); 
    uint8_t read_number(); 

    void receive_games(int size, Message& message); 

    uint16_t read_long_number();

    game_snapshot_t read_snapshot(); 

    score_DTO read_score(); 

    void send_string(std::string map_name); 

    map_structure_t receive_map(); 

    void shutDown();

    ~ProtocolClient();
};

#endif
