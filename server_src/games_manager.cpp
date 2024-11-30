#include "games_manager.h"

GamesManager::GamesManager() {}

void GamesManager::create_new_game() {
    // Buscar y limpiar juegos no vivos
    for (auto it = this->games.begin(); it != this->games.end();) {
        if (!(*it)->gameThread.is_alive()) {
            (*it)->gameThread.join();
            it = games.erase(it);
            continue;
        }
        // if ((*it)->game_id == this->games_counter) {
        //     throw GamesManagerError("Game already exists");
        // }
        ++it;
    }
    this->games.push_back(std::make_unique<game_t>(this->games_counter));
    this->games_counter++;
}

void GamesManager::add_client_to_game(int game_id, Socket&& ss, int number_of_players) {
    for (auto& game: this->games) {
        if (game->game_id == game_id) {
            game->clients.addClient(std::move(ss), game->gameQueue, game->player_count);
            for (int i = 0; i < number_of_players; i++) {
                auto create_duck = std::make_shared<DuckCreator>(game->player_count + i);
                game->gameQueue.push(create_duck);
            }
            game->player_count += number_of_players;
            return;
        }
    }
    throw GamesManagerError("Game not found");
}

void GamesManager::add_client_to_random_game(Socket&& ss, int number_of_players) {
    for (auto& game: this->games) {
        if (game->player_count + number_of_players <= 4) {
            game->clients.addClient(std::move(ss), game->gameQueue, game->player_count);
            for (int i = 0; i < number_of_players; i++) {
                auto create_duck = std::make_shared<DuckCreator>(game->player_count + i);
                game->gameQueue.push(create_duck);
            }
            game->player_count += number_of_players;
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

int GamesManager::get_game_counter() { return this->games_counter - 1; }

std::list<std::unique_ptr<game_t>>& GamesManager::get_games() { return this->games; }

GamesManager::~GamesManager() {
    for (auto& game: this->games) {
        game->gameThread.stop();
        game->gameThread.join();
    }
}