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

public:
    Lobby(GamesManager& games_manager, Socket&& socket);
    void add_client();
    ~Lobby();
};





#endif // LOBBY_H