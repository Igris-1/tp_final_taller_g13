#ifndef GAMES_MANAGER_H
#define GAMES_MANAGER_H

#include <map>
#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/action_t.h"
#include "../common_src/liberror.h"
#include "../common_src/socket.h"
#include "actions/duck_creator.h"
#include "list_of_clients_monitor.h"
#include "game_thread.h"
#include <memory>

struct game_t{
    int game_id;
    int player_count = 0;
    Queue<std::shared_ptr<Action>> gameQueue;
    ListOfClientsMonitor clients;
    GameThread gameThread;

    game_t(int id): game_id(id), gameQueue(), clients(),gameThread(gameQueue, clients){}
};

typedef struct game_t game_thread_t;


class GamesManager {
private:
    std::list<std::unique_ptr<game_t>> games;
    int games_counter = 1;
public:
    explicit GamesManager();

    void create_new_game();

    void add_client_to_game(int game_id, Socket&& client_socket, int number_of_players);

    void finish_game(int game_id);

    int get_game_counter();

    std::list<std::unique_ptr<game_t>>& get_games();

    ~GamesManager();

};

class GamesManagerError: public std::exception {
private:
    std::string msg;
public:
    GamesManagerError(std::string msg): msg(msg) {}
    virtual const char* what() const noexcept override { return msg.c_str(); }
};

#endif // GAMES_MANAGER_H
