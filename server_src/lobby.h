#ifndef LOBBY_H
#define LOBBY_H

#include "../common_src/thread.h"
#include "games_manager.h"
#include <map>
#include <filesystem>
#include <string>
#include <functional>


class Lobby : public Thread {
private:
    int lobby_id;
    GamesManager& games_manager;
    Socket socket;

    void run() override;
    bool join_random_game(bool& is_close);
    bool join_game(bool& is_close);
    bool ask_for_games(bool& is_close);
    bool ask_for_maps(bool& is_close);

public:
    Lobby(GamesManager& games_manager, Socket&& socket);
    void creating_game(bool custom_map);
    ~Lobby();
};





#endif // LOBBY_H