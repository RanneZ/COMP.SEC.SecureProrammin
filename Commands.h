#ifndef COMMANDS_H
#define COMMANDS_H

#include "Actions.h"

#include <regex>
#include <functional>
#include <vector>
#include <string>

struct Cmd {
    std::string name;
    std::regex pattern;
    std::function<void(const std::smatch&)> handler;
};

std::vector<Cmd> createCmds(Actions& act);

#endif // COMMANDS_H
