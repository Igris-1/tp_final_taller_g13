#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include <map>
#include <string>
#include <vector>

#include "../common_src/command.h"
#include "../common_src/command_info.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "client_handler.h"
#include "thread_safe_list.h"

class GameThread: public Thread {
private:
    Game game;
    ThreadSafeList<ClientHandler>* clientHandlerQueues;
    Queue<CommandInfo*>& receiverQueue;

    void sendCommands(Command* command);
    void pickUpBox(const std::string& name, int box_id);
    void execute_commands();
    void run() override;

public:
    explicit GameThread(Queue<CommandInfo*>& receiverQueue,
                        ThreadSafeList<ClientHandler>* clientHandlerQueues);
};

#endif