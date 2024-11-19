#ifndef SENDER_THREAD_H_
#define SENDER_THREAD_H_

#include <iostream>
#include <string>
#include <variant>

#include "../common_src/game_snapshot_t.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "liberror.h"


class SenderThread: public Thread {
private:
    Queue<instruction_for_client_t>& queue;
    ProtocolServer& protocol;

    void run() override {

        while (!protocol.socket_closed() && _keep_running) {
            try {

                
                instruction_for_client_t instruction = queue.pop();
                if(instruction.id == 0){
                    map_structure_t map = instruction.map;
                    protocol.sendGameStartInfo(map);
                }
                else
                if(instruction.id == 1){
                    game_snapshot_t gs = instruction.gs;
                    protocol.sendGameInfo(gs);
                }
                else if(instruction.id == 2){
                    score_DTO score = instruction.score;
                    protocol.sendScore(score);
                }
                else if(instruction.id == 3){
                    std::cout << "Sending endgame score in sender thread" << std::endl;
                    score_DTO score = instruction.score;
                    protocol.sendFinalScore(score);
                }
                else{
                    std::cerr << "Unknown instruction id: " << instruction.id << std::endl;
                }

            } catch (const ClosedQueue& e) {
                stop();
            } catch (const std::exception& e) {
                std::cerr << "Exception while in sender thread: " << e.what() << std::endl;
            } catch (...) {
                std::cerr << "Unknown exception caught in sender thread." << std::endl;
            }
        }
    }

public:
    SenderThread(Queue<instruction_for_client_t>& queue, ProtocolServer& protocol):
            queue(queue), protocol(protocol) {
        start();
    }

    ~SenderThread() override { _is_alive = false; }
};

#endif