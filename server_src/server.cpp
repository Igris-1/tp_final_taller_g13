#include "server.h"

#include "actions/action.h"
#include "games_manager.h"

#include "acceptor.h"

#define RDWR 2
#define QUEUE_MAX_SIZE 200
#define STOP_CODE "q"
#define START_CODE "f"

typedef struct{
    Queue<std::shared_ptr<Action>>& gameQueue;
    ListOfClientsMonitor& clients;
    GameThread& gameThread;
}game_thread_t;

Server::Server(const char* port): port(port) { start(); }

Server::~Server() {}

void create_game_thread(ListOfClientsMonitor clients){

   // GameThread gameThread(gameQueue, clients);

}

void Server::start() {
    try {

        // Queue<std::shared_ptr<Action>> gameQueue = Queue<std::shared_ptr<Action>>(QUEUE_MAX_SIZE);
        // ListOfClientsMonitor clients;
        // std::map<int, game_thread_t> map_of_games;
        // {0}, {1}, {2} ...
        GamesManager gamesManager;
        Acceptor acceptor(port, gamesManager);
        // Aceptor acceptor(port, gameQueue, list_clients_per_game);
        std::string input;
        while (input != START_CODE) {
            std::getline(std::cin, input);
        }

        // GameThread gameThread(gameQueue, clients);
        while (input != STOP_CODE) {
            std::getline(std::cin, input);
        }
        acceptor.close();
        acceptor.stop();
        acceptor.join();
        // gameThread.stop();
        // gameThread.join();

    } catch (const std::bad_alloc& e) {
        std::cerr << "No se pudo allocar memoria en el server: " << e.what() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Hubo una excepción en el server: " << e.what() << std::endl;
    }
}