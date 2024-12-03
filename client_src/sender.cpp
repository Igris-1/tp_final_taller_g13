#include "sender.h"
#include "protocol_client.h"

Sender::Sender(ProtocolClient& protocol, int localPlayers, Queue<action_t>& queue)
    : protocol(protocol), queue(queue), localPlayers(localPlayers) {
        start();
    }

void Sender::run() {
    try {

        while (!protocol.socket_closed() && _keep_running) {
            action_t action = queue.pop();
            protocol.send_action(action);
        }
    } catch (const ClosedQueue& e) {
        stop();
    } catch (const std::exception& e) {
        std::cerr << "Exception while in client sender thread: " << e.what() << std::endl;
    }
}

void Sender::send_game_to_join(int game_id) {
    // int game_id = std::stoi(input);
    protocol.send_number(game_id);
}

void Sender::send_max_players(int max_players_for_game){
    protocol.send_number(max_players_for_game);
}

void Sender::send_map_name(std::string& map_name){
    protocol.send_string(map_name);
}

void Sender::send_players() { protocol.send_number(localPlayers); }

Sender::~Sender() {
    _is_alive = false;
}