#ifndef LOBBY_H
#define LOBBY_H

#include "../common_src/thread.h"
#include "games_manager.h"


class Lobby : public Thread {
private:
    int lobby_id;
    GamesManager& games_manager;
    Socket socket;

    void run() override;
    void send_number(uint8_t& number);
    void send__long_number(uint16_t& number);
    void receive_number(uint8_t& number);
    void receive__long_number(uint16_t& number);

public:
    Lobby(GamesManager& games_manager, Socket&& socket);
    void creating_game(bool custom_map);
    ~Lobby();
};





#endif // LOBBY_H