// This is gennerated by AI.
// ChatGPT (GPT-5.5.)

#include "SaveAndLoad.h"
#include "JsonConverter.h"
#include "Actions.h"

#include <fstream>

bool saveUsers(const std::string &fileName, const std::vector<User> &users){
    nlohmann::json j = users;

    std::ofstream outFile(fileName);

    if (!outFile)
        return false;

    outFile << j.dump(4);

    return true;
}

std::vector<User> loadUsers(const std::string &fileName){
    std::ifstream file(fileName);

    if (!file || file.peek() == EOF)
        return {};

    nlohmann::json j;
    file >> j;

    return j.get<std::vector<User>>();
}
