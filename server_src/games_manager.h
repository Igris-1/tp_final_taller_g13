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

// typedef struct{
//     Queue<std::shared_ptr<Action>> gameQueue;
//     ListOfClientsMonitor clients;
//     GameThread gameThread(gameQueue, clients);
// }game_thread_t;


struct game_t{
    int game_id;
    int player_count = 0;
    Queue<std::shared_ptr<Action>> gameQueue;
    ListOfClientsMonitor clients;
    GameThread gameThread;

    // Constructor to initialize the members
    game_t(int id): game_id(id), gameQueue(), clients(),gameThread(gameQueue, clients){}
};

typedef struct game_t game_thread_t;

class GamesManagerError: public std::exception {
private:
    std::string msg;
public:
    GamesManagerError(std::string msg): msg(msg) {}
    virtual const char* what() const noexcept override { return msg.c_str(); }
};

class GamesManager {
    private:
        std::list<game_thread_t> games;
    public:
        GamesManager();
        void create_new_game(int game_id){
            for(auto it = games.begin(); it != games.end();){
                if(!it->gameThread.is_alive()){
                    it->gameThread.join();
                    it = games.erase(it);
                    continue;
                }
                if(it->game_id == game_id){
                    throw GamesManagerError("Game already exists");
                }
                it++;
            }
            games.push_back(game_thread_t(game_id));
        }
        void add_client_to_game(int game_id, Socket&& client_socket){
            for(auto it = games.begin(); it != games.end(); it++){
                if(it->game_id == game_id){
                    it->clients.addClient(std::move(client_socket), it->gameQueue ,it->player_count);
                    std::shared_ptr<Action> create_duck = std::make_shared<DuckCreator>( it->player_count);
                    it->gameQueue.push(create_duck);
                    it->player_count = it->player_count + 2;
                    return;
                }
            }
            throw GamesManagerError("Game not found");
        }
        void finish_game(int game_id){
            for(auto it = games.begin(); it != games.end(); it++){
                if(it->game_id == game_id){
                    it->gameThread.stop();
                    it->gameThread.join();
                    games.erase(it);
                    return;
                }
            }
            throw GamesManagerError("Game not found");
        }
};

#endif // GAMES_MANAGER_H
