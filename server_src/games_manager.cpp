#include "games_manager.h"

GamesManager::GamesManager() {}

 void GamesManager::create_new_game(int game_id) {
        // Buscar y limpiar juegos no vivos
        for (auto it = this->games.begin(); it != this->games.end(); ) {
            if (!(*it)->gameThread.is_alive()) {
                (*it)->gameThread.join();
                it = games.erase(it);
                continue;
            }
            if ((*it)->game_id == game_id) {
                throw GamesManagerError("Game already exists");
            }
            ++it;
        }
        this->games.push_back(std::make_unique<game_t>(game_id));
    }

    void GamesManager::add_client_to_game(int game_id, Socket&& client_socket) {
        for (auto& game : this->games) {
            if (game->game_id == game_id) {
                game->clients.addClient(std::move(client_socket), game->gameQueue, game->player_count);
                auto create_duck = std::make_shared<DuckCreator>(game->player_count);
                game->gameQueue.push(create_duck);
                game->player_count += 2;
                return;
            }
        }
        throw GamesManagerError("Game not found");
    }

    void GamesManager::finish_game(int game_id) {
        for (auto it = this->games.begin(); it != this->games.end(); ++it) {
            if ((*it)->game_id == game_id) {
                (*it)->gameThread.stop();
                (*it)->gameThread.join();
                games.erase(it);
                return;
            }
        }
        throw GamesManagerError("Game not found");
    }

    GamesManager::~GamesManager(){
        for (auto& game : this->games) {
            game->gameThread.stop();
            game->gameThread.join();
        }
    }