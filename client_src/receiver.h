#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>

#include <unistd.h>

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "message.h"

#include "protocol_client.h"

#define SLEEP_TIME 2000

class Receiver: public Thread {
private:
    ProtocolClient& protocol;
    Queue<Message>& queue;

    void run() override {
        while (!protocol.socket_closed() && _keep_running) {
            try {
                
                uint8_t code = protocol.read_number();
                if(code == 0x00){
                    map_structure_t map = protocol.receive_map();
                    Message message(code);
                    message.set_map(map);
                    queue.push(message);
                }
                else if (code == 0x01) {
                    game_snapshot_t gs = protocol.read_snapshot();
                    Message message(code);
                    message.set_gs(gs);
                    queue.push(message);
                }
                else if(code == 0x02){
                    score_DTO score = protocol.read_score();
                    Message message(code);
                    message.set_score(score);
                    std::cout << "Score received: " << std::endl;
                    std::cout << "1st place: " << static_cast<int>(score.first_place_score) << std::endl;
                    std::cout << "2nd place: " << static_cast<int>(score.second_place_score) << std::endl;
                    std::cout << "3rd place: " << static_cast<int>(score.third_place_score) << std::endl;
                    std::cout << "4th place: " << static_cast<int>(score.fourth_place_score) << std::endl;
                    queue.push(message);
                    
                }
                else if(code == 0x03){
                    score_DTO score = protocol.read_score();
                    Message message(code);
                    message.set_score(score);
                    std::cout << "Endgame score received: " << std::endl;
                    std::cout << "1st place: " << static_cast<int>(score.first_place_score) << std::endl;
                    std::cout << "2nd place: " << static_cast<int>(score.second_place_score) << std::endl;
                    std::cout << "3rd place: " << static_cast<int>(score.third_place_score) << std::endl;
                    std::cout << "4th place: " << static_cast<int>(score.fourth_place_score) << std::endl;
                    queue.push(message);
                }
                else if(code == 0x04){
                    Message message(code);
                    queue.push(message);
                }
                else if(code == 0x05){
                    Message message(code);
                    queue.push(message);
                }
    
                usleep(SLEEP_TIME);
            } catch (const std::exception& e) {
                std::cerr << "Exception while in client receiver thread: " << e.what() << std::endl;
            }
        }
    }

public:
    Receiver(ProtocolClient& protocol, Queue<Message>& queue):
            protocol(protocol), queue(queue) {
        start();
    }

    ~Receiver() override { _is_alive = false; }
};

#endif  // RECEIVER_H
