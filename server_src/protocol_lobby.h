#ifndef PROTOCOL_LOBBY_H
#define PROTOCOL_LOBBY_H

#define ONE_BYTE 1
#define TWO_BYTES 2
#include "../common_src/socket.h"
#include <cstdint>
#include <string>
#include "../common_src/DTOs.h"

class ProtocolLobby {
    private:
    Socket& socket;
    bool socket_is_closed;

    public:
        int get_players();
        void send_games_size(int& size);
        void send_text(const std::string& text);
        int get_max_players();
        std::string receive_map_name();
        void send_number(uint8_t& number);
        void stop_sending_maps();
        int get_game_id();
        void send_games(games_DTO& game);
        int receive_key_code();
        ProtocolLobby(Socket& socket);
        ~ProtocolLobby();



};


#endif //PROTOCOL_LOBBY_H