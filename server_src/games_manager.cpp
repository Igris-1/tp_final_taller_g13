#include "games_manager.h"
#define SHUT_DOWN_TWO 2
GamesManager::GamesManager() {}

bool GamesManager::add_client_to_game_without_lock(int game_id, Socket&& ss, int number_of_players){
    for (auto& game: this->games) {
        if (game->game_id == game_id) {
            int max_players = game->max_players;
            if(game->player_count + number_of_players > max_players){
                ss.shutdown(SHUT_DOWN_TWO);
                ss.close();
                return false;
            }
            game->clients.addClient(std::move(ss), game->gameQueue, game->player_count);
            for (int i = 0; i < number_of_players; i++) {
                auto create_duck = std::make_shared<DuckCreator>(game->player_count + i);
                game->gameQueue.push(create_duck);
            }
            game->player_count += number_of_players;
            return true;
        }
    }
    return false;
}

bool GamesManager::create_game(Socket&& ss, int number_of_players, int max_players, std::string map_name){
    for (auto it = this->games.begin(); it != this->games.end();) {
        if (!(*it)->gameThread.is_alive()) {
            (*it)->gameThread.join();
            it = games.erase(it);
            continue;
        }
        ++it;
    }
    this->games.push_back(std::make_unique<game_t>(this->games_counter, false, max_players)); // true == practice mode
    this->games_counter++;
    this->games.back()->gameThread.start();
    this->games.back()->gameThread.set_map_name(map_name);
    return this->add_client_to_game_without_lock(this->get_game_counter(), std::move(ss), number_of_players);
}

bool GamesManager::create_new_custom_game(Socket&& ss, int number_of_players, int max_players, std::string map_name){
    std::lock_guard<std::mutex> lock(this->mutex);
    // Buscar y limpiar juegos no vivos
    return this->create_game(std::move(ss), number_of_players, max_players, map_name);
}




bool GamesManager::create_new_game(Socket&& ss, int number_of_players, int max_players) {
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->create_game(std::move(ss), number_of_players, max_players, "default_map");
}

bool GamesManager::add_client_to_game(int game_id, Socket&& ss, int number_of_players) {
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->add_client_to_game_without_lock(game_id, std::move(ss), number_of_players);
}

bool GamesManager::add_to_practice_game(Socket&& ss){
    std::lock_guard<std::mutex> lock(this->mutex);
    for (auto it = this->practice_games.begin(); it != this->practice_games.end();) {
        if (!(*it)->gameThread.is_alive()) {
            (*it)->gameThread.join();
            it = games.erase(it);
            continue;
        }
        ++it;
    }
    this->games.push_back(std::make_unique<game_t>(this->games_counter, true, 2)); // true == practice mode
    this->games_counter++;
    this->games.back()->gameThread.start();
    return this->add_client_to_game_without_lock(this->get_game_counter(), std::move(ss), 2);

}

bool GamesManager::add_client_to_random_game(Socket&& ss, int number_of_players) {
    std::lock_guard<std::mutex> lock(this->mutex);
    for (auto& game: this->games) {
        if (game->player_count + number_of_players > game->max_players) {
            return false;
        }
        game->clients.addClient(std::move(ss), game->gameQueue, game->player_count);
        for (int i = 0; i < number_of_players; i++) {
            auto create_duck = std::make_shared<DuckCreator>(game->player_count + i);
            game->gameQueue.push(create_duck);
        }
        game->player_count += number_of_players;
        return true;
    }
    throw GamesManagerError("Game not found");
}

void GamesManager::finish_game(int game_id) {
    std::lock_guard<std::mutex> lock(this->mutex);
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

std::list<std::unique_ptr<game_t>>& GamesManager::get_games() { 
   std::lock_guard<std::mutex> lock(this->mutex);
    return this->games;
}

GamesManager::~GamesManager() {
    std::lock_guard<std::mutex> lock(this->mutex);
    for (auto& game: this->games) {
        game->gameThread.stop();
        game->gameThread.join();
    }
    for(auto& game: this->practice_games){
        game->gameThread.stop();
        game->gameThread.join();
    }
}