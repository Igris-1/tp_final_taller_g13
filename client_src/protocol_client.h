#ifndef PROTOCOL_CLIENT_H
#define PROTOCOL_CLIENT_H

#include <string>

#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"
#include "../common_src/score_DTO.h"
#include "../common_src/socket.h"
#include "../common_src/translator_DTOs.h"
#include <arpa/inet.h>
#include "../common_src/DTOs.h"

#include "message.h"

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

#define JOIN_DUMMY_ID 2
#define FIND_MAP_DUMMY_ID 5

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

    void send_join_dummy_id();

    int receive_games_size();

    games_DTO receive_games_dto();

    void send_number(int number); 

    void send_find_map_dummy_id();

    std::string receive_map_name(int size);

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
