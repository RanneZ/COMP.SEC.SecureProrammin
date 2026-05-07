#ifndef COMMANDS_H
#define COMMANDS_H

#include <regex>
#include <functional>
#include <vector>
#include <string>
#include "datastructures.h"
#include "email.h"

struct Cmd {
    std::string name;
    std::regex pattern;
    std::function<void(const std::smatch&)> handler;
};

std::vector<Cmd> create_cmds(datastructures& data);

#endif // COMMANDS_H
