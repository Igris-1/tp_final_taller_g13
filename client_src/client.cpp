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
        game_view() {
}

void Client::setLocalPlayers(int players) { localPlayers = players; }

Client::~Client() {}

void Client::select_game_mode(int game_mode){
    protocol.send_number_of_players(game_mode);
}

void Client::receive_map() {
    map_structure_t map = protocol.receive_map(); //esto hay que hacer que lo haga el receiver despues
    game_view.add_map(map);
}



void Client::run() {

    try {
        Receiver receiver(protocol, receiver_queue);
        Sender sender(protocol, localPlayers);
        while (sender.is_alive() && receiver.is_alive()) {
            Message m(0);

            if (receiver_queue.try_pop(m)) {
                if (m.get_code() == 0x01) {
                    game_snapshot_t gs = m.get_game_snapshot();
                    game_view.load_game(gs);
                } else if (m.get_code() == 0x02) {
                    score_DTO score = m.get_score();
                    game_view.load_score(score);
                } else if (m.get_code() == 0x03) {
                    score_DTO score = m.get_score();
                    game_view.load_endgame_score(score);
                    break;
                }
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