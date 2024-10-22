#ifndef COMMAND_INFO_H_
#define COMMAND_INFO_H_
#include <string>
#include "protocol_client.h"

class CommandInfo {

public:
    virtual ~CommandInfo() {}

    virtual action_t get_action() const = 0;
};

#endif