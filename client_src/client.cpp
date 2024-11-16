#include "client.h"

#include <iostream>
#include <vector>

#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"
#include "../common_src/queue.h"

#define EXIT_CODE "q"
#define LOCAL_PLAYERS 2
#define SLEEP_TIME_CLIENT 2000

Client::Client(const char* host, const char* port):
        localPlayers(LOCAL_PLAYERS),
        protocol(Socket(host, port)),
        receiver_queue(),
        game_view(protocol.receive_map()) {
    //run();
}

void Client::setLocalPlayers(int players) { localPlayers = players; }

Client::~Client() {}

void Client::run() {
    try {
        
        Receiver receiver(protocol, receiver_queue);
        Sender sender(protocol, localPlayers);

        while (sender.is_alive() && receiver.is_alive()) {
            game_snapshot_t gs;

            if (receiver_queue.try_pop(gs)) {
                game_view.load_game(gs);
            }
            usleep(SLEEP_TIME_CLIENT);
        }
        protocol.shutDown();

        receiver.stop();
        receiver.join();

        sender.stop();
        sender.join();

    } catch (const Exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
}
