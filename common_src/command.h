#ifndef COMMAND_H_
#define COMMAND_H_
#include <string>

#include "protocol.h"

class Command {
public:
    virtual ~Command() {}

    virtual Command* clone() const = 0;

    virtual void execute(Protocol& protocol) const = 0;
};

#endif