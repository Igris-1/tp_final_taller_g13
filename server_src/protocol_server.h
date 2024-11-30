#pragma once

#include <cstdint>
#include <mutex>
#include <string>

#include "../common_src/action_t.h"
#include "../common_src/socket.h"
#include <arpa/inet.h>
#include "game_snapshot_t.h"
#include "../common_src/translator_DTOs.h"

#define ONE_BYTE 1
#define TWO_BYTES 2

#define PROTOCOL_SEND_GAME_START_INFO 0x00
#define PROTOCOL_SEND_GAME_INFO 0x01
#define PROTOCOL_SEND_SCORE 0x02
#define PROTOCOL_SEND_FINAL_SCORE 0x03

class ProtocolServer {

private:
    Socket connection;
    bool socket_is_closed;
    std::mutex mutex;
    TranslatorDTOs translator_dto;

    void send_number(uint8_t& number);
    void send_long_number(uint16_t& number);

public:
    ProtocolServer(Socket&& client);

    // Move Constructor
    ProtocolServer(ProtocolServer&& other) noexcept;

    // Move Assignment Operator
    ProtocolServer& operator=(ProtocolServer&& other) noexcept;

    ProtocolServer(const ProtocolServer&) = delete;
    ProtocolServer& operator=(const ProtocolServer&) = delete;

    action_t receive_action();

    int receive_number();

    bool socket_closed();

    void shutDown();

    void sendGameInfo(game_snapshot_t game_snapshot);

    void sendScore(score_DTO score);

    void sendFinalScore(score_DTO score);

    void sendGameStartInfo(map_structure_t map_structure);

    ~ProtocolServer();
};
