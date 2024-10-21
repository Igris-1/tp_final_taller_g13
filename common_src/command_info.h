#ifndef COMMAND_INFO_H_
#define COMMAND_INFO_H_
#include <string>

class CommandInfo {

public:
    virtual ~CommandInfo() {}

    virtual std::string get_name() const = 0;

    virtual int get_box_id() const = 0;

    virtual bool is_empty() const = 0;
};

#endif