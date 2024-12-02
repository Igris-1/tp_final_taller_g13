#ifndef GAMES_MANAGER_H
#define GAMES_MANAGER_H

#include <map>
#include <memory>

#include "../common_src/action_t.h"
#include "../common_src/liberror.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "actions/duck_creator.h"
#include <mutex> 
#include "game_thread.h"
#include "list_of_clients_monitor.h"

struct game_t {
    int game_id;
    int player_count = 0;
    int max_players;
    Queue<std::shared_ptr<Action>> gameQueue;
    ListOfClientsMonitor clients;
    GameThread gameThread;

    game_t(int id, bool practice_mode, int max_players): game_id(id), gameQueue(), clients(), max_players(max_players), gameThread(gameQueue, clients, practice_mode, max_players){}
};

typedef struct game_t game_thread_t;


class GamesManager {
private:
    std::list<std::unique_ptr<game_t>> games;
    std::list<std::unique_ptr<game_t>> practice_games;
    int games_counter = 1;
    std::mutex mutex;
    bool add_client_to_game_without_lock(int game_id, Socket&& ss, int number_of_players);

public:
    explicit GamesManager();

    bool add_to_practice_game(Socket&& ss);
    bool create_new_game(Socket&& ss, int number_of_players, int max_players);

    bool add_client_to_game(int game_id, Socket&& ss, int number_of_players);

    void finish_game(int game_id);

    int get_game_counter();

    bool add_client_to_random_game(Socket&& ss, int number_of_players);

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

#endif  // GAMES_MANAGER_H
